/* 
 * echoserverp.c - A concurrent echo server based on processes
 */
/* $begin echoserverpmain */
#include "../csapp.h"
void echo(int connfd);

/*
 * zombie killer for child process
 *
 * the SIGCHILD processor is a block function, which means when
 * this function runs, other SIGCHILD signal cannot be handled.
 * as UNIX system do not put signals in queue, thus SIGCHILD
 * handlers must be ready to kill multiple zombies.
 */
void sigchld_handler(int sig) 
{
    /* pid_t waitpid(pid_t pid, int *status, int options);
     * to wait for state changes in a child of the calling process
     * and obtain information about the child whose state has changed.
     *
     * when reciving a SIGCHILD signal, there might be more than one
     * process ends. Thus run waitpid() until it fails, and each time
     * it clean one of its child process. func wait() also can be used
     * however it's a blocking function
     *
     * WNOHANG - return immediately if no child has exited.
     * -1 - meaning wait for any child process.
     * 0 - NULL, do nothing
     *
     * If WNOHANG was specified in options and there were no children
     * in a waitable state, then waitid() returns 0 immediately
     * on success, returns the process ID of the child whose state has 
     * changed
     */
    while (waitpid(-1, 0, WNOHANG) > 0)
	;
    return;
}

int main(int argc, char **argv) 
{
    int listenfd, connfd, port, clientlen=sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    struct hostent *hp;
    char *haddrp;

    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }
    port = atoi(argv[1]);

    /* in charge of registing SIGNAL and its HANDLER FUNCTION*/
    Signal(SIGCHLD, sigchld_handler);
    listenfd = Open_listenfd(port);
    pid_t  pid;

    while (1) {
        printf("[PARENT]wait here\n");
	connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
        printf("[PARNET]get a new connection\n");
        hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
                           sizeof(clientaddr.sin_addr.s_addr), AF_INET);
        haddrp = inet_ntoa(clientaddr.sin_addr);
	if (Fork() == 0 && printf("[CHILD]server connected to %s (%s)\n", hp->h_name, haddrp)) { 
            /* pid determins its functionality
             * if pid == 0, then this is a child process
             * then close the listening port(not accepting connections)
             * and keeps the socket with the connecting machine
             */
            //printf("this is the child process: %d\n", getpid());
	    Close(listenfd); /* Child closes its listening socket */
	    echo(connfd);    /* Child services client */
	    Close(connfd);   /* Child closes connection with client */
            printf("[CHILD]exiting process\n");
	    exit(0);         /* Child exits */
	}
	Close(connfd); /* Parent closes connected socket (important!) */
    }
}

void echo(int connfd)
{
        size_t n;
        char buf[MAXLINE];
        rio_t rio;

        Rio_readinitb(&rio, connfd);
        while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
                printf("server received %d bytes\n", n);
                Rio_writen(connfd, buf, n);
        }
}

/* $end echoserverpmain */
