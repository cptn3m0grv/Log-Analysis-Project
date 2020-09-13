#include<stdio.h>
#include<string.h>

void colorRed() { printf("\033[1;31m"); }

void colorReset() { printf("\033[0m;"); }

void colorYellow() { printf("\033[0;33m"); }

void colorGreen() { printf("\033[0;32m"); }

void convertToLog(char voiceChoice){
	
	// Variable declaration
	
	FILE *fp;                 // file pointer
        char path[128];           // variable to take log file path
	char logName[128];        // variable to take input of path and name of csv file
	int v = 0;                // variable for enabling/diabling voice assistance

	if(voiceChoice == 'y') v = 1;	// if the voiceChoice argument was true then usage of voice assistant will be enabled

	if(v) system("espeak-ng \"Enter the location of the log file\""); // only run if v is set to true
	
	// take the path of log file
	printf("Enter the location of log file: ");
        scanf("%s", path);

	if(v) system("espeak-ng \"Enter the path of  CSV file\"");

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
	printf("\nCSV file created at /root/minor/%s\n", logName);
	colorReset();

        if(v) system("espeak-ng \"C S V file create\"");
	
	// deleting of script, since it is meant to be abstract
	system("rm script.sh -f");
}

void searchForKeyword(char voiceChoice){   

        // Variable declaration
	int v = 0;
	FILE *fp;
        char line[150];
        char word[50];
	char path[128];

	// enabling the voice assistant
	if(voiceChoice == 'y') { v = 1; }

	// ask for the word to be searched in a file
	if(v) { system("espeak-ng \"enter the pattern to be searched\""); }
        printf("Enter the pattern: ");
        scanf("%s", word);

        // ask for the path of file in which the word is to be searched
	if(v) { system("espeak-ng \"enter the location of file\""); }
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
	if(v) { system("espeak-ng \"output displayed\""); }

}

int main(){
	
	// Variable Declaration

	char voiceChoice;
	int choice;

	// clear the terminal before executing the code
	system("clear");
	
	// TUI 
	colorYellow();
	printf("#######################");
	colorRed();
	printf("  WELCOME  ");
	colorYellow();
	printf("#######################");
	colorReset();
	printf("\n");
	printf("Log Analysis using Regular Expression and Pattern matching/searching algorithms\n\n\n");
	
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
	
	// take input for choice from above provided options
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // call functions for the respective tasks
	switch(choice){
	  case 1:
            convertToLog(voiceChoice);
	    break;

          case 2:
            searchForKeyword(voiceChoice);
            break;

          default:
	    if(voiceChoice == 'y'){ system("espeak-ng \"Not a valid option\""); }
            printf("Select a valid option");
            break;    
	}
        
	// speak thank you if voice assistance was provided
	if(voiceChoice == 'y'){
		system("espeak-ng \"Thank you\"");
	}

	return 0;
}
