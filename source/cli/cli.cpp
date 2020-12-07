#include "CLI11/CLI11.hpp"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"

#include "../influx/influx.hpp"
#include "../python/python.hpp"
#include "cli.hpp"

#include <cassert>
#include <cstdlib>
#include <filesystem>

using nlohmann::json;

namespace command {
    int Run1(int argc, char * argv[])
    {
        CLI::App root_cmd{ "Avocado CLI" };

        // Adding python subcommands
        CLI::App * python_cmd = 
            root_cmd.add_subcommand("python", "test command for python interface");

        CLI::App * get_fake_data_cmd = python_cmd->add_subcommand("fake-data", "get fake data");

        // Add database commands
        std::string tokenfile;
        CLI::App * database_cmd = root_cmd.add_subcommand("database", "interact with database");
        database_cmd->add_option("--tokenfile", tokenfile, "File containing Influx user token");

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

            influx::Write(tokenfile, "test_bucket", "test", "market_data", data);
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

    int Run(int argc, char * argv[])
    {
        json j = {
          {"pi", 3.141},
          {"happy", true},
          {"name", "Niels"},
          {"nothing", nullptr},
          {"answer", {
            {"everything", 42}
          }},
          {"list", {1, 0, 2}},
          {"object", {
            {"currency", "USD"},
            {"value", 42.99}
          }}
        };

        std::cout << j.dump(4) << std::endl;

        //---

        std::string config_dir = std::string(getenv("HOME")) + 
                                 std::string("/.config/avocado/");
        if (!std::filesystem::exists(config_dir))
        {
            std::string message = std::string("Config directory does not exist at ") +
                                  config_dir + std::string(". Creating directory.");
            spdlog::info(message);

            std::filesystem::create_directories(config_dir);
        }

        // TODO: Parse config file

        return 0;
    }
}
