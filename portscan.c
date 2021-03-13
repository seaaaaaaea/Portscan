#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdbool.h>


#define PORTSTART 1
#define PORTEND 65535


void usage();
int connect_soket();
bool portscan(char *host, int port);


int main(int argc, char *argv[])
{
    int opt;
    int port;
    char *host;

    /* Port specification */
    bool f_port = false;

    /* get commandline */
    if (argc < 2)
    {
        usage();
    } 

    host = strdup(argv[1]);

    while((opt = getopt(argc, argv, "h:p:")) != -1)
    {
        switch(opt)
        {
            case 'h':
                host = strdup(optarg);
                break;
            case 'p':
                port = atoi(optarg);
                f_port = true;
                break;
            case '?':
            default:
                usage();
                break;
        }
    }

    printf("Starting port scan...\n\n");

    if(f_port)
    {
        if(portscan(host, port))
        {
            printf("open port : %5d\n", port);
        }
    } else
    {
        for(int i = PORTSTART; i <= PORTEND; i++)
        {
            if(portscan(host, i))
            {
                printf("open port : %5d\n", i);
            }

        }
    }

    return 0;
}

void usage()
{
    printf("how to use\n");
    printf("options:\n");
    printf("    h : host  IP address\n");
    printf("    p : port number to know which open or not\n");
    printf("Please contact to know about this program -> xxxxxx@xxxx.xx\n");

    exit(EXIT_FAILURE);
}


bool portscan(char *host, int port)
{
    int ret;
    int sock;

    struct sockaddr_in sin;
    memset(&sin, 0x00, sizeof(sin));

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        printf("failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    /* 接続先情報 */
    sin.sin_family =  AF_INET;
    sin.sin_addr.s_addr = inet_addr(host);
    sin.sin_port = htons(port);


    if((ret = connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) != -1)
    {
        close(sock);
        
        return true;
    }
    close(sock);

    return false;
}


