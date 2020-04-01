#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define swab32(x) \
({ \
        uint32_t __x = (x); \
                ((uint32_t)( \
                (((uint32_t)(__x) & (uint32_t)0x000000ffUL) << 24) | \
                (((uint32_t)(__x) & (uint32_t)0x0000ff00UL) <<  8) | \
                (((uint32_t)(__x) & (uint32_t)0x00ff0000UL) >>  8) | \
                (((uint32_t)(__x) & (uint32_t)0xff000000UL) >> 24) )); \
})

int main (int argc, char **argv) {
        if (argc != 2) {
                printf("Usage: %s [nodeidnumber]\n", argv[0]);
                printf("Example: %s 2130706433\n", argv[0]);
                return(1);
        }
        struct sockaddr_in sa;
        char ip[INET_ADDRSTRLEN];
        uint32_t id[1];

        id[0] = atoi(argv[1]);
        id[1] = id[0] + 0x80000000;

        printf("Note: During the nodeid generation, the first bit of the first byte is masked and cannot be recovered. ");
        printf("The possible IPs are:\n");

        for (int i=0;i<2;i++) {
                sa.sin_addr.s_addr = swab32(id[i]);
                inet_ntop(AF_INET, &(sa.sin_addr), ip, INET_ADDRSTRLEN);
                printf("%u = %s\n", id[i], ip);
        }

}
