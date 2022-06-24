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
        
        int size = k.size();
        int converted[size];
        // Convert string to base-36
        for (int i=0; i < size; i++) {
            // Store the string into the array in reverse order
            converted[i] = letterDigitToNumber(k[size-1-i]);
        }

        unsigned long long w[5] = {0,0,0,0,0};
        // Base conversion to decimal
        int steps = 5;
        int r = 36;
        int count = 0;
        // Iterate through the w[] array
        for (int i=4; i >= 0; i--) {
            count++;
            // Case 1: There are less than 6 letters left in the word
            if (steps + 1 >= size) {
                for (int j=size-1; j >= (count-1)*6; j--) {
                    if (j == (count-1)*6) {
                        w[i] += converted[j];
                    }
                    else {
                        w[i] += converted[j];
                        w[i] *= r;
                    }
                }
                // Done!
                break;
            }
            // Case 2: There are more than or equal to 6 letters left in the word
            else {
                for (int j=steps; j >= steps-5; j--) {
                    if (j == steps-5) {
                        w[i] += converted[j];
                    }
                    else {
                        w[i] += converted[j];
                        w[i] *= r;
                    }
                }
                // Update step count
                steps += 6;
            }
        }
        
        // Final hash result
        HASH_INDEX_T final = 0;
        for (int i=0; i < 5; i++) {
            final += w[i]*rValues[i];
        }

        return final;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        
        // Lowercase
        if (toascii(letter) >= 97 && toascii(letter) <= 122) {
            return toascii(letter)-97;
        }
        // Uppercase
        else if (toascii(letter) >= 65 && toascii(letter) <= 90) {
            return toascii(letter)-65;
        }
        // Numbers
        else {
            return toascii(letter)-22;
        }
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
