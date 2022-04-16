#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFSIZE 1024

//
void file_server(int readfd, int writefd);
//
void client(int readfd, int writefd);

int main() {
    int read_pipe[2];
    int write_pipe[2];

    if(pipe(read_pipe) != 0) {
        printf("pipe error: %s\n", strerror(errno));
        return -1;
    }
    if(pipe(write_pipe) != 0) {
        printf("pipe error: %s\n", strerror(errno));
        return -1;
    }

    pid_t child_pid;
    if ((child_pid = fork()) == 0) {
        close(read_pipe[0]);
        close(write_pipe[1]);
        file_server(write_pipe[0], read_pipe[1]);
        exit(0);
    }

    close(read_pipe[1]);
    close(write_pipe[0]);
    client(read_pipe[0], write_pipe[1]);
    waitpid(child_pid, NULL, 0);
    return 0;
}

void client(int readfd, int writefd) {
    char buf[BUFSIZE];
    printf("enter file pathname:\n");
    fgets(buf, BUFSIZE, stdin);

    int len = strlen(buf);
    if (buf[len - 1] == '\n') {
        --len;
    }
    write(writefd, buf, len);

    while ((len = read(readfd, buf, BUFSIZE)) > 0) {
        write(STDOUT_FILENO, buf, len);
    }
}

void file_server(int readfd, int writefd) {
    char buf[BUFSIZE];
    int len;
    if ((len = read(readfd, buf, BUFSIZE)) > 0) {
        buf[len] = '\0';
    }
    // printf("pathname:%s|\n", buf);
    int fd;
    if ((fd = open(buf, O_RDONLY)) == -1) {
        // open error
        snprintf(buf + len, BUFSIZE - len, " can't open: %s", strerror(errno));
        int n = strlen(buf);
        write(writefd, buf, n);
        return;
    }
    while ((len = read(fd, buf, BUFSIZE)) > 0) {
        write(writefd, buf, len);
    }
    close(fd);
}
