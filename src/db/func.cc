#include <stdio.h>

class Fuck {
 public:
  void sub (int i) {
      printf ("__FUNCTION__ = %s\n", __FUNCTION__);
      printf ("__PRETTY_FUNCTION__ = %s\n", __PRETTY_FUNCTION__);
    }
};


int main (void) {
  Fuck ax;
  ax.sub (0);
  return 0;
}
