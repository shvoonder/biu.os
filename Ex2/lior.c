#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int n1, n2, option;
	//printf("please enter operation\n");
	//scanf ("%d\n%", &option);
	//printf("%d\n%", option);
	//printf("please enter two numbers\n");
	scanf ("%d %d",&n1, &n2);
	//printf("%d %d\n",n1,n2);
	printf("%d\n", n1-n2);
	//wait(5);
	return 0;
}
