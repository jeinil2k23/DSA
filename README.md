#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <dirent.h>
#include <sys/stat.h>


const int N_Month = 6;
const int M_Access_Count = 3;
using namespace std;

void checkfilesOld(const string&filepath)
{
struct star result;
if(stat(filePath.c_str(),&result) == 0)
{
t1 current_time = time(nullptr);
double SecondsSinceLastAccess = difftime(current_time,result.st_atime);
double MonthsSinceLastAccess = SecondsSinceLastAccess / (60 * 60 * 24 * 30 );
if(MonthsSinceLastAccess > N_Month)
{
cout<<"File is Old: "<<filepath<<endl;
}
}
}
