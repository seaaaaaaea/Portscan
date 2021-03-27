/*
 学習のためポートスキャン作成
入力判定やコマンドライン引数処理はまだまだ...
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdbool.h>

#define VERSION "1.0.0.1"

#define PORTSTART 1
#define PORTEND 65535


void version();
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
    while((opt = getopt(argc, argv, "vh:p:")) != -1)
    {
        switch(opt)
        {
            case 'v':
                version();
                exit(EXIT_SUCCESS);
                break;
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

    if (optind < argc) {
        host = strdup(argv[optind]);
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


void version()
{
    fprintf(stdout, "version %s\n", VERSION);
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


