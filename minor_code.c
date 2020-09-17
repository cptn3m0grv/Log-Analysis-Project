#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void colorRed(){ 
    printf("\033[1;31m"); 
}

void colorReset(){ 
    printf("\033[0m;"); 
}

void colorYellow(){ 
    printf("\033[0;33m"); 
}

void colorGreen(){ 
    printf("\033[0;32m"); 
}

void colorCyan(){
	printf("\033[0;36m");
}

void banner(){

	colorYellow();
	printf("***************************************************************************************\n"); // yellow, orange
	printf("***************************************************************************************\n"); // yellow, ornage
	colorGreen();
	printf("\n");
	printf("                                       WELCOME                                         \n"); // Light green
	printf("\n");
	colorCyan();
	printf("          <<<<<    Log Analysis Tool Using Pattern Matching and Regex    >>>>>         \n"); // Pink, Light blue
	printf("\n");
	colorYellow();                                                                    
	printf("***************************************************************************************\n"); //yellow, orange
	printf("***************************************************************************************\n"); // yellow, orange
	colorReset();

}

void ipBlockUnblock(char voiceChoice){

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
		printf("Enter you choice: ");
		scanf("%d", &ipChoice);

		switch (ipChoice){
		case 0:
			if(voiceChoice == 'y'){
            	system("espeak-ng -p 81 -a 55 -s 140 \"Thank you\"");
            }
            printf("Thank you !!!");
            exit(EXIT_SUCCESS);
			break;

		case 1:
			if(voiceChoice == 'y'){
				system("espeak-ng -p 81 -a 55 -s 140 \"Enter the IP to Block\"");
			}
			// Asking for IP
			printf("Enter the IP to block: ");
			scanf("%s", IP);

			strcat(commandBlock, IP);
			strcat(commandBlock, tail);

			printf("Blocking the IP: ");
			colorGreen();
			status = system(commandBlock);
			colorReset();

			if(status != 0){
				if(voiceChoice == 'y') {
					system("espeak-ng -p 81 -a 55 -s 140 \"Facing an error while blocking this IP\"");
				}
				printf("Error faced during the process !!!!");
			}
			
			printf("\nReloading the firewall: ");
			colorGreen();
			system("firewall-cmd --reload");
			colorReset();
			printf("\nDisplaying Firewall Rules--|\n");
			colorGreen();
			system("firewall-cmd --list-all");
			colorReset();
			break;
		
		case 2:
			if(voiceChoice == 'y'){
				system("espeak-ng -p 81 -a 55 -s 140 \"Enter the IP to UnBlock\"");
			}
			printf("Enter the IP to Unblock: ");
			scanf("%s", IP);

			strcat(commandUnblock, IP);
			strcat(commandUnblock, tail);

			printf("Unblocking the IP: ");
			colorGreen();
			status = system(commandUnblock);
			colorReset(); 

			if(status != 0){
				if(voiceChoice == 'y') {
					system("espeak-ng -p 81 -a 55 -s 140 \"Facing an error while unblocking this IP\"");
				}
				printf("Error faced during the process !!!!");
			}

			printf("\nReloading the firewall: ");
			colorGreen();
			system("firewall-cmd --reload");
			colorReset();
			printf("\nDisplaying Firewall Rules--|\n");
			colorGreen();
			system("firewall-cmd --list-all");
			colorReset();
			break;

		default:
			printf("Invalid Option!!");
			break;
		}
	}

}


void convertToLog(char voiceChoice){
	
	// Variable declaration
	
	FILE *fp;                 // file pointer
    char path[128];           // variable to take log file path
	char logName[128];        // variable to take input of path and name of csv file
	int v = 0;                // variable for enabling/diabling voice assistance

	if(voiceChoice == 'y') v = 1;	// if the voiceChoice argument was true then usage of voice assistant will be enabled

	if(v) system("espeak-ng -p 81 -a 55 -s 140 \"Enter the location of the log file\""); // only run if v is set to true
	
	// take the path of log file
	printf("Enter the location of log file: ");
    scanf("%s", path);

	if(v) system("espeak-ng -p 81 -a 55 -s 140 \"Enter the path of  CSV file\"");

	// CSV file path where it is to be saved
    printf("\nCSV file path: ");
    scanf("%s", logName);
        
	// write a script to convert log file into CSV
	fp = fopen("script.sh", "w");
        
	fprintf(fp, "#!/bin/bash");
    fprintf(fp, "\nsudo tac %s | awk -F' ' '{print $1\", \"$2\", \"$3\", \"$4\", \"$5\", \"$6\", \"$7\", \"$8\", \"$9\", \"$10}' > %s", path, logName);
    fprintf(fp, "\nsudo sed -i 's/-/\b\b/g' %s", logName);
    fprintf(fp, "\nsudo sed -i 's|[[]||g' %s", logName);
    fprintf(fp, "\nsudo sed -i 's|[]]||g' %s", logName);
    fprintf(fp, "\n\nsudo sed -i 's|[\"]||g' %s\n", logName);
    
	fclose(fp);
	// file pointer closed
        
	// making the script executable and run it
	system("sudo chmod +x /root/minor/script.sh");
    system("sudo ./script.sh");
        
	colorGreen();
	printf("\nCSV file created at %s\n", logName);
	colorReset();

    if(v) system("espeak-ng -p 81 -a 55 -s 140 \"C S V file created\"");
	
	// deleting of script, since it is meant to be abstract
	system("rm script.sh -f");
}

