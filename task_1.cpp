#include <iostream>
#include <queue>
#include <unordered_map>
#include <cstdint>
#include <gmpxx.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <fstream>

mpz_class ProdTree(int l, int r)
{
	if (l > r)
		return 1;
	if (l == r)
		return l;
	if (r - l == 1)
		return (mpz_class)r * l;
	int m = (l + r) / 2;
	return ProdTree(l, m) * ProdTree(m + 1, r);
}

mpz_class FactTree(int n)
{
	if (n < 0)
		return 0;
	if (n == 0)
		return 1;
	if (n == 1 || n == 2)
		return n;
	return ProdTree(2, n);
}

int increasePower(int number, int base)
{
    int power = 1;
    while ((number / base) % base == 0)
        {
            number /= base;
            ++power;
        }
    return power;
}

int miniFact(int number, int power)
{
    int currentPower = 1;
    int result = number;
    while (currentPower < power)
        {
            result += number;
            currentPower += increasePower(result, number);
        }
    return result;
}

uint64_t sum(int left, int right, int maxThread)
{
    std::ofstream file;
    file.open("factorial_out_1.txt");
    std::mutex writeMutex;
    std::atomic_int threadCount (0);
    std::queue<int> que;
    for (; left <= right; ++left)
        {
            ++threadCount;
            std::thread([&writeMutex, &threadCount, &que, &file](int left)
            {
                int currentNumber = left;
                std::unordered_map<int, int> multipliers;
                int counter = 0;
                for (int i = 2; i <= currentNumber; ++i)
                    {
                        while (currentNumber % i == 0)
                            {
                                ++counter;
                                currentNumber /= i;
                            }
                        if (counter != 0)
                            {
                                multipliers.insert(std::pair<int,int>(i, counter));
                                counter = 0;
                            }
                    }

                int result = 0;
                for (auto it = multipliers.begin(); it != multipliers.end(); ++it)
                    {
                        int temp = miniFact(it->first, it->second);
                        if (temp > result)
                            {
                                result = temp;
                            }
                    }

                writeMutex.lock();
                file <<  left << ": " << result << std::endl;
                que.push(result);
                writeMutex.unlock();
                --threadCount;
            }, left).detach();

            while (threadCount >= maxThread)
                {
                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(16));
                }
        }

    while (threadCount)
        {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(16));
        }
    uint64_t result = 0;
    while (!que.empty())
        {
            result += que.front();
            que.pop();
        }
    file.close();
    return result;
}

int main()
{
    int left;
    int right;
    int maxThread;
    std::cout << "factorial: " << FactTree(200000) << std::endl;
    std::cin >> left >> right >> maxThread;
    std::cout << sum(left, right, maxThread) << std::endl;
    return 0;
} 
