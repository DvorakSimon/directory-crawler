#include <iostream>
#include <vector>
#include <stack>
#include <dirent.h>
#include <stdio.h>

using namespace std;

vector<string> getFiles(string filePath)
{
    const char* DIR_PATH = filePath.c_str();

    vector<string> directories;

    DIR *dir = opendir(DIR_PATH);

    struct dirent *entry = readdir(dir);

    while (entry != NULL)
    {
        if (entry->d_type == DT_DIR)
            directories.push_back(entry->d_name);

        entry = readdir(dir);
    }

    closedir(dir);

    return directories;
}


int main()
{
    string searchedDir = "/home/simon/Plocha/Simon/Data";

    vector<string> directories = getFiles(searchedDir);

    for(int j = 0; j < directories.size()-1; ++j) {
        cout << directories.at(j) << endl;
    }

    stack<string> actDir;

    string strSearchedDir = string(searchedDir);

    actDir.push(strSearchedDir);

    string actSearchedDir;

    vector<string> dirFound;

    const char* actCharSearchedDir;

    while(actDir.size() > 0) {
        actSearchedDir = actDir.top();actDir.pop();
        cout << actSearchedDir;

        actCharSearchedDir = actSearchedDir.c_str();

        dirFound = getFiles(actCharSearchedDir);

        for(unsigned i = 0; i < dirFound.size()-1; i++) {
            cout << dirFound.at(i);
        }

        for(unsigned i = 0; i < dirFound.size()-1; i++) {
            actDir.push(dirFound.at(i));
        }

    }

    return 0;
}
