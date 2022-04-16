#include <stdio.h>
#include <netdb.h>
#include <string>
#include <string.h>

std::string format(struct hostent* ent) {
  std::string ret;
  if (!ent) return ret;
  if (ent->h_name) {
    ret += "h_name:";
    ret.append(ent->h_name, strlen(ent->h_name));
  }
  if (ent->h_aliases && (*(ent->h_aliases))) {
    ret += ", h_aliases:";
    ret.append(*ent->h_aliases, strlen(*ent->h_aliases));
  }
  ret += ", h_addrtype:" + std::to_string(ent->h_addrtype);
  ret += ", h_length:" + std::to_string(ent->h_length);
  if (ent->h_addr_list && *ent->h_addr_list) {
    ret += ", h_addr_list:";
    ret.append(*ent->h_addr_list, strlen(*ent->h_addr_list));
  }
  return ret;
}

int main() {

  struct hostent* ent = gethostent();
  for (; ent; ent = gethostent()) {
    printf("entry> %s\n", format(ent).c_str());
  }
  endhostent();
  return 0;
}
