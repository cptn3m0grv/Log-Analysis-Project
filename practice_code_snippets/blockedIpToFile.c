#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	char IP[20];
	char line[20];
	char line_two[20];


	printf("Enter the IP: ");
	scanf("%s", IP);

	FILE *fp;
	//FILE *fpw;
/*
	fp = fopen("block.txt", "r");

	while(fscanf(fp, "%20[^\n]\n", line) != EOF){
		while(fscanf(fp, "%20[^\n]\n", line) != EOF){
		
			if(strstr(line, IP) != NULL){
				continue;
			}
			else{
				fpw = fopen("block.txt", "a");
				fprintf(fpw, "%s\n", IP);
				fclose(fpw);
			}
		}
	}

	fclose(fp);
	printf("\n");

*/

	int status;
	char cat[] = "cat block.txt | grep ";
	strcat(cat, IP);
	status = system(cat);
	


	if(status != 0){
		fp = fopen("block.txt", "a");
		fprintf(fp, "%s\n", IP);
		fclose(fp);
	}else{
		printf("The IP is already blocked !!");
	}

	return 0;
}

