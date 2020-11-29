// dynamic mem allocation, pointers, structures, searching, pattern matching, regular expression, file handling
// name of algo --> linear search
// techniques used
// time based --> smartly 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
*	Structure to keep count of occurences of IP in the log file
*	and then to create a graph using it.
*/

struct ipList{
	char *IP;
	int count;
};

/*
*	The following 5 functions change the color of output to
*	red, yellow, green, and cyan .
*	The fifth function is to reset the color back to default.
*/

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

/*
*	The following function is to concatenate two strings
*/

char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

/*
*	The following function is to print the intro banner of the program
*/

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

	return;

}

/*
*	The following function prints a banner whenever a new options is selected
* 	it will also act as a permanent header for the program
*/

void subBanner(void){

	colorCyan();
	printf("          <<<<<    Log Analysis Tool Using Pattern Matching and Regex    >>>>>         \n"); // Pink, Light blue
	printf("\n");
	colorReset();

	return;
}

void manualVisualize(char path[], int size, int v){
	
	char line[150];
	struct ipList list[size];
	int i, j;
	FILE *fp;
	int originalCount;

	/*
	* Check if file exists or not
	*/
	fp = fopen(path, "r");
	if(fp == NULL){
		printf("\n");
		colorRed();
		printf("No Such File Exists, please check the file name again.\n");
		colorReset();
		return;
	}
	fclose(fp);

	/*
	*	This is the option to enable voice assistance.
	*/

	if(v == 1){
		system("espeak-ng -p 81 -a 55 -s 140 \"Enter the list of I P one by one\"");
	}

	// array initialization
	// O(n) --> n = number of IPs

	/*
	*	This for loop will take 'N' IP(s) from user,
	*	the input IP(s) will then be stored in the array of structures
	*/

	for(i = 0; i < size; i++){
		printf("  Enter the IP(# %d): ", i+1);
		list[i].IP = (char *)malloc(20*sizeof(char *));
		scanf("%s", list[i].IP);
		list[i].count = 0;
	}

	// O(n.m) --> n = number of IPs, m ---> length of file

	/*
	*	This for loop will count the number of occurences of each IP stored
	*	in the arrays of structure.
	*	The count will then be stored in the form of a hashmap.
	*/

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

	/*
	*	We will now be printing the graph.
	*	One "#" will be printed for every 10 occurences of the IP.
	*/

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

	return;

}

void visualizeLog(char voiceChoice){

	int whileLoopVariable = 1, choice;
	char path[128];
	int size;
	int v = 0;

	/*
	*	This is the option to enable voice assistance.
	*/

	if(voiceChoice == 'y'){
		v = 1;
	}

	/*
	* displaying menu to select the choice from.
	*/

	printf("  1. Enter IP manually\n");
	// printf("  2. Enter a file containing list of IP(s)\n");
	printf("  0. Back to Main\n");

	/*
	* While loop to run continously until the user stops it.
	* Whenever the user want to go back to main, the value of "whileLoopVariable" is set to 0
	* and the loop stops and the user is redirected to the main menu again.
	*/

	while(whileLoopVariable){

		if(voiceChoice == 'y'){
        	system("espeak-ng -p 81 -a 55 -s 140 \"Choose an option\"");
    	}

		printf("  Choose an option: ");
		scanf("%d", &choice);

		switch(choice){

			case 0:
				whileLoopVariable = 0;
				break;

			case 1:
				/*
				* We would ask for the path of log file here.
				*/

				if(voiceChoice == 'y'){
					system("espeak-ng -p 81 -a 55 -s 140 \"Enter the log file to analyze\"");
				}
				printf("  Enter the log file to visualize: ");
				scanf("%s", path);

				/*
				* We then ask to enter the number of IP(s) he is going to enter later on.
				*/

				if(voiceChoice == 'y'){
					system("espeak-ng -p 81 -a 55 -s 140 \"Enter the number of I P to visualize\"");
				}
				printf("  Enter the number of IP(s) you wish to visualize: ");
				scanf("%d", &size);

				manualVisualize(path, size, v);
				break;

			// case 2:
			// 	printf("  Nothing here yet!!!\n");
			// 	break;


			default:
				if(voiceChoice == 'y'){
					system("espeak-ng -p 81 -a 55 -s 140 \"Please select a valid option\"");
				}
				printf("  Invalid Option!!!\n");
				break;
		}

	}

	return;

}

