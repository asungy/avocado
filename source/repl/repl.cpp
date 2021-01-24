#include "repl.hpp"

#include "ncursesw/ncurses.h"
#include <string>
#include "locale.h"

namespace repl {
    void Repl::Run()
    {
        setlocale(LC_ALL, "");
        std::string str = "😎😎😎";
        initscr();
        printw(str.c_str());
        getch();
        endwin();
    }
}
