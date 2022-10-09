import Minairo;

int main()
{
    minairo::interpret("a := 15 + 24 * (10 - 1) / 3 + 7 % 2; a + 12;");
    //minairo::interpret("15 + 24 * (10 - 1) / 3 + 7 % 2;");
}
