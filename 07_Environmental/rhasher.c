#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "rhash.h"

// gcc -o rhasher rhasher.c  -L./RHash-master/librhash/ -lrhash

int main(int argc, char* argv[]) {
    // #ifdef READLINE
    //     printf("readline\n");
    // #else
    //     printf("nothing\n");
    // #endif
    char* line = NULL;
    size_t len = 0;
    ssize_t nread;

    char *hash_name, *hash_data;
    unsigned char digest[64];
    char output[130];
    unsigned hash_id;

    rhash_library_init();

    while ((nread = getline(&line, &len, stdin)) != -1) {
        hash_name = strtok(line, " ");
        hash_data = strtok(NULL, " ");
        if (!strcasecmp(hash_name, "MD5")) {
            hash_id = RHASH_MD5;
        } else if (!strcasecmp(hash_name, "SHA1")) {
            hash_id = RHASH_SHA1;
        } else if (!strcasecmp(hash_name, "TTH")) {
            hash_id = RHASH_TTH;
        } else {
            fprintf(stderr, "Unknown hash algorithm\n");
            continue;
        }

        int res;
        if (hash_data[0] == '"') {
            // hash string
            res = rhash_msg(hash_id, hash_data, strlen(hash_data), digest);
            if (res < 0) {
                fprintf(stderr, "Message digest calculation error\n");
                continue;
            }
        } else {
            // hash file
            res = rhash_file(hash_id, hash_data, digest);
            if (res < 0) {
                fprintf(stderr, "LibRHash error: %s: %s\n",
                        hash_data, strerror(errno));
                continue;
            }

        }

        unsigned output_radix;
        if ('A' <= hash_name[0] && hash_name[0] <= 'Z') {
            // output as hex
            output_radix = RHPR_HEX;
        } else {
            // output as base64
            output_radix = RHPR_BASE64;
        }
        rhash_print_bytes(output, digest,
                          rhash_get_digest_size(hash_id), output_radix);
        printf("%s %s\n", rhash_get_name(hash_id), output);
    }
    return 0;
}