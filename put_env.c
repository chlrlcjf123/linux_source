#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char **argv,char **envp)
{
    if(argc != 3)
    {
        printf("Usage: %s <key> <value> \n",argv[0]);
        return 1;
    }
 
    char *env = getenv(argv[1]);
    if(env)
    {
        printf("old %s's key is %s\n",argv[1], env);
        setenv(argv[1], argv[2], 1);
    }
    else
    {
        printf("%s's key is not existed\n", argv[1]);
        char buf[256]="";
        sprintf(buf, "%s=%s", argv[1], argv[2]);
        putenv(buf);
    }
    printf("after...\n");
    env = getenv(argv[1]);
    printf("%s's key is %s\n", argv[1], env);
    return 0;
}