int unblockAndDeleteFromFile(char IP[]){

    FILE *fp;
    char line[25];
    int availaible = 0;

	/*
	* Here we are scannning the list of blocked IP(s) using linear search
	* and if the IP is in the block list then, the variable availaible will be assigned
	* a value 1(true).
	*/

    fp = fopen("block.txt","r");
    while(EOF != fscanf(fp, "%25[^\n]\n", line)){
        if(strstr(line , IP) != NULL){
            availaible = 1;
        }
    }
    fclose(fp);

	/*
	* In this step we create a script which will delete the unblocked IP from the block list.
	* if the value of variable availaible is set to 0, then user will be prompted.
	*/

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
	
	/*
	* Here we are scannning the list of blocked IP(s) using linear search
	* and if the IP is in the block list then, the variable availaible will be assigned
	* a value 1(true).
	*/

    fp = fopen("block.txt","r");
    while(EOF != fscanf(fp, "%25[^\n]\n", line)){
        if(strstr(line , IP) != NULL){
            availaible = 1;
        }
    }
    fclose(fp);

	/*
	* The Ip will only be blocked if it is not present in the block list
	* otherwise the user will be prompted a message.
	*/

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
        
		/*
		* The string will be concatenated here in order to form a right unix commnand,
		* the function to concatenate strings is already define above.
		*/

        char *s = concat(command, IP);
        char *t = concat(s, tail);

		/*
		* This step will run the command that was formed using concatenating the strings
		* and the status code of the system command is stored in a variable for further
		* use.
		*/

        printf(" Blocking the IP\n");
        colorGreen();
        status = system(t);
        colorReset();

		/*
		* If the status value is not 0, that is if the command was not run successfully,
		* then the user will be prompted the issue.
		*/

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
	return;
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

		/*
		* The string will be concatenated here in order to form a right unix commnand,
		* the function to concatenate strings is already define above.
		*/
        
        char *s = concat(command, IP);
        char *t = concat(s, tail);

		/*
		* This step will run the command that was formed using concatenating the strings
		* and the status code of the system command is stored in a variable for further
		* use.
		*/
		if(voiceChoice == 'y'){
        	system("espeak-ng -p 81 -a 55 -s 140 \"Unblocking the IP\"");
    	}
        printf(" Unblocking the IP...\n");
        colorGreen();
        status = system(t);
        colorReset(); 

		/*
		* If the status value is not 0, that is if the command was not run successfully,
		* then the user will be prompted the issue.
		*/

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
	return;
}

void displayBlockedIP(void){
	
	FILE *fp;
	char line[30];
	int numberofLines = 0;

	fp = fopen("block.txt", "r");

	/*
	* Working of this function is pretty clear, it will display all the IP(s)
	* present in the block list.
	*/
	
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
	

	/*
	* This function will provide the options to the user,
	* to block or unblock the IP(s), and the respective functions will be called.
	*/

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

	return;

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

	/*
	* Check if file exists or not
	*/
	fp = fopen(path, "r");
	if(fp == NULL){
		printf("\n");
		colorRed();
		printf("No Such File Exists, please check the file name again.\n");
		colorReset();
		return;
	}
	fclose(fp);

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

	return;
}

