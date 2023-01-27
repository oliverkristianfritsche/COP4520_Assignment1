My approach is to use multiple threads to find prime numbers in a given range. Each thread is responsible for finding primes within a specific sub-range of the given range, and the sub-ranges are determined by dividing the range by the number of threads. A mutex is used to synchronize access to the shared variables that store the sum of primes, the number of primes, and the list of primes.

A simple primality test is used to check if a number is prime. This test checks if the number is less than or equal to 1, if it is less than or equal to 3, if it is divisible by 2 or 3, or if it is divisible by any number in the range of 5 to the square root of the number. If the number passes all these checks, it is considered prime.

As for the correctness of the design, the experimental evaluation I used for this approach was to first test using a lower upperbound such as 10 or 100, this allowed me to easily compare my results to available data to determine the correctness of my implementation.



To run on a linux machine:

g++ -o source Source.cpp -pthread