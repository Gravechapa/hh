#include <iostream>
#include <queue>
#include <map>
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

mpz_class factorial(mpz_class fact, int n)
{
    return fact * n;
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
                std::map<int, int> multipliers;
                int counter = 0;
                for (int i = 2; i <= currentNumber; ++i)
                    {
                        while (currentNumber % i == 0)
                            {
                                ++counter;
                                currentNumber /= i;
                            }
                        multipliers.insert(std::pair<int,int>(i, counter));
                        counter = 0;
                    }
                int multiplier = multipliers.rbegin()->first;
                int count = multipliers.rbegin()->second;
                int result;
                if (count > multiplier)
                    {
                        count = multiplier - 1;
                        result = multiplier * count;
                    }
                else
                    {
                        result = multiplier * count;
                    }

                bool recount = false;
                if (FactTree(result) % left != 0)
                    {   
                        recount = true;
                        writeMutex.lock();
                        std::cout << "Error " << left << std::endl;
                        writeMutex.unlock();
                    }

                if (recount)
                    {
                        counter = 1;
                        mpz_class temp = 1;
                        while(((temp = factorial(temp, counter)) % left) != 0)
                            {
                                ++counter;
                            }
                        result = counter;
                    }
                writeMutex.lock();
                std::cout << left << ": " << result << std::endl;
                file <<  left << ": " << result << std::endl;
                file.flush();
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
    std::cout << "factorial: " << FactTree(20000) << std::endl;
    std::cin >> left >> right >> maxThread;
    std::cout << sum(left, right, maxThread) << std::endl;
    return 0;
} 
