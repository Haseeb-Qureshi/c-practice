#include <stdlib.h>
#include <assert.h>

int main() {
  assert(1 == 0);
  int* i = malloc(sizeof(int));
  free(i);
  free(i);
}
