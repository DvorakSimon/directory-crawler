#ifndef USERINPUT_H
#define USERINPUT_H

#include <iostream>
#include <vector>

using namespace std;

class UserInput
{
    public:
        bool getUserInput(string message, vector<string> availableOpt);
        UserInput();
        virtual ~UserInput();
    protected:
    private:
};

#endif // USERINPUT_H
