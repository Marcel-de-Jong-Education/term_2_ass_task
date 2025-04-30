#include <iostream>
int num = -42;
int num0 = 4004;
int main()
{
    std::cout << ((unsigned int)num >> 31) << '\n';
    std::cout << ((unsigned int)num0 >> 31) << '\n';
    return 0;
}
