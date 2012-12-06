#include "pch.h"

namespace Common
{

    std::wstring StringToWString(const std::string &theString)
    {
        std::wstring aString;
        aString.reserve(theString.length());
        for(size_t i = 0; i < theString.length(); ++i)
            aString += (unsigned char)theString[i];
        return aString;
    }

    std::string WStringToString(const std::wstring &theString)
    {
        size_t aRequiredLength = wcstombs( NULL, theString.c_str(), 0 );
        if (aRequiredLength < 16384)
        {
            char aBuffer[16384];
            wcstombs( aBuffer, theString.c_str(), 16384 );
            return std::string(aBuffer);
        }
        else
        {
            APP_API_ASSERT(aRequiredLength != (size_t)-1);
            if (aRequiredLength == (size_t)-1) return "";

            char* aBuffer = new char[aRequiredLength+1];
            wcstombs( aBuffer, theString.c_str(), aRequiredLength+1 );
            std::string aStr = aBuffer;
            delete[] aBuffer;
            return aStr;
        }
    }

}//Common