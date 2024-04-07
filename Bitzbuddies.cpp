#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

const int N_MONTHS = 6; // Files older than 6 months will be considered for cleaning
const int M_ACCESS_COUNT = 3; // Files accessed less than 3 times will be considered for cleaning

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
        cerr << "Failed to open directory" << endl;
    }
}

void deleteOldFiles(const string& directory) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    if ((dir = opendir(directory.c_str())) != nullptr) {
        while ((entry = readdir(dir)) != nullptr) {
            string full_path = directory + "/" + entry->d_name;
            if (stat(full_path.c_str(), &file_stat) == 0) {
                // Check if it's a regular file and its last access time is older than N_MONTHS
                if (S_ISREG(file_stat.st_mode)) {
                    time_t currentTime = time(nullptr);
                    double secondsSinceLastAccess = difftime(currentTime, file_stat.st_atime);
                    double monthsSinceLastAccess = secondsSinceLastAccess / (60 * 60 * 24 * 30); // Approximation of months
                    if (monthsSinceLastAccess > N_MONTHS) {
                        // Delete the old file
                        unlink(full_path.c_str());
                        cout << "Deleted old file: " << full_path << endl;
                    }
                }
            }
        }
        closedir(dir);
    } else {
        cerr << "Failed to open directory" << endl;
    }
}

bool fileExists(const string& filePath) {
    struct stat buffer;
    return (stat(filePath.c_str(), &buffer) == 0);
}

void cleanFolder(const string& folderPath) {
    // Delete empty files
    deleteEmptyFiles(folderPath);

    // Delete old files
    deleteOldFiles(folderPath);

     
}

int main() {
    string folderPath = "c:/Users/VICTUS/OneDrive/Desktop/study/MAYBE DSA"; // Change this to the folder you want to clean
    cleanFolder(folderPath);
    return 0;
}