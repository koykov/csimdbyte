#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "index_sse2.h"
#include "index_sse4.h"
#include "index_avx2.h"

struct stage_t {
    char *name;
    int idx;
    char *body;
    char *needle;
    int res;
};

int64_t len(const char *s) {
    return (int64_t)strlen(s);
}

int main(void) {
    struct stage_t *stg;
    stg = calloc(1000, sizeof(struct stage_t));
    int stgc = 0;

    DIR *d;
    struct dirent *dir;
    d = opendir("../testdata");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0 || strstr(dir->d_name, ".txt") != NULL) {
                continue;
            }
            printf("%s\n", dir->d_name); // todo parse stages

            FILE *fp;
            char *line = NULL;
            size_t len = 0;
            ssize_t n;

            char buf[1000];
            strcpy(buf, "../testdata/");
            strcat(buf, dir->d_name);
            fp = fopen(buf, "r");
            if (fp == NULL) continue;

            while ((n = getline(&line, &len, fp)) != -1) {
                char *left = strtok(line, "#");
                char *right = strtok(NULL, "#");
                printf("%s - %s\n", left, right);
            }

            fclose(fp);
            if (line)
                free(line);
        }
        closedir(d);
    }

    free(stg);
    return 0;

    const char *l = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum sed eros fringilla, porttitor erat sed, tempus quam. Vivamus vitae convallis sem, et rutrum arcu. Fusce eu vehicula diam. Nulla pulvinar fermentum lacus. Nulla orci leo, auctor nec nisl eget, aliquam consequat orci. Donec ultrices laoreet metus, eu auctor sapien sollicitudin eget. In ornare molestie ullamcorper. Donec ac purus nec leo placerat tincidunt. Phasellus sed enim odio. Nam erat nisl, placerat sit amet ultrices in, vulputate eu est. In vestibulum fringilla mauris, non tincidunt diam gravida vel. Proin est nisi, elementum sed risus vel, porttitor porttitor elit!";
    const char *ss = "!";
    const char *ss1 = "purus";
    const char *ss2 = "vestibulum";
    const char *ss3 = "vestibulum fringilla mauris";
    const char *ss4 = "erat lorem iaculis tellus, malesuada rhoncus augue ipsum ac nunc";
    printf("sse2: %ld\n", index_sse2(l, len(l), ss, len(ss)));
    printf("sse2: %ld\n", index_sse2(l, len(l), ss1, len(ss1)));
    printf("sse2: %ld\n", index_sse2(l, len(l), ss2, len(ss2)));
    printf("sse2: %ld\n", index_sse2(l, len(l), ss3, len(ss3)));
    printf("sse2: %ld\n", index_sse2(l, len(l), ss4, len(ss4)));

    printf("sse4: %ld\n", index_sse4(l, len(l), ss, len(ss)));
    printf("sse4: %ld\n", index_sse4(l, len(l), ss1, len(ss1)));
    printf("sse4: %ld\n", index_sse4(l, len(l), ss2, len(ss2)));
    printf("sse4: %ld\n", index_sse4(l, len(l), ss3, len(ss3)));
    printf("sse4: %ld\n", index_sse4(l, len(l), ss4, len(ss4)));

    printf("avx2: %ld\n", index_avx2(l, len(l), ss, len(ss)));
    printf("avx2: %ld\n", index_avx2(l, len(l), ss1, len(ss1)));
    printf("avx2: %ld\n", index_avx2(l, len(l), ss2, len(ss2)));
    printf("avx2: %ld\n", index_avx2(l, len(l), ss3, len(ss3)));
    printf("avx2: %ld\n", index_avx2(l, len(l), ss4, len(ss4)));
    return 0;
}
