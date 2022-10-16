import Minairo;

#include <csignal>

#include <iostream>
#include <string>


int main()
{
    minairo::VM vm = minairo::create_VM();

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
                minairo::interpret(vm, line.c_str());
            }
            catch (...)
            {
                // TODO
                std::cerr << "error!" << std::endl;
            }
        }
    }

    minairo::destroy_VM(vm);

    return 0;
}
