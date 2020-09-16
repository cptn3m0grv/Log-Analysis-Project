#include<stdio.h>
#define SIZE 10
int main(){
    char *ip_List[SIZE];
    ip_List[0] = "192.168.0.104";
    ip_List[1] = "192.168.0.103";
    ip_List[2] = "192.168.0.101";
    ip_List[3] = "192.168.0.107";
    ip_List[4] = "192.168.0.102";
    ip_List[5] = "192.168.0.111";
    ip_List[6] = "192.168.0.131";
    ip_List[7] = "192.168.0.121";
    ip_List[8] = "192.168.0.112";
    ip_List[9] = "192.168.0.134";
    
    int occ[SIZE] = { 4, 1, 6, 2, 2, 1, 7, 5, 13, 43 };
    
    printf(" LIST OF IP \t|");
    printf("     Occurences of this Particular IP  \n");
    printf("________________|______________________________________________________________________________________\n");
    
    for(int i = 0; i< SIZE; i++){
        printf("%s\t| ", ip_List[i]);
        for(int j = 0; j < occ[i]; j++){
            printf("# ");
        }
        printf("\n");
    }
    
    return 0;
}
