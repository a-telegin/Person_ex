#include "Person.h"
#include <stdexcept>

bool Validator::ValidatePerson (const Person & person)
{
    return ValidateSex   (person)
        && ValidateBDate (person);
}

bool Validator::ValidateBDate (const Person & person)
{
    const int secToDays = 60 * 60 * 24; // The number of seconds in one day.
    const int daysOffset= 25567;        // The number of days between 1900 and 1970.
    const int daysOboe  = 1;            // Off-by-one error correction.

    Date a {1970, 1, 1};
    Date b = person.bdate;
    const std::time_t c = std::mktime (& a);
    const std::time_t d = std::mktime (& b);

    const std::time_t now = time(0);
    const int now_i = now / secToDays + daysOffset + daysOboe;
    const int days = (std::difftime (d, c) ) / secToDays + daysOffset + daysOboe;
    
    if (days > now_i){
        throw ExceptionIpnBadDateFuture();
    }

    if (days < 0){
        throw ExceptionIpnBadDateTooOld();
    }

    return ParseBDate (person) == days;
}

bool Validator::ValidateSex (const Person & person)
{
    return (ParseSex (person) == person.sex);
}

int Validator::ParseBDate (const Person & person)
{
    int result = 0;    
    std::string s = person.ptn.substr (0, 5);

    for(char& c : s) {
         if (!isdigit(c)) {
             throw ExceptionIpnNonDigit();
         }
    }   
    result = std::stoi (person.ptn.substr (0, 5), nullptr);
    return result;
}

Sex Validator::ParseSex (const Person & person)
{
    if (person.ptn.size() < 9) { 
        throw ExceptionIpnBadSizeShort();
    }

    if (person.ptn.size() > 10) {
        throw ExceptionIpnBadSizeLong();
    }

    const int x = person.ptn [8] - '0';
    return (x & 1) ? Sex::Male
                   : Sex::Female;
}

