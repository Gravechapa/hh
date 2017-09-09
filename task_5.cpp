#include <iostream>
#include <unordered_map>

int main()
{
    int result = 0;
    for (int i = 10; i <= 5100000; ++i)
        {
            std::unordered_map<int, int> data;
            std::string number = std::to_string(i);
            data.insert(std::pair<int, int>(0, number[0] - '0'));
            for (int j = 1; j < number.size(); ++j)
                {
                    int temp = data[j - 1] + (number[j] - '0');
                    if (temp == 10)
                        {
                            std::cout << i << std::endl;
                            ++result;
                            goto stop;
                        }
                    data.insert(std::pair<int, int>(j, temp));
                }
            
            for (int j = 0; j < number.size() - 2; ++j)
                {
                    for(int k = j + 2; k < number.size(); ++k)
                        {
                            int temp = data[k] - data[j];
                            if (temp == 10)
                                {
                                    std::cout << i << std::endl;
                                    ++result;
                                    goto stop;
                                }
                        }
                }
            stop:;
        }
    std::cout << result << std::endl;
    return 0;
}
