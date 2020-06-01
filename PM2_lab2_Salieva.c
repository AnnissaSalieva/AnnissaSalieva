
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    char argv[16][80];
    char *masuk[16];
    int i=0, j=0, n, rv, ch, inp, finp=0, out, fout;

    printf("$");
    while ((ch = getchar()) !=EOF)    {
     switch(ch)   {

      case  '\n':
            argv[i][j] = '\0';
            n = i;
            for (i = 0; i <= n; ++i)    {
               masuk[i] = argv[i];
            }
            masuk[i] = NULL;
            pid_t pid = fork();
            if (pid == -1)    {
                perror("fork");
            }
            else    {
                if (!pid)    {
                 if (fout==1) {
                  int fdout=open(masuk[out], O_WRONLY|O_CREAT|O_TRUNC, 0664);
                  if (fdout==-1) {
                      perror ("open");
                      exit (EXIT_FAILURE);
                  }
                  if (-1==dup2 (fdout, STDOUT_FILENO)) {
                     perror ("dup out");
                     exit (EXIT_FAILURE);
                  }
                  masuk[out]=NULL;
                 }
                 if (finp == 1) {
                  int fdin = open (masuk[inp], O_RDONLY);
                  if (fdin ==-1) {
                     perror ("open inp");
                     exit (EXIT_FAILURE);
                  }
                  if (-1 == dup2 (fdin, STDIN_FILENO)) {
                     perror ("dup inp");
                     exit (EXIT_FAILURE);
                  }
                  masuk[inp] = NULL;
                }
                    rv = execvp(masuk[0],masuk);
                    if (rv == -1)    {
                        perror("execvp");
                    }
                 }
            }
            pid = wait(NULL);
            if (pid == -1)   {
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

       case '<':
        inp=i;
        if ((ch=getchar())!= ' ') {
         argv[i][j] = ch;
         ++j;
        }
       ++finp;
       continue;

       case '>':
      if (inp==i) {
          argv[i][j] = '\0';
         ++i; j=0;
      }
      out=i;
       if ((ch=getchar())!=' ') {
         argv[i][j]=ch;
        ++j;
       }
      ++fout;

       continue;

       default:
        argv[i][j] = ch;
        ++j;break;

     }
    }
    return 0;
}
