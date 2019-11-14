#include <stdio.h>
/******************************************************
Jairius Davenport 11-12-19
Taylor Younkins 11-13-19
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

int main()
{
    int end = 0;

    int choice;
    printf("\nHi! Welcome to the Domino's Pizza Ordering Application!\n");
    do
    {
        printf("What would you like to do?\n1. Search nearest locations\n2. Display Menu\n3. Place Order");
        printf("\nI'd like to choose option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            searchNear();
            break;

        case 2:
            displayMenu();
            break;

        case 3:
            placeOrder();
            processOrder();
            break;
        }

        printf("\nWould you like to exit? (1=yes 0=no): ");
        scanf("%d", &end);
    } while (end != 1);
} //end of main

void processOrder()
{
    printf("To begin processing your order we'll need some basic information\n");
    printf("Full delivery address: ");
    scanf("%s", userAddr);
    printf("First Name: ");
    scanf("%s", userFName);
    printf("Last Name: ");
    scanf("%s", userLName);
    printf("E-mail address: ");
    scanf("%s", userEmail);
    printf("Phone number: ");
    scanf("%s", userPhone);
    printf("\nNext will prompt you for payment information \n");
    printf("\nCredit card number: ");
    scanf("%s", userCardNum);
    printf("Credit card expiration date (mm/yy): ");
    scanf("%s", userCardX);
    printf("Credit card security code or CVV (3 to 4 digit code): ");
    scanf("%s", userCardSec);
    printf("Postal code: ");
    scanf("%s", userPost);

}

void placeOrder()
{
    printf("Begin your order by selecting items\n");

    //API code goes here??
}

void searchNear()
{
    printf("To find a location near you, please input your location\n");
    printf("\nStreet address: ");
    scanf("%s", locationAddr);
    printf("\nCity: ");
    scanf("%s", locationCity);
    printf("\nState: ");
    scanf("%s", locationState);
    printf("\nZip: ");
    scanf("%s", locationZip);

    printf("Your address:\nStreet: %s\nCity: %s\nState: %s\nZip: %s", locationAddr, locationCity,locationState,locationZip);

    //API code goes here??
    printf("The store closest to you is: ");
}

void displayMenu()
{
    printf("Here is the menu selection from your nearest store\n");
    printf("Store_ID: %s", locationZip); //the value in location is completely a placeholder until we have the actual store ID

    //API code goes here??
}

//prompt using numbers
//save every input into a string
//error handling is for Alonzo

/**
    
    find closest {address info} can be full or partial address city and state, postal code etc...

    find near {address info} can be full or partial address city and state, postal code etc...

    menu for closest {address info} can be full or partital address city and state, postal code etc...

    full menu for closest {address info} can be full or partial address city and state, postal code etc...

    menu for {storeID} get store id as part of a find closest or find near request

    full menu for {storeID} get store id as part of a find closest or find near request

    order {comma deliminated list of item codes} 
    example:
    order PXC_14SCREEN, 2LSPRITE
    what is the full address for delivery? 205 N Russel Street, West lafayette, IN, 47907
    First Name? Taylor
    Last Name? Younkins
    E-Mail? tayloryounkins@gmail.com
    Phone number? 4104561552
    Credit Card Number? 34824347983742937
    Credit Card Expiration? 3242
    Credit Card Security Code or CVV (3 or 4 digit code on card)? 23423
    Postal Code? 47906-4241

    */
