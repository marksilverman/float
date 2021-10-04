#include <string>
#include <bitset>
#include <iostream>
#include <math.h>

using namespace std;

template<typename T>
void show(T arg)
{
    cout << arg << "\n";
}

template<typename T, typename... ARGS>
void show(const T arg, const ARGS... args)
{
    cout << arg;
    show (args...);
}

int main(int argc, char **argv)
{
    float f1 = argc > 1 ? stof(argv[1]) : 3.1415927;
    show("input: ", f1);

    auto asuint = (uint8_t*) &f1;
    string binary =
        bitset<8>{asuint[3]}.to_string() +
        bitset<8>{asuint[2]}.to_string() + 
        bitset<8>{asuint[1]}.to_string() +
        bitset<8>{asuint[0]}.to_string();
    show("in binary: 0b", binary);

    if (asuint[0] == 0 && asuint[1] == 0 && asuint[2] == 0)
    {
        if (asuint[3] == 0)
        {
            show("special case: all bits are zero, so value is zero");
            return 0;
        }
        if (asuint[3] == 128)
        {
            show("special case: negative zero");
            return 0;
        }
    }

    auto sign = stoi(binary.substr(0, 1), nullptr, 2);
    auto exponent_str = binary.substr(1, 8);
    unsigned int exponent = abs(stoi(exponent_str, nullptr, 2) - 127);
    auto mantissa = binary.substr(9, 23);

    show("\ns xxxxxxxx mmmmmmmmmmmmmmmmmmmmmmm");
    show(sign, " ", exponent_str, " ", mantissa, "\n");
    show("sign (1-bit): ", sign);
    show("exponent (8-bits): 0b", exponent_str, " - 0b1111111 = ", exponent);
    show("mantissa (23-bits): 0b", mantissa);

    string lhs_str = "1" + mantissa.substr(0, exponent);
    auto lhs = stoi(lhs_str, nullptr, 2);

    float total = 0.0;
    string rhs_str;
    if (exponent < mantissa.length())
    {
        rhs_str = mantissa.substr(exponent);
        for (int i = 1; i <= (int) rhs_str.length(); i++)
            total += stoi(rhs_str.substr(i-1, 1), nullptr, 2) * pow(2, -i);
    }

    float result = pow(-1, sign) * (lhs + total);

    show("\nlhs-of-radix: 0b", lhs_str, " --> ", lhs);
    show("rhs-of-radix: 0b", rhs_str, " --> ", total);

    show("result: ", result);
    if (f1 == result)
        show("the result matches the input");
    else
        show("the result does NOT match the input!");
    return 0;
}
