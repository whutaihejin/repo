#include <stdio.h>
#include <netdb.h>
#include <string>
#include <string.h>

std::string format(struct netent* ent) {
  std::string ret;
  if (!ent) return ret;
  if (ent->n_name) {
    ret += "n_name:";
    ret.append(ent->n_name, strlen(ent->n_name));
  }
  if (ent->n_aliases && (*(ent->n_aliases))) {
    ret += ", n_aliases:";
    ret.append(*ent->n_aliases, strlen(*ent->n_aliases));
  }
  ret += ", n_addrtype:" + std::to_string(ent->n_addrtype);
  ret += ", n_net:" + std::to_string(ent->n_net);
  return ret;
}

int main() {
  struct netent* ent = getnetent();
  for (; ent; ent = getnetent()) {
    printf("entry> %s\n", format(ent).c_str());
  }
  endhostent();
  return 0;
}
