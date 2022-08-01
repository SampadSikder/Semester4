#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("Hello world\n");
    fork();
    for (;;)
    {
        // printf("\nhello\n");
    }
    return 0;
}
