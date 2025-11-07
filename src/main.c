#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void slice(char *src, char *dest) {
    int j = 0;
    for (int i = 0; i < 4; i++) {
        dest[j++] = src[i];
    }
    dest[j] = '\0';
}

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  char input[100];
  char result[100];
  while(1) {
    printf("$ ");
    fgets(input, 100, stdin);
    input[strlen(input) - 1] = '\0';
    slice(input, result);
    if (strcmp(result, "exit") == 0) {
        if(input[5] == '1') {
          return 1;
        }
        break;
    }
    printf("%s: command not found\n", input);
  }
  return 0;
}
