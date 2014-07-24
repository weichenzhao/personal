#include "../csapp.h"
void command(void);

int main(int argc, char **argv) 
{
    int listenfd, connfd, port;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    fd_set read_set, ready_set;

    /*if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }
    port = atoi(argv[1]);
    listenfd = Open_listenfd(port);  //line:conc:select:openlistenfd
    */
    FD_ZERO(&read_set);              /* Clear read set */ //line:conc:select:clearreadset
    FD_SET(STDIN_FILENO, &read_set); /* Add stdin to read set */ //line:conc:select:addstdin
    //FD_SET(listenfd, &read_set);     /* Add listenfd to read set */ //line:conc:select:addlistenfd
    while (1) {
	ready_set = read_set;
	Select(listenfd+1, &ready_set, NULL, NULL, NULL); //line:conc:select:select
	if (FD_ISSET(STDIN_FILENO, &ready_set)) //line:conc:select:stdinready
	    command(); /* Read command line from stdin */
    }
}

void command(void) {
    char buf[MAXLINE];
    if (!Fgets(buf, MAXLINE, stdin))
	exit(0); /* EOF */
    printf("%s", buf); /* Process the input command */
}
