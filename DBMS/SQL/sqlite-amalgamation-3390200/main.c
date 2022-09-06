
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

int main()
{
    sqlite3_vfs vfs;
    // char *zOut;
    //*zOut='F';
    vfs.xFullPathname = SQLITE_OK;
    vfs.xOpen = SQLITE_OK;
    vfs.xAccess = SQLITE_OK;
    // vfs->xAccess = vfs_access;
    int ms;
    scanf("%d", &ms);
    int slp = sqlite3_sleep(ms);
    printf("Going to sleep for %d ms\n", slp);
}

// sqlite3_vfs obj;
// sqlite3_file *f;
// // f = (FILE *)fopen("random.db", "r");
// // sqlite3_io_methods io;
// //  io.xUnlock(f, SQLITE3_TEXT);
// // int *flag = SQLITE_OPEN_READONLY;
// // printf("%d", obj.xOpen(&obj, "keno", f, SQLITE_ACCESS_EXISTS, flag));
// // int time = obj.xSleep(&obj, 1000);
// int x = sqlite3_sleep(10000);
// // int x = sqlite3_stricmp("hello", "hello");
// printf("Calling sleep for %d", x);
// // int x = sqlite3_sleep(1000);

// // printf("%d\n", x);

// // const char *fileName = "random.db";
// // sqlite3 *object;
// // sqlite3_open_v2(fileName, &object, SQLITE_OPEN_READONLY, NULL);
// // sqlite_str_new(&object);
// // const char *x = "";
// // sqlite_str_appendAll(object, "hello there", 10);
// // puts(x);
// // sqlite_str_close(&object);
