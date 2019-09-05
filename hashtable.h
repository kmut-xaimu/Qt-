#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <map>
#include <fstream>
#include <windows.h>

using namespace std;


bool loadHashTable(map<string, string>* HashTab, string path);
string split(const char*source,const char* strDelimit, int index);
string split(const string& source, const char* strDelimit, int index);
string UTF8ToGB(const char* str);


#endif // HASHTABLE_H
