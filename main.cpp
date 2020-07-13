#include "Person.h"
#include <iostream>

int main(){
    
    Person personArray[] = 
        {
            {"2930000321", {}, {1980, 3, 21}, Sex::Female}, // OK
            {"2930000", {}, {1980, 3, 21}, Sex::Male},      // Too Short IPN
            {"29300008890", {}, {1980, 3, 21}, Sex::Male},  // Too long IPN
            {"3270098110", {}, {2021, 12, 31}, Sex::Male},  // Bad Date: Future
            {"3270098310", {}, {1899, 8, 9}, Sex::Male},    // Bad Date: Too Old
            {"293O000301", {}, {1977, 2, 13}, Sex::Female}, // Non-Digit character
        };
    
    for (unsigned int i = 0; i < 6; i++){
        std::cout << "---Validating person ["<< i << "]---" << std::endl;
        try{
            std::cout << !Validator::ValidatePerson (personArray[i]) << std::endl;
        }
        catch (ExceptionIpn& e){
            std::cout << e.what() << std::endl;
        }
    }
}
