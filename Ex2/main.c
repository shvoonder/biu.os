#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char* argv[]) {
    int i, status, compVal;
    pid_t pid;
    int fd1 = open (argv[1], O_RDONLY);
    int fd2 = open (argv[2], O_RDONLY);
    int fdOutput;
    int fdErrors;
    char letter[1];
    char name[50];
    char nameC[50];
    char nameOut[50];
    char tempName[50];

    if (fd1<0 || fd2<0) {
        close(fd1);
        close(fd2);
        return 0;
    }

    int rd1 = read(fd1, letter, 1);
    while (rd1>0){
        i=0;
        while (letter[0] != '\n'){
            name[i] = letter[0];
            rd1 = read(fd1, letter, 1);
            i++;
        }
        if (name[0] == '\n'){
            close(fd1);
            close(fd2);
            return 0;
        }
        rd1 = read(fd1, letter, 1);
        name[i] = '\0';
        strcpy (nameOut, name);
        strcpy(nameC, name);
        nameOut[i]='.';
        nameOut[i+1]='o';
        nameOut[i+2]='u';
        nameOut[i+3]='t';
        nameOut[i+4]='\0';
        nameC[i] = '.';
        nameC[i+1] = 'c';
        nameC[i+2] = '\0';
        fdOutput = open("newOutput.txt", O_RDWR | O_CREAT | O_TRUNC,0666);
        pid = fork();
        if (pid == 0) {
            fdErrors = open("errors.txt", O_RDWR | O_CREAT | O_TRUNC,0666);
            dup2(fdErrors, 2);
            execlp("gcc", "gcc", nameC, "-o", nameOut, NULL);
            close(fdErrors);
        }
        wait(&status);
        if (WEXITSTATUS(status) != 0)
            printf("%s: Compilation error\n", name);
        else{
            pid = fork();
            if (pid == 0) {
                dup2(fd2, 0);
                dup2(fdOutput, 1);
                i=0;
                tempName[0] = '.';
                tempName[1] = '/';
                while (nameOut[i] != '\0') {
                    tempName[i + 2] = nameOut[i];
                    i++;
                }
                tempName[i+2] = '\0';
                execl(tempName, tempName, NULL);
            }
            wait(&status);
            close(fdOutput);
            if (WIFEXITED(status)){
                pid = fork();
                if (pid == 0)
                    execlp("gcc", "gcc", "comp.c", "-o", "comp.out", NULL);
                wait(&status);
                pid = fork();
                if (pid == 0)
                    execl("./comp.out", "./comp.out", "output.txt", "newOutput.txt", NULL);
                wait(&status);
                compVal = WEXITSTATUS(status);
                if (compVal == 1)
                    printf("%s: 0\n", name);
                if (compVal == 2)
                    printf("%s: 100\n", name);
            }
        }
    }
    close(fd1);
    close(fd2);
    return 0;
}