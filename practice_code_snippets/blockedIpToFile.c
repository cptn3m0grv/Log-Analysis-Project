#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void unblockAndDeleteFromFile(char *IP){
    FILE *fp;
    fp = fopen("removeIp.sh", "w");
    fprintf(fp, "#!/bin/bash");
    fprintf(fp, "\nsudo sed -i '/%s/d' ./block.txt", IP);
    fclose(fp);
    system("chmod +x removeIp.sh");
    system("./removeIp.sh");
    system("rm -f removeIp.sh");
}

void blockedAndAddToFile(char *IP){

    FILE *fp, *fptr;
    char line[25];
    int availaible = 0;
    int ipBlocked = 0;

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
    }else{
        printf("\nIP IS ALREADY BLOCKED, SELECT ANOTHER OPTION IF YOU WANT TO UNBLOCK IT!!\n");
        ipBlocked = 1;
    }

}

int main(){

    char IP[20];
    int choice;
    int whileLoop = 1;

    printf("1. Block the IP\n");
    printf("2. Unblock\n");
    printf("0. Exit\n");

    while(whileLoop){
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
        case 0:
            whileLoop = 0;
            break;

        case 1:
            printf("Enter the IP to block: ");
            scanf("%s", IP);
            blockedAndAddToFile(IP);
            break;
        
        case 2:
            printf("Enter the IP to unblock: ");
            scanf("%s", IP);
            unblockAndDeleteFromFile(IP);
            break;

        default:
            break;
        }
    }
    
}
