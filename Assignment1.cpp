#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include<algorithm>

std::vector<int> primes;
std::mutex primes_mutex;
unsigned long sum_of_primes = 0;
int number_of_primes = 0;

bool is_prime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

void find_primes(int start, int end) {
    for (int i = start; i < end; i++) {
        if (is_prime(i)) {
            primes_mutex.lock();
            primes.push_back(i);
            sum_of_primes += i;
            number_of_primes++;
            primes_mutex.unlock();
        }
    }
}

int main() {
    std::vector<std::thread> threads;
    int upTill = 100;
    int num_threads = 8;
    int range = upTill / num_threads;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_threads; i++) {
        int start = i * range;
        int end = (i + 1) * range;
        if (i == num_threads - 1) {
            end = upTill;
        }

        threads.push_back(std::thread(find_primes, start, end));
    }

    for (auto& thread : threads) {
        thread.join();
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

    std::ofstream outputFile;
    outputFile.open("primes.txt");

    outputFile << duration.count() << "     ";

    outputFile << number_of_primes << "     ";
    outputFile << sum_of_primes << "    "<< std::endl;
    std::sort(primes.begin(), primes.end());
    for (int i = 0; i < primes.size(); i++ ) {
        outputFile << primes[i] << " ";
    }
    outputFile.close();
    
    return 0;
}
