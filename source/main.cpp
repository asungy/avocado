#include "repl.hpp"

int main( int argc, char * argv[] )
{
    auto repl = new repl::Repl();
    repl->Run();
}
