#include<stdio.h>
int main(){
	int status = system("espeak-ng -s 140 -p 65 \"Enter the path of log file\"");
	printf("%d\n", status);
	return 0;
}
