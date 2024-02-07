#include <iostream>
#include <vector>
#include <string>
#include <iomanip>


#include "StringUtil.h"
#include "Tests.h"
#include "FileData.h"

// #define TEST_STRING_UTIL
// #define TEST_FILE_DATA

int main()
{

#ifdef TEST_STRING_UTIL
    StringUtil_Test();
#endif

#ifdef TEST_FILE_DATA
    FileData_test();
#endif
    return 0;
}
