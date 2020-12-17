#include "CLI11/CLI11.hpp"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"

#include "../influx/influx.hpp"
#include "../python/python.hpp"
#include "cli.hpp"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <regex>
#include <string>
#include <tuple>

using nlohmann::json;

namespace command {
    ///////////////////////////////////////////////////////////////////////////
    //                          Private Functions
    ///////////////////////////////////////////////////////////////////////////

    // Parse configuration file into json object
    json GetConfig();
    // Return a string representation of the current UTC/GMT time
    std::string GMTNow();
    // Get latest database backup directory
    std::string GetLatestBackup();
    // Return Linux epoch value from database backup directory timestamp
    time_t GetBackupTimeStamp(std::string dir);

    ///////////////////////////////////////////////////////////////////////////
    // End of private functions

    inline std::string GetConfigFolder() { 
        return std::string(getenv("HOME")) + std::string("/.avocado/"); 
    };

    inline std::string GetBackupFolder() {
        return GetConfigFolder() + std::string("backups/");
    }

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

        std::string backup_dir = std::string("influxdb-") + GMTNow();
        database_backup_cmd->add_option("backup_dir", backup_dir, "Name of backup");

        CLI::App * database_restore_cmd =
            database_cmd->add_subcommand("restore", "Restore database from backup");

        std::string restore_dir{};
        database_restore_cmd->add_option("restore_dir", restore_dir, 
                                         "Path to root of backup directory");

        // Parse command
        CLI11_PARSE(root_cmd, argc, argv);

        // Check `avocado database` subcommand call
        if (database_cmd->parsed())
        {
            // Check `avocado database update`
            if (database_update_cmd->parsed())
            {
                py_interface::Initialize();
                stock::DataPoint data = py_interface::GetFakeData("AAPL");
                py_interface::Finalize();

                influx::Write(config["influx_token"], "test_bucket", "test", 
                              "market_data", data);
            }
            // Check `avocado database backup [dir]`
            else if (database_backup_cmd->parsed())
            {
                std::string backup_path = GetBackupFolder() + backup_dir;
                influx::CreateBackup(config["influx_token"], backup_path);
                spdlog::info("Created database backup at {}", backup_path);
            }
            // Check `avocado database restore [path]`
            else if (database_restore_cmd->parsed())
            {
                try {
                    restore_dir = restore_dir.empty() ? GetLatestBackup() : restore_dir;
                }
                catch(const std::runtime_error & err)
                {
                    std::cout << err.what() << std::endl;
                    exit(EXIT_SUCCESS);
                }
                influx::RestoreFromBackup(config["influx_token"], restore_dir);
                spdlog::info("Restoring database from {}", restore_dir);
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
        auto now   = std::chrono::system_clock::now();
        time_t t_c = std::chrono::system_clock::to_time_t(now);

        char buf[128];
        // Format example: 2020-12-25T135941Z
        if (std::strftime(buf, sizeof(buf), "%FT%H%M%SZ", std::gmtime(&t_c))) {
            return std::string(buf);
        } 
        else {
            throw std::runtime_error("Error occurred when trying to convert current "
                                     "system clock time to string");
        }
    }

    std::string GetLatestBackup()
    {
        // Error checking
        std::filesystem::path backup_folder{GetBackupFolder()};
        if (std::filesystem::is_empty(backup_folder))
        {
            throw std::runtime_error(
                std::string("No backups found in ") + GetBackupFolder()
            );
        }
        // Assign latest to first entry
        auto iter = std::filesystem::directory_iterator(backup_folder);
        std::string first = iter->path().c_str();     
        std::tuple<std::string, time_t> latest{
            first,
            GetBackupTimeStamp(first)
        };
        // Find backup with latest timestamp
        for (const auto & entry : std::next(iter))
        {
            std::string dir = entry.path().c_str();
            time_t time = GetBackupTimeStamp(dir);
            time_t curr = std::get<1>(latest);
            if (curr < time)
            {
                latest = std::make_tuple(dir, time);
            }
        }

        return std::get<0>(latest);
    }

    time_t GetBackupTimeStamp(std::string dir)
    {
        // Captures datetime info like in '20201216T060258Z.manifest'
        std::regex expr{".*([0-9]{4})([0-9]{2})([0-9]{2})T([0-9]{2})([0-9]{2})([0-9]{2})Z.+"};
        auto iter = std::filesystem::directory_iterator(dir);
        for (const auto & entry : iter)
        {
            std::cmatch matches{};
            // Converting filename to std::string cleans string for
            // regex_match somehow. Otherwise, it matches with
            // some artifacts.
            std::string dirname{ entry.path().filename().c_str() };
            std::regex_match(dirname.c_str(), matches, expr);
            if (matches.size() == 7) // 6 captures plus whole
            {
                struct tm backup_time = {0};
                backup_time.tm_year = std::stoi(std::string(matches[1]));
                backup_time.tm_mon  = std::stoi(std::string(matches[2]));
                backup_time.tm_mday = std::stoi(std::string(matches[3]));
                backup_time.tm_hour = std::stoi(std::string(matches[4]));
                backup_time.tm_min  = std::stoi(std::string(matches[5]));
                backup_time.tm_sec  = std::stoi(std::string(matches[6]));
                return mktime(&backup_time);
            }
        }

        throw std::runtime_error("Could not extract timestamp from backup directory");
    }
}
