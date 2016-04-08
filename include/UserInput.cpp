#include "UserInput.h"

using namespace std;

UserInput::UserInput()
{
    //ctor
}

UserInput::~UserInput()
{
    //dtor
}

bool UserInput::getUserInput(string message, vector<string> availableOpt)
{
    bool allFiles = true;
    string errorMessage = "Povolené odpovědi jsou pouze ";
    string input;
    for(int i = 0; i < availableOpt.size(); i++)
    {
        if(i == availableOpt.size() - 1)
        {
            errorMessage += availableOpt.at(i);
        }
        else
        {
            errorMessage += availableOpt.at(i) + ", ";
        }
    }

    errorMessage += "!";

    while(true)
    {
        cout << message;
        cin >> input;
        if(!input.empty())
        {
            if(input == "y" || input == "n")
            {
                if(input == "n")
                {
                    allFiles = false;
                }
                break;
            }
            else
            {
                cout << errorMessage << endl;
            }
        }
        else
        {
            cout << "Nic jsi nezadal!" << endl;
            return 1;
        }
    }

    return allFiles;
}
