#include<stdio.h>
#include<string.h>

int main(){

	FILE *fp;
	char IP[20];
	char catFile[] = "cat block.txt | grep ";
	int status;

	fp = fopen("block.txt", "w");
	fprintf(fp, "List of blocked IP(s)\n");
	fclose(fp);

	printf("Enter the IP: ");
	scanf("%s", IP);

	strcat(catFile, IP);
	status = system(catFile);

	if(status != 0){
		fp = fopen("block.txt", "a");
		fprintf(fp, "%s\n", IP);
		fclose(fp);
	}else{
		printf("Nothing to do!!!!\n");
	}


	return 0;
}