void grepify(char word[], int v, int outToFile){


	char path[128];
	FILE *fp, *out;
	int numberOfLines = 0;
    char line[350];
    char fileName[50];


	// ask for the path of file in which the word is to be searched

    if(outToFile){
		if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"Enter file name\""); }
        printf(" Enter the name of file to be saved in (the file will be overwritten if it already exists): ");
        scanf("%s", fileName);
    }

	if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"enter the location of file\""); }
	printf(" Enter the location of log file: ");
	scanf("%s", path);

	// file opened

	/*
	* Check if file exists or not
	*/
	fp = fopen(path, "r");
	if(fp == NULL){
		printf("\n");
		colorRed();
		printf("No Such File Exists, please check the file name again.\n");
		colorReset();
		return;
	}
	fclose(fp);

	fp = fopen(path,"r");
    if(outToFile){
        out = fopen(fileName, "w");
    }
	// O(n), to traverse each line
	while(EOF != fscanf(fp, "%350[^\n]\n", line)){
		if(strstr(line , word) != NULL){
			colorRed();
			++numberOfLines;
			printf("> %s\n" , line);
            if(outToFile){
                fprintf(out, "%d %s\n", numberOfLines, line);
            }
			colorReset();
		}else{
			continue;
		}
	}

	fclose(fp);
    if(outToFile){
        fclose(out);
    }
	// file closed after displaying the output

	colorGreen();
	printf("\t\t********* %d line(s) displayed *********\n", numberOfLines);
    if(outToFile){
        printf("\t\t********* Output saved to file %s *********\n", fileName);
		if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"Output saved\""); }
    }
	colorReset();

	if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"output displayed\""); }

    return;
}

void searchForKeyword(char voiceChoice){   

    // Variable declaration
	int v = 0;
	char * s;
    char word[100];
	int swChoice;
	int whileLoopVariable = 1;
	char chr;
	int outToFile;

	// enabling the voice assistant
	if(voiceChoice == 'y') { v = 1; }

	// while loop begins
	while(whileLoopVariable){
		printf("\n");
		printf(" 1. Search with IP\n");
		printf(" 2. Search with Date (DD/Mon/YYYY)\n");
		printf(" 3. Search with HTTP Method\n");
		printf(" 4. Status Code / Response Code\n");
		printf(" 5. Search with page name or others\n");
		printf(" 0. Back To Main\n");
		if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"enter the choice\""); }
		

		printf("\n Enter you choice: ");
		scanf("%d", &swChoice);

		// ask for the word to be searched in a file
		if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"enter the pattern to be searched\""); }

		switch (swChoice){
			case 0:
				whileLoopVariable = 0;
				break;
			case 1:
				if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"Do you want to store the output\""); }
				printf(" Do you want to save the output in a separate file(y/n): ");
				scanf(" %c", &chr);

				outToFile = (chr == 'y') ? 1 : 0;
				printf("\n Enter the IP: ");
				scanf("%s", word);
				grepify(word, v, outToFile);
				break;
			case 2:
				if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"Do you want to store the output\""); }
				printf(" Do you want to save the output in a separate file(y/n): ");
				scanf(" %c", &chr);

				outToFile = (chr == 'y') ? 1 : 0;
				printf("\n Enter the Date [Ex. 04/Nov/2000]: ");
				scanf("%s", word);
				grepify(word, v, outToFile);
				break;
			case 3:
				if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"Do you want to store the output\""); }
				printf(" Do you want to save the output in a separate file(y/n): ");
				scanf(" %c", &chr);

				outToFile = (chr == 'y') ? 1 : 0;
				s = word;
				printf("\n Enter the HTTP method: ");
				scanf("%s", word);
				while(*s){
					*s = (*s > 'a' && *s <= 'z') ? *s-32 : *s;
					s++;
				}
				grepify(word, v, outToFile);
				break;
			case 4:
				if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"Do you want to store the output\""); }
				printf(" Do you want to save the output in a separate file(y/n): ");
				scanf(" %c", &chr);

				outToFile = (chr == 'y') ? 1 : 0;
				printf("\n Enter the status code/ response code: ");
				scanf("%s", word);
				grepify(word, v, outToFile);
				break;
			case 5:
				if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"Do you want to store the output\""); }
				printf(" Do you want to save the output in a separate file(y/n): ");
				scanf(" %c", &chr);

				outToFile = (chr == 'y') ? 1 : 0;
				printf("\n Others(Case sensitive): ");
				scanf("%s", word);
				grepify(word, v, outToFile);
				break;
			default:
				printf("Invalid Option!!!");
				break;
		}
	}
	//while loop ends

	return;
}

