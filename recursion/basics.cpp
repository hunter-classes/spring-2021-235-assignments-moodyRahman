
#include <iostream>

int recurseFib(int n)
{
    if (n < 2)
    {
        return 1;
    }
    return n + recurseFib(n - 1);
}

int iterFib(int n)
{
    int out = 0;
    while (n)
    {
        out += n;
        n--;
    }
    return out;
}


int main(int argc, char const *argv[])
{

    std::cout << iterFib(10) << std::endl;
    // recurseFib(10);

    return 0;
}
