#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int binaryIO(const char* file) {
    const size_t LEN = 1024;
    size_t base[LEN];
    for (size_t i = 0; i < LEN; ++i) {
        base[i] = i + 1;
    } 
    FILE* fp = nullptr;
    if ((fp = fopen(file, "w")) == nullptr) {
        printf("fopen error\n");
        return 1;
    }
    if (fwrite(base, sizeof(size_t), LEN, fp) < LEN) {
        printf("fwrite open\n");
        return 1;
    }
    fclose(fp);
    if ((fp = fopen(file, "r")) == nullptr) {
        printf("fopen error\n");
        return 1;
    }
    size_t copy[LEN], l = 0;
    if ((l = fread(copy, sizeof(size_t), LEN, fp)) < LEN) {
        printf("read error: %ld\n", (long)l);
        return 1;
    }
    for (size_t i = 0; i < LEN; ++i) {
        assert(copy[i] == base[i]);
        printf("%d ", (int)copy[i]);
        if ((i + 1) % 20 == 0) {
            printf("\n");
        }
    }
    unlink(file);
    printf("\n");
    return 0;
}

int binaryIO2(const char* file) {
    const size_t LEN = 1024;
    size_t base[LEN];
    for (size_t i = 0; i < LEN; ++i) {
        base[i] = i + 1;
    } 
    FILE* fp = nullptr;
    if ((fp = fopen(file, "w+")) == nullptr) {
        printf("fopen error\n");
        return 1;
    }
    if (fwrite(base, sizeof(size_t), LEN, fp) < LEN) {
        printf("fwrite error\n");
        return 1;
    }
    // fflush(fp);
    rewind(fp);
    size_t copy[LEN], l = 0;
    if ((l = fread(copy, sizeof(size_t), LEN, fp)) < LEN) {
        printf("read error: %ld\n", (long)l);
        return 1;
    }
    for (size_t i = 0; i < LEN; ++i) {
        assert(copy[i] == base[i]);
        printf("%d ", (int)copy[i]);
        if ((i + 1) % 20 == 0) {
            printf("\n");
        }
    }
    unlink(file);
    printf("\n");
    return 0;
}

int main() {
    binaryIO("base.dat");
    binaryIO2("base2.dat");
    return 0;
}
