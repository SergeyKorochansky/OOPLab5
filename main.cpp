#include <iostream>
#include "speciallist.h"

int main()
{
    typedef std::string nameType;
    typedef int numberType;
    typedef special_list<nameType, numberType, std::less<nameType> > DataList;

    DataList data;
    std::cout << "Enter name value pairs (blank to finish)" << std::endl;

    while(true)
    {
        std::string userInput;
        std::getline(std::cin, userInput);
        if(userInput.empty())
            break;
        std::istringstream userInputParts(userInput);
        userInputParts >> data;
    }

    std::cout << data;

//    Or you can use this:
//
//    for(auto const &i: data)
//    {
//        std::cout << "name: " << std::get<0>(i)
//             << " total: " << std::get<1>(i)
//             << " mean: " << std::get<2>(i)
//             << " median: " << std::get<3>(i)
//             << std::endl;
//    }

    return 0;
}

