#include <iostream>
#include <algorithm>

int main()
{
    int first;
    int second;
    std::string firstString;
    std::string secondString;
    int currentNumber = 3;
    while(true)
        {
            first = 4 * currentNumber;
            second = 6 * currentNumber;
            firstString = std::to_string(first);
            secondString = std::to_string(second);
            std::sort(firstString.begin(), firstString.end());
            std::sort(secondString.begin(), secondString.end());
            if(firstString == secondString)
                {
                    break;
                }
            ++currentNumber;
        }
    std::cout << currentNumber << std::endl;
    return 0;
}
