#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int validate_ip(char *ip);
int check_subnet_mask(int subnet_mask);
void check_ip_type(char *ip);
void dec_to_hex_ip(char *ip);
void dec_to_bin_ip(char *ip);

int main() {
    char ip1[20] ;
    int subnet_mask;
    char ip_address[20];
    FILE *fptr;

    while(validate_ip(ip1) != 1 ){
        printf(" Veulliez entrez une a dresse IP valide (Format : xxx.xxx.xxx.xxx) ");
        gets(ip1);
        sprintf(ip_address, "%s", ip1);
    }
    printf("Adresse IP: %s\n", ip_address);

    printf("Entrez le masque sous reseau, entre 1 et 32: ");
    scanf("%d", &subnet_mask);

    while(check_subnet_mask(subnet_mask) != 1 ){
        printf("ERREUR! Veuillez entrez un masque sous reseau correcte: ");
        scanf("%d", &subnet_mask);
    }

    // stock IP address on file
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
// function to validate IP address
int validate_ip(char *ip)
{
    int num, dots = 0;
    char *ptr;

    if (ip == NULL)
        return 0;

    ptr = strtok(ip, ".");
    if (ptr == NULL)
        return 0;

    while (ptr) {
        if (!*ptr)
            return 0;

        num = atoi(ptr);
        if (num < 0 || num > 255)
            return 0;

        // To avoid 01.02.03.4 is considered as valid IP
        if (*ptr == '0' && *(ptr + 1))
            return 0;

        ptr = strtok(NULL, ".");
        dots++;
    }

    if (dots != 4)
        return 0;

    return 1;
}

// function to check if subnet mask is valid
int check_subnet_mask(int subnet_mask)
{
    if (subnet_mask < 1 || subnet_mask > 32)
        return 0;
    else
        return 1;
}

// function to determine the type of IP address
void check_ip_type(char *ip)
{
    int first_octet;
    sscanf(ip, "%d.", &first_octet);

    if (first_octet >= 1 && first_octet <= 127)
        printf("\n\tAdresse IP de classe A\n");

    else if (first_octet >= 128 && first_octet <= 191)
        printf("\n\tAdresse IP de classe B\n");

    else if (first_octet >= 192 && first_octet <= 223)
        printf("\n\tAdresse IP de classe C\n");

    else if (first_octet >= 224 && first_octet <= 239)
        printf("\n\tAdresse IP de classe D\n");

    else if (first_octet >= 240 && first_octet <= 255)
        printf("\n\tAdresse IP de classe E\n");

    else
        printf("\n\tAdresse IP invalide\n");
}

// function to convert IP address from decimal to binary
void dec_to_bin_ip(char *ip)
{
    int i, j, k, num;
    char *ptr, bin_octet[9], bin_ip[33];

    ptr = strtok(ip, ".");

    while (ptr) {
        num = atoi(ptr);
        memset(bin_octet, '0', 8);

        i = 0;
        while (num > 0) {
            bin_octet[i] = (num % 2) + '0';
            num /= 2;
            i++;
        }

        bin_octet[i] = '\0';

        for (j = 0, k = strlen(bin_octet) - 1; j < strlen(bin_octet); j++, k--)
            bin_ip[strlen(bin_ip)] = bin_octet[k];

        ptr = strtok(NULL, ".");

        if (ptr != NULL)
            bin_ip[strlen(bin_ip)] = '.';
    }

    bin_ip[strlen(bin_ip)] = '\0';

    printf("\n\tL'adresse IP en binaire est : %s\n", bin_ip);
}

// function to convert IP address from decimal to hexadecimal
void dec_to_hex_ip(char *ip)
{
    int i, j, k, num;
    char *ptr, hex_octet[3], hex_ip[12];

    ptr = strtok(ip, ".");

    while (ptr) {
        num = atoi(ptr);
        memset(hex_octet, 0, sizeof(hex_octet));
        sprintf(hex_octet, "%X", num);

        if (strlen(hex_octet) == 1) {
            hex_ip[k++] = '0';
            hex_ip[k++] = hex_octet[0];
        } else {
            hex_ip[k++] = hex_octet[0];
            hex_ip[k++] = hex_octet[1];
        }

        hex_ip[k++] = ':';
        ptr = strtok(NULL, ".");
    }

    hex_ip[k - 1] = '\0';
    printf("Adresse IP en Hexadecimal: %s\n", hex_ip);
}
