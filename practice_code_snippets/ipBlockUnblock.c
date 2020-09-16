#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void ipBlockUnblock(char voiceChoice){
	int v = 0;

	if(voiceChoice == 'y') {
		v = 1;
	}

	int status;

	char commandBlock[] = "firewall-cmd --permanent --add-rich-rule=\"rule family='ipv4' source address='";
	char commandUnblock[] = "firewall-cmd --permanent --remove-rich-rule=\"rule family='ipv4' source address='";
	char IP[20];
	char tail[] = "' reject\"";
	int ipChoice;

	if(voiceChoice == 'y') {
		system("espeak-ng -p 81 -a 55 -s 140 \"Please select an option\"");
	}

	printf("1. Block a particular IP\n");
	printf("2. Unblock a previously blocked IP\n");
	printf("3. Exit\n");


	while(1){
	
	printf("Enter your choice: ");
	scanf("%d", &ipChoice);
		switch(ipChoice){
			case 0:
				if(voiceChoice == 'y'){
					system("espeak-ng -p 81 -a 55 -s 140 \"Thank you\"");
				}
				printf("Thank you !!!");
				exit(EXIT_SUCCESS);
			case 1:
				if(voiceChoice == 'y'){
					system("espeak-ng -p 81 -a 55 -s 140 \"Enter the IP to Block\"");
				}
				printf("Enter the IP to block: ");
				scanf("%s", IP);

				strcat(commandBlock, IP);
				strcat(commandBlock, tail);

				status = system(commandBlock);

				if(status != 0){
					if(voiceChoice == 'y') {
						system("espeak-ng -p 81 -a 55 -s 140 \"Facing an error while blocking this IP\"");
					}
					printf("Error faced during the process !!!!");
				}

				system("firewall-cmd --reload");
				system("firewall-cmd --list-all");
				break;
			case 2:

				if(voiceChoice == 'y'){
					system("espeak-ng -p 81 -a 55 -s 140 \"Enter the IP to UnBlock\"");
				}
				printf("Enter the IP to Unblock: ");
				scanf("%s", IP);

				strcat(commandUnblock, IP);
				strcat(commandUnblock, tail);

				status = system(commandUnblock);

				if(status != 0){
					if(voiceChoice == 'y') {
						system("espeak-ng -p 81 -a 55 -s 140 \"Facing an error while unblocking this IP\"");
					}
					printf("Error faced during the process !!!!");
				}

				system("firewall-cmd --reload");
				system("firewall-cmd --list-all");
				break;
			default:
				printf("Invalid option");
				break;
			}

	}
}

int main(){

	char voiceChoice;
	
	printf("Voice (y/n): ");
	scanf("%c", &voiceChoice);	
	ipBlockUnblock(voiceChoice);


	return 0;
}
