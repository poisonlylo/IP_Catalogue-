#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int validate_number(char *str) {
    while (*str) {
        if(!isdigit(*str)){ //if the character is not a number, return false
            return 0;
        }
        str++; //point to next character
    }
    return 1;
}
int validate_ip(char *ip) { //check whether the IP is valid or not
    int i, num, dots = 0;
    char *ptr;
    if (ip == NULL)
        return 0;
    ptr = strtok(ip, "."); //cut the string using dor delimiter
    if (ptr == NULL)
        return 0;

    while (ptr) {
        if (!validate_number(ptr)) //check whether the sub string is holding only number or not
        return 0;
        num = atoi(ptr); //convert substring to number
        if (num >= 0 && num <= 255) {
            ptr = strtok(NULL, "."); //cut the next part of the string
            if (ptr != NULL)
                dots++; //increase the dot count
        } else
            return 0;
    }
    if (dots != 3) //if the number of dots are not 3, return false
        return 0;
    return 1;
}

int check_subnet_mask(int subnet_mask){
    if (subnet_mask >0 && subnet_mask <=32) {
        return 1;
    }else {
        return 0;
    }
}


char* dec_to_hex_ip(char* ip) {
    if (!validate_ip(ip)) {
        return NULL; // invalid IP address format
    }
    char* hex_ip = malloc(9); // allocate space for the 8-character hexadecimal IP string, plus a null terminator
    if (hex_ip == NULL) {
        return NULL; // memory allocation failed
    }
    memset(hex_ip, 0, 9); // initialize the hex_ip buffer to all zeros
    char* ptr = strtok(ip, ".");
    while (ptr) {
        int num = atoi(ptr);
        sprintf(hex_ip + strlen(hex_ip), "%02X", num);
        ptr = strtok(NULL, ".");
    }
    printf("L'adresse IP en hexadecimal est : %s", hex_ip);
    return hex_ip;
}

void dec_to_bin_ip(char* ip, char* bin_ip) {
    if (!validate_ip(ip)) {
        bin_ip[0] = '\0'; // invalid IP address format
        return;
    }
    char* ptr = strtok(ip, ".");
    while (ptr) {
        int num = atoi(ptr);
        char octet[9];
        itoa(num, octet, 2);
        int len = strlen(octet);
        if (len < 8) {
            int i;
            for (i = 0; i < 8 - len; i++) {
                strcat(bin_ip, "0");
            }
        }
        strcat(bin_ip, octet);
        strcat(bin_ip, ".");
        ptr = strtok(NULL, ".");
    }
    bin_ip[strlen(bin_ip) - 1] = '\0'; // remove the trailing dot
    printf("L'adresse IP en binaire est : %s", bin_ip);
}


int check_ip_type(char* ip_address){
    int ip1,ip2,ip3,ip4;
    int subnet_mask;
    char class_type;
    if (sscanf(ip_address, "%d.%d.%d.%d/%d", &ip1, &ip2, &ip3, &ip4, &subnet_mask) != 5) {
        return 0;
    }

    if (ip1 == 10) { // Private IP range
        printf("This Ip address is private");
        return 1;
    }
    else if (ip1 == 172 && ip2 >= 16 && ip2 <= 31) { // Private IP range
        printf("This Ip address is private");
        return 1;
    }
    else if (ip1 == 192 && ip2 == 168) { // Private IP range
        printf("This Ip address is private");
        return 1;
    }
    else if (ip1 == 0 && ip2 == 0 && ip3 == 0 && ip4 == 0) { // Special IP: 0.0.0.0
        printf("This Ip address is a special Ip: 0.0.0.0 ");
        return 2;
    }
    else if (ip1 == 127 && ip2 == 0 && ip3 == 0 && ip4 == 1) { // Special IP: 127.0.0.1
        printf("This Ip address is the Loopback address (127.0.0.1)");
        return 2;
    }
    else if (ip1 >= 224 && ip1 <= 239) { // Special IP: Multicast
        printf("This Ip address is Multicast Ip  ");
        return 2;
    }
    else if (ip1 >= 240 && ip1 <= 255) { // Special IP: Reserved
        printf("This Ip is a Reserved Ip address");
        return 2;
    }
    else {
        return 0;
    }
}



int main() {
    char ip1[20] ;
    int subnet_mask;
    char ip_address[20];
    FILE *fptr;

    while(validate_ip(ip1) != 1 ){
        printf(" Veulliez entrez une a dresse IP valide (Format : xxx.xxx.xxx.xxx) ");
        gets(ip1);
        sprintf(ip_address, "%s", ip1);

        // printf(ip1);
    }
    printf(ip_address);

    printf("Entrez le masque sous reseau, entre 1 et 32");
    scanf("%d", &subnet_mask);

    while(check_subnet_mask(subnet_mask) != 1 ){
        printf("ERREUR! Veuillez entrez un masque sous reseau correcte ");
        scanf("%d", &subnet_mask);
    }


    // stock IP address on file
    // convert int to str
    char filename[20];
    sprintf(filename, "%d", subnet_mask);
    fptr = fopen(filename,"a");

    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    fprintf(fptr, "%s", ip_address);
    fprintf(fptr, "\n");
    fclose(fptr);

    int ch;


    while(1){

        printf("\n\n\t\tMENU PRINCIPAL:");

        printf("\n\n\tConnaître le type de l'adresse IP\t[1]");

        printf("\n\n\tConvertir en Binaire \t[2]");

        printf("\n\n\tConvertir en Hexadecimal\t[3]");

        printf("\n\tSortie\t\t[5]");

        printf("\n\n\tSaisissez votre choix :");

        scanf("%d",&ch);

        switch(ch){

        case 1:

            check_ip_type(ip_address);
            
        break;

        case 2:

            dec_to_bin_ip(ip_address);
           

        break;

        case 3:
            dec_to_hex_ip(ip_address);
        
        
        break;

        case 4:


        break;

        case 5:

        printf("\n\n\t\tMerci d'avoir utiliser l'appli  ");

        exit(0);

        default:

        printf("\nFAUX! veulliez reessayer une nouvelle fois..");

        break;
        }
    }


return 0;
}