#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) { 
  for (;;) {
    // Flush after every printf
    setbuf(stdout, NULL);
    printf("$ ");
    char input[100];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    printf("%s: command not found\n", input);
  }
  




  return 0;
}
