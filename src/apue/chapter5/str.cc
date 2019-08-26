#include <stdio.h>
#include <string>
#include <assert.h>

int main() {
    std::string str("\x07\x21");
    const char* ptr = str.data();
    const unsigned char* p = reinterpret_cast<const unsigned char*>(ptr);
    assert(*p == 7);
    assert(*(p + 1) == 33);
    const unsigned char* limit = p + str.size();
    for (; p < limit; ++p) {
        printf("%d ", *p);
    }
    printf("\n");
    for (size_t i = 0; i < str.size(); ++i) {
        unsigned char c = str[i];
        printf("%#x ", c);
    }
    printf("\n");
    return 0;
}
