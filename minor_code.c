// while loop in pattern search
// dynamic mem allocation, pointers, structures, searching, pattern matching, regular expression, file handling

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct ipList{
	char *IP;
	int count;
};

void colorRed(){ 
    printf("\033[1;31m"); 
}

void colorReset(){ 
    printf("\033[0m"); 
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

char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
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

void subBanner(void){
	colorCyan();
	printf("          <<<<<    Log Analysis Tool Using Pattern Matching and Regex    >>>>>         \n"); // Pink, Light blue
	printf("\n");
	colorReset();
}

void manualVisualize(char path[], int size, int v){
	
	char line[150];
	struct ipList list[size];
	int i, j;
	FILE *fp;
	int originalCount;

	if(v == 1){
		system("espeak-ng -p 81 -a 55 -s 140 \"Enter the list of I P one by one\"");
	}

	// array initialization
	// O(n) --> n = number of IPs
	for(i = 0; i < size; i++){
		printf("  Enter the IP(# %d): ", i+1);
		list[i].IP = (char *)malloc(20*sizeof(char *));
		scanf("%s", list[i].IP);
		list[i].count = 0;
	}

	// O(n.m) --> n = number of IPs, m ---> length of file
	for(i = 0; i < size; i++){
		fp = fopen(path, "r");
		while(fscanf(fp, "%150[^\n]\n", line) != EOF){
			if(strstr(line, list[i].IP) != NULL){
				list[i].count += 1;
			}
		}
		fclose(fp);
	}

	printf("\n");
	//O(nm) --> n = number of ip, m = occurence of Ip in a particular file / 10
 	for(i = 0; i < size; i++){
		colorYellow();
		printf("%-15s | ", list[i].IP);
		originalCount = list[i].count;
		list[i].count = list[i].count / 10; // scaling
		colorGreen();
		for(j = 1; j <= list[i].count; j++){
			printf("# ");
		}
		colorCyan();
		printf(" %d", originalCount);
		colorReset();
		printf("\n");
	}

	if(v == 1){
		system("espeak-ng -p 81 -a 55 -s 140 \"Result	s displayed\"");
	}

	printf("\n");
	colorRed();
	printf("   Each '#' represents 10 occurences in the log file !!!\n\n");
	colorReset();


}

void visualizeLog(char voiceChoice){

	int whileLoopVariable = 1, choice;
	char path[128];
	int size;
	int v = 0;

	if(voiceChoice == 'y'){
		v = 1;
	}

	printf("  1. Enter IP manually\n");
	printf("  2. Enter a file containing list of IP(s)\n");
	printf("  3. Back to Main\n");

	while(whileLoopVariable){

		if(voiceChoice == 'y'){
        	system("espeak-ng -p 81 -a 55 -s 140 \"Choose an option\"");
    	}

		printf("  Choose an option: ");
		scanf("%d", &choice);

		switch(choice){
			case 1:
				if(voiceChoice == 'y'){
					system("espeak-ng -p 81 -a 55 -s 140 \"Enter the log file to analyze\"");
				}
				printf("  Enter the log file to visualize: ");
				scanf("%s", path);

				if(voiceChoice == 'y'){
					system("espeak-ng -p 81 -a 55 -s 140 \"Enter the number of I P to visualize\"");
				}
				printf("  Enter the number of IP(s) you wish to visualize: ");
				scanf("%d", &size);

				manualVisualize(path, size, v);
				break;

			case 2:
				printf("  Nothing here yet!!!\n");
				break;

			case 3:
				whileLoopVariable = 0;
				break;

			default:
				if(voiceChoice == 'y'){
					system("espeak-ng -p 81 -a 55 -s 140 \"Please select a valid option\"");
				}
				printf("  Invalid Option!!!\n");
				break;
		}

	}

}

int unblockAndDeleteFromFile(char IP[]){

    FILE *fp;
    char line[25];
    int availaible = 0;

    fp = fopen("block.txt","r");
    while(EOF != fscanf(fp, "%25[^\n]\n", line)){
        if(strstr(line , IP) != NULL){
            availaible = 1;
        }
    }
    fclose(fp);

    if(availaible == 1){
        fp = fopen("removeIp.sh", "w");
        fprintf(fp, "#!/bin/bash");
        fprintf(fp, "\nsudo sed -i '/%s/d' ./block.txt", IP);
        fclose(fp);
        system("chmod +x removeIp.sh");
        system("./removeIp.sh");
        system("rm -f removeIp.sh");
        return 0;
    }else{
        printf("\nThe IP is not in the blocked list !!!\n");
        return 1;
    }
}

int blockedAndAddToFile(char IP[]){

    FILE *fp, *fptr;
    char line[25];
    int availaible = 0;
    
    fptr = fopen("block.txt", "a");
    fclose(fptr);

    fp = fopen("block.txt","r");
    while(EOF != fscanf(fp, "%25[^\n]\n", line)){
        if(strstr(line , IP) != NULL){
            availaible = 1;
        }
    }
    fclose(fp);

    if(availaible == 0){
        fp = fopen("block.txt", "a");
        fprintf(fp, "%s\n", IP);
        fclose(fp);
        return 0;
    }else{
        printf("\nIP IS ALREADY BLOCKED, SELECT ANOTHER OPTION IF YOU WANT TO UNBLOCK IT!!\n");
        return 1;
    }

}

void block(char voiceChoice){

    char *command = "firewall-cmd --permanent --add-rich-rule=\"rule family='ipv4' source address='";
    char IP[20];
    char *tail = "' reject\"";
    int status;

    if(voiceChoice == 'y'){
        system("espeak-ng -p 81 -a 55 -s 140 \"Enter the IP to Block\"");
    }
    // Asking for IP
    printf(" Enter the IP to block: ");
    scanf("%s", IP);

    if(blockedAndAddToFile(IP) == 0){
        
        char *s = concat(command, IP);
        char *t = concat(s, tail);

        printf(" Blocking the IP\n");
        colorGreen();
        status = system(t);
        colorReset();

        if(status != 0){
            if(voiceChoice == 'y') {
                system("espeak-ng -p 81 -a 55 -s 140 \"Facing an error while blocking this IP\"");
            }
            printf("Error faced during the process !!!!\n");
        }
        system("firewall-cmd --reload");
        free(s); free(t);
    }

    printf("\n");
}

void unblock(char voiceChoice){

    int status;
    char *command = "firewall-cmd --permanent --remove-rich-rule=\"rule family='ipv4' source address='";
    char IP[20];
	char *tail= "' reject\"";

    if(voiceChoice == 'y'){
        system("espeak-ng -p 81 -a 55 -s 140 \"Enter the IP to UnBlock\"");
    }
    printf(" Enter the IP to Unblock: ");
    scanf("%s", IP);

    if(unblockAndDeleteFromFile(IP) == 0){
        
        char *s = concat(command, IP);
        char *t = concat(s, tail);

        printf(" Unblocking the IP\n");
        colorGreen();
        status = system(t);
        colorReset(); 

        if(status != 0){
            if(voiceChoice == 'y') {
                system("espeak-ng -p 81 -a 55 -s 140 \"Facing an error while unblocking this IP\"");
            }
            printf("Error faced during the process !!!!\n");
        }else{
            system("firewall-cmd --reload");
            free(s); free(t);
        }
    }
    printf("\n");
}

void displayBlockedIP(void){
	
	FILE *fp;
	char line[30];
	int numberofLines = 0;

	fp = fopen("block.txt", "r");
	
	while(EOF != fscanf(fp, "%30[^\n]\n", line)){
		colorRed();
		printf("%s\n" , line);
		numberofLines += 1;
		colorReset();
    }
	
	fclose(fp);

	colorGreen();
	printf("\t\t********* %d line(s) displayed *********\n", numberofLines);
	colorReset();

	return;

}

void ipBlockUnblock(char voiceChoice){

    int status;
	int whileLoopVariable = 1;
    int ipChoice;
	


	while(whileLoopVariable){
        if(voiceChoice == 'y') {
            system("espeak-ng -p 81 -a 55 -s 140 \"Please select an option\"");
        }

        colorYellow();
        printf(" 1. Block a particular IP\n");
        printf(" 2. Unblock a previously blocked IP\n");
		printf(" 3. Display the blocked lists\n");
        printf(" 0. Back To Main\n");

		colorCyan();
		printf(" Enter you choice: ");
		colorReset();
		scanf("%d", &ipChoice);

		switch (ipChoice){
		    case 0:
                whileLoopVariable = 0;
			    break;
            case 1:
                block(voiceChoice);
                break;
            case 2:
                unblock(voiceChoice);
                break;
			case 3:
				if(voiceChoice == 'y'){
					system("espeak-ng -p 81 -a 55 -s 140 \"Displaying blocked IP\"");
				}
				displayBlockedIP();
				if(voiceChoice == 'y'){
					system("sleep 2");					
					system("espeak-ng -p 81 -a 55 -s 140 \"Blocked IPs displayed\"");
				}
				break;
            default:
                printf("\nInvalid Option!!\n");
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
	
	// take the path of log file
	printf("Enter the location of log file: ");
	if(v) system("espeak-ng -p 81 -a 55 -s 140 \"Enter the location of the log file\""); // only run if v is set to true
    scanf("%s", path);

	// CSV file path where it is to be saved
    printf("\nCSV file path: ");
    if(v) system("espeak-ng -p 81 -a 55 -s 140 \"Enter the path of  CSV file\"");    
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
	int numberOfLines = 0;
	// enabling the voice assistant
	if(voiceChoice == 'y') { v = 1; }

	printf("\n");
	printf(" 1. Search with IP\n");
	printf(" 2. Search with Date (DD/Mon/YYYY)\n");
	printf(" 3. Search with HTTP Method\n");
	printf(" 4. Status Code / Response Code\n");
	printf(" 5. Search with page name or others\n");

	if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"enter the choice\""); }

	printf("\n Enter you choice: ");
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
    printf(" Enter the location of log file: ");
    scanf("%s", path);

	// file opened

    fp = fopen(path,"r");

	// O(n), to traverse each line
    while(EOF != fscanf(fp, "%150[^\n]\n", line)){
        if(strstr(line , word) != NULL){
            colorRed();
            printf("> %s\n" , line);
			numberOfLines += 1;
            colorReset();
        }else{
        	continue;
        }
    }

    fclose(fp);
	// file closed after displaying the output

	colorGreen();
	printf("\t\t********* %d line(s) displayed *********\n", numberOfLines);
	colorReset();

	if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"output displayed\""); }

}

