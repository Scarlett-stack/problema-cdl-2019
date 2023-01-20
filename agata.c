#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    FILE *f[7];
    int i;
    char **text=malloc(30*sizeof(char*));
    for (i=0; i<30; i++)
      text[i]=malloc(300*sizeof(char));
    for (i=1; i<argc; i++)
      f[i]=fopen(argv[i],"r");
    
    char s[30];
    int N=0;
    fgets(s,30,stdin);
    while (strcmp(s,"/exit")!=0)
    {
       strcpy(text[N++], s);
       fgets(s,30,stdin);
    }
    for (i=0; i<N; i++)
    printf("%s\n", text[i]);
    return 0;
}