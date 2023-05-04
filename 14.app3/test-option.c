// =====================================
// 짧은 옵션용 샘플 코드
//   작성자 : 양상봉
//   작성일 : 
// =====================================

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void usage(char *command) {
    printf( "usage:\n"
            "      %s -d\n"
            "  or  %s -e filename\n"
            "  or  %s -h\n", command, command, command);
}

int main(int argc, char **argv) {
    int opt;
    while( (opt = getopt(argc, argv, "de:h")) != -1 ) {
        switch(opt) {
        case 'd':
            printf(">>> option: d\n");
            break;
        case 'e':
            printf(">>> option: e, %s\n", optarg);
            break;
        case 'h':
            printf(">>> option: h\n");
            usage(argv[0]);

            return EXIT_FAILURE;
        default:
            printf(">>> N.A\n");
            usage(argv[0]);

            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
