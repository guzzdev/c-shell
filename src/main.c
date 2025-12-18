#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  for (;;)
  {

    char *path_env = getenv("PATH");
    char path_copy[1024];

    strcpy(path_copy, path_env);
    

    printf("%i", access(path_copy, F_OK));

    printf(path_copy, ":");
    printf(strtok(NULL, ":"));
    printf(strtok(NULL, ":"));

    // Flush after every printf
    setbuf(stdout, NULL);
    printf("$ ");
    char input[100];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strcmp(input, "exit") == 0)
    {
      break;
    } else if (strncmp(input, "echo", 4) == 0)
    {
      printf("%s\n", input + 5); // Print everything after "echo "
      continue;
    } else if (strncmp(input, "type", 4) == 0) {
      if (strcmp(input + 5, "exit") == 0) {
        printf("%s is a shell builtin\n", input + 5); 
        continue;
      }
      if (strcmp(input + 5, "echo") == 0) {
        printf("%s is a shell builtin\n", input + 5); 
        continue;
      } 
      if (strcmp(input + 5, "type") == 0) {
        printf("%s is a shell builtin\n", input + 5); 
        continue;
      } 
      // if () {
      
      // }
      else {
        printf("%s: not found\n", input + 5);
      }
      continue;
    }
    else
    {
      printf("%s: command not found\n", input);
    }
  }

  return 0;
}
