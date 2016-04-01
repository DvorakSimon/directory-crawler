#include <iostream>
#include <vector>
#include <stack>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

using namespace std;

vector<string> getFiles(string filePath)
{
    const char* DIR_PATH = filePath.c_str();

    vector<string> directories;

    DIR *dir = opendir(DIR_PATH);

    struct dirent *entry = readdir(dir);

    while (entry != NULL)
    {
        if (entry->d_type == DT_DIR) {
            if(!strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".")) {

            } else {
                directories.push_back(filePath + "/" + entry->d_name);
            }
        }

        entry = readdir(dir);
    }

    closedir(dir);

    return directories;
}


int main(void)
{
    string searchedDir = "/home/simon/Plocha/Simon";

    stack<string> actDir;

    actDir.push(searchedDir);

    string actSearchedDir;

    vector<string> dirFound;

    string newString = searchedDir;

    int dirCount = 0;

    while(actDir.size() > 0) {
        actSearchedDir = actDir.top();actDir.pop();

        cout << actSearchedDir << endl;

        dirFound = getFiles(actSearchedDir.c_str());

        for(unsigned i = 0; i < dirFound.size(); i++) {
            if(!dirFound.empty()) {
                newString = dirFound.at(i);
                //cout << newString << endl;
                actDir.push(newString);
            } else {
                break;
            }
        }
        dirCount++;
    }

    cout << "Bylo nalezeno celkem " << dirCount-1 << " složek";

    return 0;
}
