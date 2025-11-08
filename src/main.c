#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    CMD_EXIT,
    CMD_ECHO,
    CMD_TYPE,
    CMD_UNKNOWN
} CommandType;

void parseCommand(char *src, char *dest) {
    int j = 0;
    for (int i = 0; i < strlen(src); i++) {
        if(src[i] == ' ' || src[i] == '\0') {
          break;
        }
        dest[j++] = src[i];
    }
    dest[j] = '\0';
}

CommandType getCommandType(char *input) {
    char command[10];
    parseCommand(input, command);

    if (strcmp(command, "exit") == 0) return CMD_EXIT;
    else if (strcmp(command, "echo") == 0) return CMD_ECHO;
    else if (strcmp(command, "type") == 0) return CMD_TYPE;
    else return CMD_UNKNOWN;
}

void parseArgs(char *src, char *dest) {
  int j = -1;
  for(int i = 0; i < strlen(src); i++) {
    if(src[i] == ' ' || src[i] == '\0') {
      j = i;
      break;
    }
  }
  if(j != -1) {
    strcpy(dest, src + j + 1);
  } else {
    dest[0] = '\0';
  }
}

void cleanString(char *str) {
  if(str == NULL) {
    return;
  }
  int i = 0;
  while (isspace((unsigned char)str[i])) {
      i++;
  }

  int j = 0;
  while (str[j++] = str[i++]);
}

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  char input[100];
  char command[10];
  char args[100];
  while(1) {
    printf("$ ");
    fgets(input, 100, stdin);
    input[strlen(input) - 1] = '\0';
    CommandType cmd = getCommandType(input);
    parseArgs(input, args);
    cleanString(args);
    switch(cmd) {
      case CMD_EXIT:
        if (strlen(args) == 1) {
          if(strcmp(args, "0") == 0) {
          return 0;
          }
          return 1;
        }
        break;
      case CMD_ECHO:
        printf("%s\n", args);
        break;
      case CMD_TYPE:
        if(strcmp(args, "echo") == 0) {
          printf("%s is a shell builtin\n", args);
        } else if (strcmp(args, "exit") == 0) {
          printf("%s is a shell builtin\n", args);
        } else if (strcmp(args, "type") == 0) {
          printf("%s is a shell builtin\n", args);
        } else {
          printf("%s: not found\n", args);
        }
        break;
      case CMD_UNKNOWN:
        printf("%s: command not found\n", input);
        break;
    }
  }
  return 0;
}