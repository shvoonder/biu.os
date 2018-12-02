/**************************************
 * Guy Salman
 * ID: 308491091
 * Course: 83-381-01 (Operating Systems)
 * Practice: 83-381-02 
 **************************************/
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>


void check_Output(char *name, char * input)
{
    int status;
    int fd_in=open(input,O_RDONLY); //opening the input file
    if(fd_in==-1)
    {
        printf("Error....can't open argv[2]");
        exit (-1);
    }
    int fd_out = open("outFile.txt", O_CREAT | O_WRONLY | O_TRUNC,0666); //creating temp file
    if (fd_out == -1)
    {
        printf("error with outFile.txt");
        exit(-1);
    } //open failure
    pid_t pid = fork(); //forking for exec
    if (pid == 0)
    { //child
        dup2(fd_in, 0);
        dup2(fd_out, 1);
        execl(name,name, NULL);
    }
    else {wait(&status);} //father waiting until son will change his status
    close(fd_in);
    close(fd_out);
}

int get_Mark(char const *output)
{
    int status;
    int fd;
    pid_t pid;
    fd = open("comp.out", O_RDONLY); 
    if (fd == -1)
     {
        pid = fork(); //we use fork for the execlp command later
        if (pid == 0)// do the execlp from the child
        {
            execlp("gcc", "gcc", "-o", "comp.out", "comp.c", NULL);
        } 
        else
        {
             wait(&status);
        } //father waiting until son will change his status
    }
    else 
    {
        close(fd);
    } //already created
    pid = fork(); //forking for exec
    if (pid == 0)
    {
        execl("comp.out", "comp.out", "outFile.txt", output, NULL);
    } //child
    else 
    {
        wait(&status);
    } //father
    if (WEXITSTATUS(status) == 2)
    {
        return 100;
    } //get return value from comp
    else 
    {
        return 0;
    }
}
int runFile(char *name,int comp_result,char *input,char *output)
{
    int Mark=-1; // Grade flag
    if (comp_result==0)
    {
        return Mark;
    }
    check_Output(name,input); //stdout of .out file
    Mark=get_Mark(output); // this function compare the files and give the Mark
    return Mark;
}
int compileCommand(char *name,int fileLength)
{
    
    int status;
    char nameOut[32];   
    pid_t pid;
    strcpy(nameOut,name); // copying the name of the file to new array to creating out file later.
    strcpy(name+fileLength,".c");//go to the end of the string and add .c
    //printf("%s: ",name);
    strcpy(nameOut+fileLength,".out");//go to the end of the string and add .out
    //printf("%s: ",nameOut);
    int fd= open("gccReport.txt",O_CREAT | O_WRONLY ,0666);
    if (fd==-1)
    {
        printf("error creating logs for gcc"); 
        exit(-1);
    }
    if((pid=fork())==0)
    {
        dup2(fd, 1);//io redirection
        dup2(fd, 2);
    	execlp("gcc","gcc","-o", nameOut, name, NULL); // compile command
    }
    else 
    {
        wait(&status);
        close(fd);
    } // if you are the father wait until the son will done
    int fdNew=open(nameOut,O_RDONLY);
    if(fdNew==-1) //file not open - compile failed
    {
        return 0;
    }
    else
    {
        close(fdNew);
        strcpy(name,nameOut); //update name
        return 1;
    }
}

int main (int argc, char ** argv)
{
    int fd1;
    char ReadingBuffer;
    int ReadFile_Result;
    char NameOfFile [32];
    int nameLength=0;
    int run_result;
    int comp_result;
    if(argc!=4)
    {
        printf("Error..Wrong number of inputs");
        return 0;
    }
    fd1=open(argv[1],O_RDONLY);
    if (fd1==-1)
    {
        printf("Error...Cant open file1");
        return 0;
    }
    ReadFile_Result=read(fd1,&ReadingBuffer,1);
    while (ReadFile_Result!=0)
    {
     do{
		    if (ReadFile_Result==-1)
		    {
		        printf("Error..Cant read file1");
		        close(fd1);
		        return 0;
		    }
		    NameOfFile[nameLength]=ReadingBuffer;
		    nameLength++;
		    ReadFile_Result=read(fd1,&ReadingBuffer,1);
    	}
    	while((int)ReadingBuffer!=10);
		nameLength--;
		NameOfFile[nameLength] = '\0';
		comp_result=compileCommand(NameOfFile,nameLength);
		run_result=runFile(NameOfFile,comp_result,argv[2],argv[3]);
		NameOfFile[nameLength] = '\0'; //deleting the .out that we add in complieCommand
		printf("%s: ",NameOfFile);
		if (run_result == -1)
			{
				printf("Compilation error\n");
			} 
		else 
			{
				printf("%d\n", run_result);
			}
		ReadFile_Result=read(fd1,&ReadingBuffer,1);
		nameLength=0; // get ready for the next name.
   }
}
