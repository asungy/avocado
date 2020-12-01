#include "CLI11/CLI11.hpp"

#include "../influx/influx.hpp"
#include "../python/python.hpp"
#include "cli.hpp"

#include <cassert>

namespace command {
    int Run(int argc, char * argv[])
    {
        CLI::App root_cmd{ "Avocado CLI" };

        // Adding python subcommands
        CLI::App * python_cmd = 
            root_cmd.add_subcommand("python", "test command for python interface");

        CLI::App * multiply_cmd = python_cmd->add_subcommand("multiply", "multiply two numbers");
        CLI::App * get_fake_data_cmd = python_cmd->add_subcommand("fake-data", "get fake data");

        std::vector<int> factors;
        multiply_cmd->add_option("factors", factors, "two numbers to multiply");

        // Add database commands
        std::string tokenfile;
        CLI::App * database_cmd = root_cmd.add_subcommand("database", "interact with database");
        database_cmd->add_option("--tokenfile", tokenfile, "File containing Influx user token");

        CLI::App * add_point_cmd = 
            database_cmd->add_subcommand("add_point", "Adds a point to database");

        // Parse command
        CLI11_PARSE(root_cmd, argc, argv);

        // Check if command was received
        if (add_point_cmd->parsed())
        {
            py_interface::Initialize();
            stock::DataPoint data = py_interface::GetFakeData("AAPL");
            py_interface::Finalize();
            influx::Write(tokenfile, data);
        }
        else if (multiply_cmd->parsed())
        {
            if (factors.size() == 2)
            {
                py_interface::Initialize();
                py_interface::Call_Multiply(factors[0], factors[1]);
                py_interface::Finalize();
            }
            else 
            {
                std::cout << "Please provided two numbers to multiply" << std::endl;
            }
        } 
        else if (get_fake_data_cmd->parsed())
        {
            py_interface::Initialize();
            py_interface::GetFakeList();
            py_interface::Finalize();
        }

        return 0;
    }
}
