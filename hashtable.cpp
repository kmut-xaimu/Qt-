#include "hashtable.h"
#include <QDebug>

string UTF8ToGB(const char* str)
{
    string result;
    WCHAR* strSrc;
    LPSTR szRes;

    //获得临时变量的大小
    int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
    strSrc = new WCHAR[i + 1];
    MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

    //获得临时变量的大小
    i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, nullptr, 0, nullptr, nullptr);
    szRes = new CHAR[i + 1];
    WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i,nullptr, nullptr);

    result = szRes;
    delete[]strSrc;
    delete[]szRes;

    return result;
}

//从0开始
string split(const char*source,const char* strDelimit, int index)
{
    if (index<0)
    {
        return "";
    }
    size_t len = strlen(source);
    string result = source;
    //cout << result.size();
    size_t start = 0, end = 0;

    int cnt = 0;
    size_t i = 0;
    for (i = 0; i < len; i++)
    {
        if (source[i] == strDelimit[0])
        {
            if (index == 0)
            {
                end = i;
                return result.substr(0, end);
            }

            cnt++;
            if (cnt == index)
            {
                start = i + 1;
            }
            if (cnt == index+1)
            {
                end = i;
                break;
            }

        }
    }

    if (i == len)
    {
        end = i;
    }

    return result.substr(start, end-start);

}

string split(const string& source, const char* strDelimit, int index)
{
    if (index < 0)
    {
        return "";
    }
    size_t len = source.size();

    //cout << result.size();
    size_t start = 0, end = 0;

    int cnt = 0;
    size_t i = 0;
    for (i = 0; i < len; i++)
    {
        if (source[i] == strDelimit[0])
        {
            if (index == 0)
            {
                end = i;
                return source.substr(0, end);
            }

            cnt++;
            if (cnt == index)
            {
                start = i + 1;
            }
            if (cnt == index + 1)
            {
                end = i;
                break;
            }

        }
    }

    if (i == len)
    {
        end = i;
    }

    return source.substr(start, end - start);

}
bool loadHashTable(map<string, string>* HashTab,string path)
{
    ifstream infile;

    infile.open(path, ios::out | ios::in);
    if (!infile.is_open())
    {
        cout << "[Error]:File cannot be opened!" << endl;
        return false;
    }

    char txtin[160] = { 0 };
    int i = 0;

    //while ((infile >> txtin).good())
    //{
    //	i++;
    //	HashTab[split(UTF8ToGB(txtin), ":", 0)] = split(UTF8ToGB(txtin), ":", 1);
    //	cout << HashTab[split(UTF8ToGB(txtin), ":", 0)] << endl;
    //}


    while ((infile >> txtin).good())
    {
        i++;
        (*HashTab)[split(txtin, ":", 0)] = split(txtin, ":", 1);
        //cout << (*HashTab)[split(txtin, ":", 0)].c_str() << endl;
    }


    //cout << i << endl;
    infile.close();
    return true;
}

