#include "CLI11/CLI11.hpp"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"

#include "../influx/influx.hpp"
#include "../python/python.hpp"
#include "cli.hpp"

#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using nlohmann::json;

namespace command {
    // Forward declarations for private functions
    json GetConfig();
    std::string GMTNow();

    inline std::string GetConfigFolder() { 
        return std::string(getenv("HOME")) + std::string("/.avocado/"); 
    };

    int Run(int argc, char * argv[])
    {
        json config = GetConfig();

        CLI::App root_cmd{ "Avocado CLI" };

        // Add database commands
        CLI::App * database_cmd = 
            root_cmd.add_subcommand("database", "interact with database");

        CLI::App * database_update_cmd = 
            database_cmd->add_subcommand("update", "Adds a point to database");

        CLI::App * database_backup_cmd =
            database_cmd->add_subcommand("backup", "Create backup of database");

        // Parse command
        CLI11_PARSE(root_cmd, argc, argv);

        // Check `avocado database` subcommand call
        if (database_cmd->parsed())
        {
            if (database_update_cmd->parsed())
            {
                py_interface::Initialize();
                stock::DataPoint data = py_interface::GetFakeData("AAPL");
                py_interface::Finalize();

                influx::Write(config["influx_token"], "test_bucket", "test", 
                              "market_data", data);
            }
            else if (database_backup_cmd->parsed())
            {
                std::string dirname = std::string("influxdb-") + GMTNow();
                std::string dirpath = GetConfigFolder() + 
                                      std::string("backups/") + dirname;

                influx::CreateBackup(config["influx_token"], dirpath);
            }
            else 
            {
                std::cout << database_cmd->help() << std::endl;
            }

            return 0;
        }

        std::cout << root_cmd.help() << std::endl;
        return 0;
    }

    json GetConfig()
    {
        // Create configuration directory, if it does not exist.
        std::string config_dir = GetConfigFolder();
                                 
        if (!std::filesystem::exists(config_dir))
        {
            std::string message = std::string("Config directory does not exist at ") +
                                  config_dir + std::string(". Creating directory.");
            spdlog::info(message);
            std::filesystem::create_directories(config_dir);
        }

        // Create configuration file, if it does not exist.
        std::string config_file = config_dir + "config.json";
        if (!std::filesystem::exists(config_file))
        {
            std::string message{ "Config file does not exist. Creating config.json" };
            spdlog::info(message);

            // Prompting user to init config file
            std::string influx_token{};
            std::cout << "Enter Influx token: ";
            std::cin >> influx_token;

            json config_json{};
            config_json["influx_token"] = influx_token;

            std::ofstream file(config_file);
            file << config_json.dump(4);
            file.close();
        }

        // Parse config file
        std::ifstream file(config_file);
        json config_json;
        file >> config_json;
        file.close();

        return config_json;
    }

    std::string GMTNow()
    {
        auto now = std::chrono::system_clock::now();
        time_t t_c = std::chrono::system_clock::to_time_t(now);

        char buf[128];
        if (std::strftime(buf, sizeof(buf), "%FT%TZ", std::gmtime(&t_c))) {
            return std::string(buf);
        } 
        else {
            throw std::runtime_error("Error occurred when trying to convert current "
                                     "system clock time to string");
        }
    }
}
