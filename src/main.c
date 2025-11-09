#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

typedef enum {
    CMD_EXIT,
    CMD_ECHO,
    CMD_TYPE,
    CMD_PWD,
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
    char command[100];
    parseCommand(input, command);

    if (strcmp(command, "exit") == 0) return CMD_EXIT;
    else if (strcmp(command, "echo") == 0) return CMD_ECHO;
    else if (strcmp(command, "type") == 0) return CMD_TYPE;
    else if (strcmp(command, "pwd") == 0) return CMD_PWD;
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

int findExecutable(char *cmd, char *fullPath) {
  char *pathValue;
  char *token;
  char pathCopy[1024];
  pathValue = getenv("PATH");
  if(pathValue == NULL) return 0;
  strncpy(pathCopy, pathValue, sizeof(pathCopy) - 1);
  pathCopy[sizeof(pathCopy) - 1] = '\0';
  token = strtok(pathCopy, ":;");
  while(token != NULL) {
    sprintf(fullPath, "%s/%s", token, cmd);
    if(access(fullPath, X_OK) == 0) {
      return 1;
    }
    token = strtok(NULL, ":;");
  }
  return 0;
}

void runExternal(char *args) {
    char argsCopy[100];
    strcpy(argsCopy, args);

    char *argv[20];
    pid_t pid;
    int status;

    char *token = strtok(argsCopy, " ");
    int i = 0;
    while(token != NULL && i < 19) {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

    if (i == 0) return;
    pid = fork();
    if (pid == 0) {
        execvp(argv[0], argv);
        perror("execvp failed");
        exit(1);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
    } else {
        fprintf(stderr, "fork failed\n");
    }
}


int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  char input[100];
  char command[100];
  char args[100];
  char fullPath[256];
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
          if(strcmp(args, "1") == 0) {
          return 1;
          }
          return 0;
        }
        return 0;
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
        } else if(findExecutable(args, fullPath) == 1) {
          printf("%s is %s\n", args, fullPath);
        } else {
          printf("%s: not found\n", args);
        }
        break;
      case CMD_PWD:
        char cwd[PATH_MAX];
        if(getcwd(cwd, sizeof(cwd)) != NULL) {
          printf("%s\n", cwd);
        }
        break;
      case CMD_UNKNOWN:
        parseCommand(input, command);
        if(findExecutable(command, fullPath) == 1) {
          runExternal(input);
          break;
        }
      default:
        printf("%s: command not found\n", input);
        break;
    }
  }
  return 0;
}