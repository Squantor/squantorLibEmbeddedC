/*
MIT License

Copyright (c) 2019 Bart Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <stddef.h>
#include <command_mini.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int commandCompare(const char *__restrict__ pattern, const char *__restrict__ cmdline)
{
    while((*pattern) && (*pattern == *cmdline))
    {
        ++pattern;
        ++cmdline;
    }
    // check if the command has an argument
    if((*pattern == '\0') && (*cmdline == ' '))
        // yes, pattern ended with terminator and cmdline had more chars
        return 0;
    else
        return(*(unsigned char *)pattern - *(unsigned char *)cmdline);
}

result commandInterpret(commandEntry_t *__restrict__ list, const char *__restrict__ command)
{
    while(list->handler != NULL)
    {
        if(commandCompare(list->command, command) == 0)
        {
            // we have matched the command, parse argument and if needed pass to handler
            const char *s = command;
            while(isalnum(*s))
                s++;
            while(isspace(*s))
                s++;
            if(*s == '\0')
                return list->handler(NULL);
            else
                return list->handler(s);
        }
        list++;
    }
    return commandNotFound;
}