// Mouchamel, Mathew
// CS 131 : Discrete Structures
// FALL 2023
// ...
// Semester Github Project
// 12/10/2023

#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

void displayMessage();
vector<unsigned long int> getNumbers();
void printNumbersVector(vector<unsigned long int> numbers);
map<unsigned long int, unsigned long int> primeFactorization(unsigned long int number);
void printPrimeFactorization(unsigned long int number, map<unsigned long int, unsigned long int> primeFactors);
vector<map<unsigned long int, unsigned long int>> factorizeNumbersVector(vector<unsigned long int> numbers);
void calculateGCD(const vector<map<unsigned long int, unsigned long int>>& factorizations);
void calculateLCM(const vector<map<unsigned long int, unsigned long int>>& factorizations);

int main()
{
    displayMessage();

    vector<unsigned long int> numbers = getNumbers();
    printNumbersVector(numbers);
    vector<map<unsigned long int, unsigned long int>> factors = factorizeNumbersVector(numbers);

    calculateGCD(factors);
    calculateLCM(factors);
}

// Displays welcome message
void displayMessage()
{
    cout << "\nWelcome to the prime factorization program\n\n" << endl;
}

// Prompts user to enter a count (n) of numbers, then prompts the user to enter n integers, and returns a vector of the inputted integers
vector<unsigned long int> getNumbers()
{
    int count = 0;
    vector<unsigned long int> numbers;

    while (count < 1)
    {
        cout << "How many numbers would you like to enter? (Enter a number above 0) ";
        cin >> count;
        cout << endl;

        if (count < 1)
        {
            cout << "Enter a number above 0" << endl;
        }
    }
    
    
    for (int num = 0; num < count; num++)
    {
        unsigned long int number;
        cout << "Number " << (num + 1) << ": ";
        cin >> number;

        if (number < 0)
        {
            number *= -1;
        }

        numbers.push_back(number);
    }

    cout << endl << endl;
    
    return numbers;
}

void printNumbersVector(vector<unsigned long int> numbers)
{
    cout << "Numbers  =  [  ";

    int count = 1;
    int total = numbers.size();

    for (unsigned long int number : numbers)
    {
        if (count < total)
        {
            cout << number << ",  ";
        }
        else
        {
            cout << number << "  ]\n\n" << endl;
        }

        count++;
    }
}

// Finds the prime factorization of a number by mapping each prime number to its power (i.e. 2 : 3 --> 2 ^ 3)
map<unsigned long int, unsigned long int> primeFactorization(unsigned long int number)
{
    map<unsigned long int, unsigned long int> factors;

    if (number == 1)
    {
        factors[1] = 1;
        return factors;
    }

    for (unsigned long int num = 2; num <= number / num; num++)
    {
        while (number % num == 0)
        {
            factors[num]++;
            number /= num;
        }
    }

    if (number > 1)
    {
        factors[number]++;
    }
    
    return factors;
}

// Prints a detailed prime factorization of a number using a given map of factors and their corresponding powers
void printPrimeFactorization(unsigned long int number, map<unsigned long int, unsigned long int> primeFactors)
{
    int count = 0;
    int total = primeFactors.size();

    for (const auto& pair : primeFactors)
    {
        count++;
        
        if (count < total)
        {
            cout << '(' << pair.first << " ^ " << pair.second << ")  *  ";
        }
        else
        {
            cout << '(' << pair.first << " ^ " << pair.second << ')' << endl;
        }
    }
}

// Receives a vector of numbers and returns a vector of the prime factorization of each integer in the vector
vector<map<unsigned long int, unsigned long int>> factorizeNumbersVector(vector<unsigned long int> numbers)
{
    vector<map<unsigned long int, unsigned long int>> factorizedNumbers;

    for (unsigned long int number : numbers)
    {
        map<unsigned long int, unsigned long int> primeFactors = primeFactorization(number);
        factorizedNumbers.push_back(primeFactors);

        cout << setw(5) << left << number << " -->   ";
        printPrimeFactorization(number, primeFactors);
    }

    cout << endl;

    return factorizedNumbers;
}

// Function to calculate GCD
void calculateGCD(const vector<map<unsigned long int, unsigned long int>>& factorizations)
{
    // The common factors is initialized as the first number's prime factors - this will only shrink, not expand
    map<unsigned long int, unsigned long int> commonFactors = factorizations[0];

    // Iterate through the factors of the numbers, starting with the second number
    for (const auto& factors : factorizations)
    {
        if (factors != factorizations.front())
        {
            map<unsigned long int, unsigned long int> updatedCommonFactors = commonFactors;

            // Iterate through the common factors, updating the new common factors vector
            for (const auto& currentFactor : commonFactors)
            {
                unsigned long int currentPrimeNumber = currentFactor.first;

                // Erase the factor if it isn't a common factor
                if (factors.count(currentPrimeNumber) == 0)
                {
                    updatedCommonFactors.erase(currentPrimeNumber);
                }
                // If the factor is a common factor, take the minimum power
                else
                {
                    updatedCommonFactors[currentPrimeNumber] = min(commonFactors[currentPrimeNumber], factors.at(currentPrimeNumber));
                }
            }

            // Update the common factors
            commonFactors = updatedCommonFactors;
        }
    }

    if (commonFactors.empty())
    {
        commonFactors[1] = 1;
    }

    unsigned long long int gcd = 1;

    for (const auto& factor : commonFactors)
    {
        gcd *= ceil(pow(factor.first, factor.second));
    }

    // Print GCD and GCD prime factorization
    cout << "\n\nGCD: " << gcd << "\nGCD: ";
    printPrimeFactorization(gcd, commonFactors);
    cout << endl << endl;
}

// Function to calculate LCM
void calculateLCM(const vector<map<unsigned long int, unsigned long int>>& factorizations)
{
    // This vector doesn't need to be initialized since it will only expand, not shrink, unlike the GCD commonFactors vector
    map<unsigned long int, unsigned long int> combinedFactors;

    // Iterate through each number's prime factorizations
    for (const auto& factors : factorizations)
    {
        // Iterate through each factor of the prime factorizations
        for (const auto& factor : factors)
        {
            // Every factor's max power is added
            combinedFactors[factor.first] = max(combinedFactors[factor.first], factor.second);
        }
    }

    // Remove 1 from the prime factorization of the LCM if other numbers are involved in the prime factorization
    if (combinedFactors.size() > 1 &&  combinedFactors.count(1) == 1)
    {
        combinedFactors.erase(1);
    }

    unsigned long long int lcm = 1;

    for (const auto& factor : combinedFactors)
    {
        lcm *= ceil(pow(factor.first, factor.second));
    }

    // Print LCM and LCM prime factorization
    cout << "LCM: " << lcm << "\nLCM: ";
    printPrimeFactorization(lcm, combinedFactors);
    cout << endl << endl;
}
