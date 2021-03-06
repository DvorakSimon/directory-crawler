#include <iostream>
#include <vector>
#include <stack>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/timeb.h>

using namespace std;

/*
 * The function returns directories found in directory.
 * First parameter is path where you want to find directories.
 * You can also use double slashes like this ...../dir/dir//dir. Not recomanded!
 */
vector<string> getDirs(string dirPath)
{
    // Converting path to const char* because the function opendir is programmed in c
    // and c methods parameters accepts only const char* so I must convert it.
    const char* DIR_PATH = dirPath.c_str();

    // Declaration of dynamic array that contains found directories by path.
    vector<string> directories;

    // Call a function to try to open the dir by path.
    // If it doesnt exists the function will return segmentation error.
    DIR *dir = opendir(DIR_PATH);

    // Then try to read the dir
    struct dirent *entry = readdir(dir);

    // While dir has a directory.
    while (entry != NULL)
    {
        // If type of stream is directory.
        if (entry->d_type == DT_DIR) {
            // If the "directory" name is not ".." or ".".
            if(!strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".")) {

            } else {
                // push the actual dir path PLUS actual directory to the dynamic array.
                directories.push_back(dirPath + "/" + entry->d_name);
            }
        }

        entry = readdir(dir);
    }

    // Close the dir.
    closedir(dir);

    return directories;
}

vector<string> getFiles(string dirPath)
{
    // Converting path to const char* because the function opendir is programmed in c
    // and c methods parameters accepts only const char* so I must convert it.
    const char* DIR_PATH = dirPath.c_str();

    // Declaration of dynamic array that contains found directories by path.
    vector<string> files;

    // Call a function to try to open the dir by path.
    // If it doesnt exists the function will return segmentation error.
    // TODO: Sanitize and check the dirPath and handle the errors.
    // Sanitize: double slashes, ...
    DIR *dir = opendir(DIR_PATH);

    // Then try to read the dir
    struct dirent *entry = readdir(dir);

    // While dir has a directory.
    while (entry != NULL)
    {
        // If type of stream is directory.
        if (entry->d_type != DT_DIR) {
                // If the "directory" name is not ".." or ".".
                if(!strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".")) {

                } else {
                    // push the actual dir path PLUS actual directory to the dynamic array.
                    files.push_back(entry->d_name);
                }
        }

        entry = readdir(dir);
    }

    // Close the dir.
    closedir(dir);


    return files;
}

void getFoundMessage(string actSearchedDir, string fileName) {
    cout << "Soubor nalezen ve slozce " << actSearchedDir << "." << endl;
    cout << "Soubor se tedy nachází v " << actSearchedDir << "/" << fileName << endl;
}

long getCurrentTime() {
    timeb timebstr;
    ftime( &timebstr );
    return (long)(timebstr.time)*1000 + timebstr.millitm;
}

int main(void)
{
    // A root path where you want to start searching.
    // User will specify (UWS).
    // For example: "/home/simon/Plocha/Simon/Data/Pokus" if it exists of course
    string searchedDir;
    // UWS
    // For example: "VEPR.TXT"
    string searchedFile;

    // File is/isnt exactly matching with name.
    bool exactMatch = false;
    string strExactMatch;

    cout << "Zadej adresář, ve kterém chceš hledat: ";
    cin >> searchedDir;

    cout << "Budu hledat ve složce: " << searchedDir << endl;

    cout << "Zadej soubor, který chceš hledat: ";
    cin >> searchedFile;

    cout << "Hledám soubor: " << searchedFile << endl;

    while(true) {
        cout << "Musí se soubor shodovat přesně? (y/n): ";
        cin >> strExactMatch;
        if(!strExactMatch.empty()) {
            if(strExactMatch == "y" || strExactMatch == "n") {
                if(strExactMatch == "y") {
                    exactMatch = true;
                }
                break;
            } else {
                cout << "Povolené odpovědi jsou pouze y nebo n!";
            }
        } else {
            cout << "Nic jsi nezadal!" << endl;
            return 1;
        }
    }

    bool allFiles = true;
    string strAllFiles;

    while(true) {
        cout << "Přejete si hledat všechny soubory? (y/n): ";
        cin >> strAllFiles;
        if(!strAllFiles.empty()) {
            if(strAllFiles == "y" || strAllFiles == "n") {
                if(strAllFiles == "n") {
                    allFiles = false;
                }
                break;
            } else {
                cout << "Povolené odpovědi jsou pouze y, nebo n!";
            }
        } else {
            cout << "Nic jsi nezadal!" << endl;
            return 1;
        }
    }



    long startTime = getCurrentTime();

    stack<string> actDir;

    actDir.push(searchedDir);

    string actSearchedDir;

    vector<string> dirFound;
    vector<string> fileFound;

    vector<string> results;

    int dirCount = 0;

    while(actDir.size() > 0) {
        actSearchedDir = actDir.top();actDir.pop();

        cout << actSearchedDir << endl;

        dirFound = getDirs(actSearchedDir.c_str());
        fileFound = getFiles(actSearchedDir.c_str());

        for(unsigned j = 0; j < fileFound.size(); j++) {
            //cout << "Soubor: " << fileFound.at(j) << endl;
            //cout << "POROVNAVAM: " << fileFound.at(j) << " a " << searchedFile << endl;
            if(exactMatch) {
                if(fileFound.at(j) == searchedFile) {
                    if(allFiles) {
                        results.push_back(actSearchedDir + "/" + fileFound.at(j));
                    } else {
                        getFoundMessage(actSearchedDir, fileFound.at(j));
                        return 0;
                    }
                }
            } else {
                if(fileFound.at(j).find(searchedFile) != string::npos) {
                    if(allFiles) {
                        results.push_back(actSearchedDir + "/" + fileFound.at(j));
                    } else {
                        getFoundMessage(actSearchedDir, fileFound.at(j));
                        return 0;
                    }
                }
            }
        }

        for(unsigned i = 0; i < dirFound.size(); i++) {
            if(!dirFound.empty()) {
                actDir.push(dirFound.at(i));
            } else {
                break;
            }
        }
        dirCount++;
    }

    if(allFiles) {
        cout << "------------------------------" << endl;
        cout << "-- Výpis nalezených souborů --" << endl;
        cout << "------------------------------" << endl;

        for(unsigned k = 0; k < results.size(); k++) {
            cout << results.at(k) << endl;
        }
    }

    long endTime = getCurrentTime();

    cout << "Bylo nalezeno celkem " << dirCount-1 << " složek" << endl;
    cout << "Hledání celkem zabralo " << int(endTime - startTime) << " milisekund." << endl;
    cout << "To je asi " << double(endTime - startTime) / 1000 << " sekund." << endl;

    return 0;
}
