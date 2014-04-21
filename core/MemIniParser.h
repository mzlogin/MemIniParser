#ifndef _MEMINIPARSER_
#define _MEMINIPARSER_

class CDataCouple
{
public:
    CDataCouple(wchar_t* pszSection, wchar_t* pszKey, wchar_t* pszValue);
    ~CDataCouple();
private:
    wchar_t* m_pszSection;
    wchar_t* m_pszKey;
    wchar_t* m_pszValue;
};

class CMemIniParser
{
public:
private:
    CDataCouple* m_dcCoupleMaps;
};

#endif // _MEMINIPARSER_
