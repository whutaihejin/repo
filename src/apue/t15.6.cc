#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

#define DEFAULT_PAGER "/bin/more"
#define MAXLINE 1024

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage t15.6 <file pathname>\n"), exit(1);
    }
    int fd[2];
    pid_t pid;
    char* buf[MAXLINE];
    FILE *fp;
    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("can't open %s\n", argv[1]), exit(1);
    }
    if (pipe(fd) < 0) {
        printf("pipe error\n"), exit(1);
    }
    if ((pid = fork()) < 0) {
        printf("fork error\n"), exit(1);
    } else if (pid > 0) { // parent
        close(fd[0]);
        while (fgets(buf, MAXLINE, fp) != NULL) {
            int n = strlen(buf);
            if (write(fd[1], buf, n) != n) {
                printf("write error\n");
            }
        }
        if (ferror(fp)) {
            printf("fgets error\n");
        }
        close(fd[1]);
        if (waitpid(pid, NULL, 0) < 0) {
            printf("waitpid error\n");
        }
    } else { // child
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {
            printf("dup2 error to stdin\n");
        }
        close(fd[0]);
        const char *pager, *argument;
        if ((pager = getenv("pager")) == NULL) {
            pager = DEFAULT_PAGER;
        } 
        if ((argument = strrchr(pager, '/')) != NULL) {
            argument++;
        } else {
            argument = pager;
        }
        if (execl(pager, argument, NULL) < 0) {
            printf("execl error for %s\n", pager), exit(1);
        }
    }
    return 0;
}
