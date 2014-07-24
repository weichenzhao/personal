/* 
 * echoserverp.c - A concurrent echo server based on processes
 */
/* $begin echoserverpmain */
#include "../csapp.h"
#include <unistd.h>
void echo(int connfd);
void command(void);
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
    //printf("[PARENT]SIGCHLD catched from %d\n", getpid());
    while (waitpid(-1, 0, WNOHANG) > 0)
	;
    return;
}

int main(int argc, char **argv)
{
    //Signal(SIGCHLD, sigchld_handler);
    struct sigaction sa_usr;
    sa_usr.sa_flags = SA_RESTART;
    sa_usr.sa_handler = sigchld_handler;
    //sigaction(SIGCHLD, &sa_usr, NULL);

    int listenfd, connfd, port, clientlen=sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    struct hostent *hp;
    char *haddrp;
    fd_set read_set, ready_set;

    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }
    port = atoi(argv[1]);

    /* in charge of registing SIGNAL and its HANDLER FUNCTION*/
    Signal(SIGCHLD, sigchld_handler);
    listenfd = Open_listenfd(port);
    pid_t  pid;

    FD_ZERO(&read_set);              /* Clear read set */ //line:conc:select:clearreadset
    FD_SET(STDIN_FILENO, &read_set); /* Add stdin to read set */ //line:conc:select:addstdin
    FD_SET(listenfd, &read_set);     /* Add listenfd to read set */ //line:conc:select:addlistenfd
    printf("[PARENT]process id: %d\n", getpid());

    int rc = 0;

    while (1) {
        ready_set = read_set;
        /* when waiting in `select()` function, if a child process ends, `select()` will be interupted
         * by the `SIGCHLD` signal. Thus, it will raise "Interrupted system call" error.
         * this error should be ignored or handled by `SIGCHLD` handler function.
         *
         * From this problem, it can be seen that `select()` (also `poll()`) has a flaw dealing with signals.
         * change `Select` to `pselect` perfectly solved this problem (that's why `pselect` was created).
         */
        printf("[PARENT]starting select\n");
        //       max fd  |  read set | write fd | error fd | timeout
        rc = pselect(listenfd+1, &ready_set,   NULL,    NULL,    NULL, NULL); //line:conc:select:select
        printf("[-------------]select get a input: stdin,%d  1,%d  2,%d  3,%d  4,%d  lfd,%d\n", FD_ISSET(0, &ready_set), FD_ISSET(1, &ready_set), FD_ISSET(2, &ready_set), FD_ISSET(3, &ready_set), FD_ISSET(4, &ready_set), FD_ISSET(listenfd, &ready_set));
        printf("%d, %d\n", listenfd, rc);
        /*select & pselect returns number of ready fd(s). If -1 then error.
         *in that situation, ready_fd will not be changed, thus each of the if
         *brance can be reached. Because the `Fget` call in `command` function
         *blocks this program, you will see the program stucked at that line
         *until you input something in cmd line.
         */
        if (rc > 0)
        {
            if (FD_ISSET(STDIN_FILENO, &ready_set)) //line:conc:select:stdinready
                {printf("in command circle\n");
                 command();} /* Read command line from stdin */
            if (FD_ISSET(listenfd, &ready_set)) { //line:conc:select:listenfdready
                connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
                printf("[PARNET]get a new connection\n");
                hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
                                   sizeof(clientaddr.sin_addr.s_addr), AF_INET);
                haddrp = inet_ntoa(clientaddr.sin_addr);
	        if (Fork() == 0 && printf("[CHILD]server connected to %s (%s:%d)\n", hp->h_name, haddrp, clientaddr.sin_port)) { 
                    /* pid determins its functionality
                     * if pid == 0, then this is a child process
                     * then close the listening port(not accepting connections)
                     * and keeps the socket with the connecting machine
                     */
                    printf("[CHILD]process id: %d\n", getpid());
    	            Close(listenfd); /* Child closes its listening socket */
                    //printf("%d\n",connfd);
	            echo(connfd);    /* Child services client */
	            Close(connfd);   /* Child closes connection with client */
                    printf("[CHILD]# %d process exiting\n", getpid());
                    exit(0);         /* Child exits */
                }
	    Close(connfd); /* Parent closes connected socket (important!) */
	    }
            printf("End of a select turn\n");
        }
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

void command(void) {
    printf("in command function");
    char buf[MAXLINE];
    if (!Fgets(buf, MAXLINE, stdin))
        exit(0); /* EOF */
    printf("[CMD]: %s", buf); /* Process the input command */
    return;
}
/* $end echoserverpmain */
