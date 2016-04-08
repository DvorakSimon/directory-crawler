#include "Checker.h"

#include <iostream>

using namespace std;

string _path;

Checker::Checker(string path)
{
    _path = path;
}

Checker::~Checker()
{
    //dtor
}

string Checker::CheckPath()
{
    if(_path.at(_path.length()-1) == '/' && _path.length() > 1)
    {
        cout << "Cesta obsahuje lomitko na konci! Odstranuji ho!" << endl;
        for(int i = _path.length() - 1; _path.at(i) == '/'; i--)
        {
            _path.erase(i);
        }
        cout << "Cesta: " << _path << endl;
        return _path;
    }

    return _path;
}

