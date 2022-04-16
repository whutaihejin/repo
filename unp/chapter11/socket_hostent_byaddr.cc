#include <stdlib.h>
#include <iostream>

#include <netdb.h>
#include <arpa/inet.h>

void Usage() {
    std::cout << "usage:\n"
        << "  dns <address>" << std::endl;
}

std::ostream& operator<<(std::ostream& out, const struct hostent& entry);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        Usage();
        exit(0);
    }
    struct in_addr addr;
    if (inet_pton(AF_INET, argv[1], &addr) != 1) {
        std::cout << "inet_pton error" << std::endl;
        return 0;
    }
    struct hostent* entry = gethostbyaddr(&addr, sizeof(struct in_addr), AF_INET);
    if (entry == NULL) {
        std::cout << "gethostbyaddr error: " << hstrerror(h_errno) << std::endl;
        return 0;
    }
    if (entry != NULL) {
        std::cout << *entry << std::endl;
    }
    return 0;
}

std::ostream& operator<<(std::ostream& out, const struct hostent& entry) {
    out << "hostent{h_name=";
    if (entry.h_name == NULL) {
        out << "NULL";
    } else {
        out << entry.h_name;
    }
    std::cout << " h_aliases=[";
    std::string sep;
    for (char** p = entry.h_aliases; *p != NULL; ++p) {
        std::cout << sep <<  *p;
        sep = ",";
    }
    std::cout << "]";
    std::cout << " h_addrtype=" << entry.h_addrtype
        << " h_length=" << entry.h_length;
    char buf[INET_ADDRSTRLEN] = {0};
    std::cout << " h_addr_list=[";
    switch (entry.h_addrtype) {
        case AF_INET:
            struct in_addr** addr = (struct in_addr**)(entry.h_addr_list);
            std::string sep;
            for (; *addr != NULL; ++addr) {
                std::cout << sep << inet_ntop(AF_INET, *addr, buf, sizeof(buf));
                sep = ",";
            }
        // default:
            // ignore
    }
    out << "]}";
    return out;
}
