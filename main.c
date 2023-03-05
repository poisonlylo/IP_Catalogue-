#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>

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

        printf("\n\n\t[1] Connaitre le type de l'adresse IP");

        printf("\n\n\t[2] Convertir en Binaire ");

        printf("\n\n\t[3] Convertir en Hexadecimal");

        printf("\n\t[5] Sortie");

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
void check_ip_type(char *ip) {
    int first_octet, second_octet, third_octet, fourth_octet;
    sscanf(ip, "%d.%d.%d.%d", &first_octet, &second_octet, &third_octet, &fourth_octet);

    if (first_octet == 10 || (first_octet == 172 && second_octet >= 16 && second_octet <= 31) ||
        (first_octet == 192 && second_octet == 168)) {
        printf("\n\t\t\tIP privé\n");
    } else if (first_octet == 169 && second_octet == 254) {
        printf("\n\t\t\tIP auto-configuré\n");
    } else if (first_octet == 127) {
        printf("\n\t\t\tIP local (loopback)\n");
    } else if (first_octet >= 1 && first_octet <= 126) {
        printf("\n\t\t\tAdresse IP de classe A (publique)\n");
    } else if (first_octet >= 128 && first_octet <= 191) {
        printf("\n\t\t\tAdresse IP de classe B (publique)\n");
    } else if (first_octet >= 192 && first_octet <= 223) {
        printf("\n\t\t\tAdresse IP de classe C (publique)\n");
    } else if (first_octet >= 224 && first_octet <= 239) {
        printf("\n\t\t\tAdresse IP de classe D (multicast)\n");
    } else if (first_octet >= 240 && first_octet <= 255) {
        printf("\n\t\t\tAdresse IP de classe E (expérimentale)\n");
    } else {
        printf("\n\t\t\tAdresse IP invalide\n");
    }
}


// function to convert IP address from decimal to binary
void dec_to_bin_ip(char *ip) {
    int num, i = 0;
    char *ptr;
    char binary_ip[35] = ""; // each octet will be 8 bits + 1 for the dot (total 35)

    ptr = strtok(ip, ".");
    while (ptr) {
        num = atoi(ptr);
        for (int j = 7; j >= 0; j--) {
            if (num & (1 << j)) {
                binary_ip[i] = '1';
            } else {
                binary_ip[i] = '0';
            }
            i++;
        }
        binary_ip[i] = '.'; // add dot between octets
        i++;
        ptr = strtok(NULL, ".");
    }
    binary_ip[i - 1] = '\0'; // remove last dot

    printf("\n\t\t\tAdresse IP en binaire : %s\n", binary_ip);
}




// function to convert IP address from decimal to hexadecimal
void dec_to_hex_ip(char *ip) {
    int first_octet, second_octet, third_octet, fourth_octet;
    sscanf(ip, "%d.%d.%d.%d", &first_octet, &second_octet, &third_octet, &fourth_octet);

    printf("\n\t\t\tAdresse IP en Hexadecimal : %02X:%02X:%02X:%02X\n", first_octet, second_octet, third_octet, fourth_octet);
}
