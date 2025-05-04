#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0ULL, 0ULL, 0ULL, 0ULL, 0ULL};
        int w_index = 4;
        int position = 0;
        unsigned long long current = 0ULL;
        unsigned long long mult = 1ULL;
        for(int i = static_cast<int>(k.size()) - 1; i >= 0; --i){
            unsigned int digit = letterDigitToNumber(k[i]);
            current += static_cast<unsigned long long>(digit) * mult;
            mult *= 36ULL;
            ++position;
            if(position == 6){
                w[w_index--] = current;
                current = 0ULL;
                mult = 1ULL;
                position = 0;
            }
        }
        if(position > 0 && w_index >= 0){
            w[w_index--] = current;
        }
        unsigned long long hash = 0ULL;
        for(int i = 0; i < 5; i++){
            hash += static_cast<unsigned long long>(rValues[i]) * w[i];
        }
        return static_cast<HASH_INDEX_T>(hash);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(std::isalpha(static_cast<unsigned char>(letter))){
            return static_cast<HASH_INDEX_T>(std::tolower(letter) - 'a');
        }
        else if(std::isdigit(static_cast<unsigned char>(letter))){
            return static_cast<HASH_INDEX_T>((letter - '0') + 26);
        }
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
