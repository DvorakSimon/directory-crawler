#ifndef CHECKER_H
#define CHECKER_H

#include <iostream>

using namespace std;

class Checker
{
    public:
        string CheckPath();

        Checker(string path);
        virtual ~Checker();
    protected:
    private:
};

#endif // CHECKER_H
