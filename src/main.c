#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  char input[100];
  printf("$ ");
  input[strlen(input) - 1] = '\0';
  printf("%s: command not found\n", input);
  fgets(input, 100, stdin);
  return 0;
}
