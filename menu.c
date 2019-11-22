#include <stdio.h>
/******************************************************
Authors: Jairius, Taylor
*******************************************************/
void placeOrder();
void processOrder();
void searchNear();
void displayMenu();
const int a = 10, b = 100, c = 30, d = 5, e = 50;

char userAddr[50];
char userFName[25];
char userLName[35];
char userEmail[50];
char userPhone[10];
char userCardNum[16];
char userCardX[5];
char userCardSec[4];
char userPost[10];       
char order[30];          
char locationAddr[30];
char locationCity[25];
char locationState[2];
char locationZip[8];
char menuItems[50];      

void processOrder(){
    char temp;

    printf("To begin processing your order we'll need some basic information\n");
    printf("Full delivery address: ");
    scanf("%c",&temp);
    scanf("%[^\n]", userAddr);

    printf("First Name: ");
    scanf("%c",&temp);
    scanf("%[^\n]", userFName);

    printf("Last Name: ");
    scanf("%c",&temp);
    scanf("%[^\n]", userLName);

    printf("E-mail address: ");
    scanf("%c",&temp);
    scanf("%[^\n]", userEmail);

    printf("Phone number: ");
    scanf("%c",&temp);
    scanf("%[^\n]", userPhone);

    //prompt for credit card
    printf("\nNext will prompt you for payment information \n");
    printf("\nCredit card number: ");
    scanf("%c",&temp);
    scanf("%[^\n]", userCardNum);
    printf("Credit card expiration date (mm/yy): ");
    scanf("%s", userCardX);
    printf("Credit card security code or CVV (3 to 4 digit code): ");
    scanf("%s", userCardSec);
    printf("Postal code: ");
    scanf("%s", userPost);  

}

void placeOrder(){
    printf("Begin your order by selecting items\n");
    printf("Enter items you want: ");
    scanf("%c",&temp);

    //this needs to be asking for peoples items one at a time, loop until they are done 
    scanf("%[^\n]", menuItems);

    //API code goes here??
}


void searchNear(){
    char temp;

    printf("To find a location near you, please input your location\n");
    printf("Street address: ");
    scanf("%c",&temp);
    scanf("%[^\n]", locationAddr);

    printf("\nCity: ");
    scanf("%c",&temp);
    scanf("%[^\n]", locationCity);

    //locationState
    printf("\nState: ");
    scanf("%c",&temp);
    scanf("%[^\n]", locationState);

    printf("\nZip: ");
    scanf("%c",&temp);
    scanf("%s", locationZip);

    printf("Total address: %s, %s, %s, %s", locationAddr, locationCity, locationState,locationZip);

    //API code goes here??
    printf("The store closest to you is: ");
}


void displayMenu(){
    printf("Here is the menu selection from your nearest store\n");
    printf("Store_ID: %s", locationZip);  //the value in location is completely a placeholder until we have the actual store ID
    //API code goes here??
}

int main () {
    int end = 0; 
    int choice;

    printf("\nHi! Welcome to the Domino's Pizza Ordering Application!\n");
    do {
        printf("What would you like to do?\n1. Place Order\n2. Search nearest locations\n3. Display Menu\n");
        printf("I'd like to choose option: ");
        scanf("%d", &choice);

        switch (choice){
        case 1:
            placeOrder();
            processOrder();
        break;

        case 2:
            searchNear();
        break;

        case 3:
            displayMenu();
            break;
        }

        printf("\nWould you like to exit? (1=yes 0=no): ");
        scanf("%d", &end);

    } while (end !=1);
}  //end of main



