#include "core/MemIniParser.h"
#include <Windows.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    wchar_t *pIniContent = L"[General]\n  url = hello \n filesize=13423l4   \r\n md5= 1234997234sldfjasldfhakljs\n\n";

    CMemIniParser parser(pIniContent);
    parser.Parser();
    wchar_t* pszValue = new wchar_t[MAX_PATH];
    memset(pszValue, 0, MAX_PATH * sizeof(wchar_t));
    parser.ReadKey(L"General", L"url", pszValue, MAX_PATH - 1);
    delete [] pszValue;

    return 0;
}
