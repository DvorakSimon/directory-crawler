#include "FileLib.h"

using namespace std;

FileLib::FileLib()
{
    //ctor
}

FileLib::~FileLib()
{
    //dtor
}

vector<string> FileLib::getFiles(string dirPath)
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

/*
 * The function returns directories found in directory.
 * First parameter is path where you want to find directories.
 * You can also use double slashes like this ...../dir/dir//dir. Not recomanded!
 */
vector<string> FileLib::getDirs(string dirPath)
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
