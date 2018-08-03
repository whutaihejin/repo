#include <iostream>

#include <netdb.h>

void Usage() {
    std::cout << "usage:\n"
        << "  socket_servent_byname <service name>" << std::endl;
}

std::ostream& operator<<(std::ostream&, const struct servent&);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        Usage();
        return -1;
    }
    struct servent* entry;
    if ((entry = getservbyname(argv[1], NULL)) == NULL) {
        std::cout << "getservbyname error" << std::endl;
        return -1;
    }
    std::cout << *entry << std::endl;
    return 0;
}

std::ostream& operator<<(std::ostream& os, const struct servent& entry) {
    os << "servent{s_name=" << entry.s_name
        << " s_port=" << ntohs(entry.s_port)
        << " s_proto=" << entry.s_proto;
    os << " s_aliases=[";
    std::string sep;
    for (char** p = entry.s_aliases; *p != NULL; p++) {
        std::cout << sep << *p;
        sep = ",";
    }
    os << "]";
    return os;
}
