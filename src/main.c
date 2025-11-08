#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseString(int start, int end, char *src, char *dest) {
    int j = 0;
    for (int i = start; i < end; i++) {
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
    parseString(0, 5, input, result);
    if (strcmp(result, "exit ") == 0) {
        if(input[5] == '1' && strlen(input) == 6) {
          return 1;
        } else if (input[5] == '0' && strlen(input) == 6) {
          return 0;
        }
    } else if(strcmp(result, "echo ") == 0) {
      parseString(5, strlen(input), input, result);
      printf("%s\n", result);
    } else {
       printf("%s: command not found\n", input);
    }
  }
  return 0;
}
