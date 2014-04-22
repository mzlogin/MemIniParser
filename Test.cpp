#include "core/MemIniParser.h"
#include <Windows.h>

int main(int argc, char** argv)
{
    wchar_t *pIniContent = L"[General]\n  url = hello \n filesize=13423l4   \r\n md5= 1234997234sldfjasldfhakljs\n\n";

    CMemIniParser parser(pIniContent);
    parser.Parser();

    return 0;
}
