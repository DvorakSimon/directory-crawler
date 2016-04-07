#ifndef FILELIB_H
#define FILELIB_H

#include <iostream>
#include <vector>
#include <stack>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/timeb.h>

using namespace std;


class FileLib
{
    public:
        vector<string> getFiles(string dirPath);
        vector<string> getDirs(string dirPath);
        FileLib();
        virtual ~FileLib();
    protected:
    private:
};

#endif // FILELIB_H
