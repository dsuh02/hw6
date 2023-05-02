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
      unsigned long long total = 0;
      std::string temp = k;
      HASH_INDEX_T str_size = k.size();
      int valA;
      size_t arr[5];

      if(str_size==6){
        for(size_t i=0; i<6; i++){
          valA =letterDigitToNumber(k[i]);
          total =(total*36)+valA;
        }
        total = total *rValues[4];
        return total;
      }
      else if(str_size < 6){
        temp.append(6 - str_size, '!');
        for (size_t i = 0; i < 6; i++){
          if(temp[i] != '!'){
            valA = letterDigitToNumber(k[i]);
            total = (total * 36) + valA;
          }
          else{
            break;
          }
        }
        total = total * rValues[4];
        return total;
      }
      else{
        unsigned long long totalSum = 0;
        temp.insert(0, 30 - str_size, '!');
        std::cout << temp << std::endl;

        for(size_t i = 0; i < 5; i++){
          for(size_t j = 6 * i; j < 6 * (i + 1); j++){
            valA = temp[j] != '!' ? letterDigitToNumber(temp[j]) : 0;
            total = (total * 36) + valA;
          }
          arr[i] = total;
          total = 0;
        }

        for(size_t i = 0; i < 5; i++){
          totalSum += arr[i] * rValues[i];
        }

        return totalSum;
      }
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
      char charLetter = tolower(letter);

        if (charLetter <= 'z' && charLetter >= 'a'){//if is alpha
            return charLetter = charLetter - 'a';
        }else if(charLetter <= '9' && charLetter >= '0'){//if is num
            return charLetter - '0' + 26;
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
