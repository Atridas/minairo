import Minairo;

#include <string>

int main()
{
    std::string code;

    code += "a := 15 + 24 * (10 - 1) / 3 + 7 % 2;\n";
    code += "{\n";
    code += "  b := 12 + a; \n";
    code += "  a := 15; \n";
    code += "  {\n";
    code += "    c := 12 + a; \n";
    code += "    b := 5; \n";
    code += "  }\n";
    code += "  c := b; \n";
    code += "}\n";
    code += "a + 12;\n";


    minairo::interpret(code);
    //minairo::interpret("15 + 24 * (10 - 1) / 3 + 7 % 2;");
}
