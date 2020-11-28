#include "CLI11/CLI11.hpp"

#include "command.hpp"
#include "../python/python.hpp"

namespace command {
    int Run(int argc, char * argv[])
    {
        CLI::App root_cmd{ "Avocado CLI" };
        CLI::App * multiply_cmd = root_cmd.add_subcommand("multiply", "Muliply two numbers");

        std::vector<int> factors;
        multiply_cmd->add_option("factors", factors, "two numbers to multiply");

        try {
            root_cmd.parse(argc, argv);
        } catch (const CLI::ParseError &e) {
            return root_cmd.exit(e);
        }

        // std::cout << "First factor: " << factors[0] << std::endl
        //           << "Second factor: " << factors[1] << std::endl;

        return 0;
    }


    auto TestFunction() -> int
    {
        return 42;
    }
}
