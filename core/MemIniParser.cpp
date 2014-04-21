#include "MemIniParser.h"
#include <assert.h>

CDataCouple::CDataCouple(wchar_t* pszSection, wchar_t* pszKey, wchar_t* pszValue)
{
    assert(NULL != pszSection);
    assert(NULL != pszKey);
    assert(NULL != pszValue);

    size_t nLen = wcslen(pszSection); 
    m_pszSection = new wchar_t[nLen];
    memset(m_pszSection, 0, nLen * sizeof(wchar_t));
    wcscpy(m_pszSection, pszSection);

    nLen = wcslen(pszKey);
    m_pszKey = new wchar_t[nLen];
    memset(m_pszKey, 0, nLen * sizeof(wchar_t));
    wcscpy(m_pszKey, pszKey);

    nLen = wcslen(pszValue);
    m_pszValue =  new wchar_t[nLen];
    wcscpy(m_pszValue, pszValue);
}

CDataCouple::~CDataCouple()
{
    if (m_pszSection) { delete [] m_pszSection; m_pszSection = NULL; }
    if (m_pszKey) { delete [] m_pszKey; m_pszKey = NULL; }
    if (m_pszValue) { delete [] m_pszValue; m_pszValue = NULL; }
}
