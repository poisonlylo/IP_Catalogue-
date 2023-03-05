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
int main() {
    char ip1[20] ;
    int subnet_mask;
    char ip_address[20];
    FILE *fptr;

    while(validate_ip(ip1) != 1 ){
        printf(" Veulliez entrez une a dresse IP correcte ");
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

    printf("\tConverssions \n");


    while(1){

        printf("\n\n\t\tMENU PRINCIPAL:");

        printf("\n\n\tConvertir en Binaire \t[1]");

        printf("\n\tConvertir en Decimal\t[2]");

        printf("\n\tConvertir en Hexadecimal\t[3]");

        printf("\n\tSortie\t\t[5]");

        printf("\n\n\tSaisissez votre choix :");

        scanf("%d",&ch);

        switch(ch){

        case 1:

            decimal_to_binary();

        break;

        case 2:

            binary_to_hex();

        break;

        case 3:

        edit_note();

        break;

        case 4:

        delete_note();

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