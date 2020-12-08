#include "CLI11/CLI11.hpp"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"

#include "../influx/influx.hpp"
#include "../python/python.hpp"
#include "cli.hpp"

#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>

using nlohmann::json;

namespace command {
    // Forward declarations
    json GetConfig();

    int Run(int argc, char * argv[])
    {
        json config = GetConfig();

        CLI::App root_cmd{ "Avocado CLI" };

        // Adding python subcommands
        CLI::App * python_cmd = 
            root_cmd.add_subcommand("python", "test command for python interface");

        CLI::App * get_fake_data_cmd = python_cmd->add_subcommand("fake-data", "get fake data");

        // Add database commands
        CLI::App * database_cmd = root_cmd.add_subcommand("database", "interact with database");

        CLI::App * update_cmd = 
            database_cmd->add_subcommand("update", "Adds a point to database");

        // Parse command
        CLI11_PARSE(root_cmd, argc, argv);

        // Check if command was received
        if (update_cmd->parsed())
        {
            py_interface::Initialize();
            stock::DataPoint data = py_interface::GetFakeData("AAPL");
            py_interface::Finalize();

            influx::Write(config["influx_token"], "test_bucket", "test", "market_data", data);
        }
        else if (get_fake_data_cmd->parsed())
        {
            py_interface::Initialize();
            py_interface::GetFakeList();
            py_interface::Finalize();
        }
        else
        {
            std::cout << root_cmd.help() << std::endl;
        }

        return 0;
    }

    json GetConfig()
    {
        // Create configuration directory, if it does not exist.
        std::string config_dir = std::string(getenv("HOME")) + 
                                 std::string("/.avocado/");
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
}
