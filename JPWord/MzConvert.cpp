#include "stdafx.h"
#include "MzConvert.h"

wstring MzConvert::string2wstring(const string& s)
    {
        int len;
        int slength = (int)s.length() + 1;
        len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
        wchar_t* buf = new wchar_t[len];
        MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
        std::wstring r(buf);
        delete[] buf;
                
        return r;
    }
   

   wstring MzConvert::ANSIToUnicode( const string& str )
    {
        size_t len = str.length();

        int unicodeLen = ::MultiByteToWideChar( CP_ACP, 0, str.c_str(), -1, NULL, 0 );

        wchar_t * pUnicode;
        pUnicode = new wchar_t[unicodeLen+1];

        memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));

        MultiByteToWideChar( CP_ACP, 0, str.c_str(), -1, (LPWSTR)pUnicode, unicodeLen );


        wstring rt = ( wchar_t* )pUnicode;
        delete pUnicode;

        return rt;
    }


    string MzConvert::UnicodeToANSI( const wstring& str )
    {
        char* pElementText;
        int iTextLen;

        // wide char to multi char
        iTextLen = WideCharToMultiByte( CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL );

        pElementText = new char[iTextLen + 1];
        memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );

        WideCharToMultiByte( CP_ACP, 0, str.c_str(), -1, pElementText, iTextLen, NULL, NULL );

        string strText = pElementText;
        delete[] pElementText;

        return strText;
    }


   wstring MzConvert::UTF8ToUnicode( const string& str )
    {
        size_t len = str.length();
        int unicodeLen = ::MultiByteToWideChar( CP_UTF8, 0, str.c_str(), -1, NULL, 0 );

        wchar_t * pUnicode;
        pUnicode = new wchar_t[unicodeLen+1];
        memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));

        MultiByteToWideChar( CP_UTF8, 0, str.c_str(), -1, (LPWSTR)pUnicode, unicodeLen );


        wstring rt = ( wchar_t* )pUnicode;
        delete pUnicode;

        return rt;
    }


    string MzConvert::UnicodeToUTF8( const wstring& str )
    {
        char* pElementText;
        int iTextLen;

        // wide char to multi char
        iTextLen = WideCharToMultiByte( CP_UTF8, 0, str.c_str(), -1, NULL, 0, NULL, NULL );
        pElementText = new char[iTextLen + 1];

        memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );

        WideCharToMultiByte( CP_UTF8, 0, str.c_str(), -1, pElementText, iTextLen, NULL, NULL );

        string strText = pElementText;
        delete[] pElementText;

        return strText;
    }