void searchForKeyword(char voiceChoice){   

    // Variable declarationa
	int v = 0;
	FILE *fp;
	char * s;
    char line[150];
    char word[100];
	char path[128];
	int swChoice;
	// enabling the voice assistant
	if(voiceChoice == 'y') { v = 1; }


	printf(" 1. Search with IP\n");
	printf(" 2. Search with Date (DD/Mon/YYYY)\n");
	printf(" 3. Search with HTTP Method\n");
	printf(" 4. Status Code / Response Code\n");
	printf(" 5. Search with page name or others\n");

	if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"enter the choice\""); }

	printf("\n Enter the choice: ");
	scanf("%d", &swChoice);

	// ask for the word to be searched in a file
	if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"enter the pattern to be searched\""); }

	switch (swChoice){
		case 1:
			printf("\n Enter the IP: ");
			scanf("%s", word);
			break;
		case 2:
			printf("\n Enter the Date [Ex. 04/Nov/2000]: ");
			scanf("%s", word);
			break;
		case 3:
			s = word;
			printf("\n Enter the HTTP method: ");
			scanf("%s", word);
			while(*s){
				*s = (*s > 'a' && *s <= 'z') ? *s-32 : *s;
				s++;
			}
			break;
		case 4:
			printf("\n Enter the status code/ response code: ");
			scanf("%s", word);
			break;
		case 5:
			printf("\n Others(Case sensitive): ");
			scanf("%s", word);
			break;
		default:
			printf("Invalid Option!!!");
			break;
	}

    // ask for the path of file in which the word is to be searched
	if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"enter the location of file\""); }
    printf("Enter the location of log file: ");
    scanf("%s", path);

	// file opened

    fp = fopen(path,"r");

    while(EOF != fscanf(fp, "%150[^\n]\n", line)){
        if(strstr(line , word) != NULL){
            colorRed();
            printf("\b> %s\n" , line);
            colorReset();
        }else{
        continue;
        }
    }

    fclose(fp);
	// file closed after displaying the output
	if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"output displayed\""); }

}

int main(){
	
	// Variable Declaration

	char voiceChoice;
	int choice;

	// clear the terminal before executing the code
	system("clear");
	
	// TUI 
	banner();
	
	// takes input for voice assistant, needed or not
	printf("Do you need voice assistance while executing this program (y/n):  ");
	scanf("%c", &voiceChoice);

	if(voiceChoice != 'y' && voiceChoice != 'n'){
		printf("Invalid Input!!!");
	}
	
	// Display multiple options
	printf("\n\n\n");
	printf("1. To covert log file into CSV file.\n");
    printf("2. To search for a occurence of a word in log file.\n");
	printf("3. Block / Unblock a particular IP using firewall.\n");
	printf("0. Exit program\n");

	// take input for choice from above provided options
	while(1){
      printf("\nEnter your choice: ");
      scanf("%d", &choice);

        // call functions for the respective tasks
	  switch(choice){
	    case 0:
	      if(voiceChoice == 'y'){
		  system("espeak-ng -p 81 -a 55 -s 140 \"Thank you\"");
	      }
	      exit(EXIT_SUCCESS);

	    case 1:
          convertToLog(voiceChoice);
	      break;

        case 2:
          searchForKeyword(voiceChoice);
          break;

	    case 3:
	      ipBlockUnblock(voiceChoice);
	      break;

        default:
	      if(voiceChoice == 'y'){ system("espeak-ng  -p 81 -a 55 -s 140 \"Not a valid option\""); }
          printf("Select a valid option");
          break;    
	  }
	}
        

	return 0;
}
