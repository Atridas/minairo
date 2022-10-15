import Minairo;

#include <csignal>

#include <iostream>
#include <string>


int main()
{

    minairo::State state = minairo::create_repl();

    /*std::cout << ">a := 15 + 24 * (10 - 1) / 3 + 7 % 2;\n";
    minairo::interpret(state, "a : = 15 + 24 * (10 - 1) / 3 + 7 % 2;");

    {
        std::string code;
        code += "{\n";
        code += "  b := 12 + a; \n";
        code += "  a := 15; \n";
        code += "  {\n";
        code += "    c := 12 + a; \n";
        code += "    b := 5; \n";
        code += "  }\n";
        code += "  c := b; \n";
        code += "}\n";
        std::cout << ">" << code;
        minairo::interpret(state, code);
    }

    std::cout << ">a + 12;\n";
    minairo::interpret(state, "a + 12;");*/

    std::string line;
    for (;;)
    {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (std::cin.eof()) {
            break;
        }
        else if (!line.empty())
        {
            try
            {
                minairo::interpret(state, line.c_str());

            }
            catch (...)
            {
                // TODO
                std::cerr << "error!" << std::endl;
            }
        }
    }

    minairo::destroy_repl(state);

    return 0;
}
