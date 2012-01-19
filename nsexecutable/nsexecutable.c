/* 
   A simple experiment to determine if _NSGetExecutablePath returns NUL
   terminated strings.

   gcc nsexecutable.c; ./a.out

   Result (on Snow Leopard), is that it is indeed NUL terminated.
 */

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mach-o/dyld.h>

int
main(void)
{
    uint32_t size = 0;
    char *buf;
    int r;

    r = _NSGetExecutablePath(NULL, &size);

    printf("Returned: %d. Buffer size required: %" PRId32 "\n", r, size);

    buf = malloc(size);
    memset(buf, -1, sizeof buf);

    r = _NSGetExecutablePath(buf, &size);
    printf("Returned: %d\n", r);

    if (r == 0 && buf[size - 1] == '\0') {
        printf("Size includes NUL terminator.\n");
        printf("Path length: %ld\n", strlen(buf));
        printf("Executable path: %s\n", buf);
    } else {
        printf("Size does not include NUL terminate.\n");
    }

}
