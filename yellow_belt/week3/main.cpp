#include "phone_number.h"
#include <iostream>

int main()
{
    try
    {
        PhoneNumber phone("+7-1233");
        std::cout << phone.GetCountryCode() << std::endl;
        std::cout << phone.GetCityCode() << std::endl;
        std::cout << phone.GetLocalNumber() << std::endl;
        std::cout << phone.GetInternationalNumber() << std::endl;
    }
    catch(std::invalid_argument& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}
