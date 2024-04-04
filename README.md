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
