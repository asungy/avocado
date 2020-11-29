#pragma once 

namespace command {
    void Run(int argc, char * argv[]);

    // Test function used as a placeholder in the test suite for now
    inline auto TestFunction() -> int
    {
        return 42;
    }
}
