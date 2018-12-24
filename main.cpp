#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "AsciiTransfer.h"

AsciiTransfer t;

void usage() {
    puts("usage: axfer -r");
    puts("       axfer -s file");
}

int main(int argc, char **argv) {
    char file[1024];
    int status = 0;

    if (argc >= 2) {
        if (!strcmp("-r", argv[1])) {
            if (argc == 2) {
                t.recv();
            } else {
                status = -1;
                usage();
            }
        } else if (!strcmp("-s", argv[1])) {
            if (argc == 3) {
                t.send(argv[2]);
            } else {
                status = -1;
                usage();
            }
        }
    } else {
        status = -1;
        usage();
    }

    return status;
}
