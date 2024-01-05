#include <stdio.h>
#include <string.h>
#include "index_sse2.h"
#include "index_sse4.h"

int main() {
    const char *l = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum sed eros fringilla, porttitor erat sed, tempus quam. Vivamus vitae convallis sem, et rutrum arcu. Fusce eu vehicula diam. Nulla pulvinar fermentum lacus. Nulla orci leo, auctor nec nisl eget, aliquam consequat orci. Donec ultrices laoreet metus, eu auctor sapien sollicitudin eget. In ornare molestie ullamcorper. Donec ac purus nec leo placerat tincidunt. Phasellus sed enim odio. Nam erat nisl, placerat sit amet ultrices in, vulputate eu est. In vestibulum fringilla mauris, non tincidunt diam gravida vel. Proin est nisi, elementum sed risus vel, porttitor porttitor elit!";
    const char *ss = "!";
    const char *ss1 = "purus";
    const char *ss2 = "vestibulum";
    const char *ss3 = "vestibulum fringilla mauris";
    printf("sse2: %d\n", index_sse2(l, strlen(l), ss, strlen(ss)));
    printf("sse2: %d\n", index_sse2(l, strlen(l), ss1, strlen(ss1)));
    printf("sse2: %d\n", index_sse2(l, strlen(l), ss2, strlen(ss2)));
    printf("sse2: %d\n", index_sse2(l, strlen(l), ss3, strlen(ss3)));

    printf("sse4: %d\n", index_sse4(l, strlen(l), ss, strlen(ss)));
    printf("sse4: %d\n", index_sse4(l, strlen(l), ss1, strlen(ss1)));
    printf("sse4: %d\n", index_sse4(l, strlen(l), ss2, strlen(ss2)));
    printf("sse4: %d\n", index_sse4(l, strlen(l), ss3, strlen(ss3)));
    return 0;
}
