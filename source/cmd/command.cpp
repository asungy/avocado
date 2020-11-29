#include "CLI11/CLI11.hpp"

#include "command.hpp"
#include "../python/python.hpp"

namespace command {
    void Run(int argc, char * argv[])
    {
        CLI::App root_cmd{ "Avocado CLI" };

        // Adding python subcommands
        CLI::App * python_cmd = 
            root_cmd.add_subcommand("python", "test command for python interface");

        CLI::App * multiply_cmd = 
            python_cmd->add_subcommand("multiply", "multiply two numbers");

        CLI::App * get_fake_data_cmd = 
            python_cmd->add_subcommand("fake-data", "get fake data");

        std::vector<int> factors = {};
        multiply_cmd->add_option("factors", factors, "two numbers to multiply");

        // Parse command
        try 
        {
            root_cmd.parse(argc, argv);
        } 
        catch (const CLI::ParseError &e)
        {
            root_cmd.exit(e);
        }

        // Check if command was received
        if (multiply_cmd->parsed())
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
    }
}
