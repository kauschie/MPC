#include <iostream>
#include <vector>
#include <string>
#include <iomanip>


#include "StringUtil.h"
#include "Tests.h"
#include "FileData.h"
#include "PatchData.h"

// #define TEST_STRING_UTIL
// #define TEST_FILE_DATA
#define TEST_PATCH_ADE

extern void PatchData_test();
extern void StringUtil_Test();
extern void FileData_test();

int main()
{

#ifdef TEST_STRING_UTIL
    StringUtil_Test();
#endif

#ifdef TEST_FILE_DATA
    FileData_test();
#endif

#ifdef TEST_PATCH_ADE
    PatchData_test();
#endif

    
    return 0;
}
