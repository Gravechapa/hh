#include <iostream>
#include <sstream>

int main()
{
    int first;
    int second;
    int third;
    int result = 0;
    for (char w = '1'; w <= '9'; ++w)
        {
            for (char v = '0'; v <= '9'; ++v)
                {
                    for (char z = '1'; z <= '9'; ++z)
                        {
                            for (char r = '1'; r <= '9'; ++r)
                                {
                                    for (char u = '0'; u <= '9'; ++u)
                                        {
                                            std::stringstream firstString;
                                            std::stringstream secondStreing;
                                            std::stringstream thirdString;
                                            firstString << w << v << z;
                                            firstString >> first;
                                            secondStreing << z << v << v;
                                            secondStreing >> second;
                                            thirdString << r << w << r << u;
                                            thirdString >> third;
                                            if (first + second == third)
                                                {
                                                    std::cout << firstString.str() << " " << 
                                                    secondStreing.str() << " " << thirdString.str() << std::endl;
                                                    ++result;
                                                }
                                        }
                                }
                        }
                }
        }
    std::cout << result << std::endl;
    return 0;
}
