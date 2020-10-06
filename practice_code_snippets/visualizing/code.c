#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ipList{
    char *IP;
    int count;
};


int ipInFile(char IP[], char new_path[]){
    FILE *fp;
    char line[16];
    fp = fopen(new_path, "r");
    while (EOF != fscanf(fp, "%16[^\n]\n", line)){
        if(strstr(line, IP) != NULL){
            return 1;
        }
    }
    fclose(fp);
    
    return 0;
}
void generateUnique(char path[]){
    
    FILE* fp, *fptr;
    char line[16];
    char new_path[] = "uniqueIp.txt";
    fptr = fopen(new_path, "w");
    fclose(fptr);

    fp = fopen(path,"r");

    while(EOF != fscanf(fp, "%16[^\n]\n", line)){
        if(!ipInFile(line, new_path)){
            fptr = fopen(new_path, "a");
            fprintf(fptr, "%s\n", line);
            fclose(fptr);
        }else{continue;}
    }
    fclose(fp);
}

int main(){
    char path[128];
    printf("Enter the log file to visualize: ");
    scanf("%s", path);
    generateUnique(path);
    return 0;
}
