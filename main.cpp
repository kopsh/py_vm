# include <stdio.h>
# include <code/binaryFileParser.hpp>

int main(int argc, char** argvs)
{
    if (argc <= 1) {
        printf("vm need a parameter!\n");
        return 0;
    }

    BufferedInputStream stream(argvs[1]);
    BinaryFileParser parser(&stream);
    CodeObject* code_object = parser.parse();
    return 0;
}