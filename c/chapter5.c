#include <stdio.h>
#include <stdlib.h> // declares malloc
#include <string.h>

char** readLines(FILE* readFile) {
  char** lines = malloc(255 * sizeof(char*));
  int i = 0;
  while (1) {
    char* buf = malloc(255);
    if (!fgets(buf, 255, readFile)) {
      free(buf);
      break;
    }
    buf[strlen(buf) - 1] = 0;
    lines[i] = buf;
    i++;
  }
  lines[i] = 0;
  return lines;
}

void freeLines(char** lines) {
  int i = 0;
  while (lines[i]) {
    free(lines[i]);
    i++;
  }
  free(lines);
}

void reverseLine(char* line) {
  int start = 0;
  int end = strlen(line) - 1;
  while (start < end) {
    char temp = line[start];
    line[start] = line[end];
    line[end] = temp;
    start++;
    end--;
  }
}

void writeLines(FILE* writeFile, char** lines) {
  int i = 0;
  while (lines[i]) {
    fprintf(writeFile, "%s\n", lines[i]);
    i++;
  }
}

void reverseLines(char** lines) {
  int i = 0;
  while (lines[i]) {
    reverseLine(lines[i]);
    i++;
  }

  int start = 0;
  int end = i - 1;
  while (start < end) {
    char* temp = lines[start];
    lines[start] = lines[end];
    lines[end] = temp;
    start++;
    end--;
  }
}

int main() {
  printf("Please enter a file to open!");
  char readFileName[255];
  fgets(readFileName, 255, stdin);
  readFileName[strlen(readFileName) - 1] = 0;

  printf("And where do you want me to write to?");
  char writeFileName[255];
  fgets(writeFileName, 255, stdin);
  writeFileName[strlen(writeFileName) - 1] = 0;

  FILE* readFile = fopen(readFileName, "r");
  char** lines = readLines(readFile);

  reverseLines(lines);
  // write out reversed lines to file
  FILE* writeFile = fopen(writeFileName, "w");
  writeLines(writeFile, lines);

  freeLines(lines);
}
