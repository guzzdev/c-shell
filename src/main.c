#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int isBuiltIn(char *cmd)
{
  return strcmp(cmd, "exit") == 0 ||
         strcmp(cmd, "echo") == 0 ||
         strcmp(cmd, "pwd") == 0 ||
         strcmp(cmd, "type") == 0;
}

char *findPath(char *cmd)
{
  char *path_env = getenv("PATH");
  char path_copy[1024];
  strcpy(path_copy, path_env);

  char *file = cmd;
  char *dir = strtok(path_copy, ":");
  while (dir != NULL)
  {
    char file_path[1024];
    strcpy(file_path, dir);
    strcat(file_path, "/");
    strcat(file_path, file);

    dir = strtok(NULL, ":");

    if (access(file_path, X_OK) == 0)
    {
      return strdup(file_path);
    }
  }
  return NULL;
}

int handleType(char *cmd)
{

  if (isBuiltIn(cmd))
  {
    printf("%s is a shell builtin\n", cmd);
  }
  else
  {
    char *foundPath = findPath(cmd);
    if (foundPath != NULL)
    {
      printf("%s is %s\n", cmd, foundPath);
      free(foundPath);
    }
    else
    {
      printf("%s: not found\n", cmd);
    }
  }
  return 0;
}

int main(int argc, char *argv[])
{
  for (;;)
  {
    setbuf(stdout, NULL);
    printf("$ ");

    char input[100];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "exit") == 0)
    {
      break;
    }
    else if (strncmp(input, "echo", 4) == 0)
    {
      printf("%s\n", input + 5);
      continue;
    }
    else if (strncmp(input, "type", 4) == 0)
    {
      handleType(input + 5);
    }
    else if (strcmp(input, "pwd") == 0)
    {
      char buffer[256];
      getcwd(buffer, 256);
      printf("%s \n", buffer);
    }
    else if (strncmp(input, "cd", 2) == 0)
    {
      if (strcmp(&input[3], "~") == 0)
      {
        chdir(getenv("HOME"));
        continue;
      }
      else if (chdir(input + 3) != 0)
      {
        printf("cd: %s: No such file or directory\n", input+3);
      }
    }
    else if (!isBuiltIn(input))
    {
      char *args[100] = {0};
      
      char *buffer = strtok(input, " ");
      int index = 0;
      
      while (buffer != NULL) {
        args[index++] = buffer;
        buffer = strtok(NULL, " ");
      }
    
      args[index] = NULL;
      char *path = findPath(args[0]);

      if (path != NULL)
      {
        pid_t pid = fork();
        
        if (pid == 0) {
            execv(path, args);
            perror("execv failed");
            exit(1);
        }
        else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            continue;
        }
        else {
            perror("fork failed");
            continue;
        }
        free(path);}
      else {
        printf("%s: command not found\n", args[0]);
      }
    }
    else
    {
      printf("%s: command not found\n", input);
    }
  }
}