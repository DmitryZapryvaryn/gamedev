#include <hello_lib.hpp>

std::string fizzBuzz(int number) {
    std::string result;
    
    bool isFizz = number % 3 == 0;
    bool isBuzz = number % 5 == 0;
    
    if(isFizz && isBuzz) {
        result = "FizzBuzz";
    } else if(isFizz) {
        result = "Fizz";
    } else if (isBuzz) {
        result = "Buzz";
    } else {
        result = std::to_string(number);
    }

    return result;
}
