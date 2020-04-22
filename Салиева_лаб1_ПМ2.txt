/*лабораторная работа 1, Салиева Аннисса, ПМ2*\


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    char argv[16][80];
    char *masuk[16];
    int i=0, j=0, n, rv, ch;

    printf("$");
    while ((ch = getchar()) !=EOF)
  {
    switch(ch)
      {

      case  '\n':
            argv[i][j] = '\0';
            n = i;
            for (i = 0; i <= n; ++i)
              {
               masuk[i] = argv[i];
              }
            masuk[i] = NULL;
            pid_t pid = fork();
            if (pid == -1)
               {
                perror("fork");
               }
            else
              {
                if (!pid)
                   {
                    rv = execvp(masuk[0],masuk);
                    if (rv == -1)
                      {
                        perror("execvp");
                      }
                   }
               }
            pid = wait(NULL);
            if (pid == -1)
              {
                perror("wait");
              }
            printf("$");
            i = 0; j = 0;
            continue;
         break;

       case ' ':
            argv[i][j] = '\0';
            ++i;
            j = 0;
            continue;
        break;

       default:
        argv[i][j] = ch;
        ++j;break;

       }
  }
    return 0;
}
