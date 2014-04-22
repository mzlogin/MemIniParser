#ifndef _MEMINIPARSER_
#define _MEMINIPARSER_

class CDataCouple
{
public:
    CDataCouple();
    ~CDataCouple();
    void SetValue(wchar_t* pszSection, wchar_t* pszKey, wchar_t* pszValue);

    wchar_t* m_pszSection;
    wchar_t* m_pszKey;
    wchar_t* m_pszValue;
};

class CMemIniParser
{
public:
    CMemIniParser(wchar_t* pszContent);
    ~CMemIniParser();

    bool Parser();
    bool ReadKey(wchar_t* pszSection, wchar_t* pszKey, wchar_t* pszValue, int nLen);

protected:
    int CountChar(wchar_t* pszSrc, wchar_t cDst);
    int GetLine(wchar_t* pszSrc, int nLen);
    void Trim(wchar_t* pszSrc);

private:
    CDataCouple* m_dcCoupleMaps;
    int m_nMapLen;
    wchar_t* m_pszContent;
};

#endif // _MEMINIPARSER_
