#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int decimal_to_binary(int decimal);
int binary_to_hex(int binary);

int main() {
    char ip_address[16];
    printf("Enter the IP address in decimal format (e.g. 192.168.1.1): \n");
    scanf("%s", ip_address);
    
    char *token;
    int binary_address[4];
    int i = 0;
    token = strtok(ip_address, ".");
    while (token != NULL) {
        binary_address[i] = decimal_to_binary(atoi(token));
        i++;
        token = strtok(NULL, ".");
    }
    
    printf("The binary representation of the IP address is:  \n");
    for (i = 0; i < 4; i++) {
        printf("%08d ", binary_address[i]);
    }
    printf("\n");
    
    printf("The hexadecimal representation of the IP address is:  \n");
    for (i = 0; i < 4; i++) {
        printf("%02X", binary_to_hex(binary_address[i]));
        if (i < 3) {
            printf(":");
        }
    }
    printf("\n");
    
    return 0;
}

int decimal_to_binary(int decimal) {
    int binary = 0;
    int base = 1;
    while (decimal > 0) {
        int rem = decimal % 2;
        binary = binary + rem * base;
        decimal = decimal / 2;
        base = base * 10;
    }
    return binary;
}

int binary_to_hex(int binary) {
    int hex = 0;
    int base = 1;
    while (binary > 0) {
        int rem = binary % 10;
        hex = hex + rem * base;
        binary = binary / 10;
        base = base * 2;
    }
    return hex;
}
