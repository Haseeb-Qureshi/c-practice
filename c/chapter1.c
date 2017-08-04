#include <stdio.h>
#include <errno.h>

void hgets(char* buf, int size);
void swap(int* x, int* y);

enum modes {
  READ = 1,
  WRITE = 2,
  DELETE = 4
};

int main() {
  int x = 1;
  int y = 2;
  swap(&x, &y);
  printf("x: %d, y: %d\n", x, y);
}

int printstuff() {
  printf("Please enter a filename.\n");
  char buf[8];
  hgets(buf, 8);

  int i = 0;
  while (buf[i] != 0) {
    putchar(buf[i]);
    i++;
  }
  return 0;
}

void hgets(char* buf, int size) {
  int c;
  c = getc(stdin);
  int i = 0;

  while (c != '\n' && c != EOF && i < size - 1) {
    buf[i] = c;
    c = getc(stdin);
    i++;
  }

  buf[i] = 0;
}

void swap(int* x, int* y) {
  *x = *x ^ *y;
  *y = *x ^ *y;
  *x = *x ^ *y;
}
