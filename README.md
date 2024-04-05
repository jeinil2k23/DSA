#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <dirent.h>
#include <sys/stat.h>


const int N_MONTHS = 6;
const int M_Access_Count = 3;
using namespace std;

void checkIfFileIsOld(const string& filePath) {
    struct stat result;
    if (stat(filePath.c_str(), &result) == 0) {
        time_t currentTime = time(nullptr);
        double secondsSinceLastAccess = difftime(currentTime, result.st_atime);
        double monthsSinceLastAccess = secondsSinceLastAccess / (60 * 60 * 24 * 30); // Approximation of months
        if (monthsSinceLastAccess > N_MONTHS) {
            cout << "File is old: " << filePath << endl;
        }
    }
}
void cleanFolder(const string& folderPath) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(folderPath.c_str())) != nullptr) {
        while ((entry = readdir(dir)) != nullptr) {
            string fileName = entry->d_name;
            if (fileName != "." && fileName != "..") {
                string filePath = folderPath + "/" + fileName;
                checkIfFileIsOld(filePath);
                checkIfFileIsEmpty(filePath);
                checkFileAccessCount(filePath);
                // Perform cleaning if necessary
            }
        }
        closedir(dir);
