#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// 'move infile outfile' is equivalent to 'cat infile > outfile'

#define BUF_SIZE 1024

int move(char* infile, char* outfile) {
    FILE* in = fopen(infile, "r");
    if (!in) {
        perror("Can't open infile");
        return -1;
    }

    FILE* out = fopen(outfile, "w");
    if (!out) {
        perror("Can't open outfile");
        return -1;
    }
    char* buf = (char*) malloc(BUF_SIZE * sizeof(char));
    if (buf == NULL) {
        perror("Allocation error");
        fclose(out);
        remove(outfile);
        return -1;
    }
    // buf check
    size_t count;
    while (!feof(in)) {
        // check read/write operations
        count = fread(buf, sizeof(char), BUF_SIZE, in);
        // printf("%ld %d\n", count, feof(in));
        if (count != BUF_SIZE && !feof(in)) {
            errno = EAGAIN;
            perror("Can't read from infile");
            fclose(out);
            remove(outfile);
            return -1;
        }
        int written = fwrite(buf, sizeof(char), count, out);
        if (count != written) {
            errno = EAGAIN;
            perror("Can't write to outfile");
            fclose(out);
            remove(outfile);
            return -1;
        }
    }
    // check close correctness
    int ret;
    ret = fclose(in);
    if (ret) {
        perror("Can't close infile");
        fclose(out);
        remove(outfile);
        return -1;
    }
    ret = fclose(out);
    if (ret) {
        perror("Can't close outfile");
        remove(outfile);
        return -1;
    }
    free(buf);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        errno = EINVAL;
        perror("move accepts exactly 2 arguments");
        return -1;
    }

    int ret;
    ret = move(argv[1], argv[2]);

    // if operation ends succesfully -- remove infile
    if (!ret) {
        if (remove(argv[1])) {
            // don't remove outfile to save moved text
            perror("Can't remove infile");
            return -1;
        }
    }
    return 0;
}

