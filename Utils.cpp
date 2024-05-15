
#include <iostream>
using namespace std;
#include "Utils.h"

namespace sdds {

    int getIntegerInput(int minimumRange, int maximumRange, const char* msg) {
        int in;
        bool validInput = false;
        while (validInput == false)
        {
            cin >> in;
            if (!cin || in < minimumRange || in > maximumRange)
            {
                std::cout << msg;
                cin.clear();
                cin.ignore(1000, '\n');
                validInput = false;
            }
            else
            {
                validInput = true;
            }

        }
        return in;
    }
}