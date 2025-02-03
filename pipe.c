#include <fcntl.h>                                  // file control options
#include <stdio.h>                                  // std in out operations
#include <stdlib.h>                                 // standard library
#include <unistd.h>                                 // linux POSIX
#include <sys/wait.h>                               // linux process mgmt
#include <errno.h>                                  // error conditions

void execute_pipe(int argc, char *argv[]);          // func declaration

int main(int argc, char *argv[])                    // argc is # args
{                                                   // argv is arg vector
    if (argc - 1 < 1) {                             // if there are no args
        perror("no arguments passed");              // then print error
        exit(EINVAL);                               // and terminate program
    }
    
    execute_pipe(argc, argv);                       // else call piping func
    return 0;                                       // and terminate program
}

void execute_pipe(int argc, char *argv[])           // argc is # args
{                                                   // argv is arg vector
    int fd[argc - 2][2];                            // file descriptors
    pid_t pid[argc - 1];                            // processes IDs
    
    for (int i = 0; i < argc - 1; i++) {            // for all but last arg
        if (i < argc - 2 && pipe(fd[i]) == -1) {    // create pipe for fd
            perror("pipe failed");                  // if fail print error
            exit(errno);                            // and exit program.
        }
 
        pid[i] = fork();                            // create a fork
        if (pid[i] == -1) {                         // if fork fails
            perror("fork failed");                  // then print error
            exit(errno);                            // and terminate program
        }

        if (pid[i] == 0) {                          // if child process
            if (i > 0) {                            // if not first arg
                dup2(fd[i - 1][0], 0);              // put fd1 0 in stdin,
            }
            if (i < argc - 2) {                     // if not last arg
                dup2(fd[i][1], 1);                  // put fd 1 in stdout
            }
            
            for (int j = 0; j < argc - 2; j++) {    // for all pipes in child
                close(fd[j][0]);                    // close all reads
                close(fd[j][1]);                    // close all writes
            }

            execlp(argv[i + 1], argv[i + 1],
                                    (char *)NULL);  // if fail to execute
            perror("execlp failed");                // print error
            exit(errno);                            // and terminate program
        }
    }
    
    for (int i = 0; i < argc - 2; i++) {            // close all pipes in parent
        close(fd[i][0]);
        close(fd[i][1]);
    }

    for (int i = 0; i < argc - 1; i++) {            // wait for all child
        int status;
        
        waitpid(pid[i], &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            perror("executing failed");
            exit(WEXITSTATUS(status));
        }
    }
}
