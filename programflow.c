#include "main.h"

char *_fullpathbuffer(char **av, char *PATH, char *copy)
{
        char *tok = NULL, *fullpathbuffer = NULL, *concatstr = NULL;
        static char tmp[256];
        int PATHcount = 0, fullpathflag = 0, z = 0, toklen = 0;
        struct stat h;

        copy = NULL;
        copy = _strdup(PATH);
        PATHcount = _splitPATH(copy);
        tok = strtok(copy, ": =");
        while (tok != NULL)
        {
                concatstr = _concat(tmp, av, tok);
                if (stat(concatstr, &h) == 0)
                {
                        fullpathbuffer = concatstr;
                        fullpathflag = 1;
                        break;
                }
                if (z < PATHcount - 2)
                {
                        toklen = _strlen(tok);
                        if (tok[toklen + 1] == ':')
                        {
                                if (stat(av[0], &h) == 0)
                                {
                                        fullpathbuffer = av[0];
                                        fullpathflag = 1;
                                        break;
                                }
                        }
                }
                z++;
                tok = strtok(NULL, ":");
        }
        if (fullpathflag == 0)
                fullpathbuffer = av[0];
        free(copy);
        return (fullpathbuffer);
}
