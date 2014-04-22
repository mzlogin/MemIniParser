#include "MemIniParser.h"
#include <assert.h>
#include <string.h>

CDataCouple::CDataCouple() : m_pszSection(NULL), m_pszKey(NULL), m_pszValue(NULL)
{
}

CDataCouple::~CDataCouple()
{
    if (m_pszSection) 
    { 
        delete [] m_pszSection; 
        m_pszSection = NULL; 
    }

    if (m_pszKey) 
    { 
        delete [] m_pszKey; 
        m_pszKey = NULL; 
    }

    if (m_pszValue) 
    { 
        delete [] m_pszValue; 
        m_pszValue = NULL; 
    }
}

void CDataCouple::SetValue(wchar_t* pszSection, wchar_t* pszKey, wchar_t* pszValue)
{
    assert(NULL != pszSection);
    assert(NULL != pszKey);
    assert(NULL != pszValue);

    int nLen = wcslen(pszSection) + 1; 
    m_pszSection = new wchar_t[nLen];
    memset(m_pszSection, 0, nLen * sizeof(wchar_t));
    wcscpy(m_pszSection, pszSection);

    nLen = wcslen(pszKey) + 1;
    m_pszKey = new wchar_t[nLen];
    memset(m_pszKey, 0, nLen * sizeof(wchar_t));
    wcscpy(m_pszKey, pszKey);

    nLen = wcslen(pszValue) + 1;
    m_pszValue =  new wchar_t[nLen];
    wcscpy(m_pszValue, pszValue);
}

CMemIniParser::CMemIniParser(wchar_t* pszContent)
{
    assert(NULL != pszContent);

    int nLen = wcslen(pszContent) + 1;
    m_pszContent = new wchar_t[nLen];
    wcscpy(m_pszContent, pszContent);

    int nLineFeed = CountChar(pszContent, '\n');
    if (nLineFeed > 0)
    {
        m_dcCoupleMaps = new CDataCouple[nLineFeed];
        m_nMapLen = nLineFeed;
    }
}

CMemIniParser::~CMemIniParser()
{
    if (m_pszContent) 
    { 
        delete [] m_pszContent; 
        m_pszContent = NULL; 
    }

    if (m_dcCoupleMaps) 
    { 
        delete [] m_dcCoupleMaps; 
        m_dcCoupleMaps = NULL; 
    }
}

bool CMemIniParser::Parser()
{
    bool bRet = false;
    do 
    {
        if (!m_pszContent || !m_dcCoupleMaps)
        {
            break;
        }

        int nLen = wcslen(m_pszContent);
        int nOffset = 0;
        int nWorkMap = 0;
        wchar_t* pszSection = NULL;

        while (nOffset < nLen)
        {
            int nLineLen = GetLine(m_pszContent + nOffset, nLen - nOffset);
            if (nLineLen > 0)
            {
                wchar_t* pszLine = new wchar_t[nLineLen + 1];
                memset(pszLine, 0, (nLineLen + 1) * sizeof(wchar_t));
                wcsncpy(pszLine, m_pszContent + nOffset, nLineLen);

                Trim(pszLine);
                nLineLen = wcslen(pszLine);
                if (nLineLen > 0 && *pszLine != ';')
                {   // split pszLine to a DataCouple
                    if ('[' == pszLine[0] && ']' == pszLine[nLineLen - 1])
                    {   // section
                        if (pszSection)
                        {
                            delete [] pszSection;
                            pszSection = NULL;
                        }
                        pszSection = new wchar_t[nLineLen + 1];
                        memset(pszSection, 0, (nLineLen + 1) * sizeof(wchar_t));
                        wcsncpy(pszSection, pszLine + 1, nLineLen - 2); // without '[' and ']'
                    }
                    else
                    {   // key-value couple
                        int nPos;
                        wchar_t* pSplit = wcschr(pszLine, '=');
                        if (pSplit)
                        {
                            int nKeyLen = pSplit - pszLine;
                            wchar_t* pszKey = new wchar_t[nKeyLen + 1];
                            memset(pszKey, 0, (nKeyLen + 1) * sizeof(wchar_t));
                            wcsncpy(pszKey, pszLine, nKeyLen);
                            Trim(pszKey);

                            wchar_t* pszValue = NULL;
                            if (nLineLen - nKeyLen > 1)
                            {
                                int nValueLen = nLineLen - nKeyLen - 1;
                                pszValue = new wchar_t[nValueLen + 1];
                                memset(pszValue, 0, (nValueLen + 1) * sizeof(wchar_t));
                                wcscpy(pszValue, pSplit + 1);
                                Trim(pszValue);

                                m_dcCoupleMaps[nWorkMap].SetValue(pszSection, pszKey, pszValue);
                                nWorkMap++;
                            }

                            if (pszKey)
                            {
                                delete [] pszKey;
                                pszKey = NULL;
                            }

                            if (pszValue)
                            {
                                delete [] pszValue;
                                pszValue = NULL;
                            }
                        }
                    }
                }

                if (pszLine)
                {
                    delete [] pszLine;
                    pszLine = NULL;
                }
            }

            nOffset = nOffset + nLineLen + 1;
        }

        if (nOffset >= nLen)
        {
            bRet = true;
        }

        if (pszSection)
        {
            delete [] pszSection;
            pszSection = NULL;
        }

    } while (false);

    return bRet;
}

int CMemIniParser::CountChar(wchar_t* pszSrc, wchar_t cDst)
{
    int nRet = 0;
    wchar_t* pWork = pszSrc;
    while (*pWork != 0)
    {
        if (*pWork == cDst)
        {
            nRet++;
        }
        pWork++;
    }
    
    return nRet;
}

int CMemIniParser::GetLine(wchar_t* pszSrc, int nLen)
{
    assert(pszSrc != NULL);

    wchar_t* pWork = pszSrc;
    int nLineLen = 0;
    while (true)
    {
        if (*pWork == '\n')
        {
            break;
        }

        if (nLineLen >= nLen)
        {
            break;
        }

        pWork++;
        nLineLen++;
    }    

    return nLineLen;
}

void CMemIniParser::Trim(wchar_t* pszSrc)
{
    if (!pszSrc)
    {
        return;
    }

    int nStartPos = 0;
    int nEndPos = wcslen(pszSrc);

    wchar_t* pWork = pszSrc;
    while (nStartPos < nEndPos && (*pWork == ' ' || *pWork == '\t'))
    {
        pWork++;
        nStartPos++;
    }

    pWork = pszSrc + nEndPos - 1;
    while (nStartPos < nEndPos && (*pWork == ' ' || *pWork == '\t'))
    {
        pWork--;
        nEndPos--;
    }

    if (0 == nStartPos)
    {
        pszSrc[nEndPos] = '\0';
        return;
    }

    int i;
    for (i = 0; i < nEndPos - nStartPos; i++)
    {
        pszSrc[i] = pszSrc[i + nStartPos];
    }
    pszSrc[i] = '\0';
}

bool CMemIniParser::ReadKey(wchar_t* pszSection, wchar_t* pszKey, wchar_t* pszValue, int nLen)
{
    bool bRet = false;
    for (int i = 0; i < m_nMapLen; i++)
    {
        if (0 == wcscmp(m_dcCoupleMaps[i].m_pszSection, pszSection) && 0 == wcscmp(m_dcCoupleMaps[i].m_pszKey, pszKey))
        {
            wcsncpy(pszValue, m_dcCoupleMaps[i].m_pszValue, nLen);
            bRet = true;
            break;
        }
    }
    return bRet;
}
