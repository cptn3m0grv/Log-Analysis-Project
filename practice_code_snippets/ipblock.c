#include<stdio.h>
#include<string.h>

int main(){
	printf("Enter the number of IP to block: ");
	scanf("%d", &ipListSize);
	
	char first_half[] = "firewall-cmd --permanent --add-rich-rule=\"rule family='ipv4' source address='";


	
	scanf("%20s", second_half);
	char final_half[] = "' accept\"";
	
	strcat(first_half, second_half);
	strcat(first_half, final_half);
	
	system(first_half);
	system("firewall-cmd --reload");
	system("firewall-cmd --list-all");

	return 0;
}
