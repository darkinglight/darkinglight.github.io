#include <iostream>
using std::cout;
using std::endl;

void testfunc(const char* & str) {
    cout << "address in func:" << static_cast<const void *>(str) << endl;
}

int main()
{
    const char *pszStr = "this is a string";

    cout << "string:" << pszStr << endl;

    cout << "address:" << static_cast<const void *>(pszStr) << endl;

    testfunc(pszStr);

    return 0;
}
