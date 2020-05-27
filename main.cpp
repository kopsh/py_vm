# include <stdio.h>
# include "code/binaryFileParser.hpp"
# include "runtime/interpreter.hpp"
# include "runtime/universe.hpp"

int main(int argc, char** argvs)
{
    if (argc <= 1) {
        printf("vm need a parameter!\n");
        return 0;
    }

    Universe::genesis();
    BufferedInputStream stream(argvs[1]);
    BinaryFileParser parser(&stream);
    CodeObject* main_code = parser.parse();

    Interpreter* i = Interpreter::get_instance();
    i->run(main_code);
    Universe::destory();
    return 0;
}