int main(void){
	
	// Variable Declaration
	int whileLoopVariable = 1;
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
	

	// take input for choice from above provided options
	while(whileLoopVariable){
		// Display multiple options
		printf("\n\n\n");
		printf("1. To covert log file into CSV file.\n");
		printf("2. To search for a occurence of a word in log file.\n");
		printf("3. Block / Unblock a particular IP using firewall.\n");
		printf("4. Visualize Log Files\n");
		printf("0. Exit program\n");	

		printf("\nSelect an option: ");
		scanf("%d", &choice);

        // call functions for the respective tasks
	  switch(choice){
	    case 0:
	      if(voiceChoice == 'y'){
		  system("espeak-ng -p 81 -a 55 -s 140 \"Thank you\"");
	      }
		  whileLoopVariable = 0;
		  break;
	    case 1:
		  system("clear");
		  subBanner();
          convertToLog(voiceChoice);
	      break;

        case 2:
		  system("clear");
		  subBanner();
          searchForKeyword(voiceChoice);
          break;

	    case 3:
		  system("clear");
		  subBanner();
	      ipBlockUnblock(voiceChoice);
	      break;

		case 4:
		  system("clear");
		  subBanner();
		  visualizeLog(voiceChoice);
		  break;

        default:
	      if(voiceChoice == 'y'){ system("espeak-ng  -p 81 -a 55 -s 140 \"Not a valid option\""); }
          printf("Select a valid option");
          break;    
	  }
	}
	
	colorGreen();
	printf("\n\n\t\tThank you !!!\n");
	colorReset();

	return 0;
}
