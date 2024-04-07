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
        } else {
        cerr << "Error opening directory " << folderPath << endl;
    }
}

void deleteEmptyFiles(const string& directory) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    if ((dir = opendir(directory.c_str())) != nullptr) {
        while ((entry = readdir(dir)) != nullptr) {
            string full_path = directory + "/" + entry->d_name;
            if (stat(full_path.c_str(), &file_stat) == 0) {
                // Check if it's a regular file and its size is zero
                if (S_ISREG(file_stat.st_mode) && file_stat.st_size == 0) {
                    // Delete the empty file
                    unlink(full_path.c_str());
                    cout << "Deleted empty file: " << full_path << endl;
                }
            }
        }
        closedir(dir);
    } else {
        cout << "Failed to open directory" << endl;
    }
}

int main() {
    string folderPath = "path/to/your/folder"; // Change this to the folder you want to clean
    cleanFolder(folderPath);
    return 0;
}
