#pragma once

#include <tuple>

namespace repl {
    class Repl
    {
    public:
        Repl() = default;
        ~Repl() = default;

        void Run();
    private:
        int max_height; /* number of rows */
        int max_width;  /* number of columns */
        std::tuple<int, int> cursor_position;
    };
}
