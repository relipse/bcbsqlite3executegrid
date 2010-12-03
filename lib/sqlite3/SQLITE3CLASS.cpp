
#include "SQLITE3CLASS.h"


std::string SQLITE3::escape(string const &str, char const *series, bool backslash)
{
    string ret;
    string::size_type left = 0;

    while (true)
    {
        string::size_type right = str.find_first_of(series, left);

        ret += str.substr(left, right - left);  // append until separator

        if (right == string::npos)                  // done when all copied
            return ret;

        if (backslash) ret += "\\";         // append backslash
        else ret += str[right];             // append special char (twice) "can't" becomes "can''t"

        ret += str[right];                  // append the special char
        left = right + 1;
    }
    //not needed, however i am a skeptic -Jim K. 18Nov2010
    return ret;

}
