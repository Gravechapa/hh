#include <iostream>
#include <algorithm>
#include <gmpxx.h> 

int main()
{
    int result = 0;
    std::string normal;
    std::string reversed;
    mpz_class temp;
    for (int i = 1; i < 13147; ++i)
        {
            mpz_class num = i;
            bool pol = false;
            for (int j = 0; j < 50; ++j)
                {
                    std::string tempString = num.get_str();
                    std::reverse(tempString.begin(), tempString.end());
                    temp.set_str(tempString, 10);
                    num += temp;
                    normal = reversed = num.get_str();
                    std::reverse(reversed.begin(), reversed.end());
                    if (normal == reversed)
                        {
                            pol = true;
                            break;
                        }
                }
            if (!pol)
                {
                    ++result;
                }
        }
    std::cout << result << std::endl;
    return 0;
}