void grepInTime(char voiceChoice, int fileOut){
    int v = 0, flag = 0;
    int numberOfLines = 0;
    FILE *fp, *fpp;
    char start[50], end[50], line[350], path[150], outName[150];

	if(voiceChoice == 'y'){ v = 1;}

	// Asking for the path of log file
	if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"Enter path of the log file\""); }
    printf("Enter the path to the log file: ");
    scanf("%s", path);

	/*
	* Check if file exists or not
	*/
	fp = fopen(path, "r");
	if(fp == NULL){
		printf("\n");
		colorRed();
		printf("No Such File Exists, please check the file name again.\n");
		colorReset();
		return;
	}
	fclose(fp);

	// Asking for the start time
	if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"Enter the start time\""); }
    printf("Enter the start time: ");
    scanf("%s", start);

	// Asking for the end time
	if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"Enter the end time\""); }
    printf("Enter the end time: ");
    scanf("%s", end);

	if(fileOut==1){
		if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"Enter the name of the output file\""); }
		printf("Enter the name of the file to save output (the file will be overwritten if it already exists): ");
		scanf("%s", outName);
	}
    
	/*
	* The algo of the this function is easy but implemented in a very smart manner.
	* The first loop first searched for the first apperance of start date and sets the flag to true
	* and if the flag is true at a particular time then that line will be printed
	* as soon as the first end date appears, the flag is set to false and then the loop breaks to save
	* time and resources.
	* The next loop simply prints each line in which the end date is found.
	*/
    fp = fopen(path, "r");
	if(fileOut==1){
		fpp = fopen(outName, "w");
	}
	printf("\n");
    while(EOF != fscanf(fp, "%350[^\n]\n", line)){
        if(strstr(line, start) != NULL){
            flag = 1;
        }
        if(strstr(line, end) != NULL){
            flag = 0;
            break;
        }
        if(flag){
            ++numberOfLines;
			colorRed();
            printf("%s\n", line);
			colorReset();
			if(fileOut==1){
				fprintf(fpp, "%s\n", line);
			}
        }
    }
    fclose(fp);

    fp = fopen(path, "r");
    while(EOF != fscanf(fp, "%350[^\n]\n", line)){
        if(strstr(line, end) != NULL){
            ++numberOfLines;
			colorRed();
            printf("%s\n", line);
			colorReset();
			if(fileOut==1){
				fprintf(fpp, "%s\n", line);
			}
        }
    }
    fclose(fp);
	if(fileOut==1){
		fclose(fpp);
	}
    
	printf("\n\n");
	colorGreen();
    printf("\t\t*********** Displayed %d Lines ****************\n", numberOfLines);
	if(fileOut==1){
		printf("\t\t*********** Output Saved to File %s ****************\n", outName);
		if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"Output save to the file\""); }
	}
	if(v) { system("espeak-ng -p 81 -a 55 -s 140 \"Output displayed\""); }
	colorReset();

    return;
}

int main(void){
	
	// Variable Declaration
	int whileLoopVariable = 1;
	char voiceChoice, chr;
	int choice, fileOut;

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
		printf("5. View Logs within a particular time frame.\n");
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

		case 5:
		  system("clear");
		  subBanner();
		  if(voiceChoice == 'y') { system("espeak-ng -p 81 -a 55 -s 140 \"Do you want to store the output\""); }
		  printf("Do you want to save the output to a file(y/n): ");
		  scanf(" %c", &chr);
		  fileOut = (chr=='y')?1:0;
		  grepInTime(voiceChoice, fileOut);
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
