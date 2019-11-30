#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdbool.h>

/******************************************************
Authors: 
Jairius: Menu, User Input
Taylor: API Integration, file IO
Andrew: Structs, Struct Methods
*******************************************************/


void placeOrder();
void processOrder();
void searchNear();
void displayMenu();
char* concat( char *s1,  char *s2);
const int a = 10, b = 100, c = 30, d = 5, e = 50;

char street[50];
char city[50];
char zip[5];
char state[2];
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

typedef struct Address
{
  char* street;
  char* city;
  char* state;
  char* zip;
} Address;

Address* createAddress(char* str, char* cit, char* sta, char* z)
{
  Address *addr = (Address*)malloc(sizeof(Address));
  addr->street = str;
  printf("address: %s", addr->street);
  addr->city = cit;
  addr->state = sta;
  addr->zip = z;
  return addr;
}

void AddressToString(Address* addr)
{
  printf("\nUser Address: %s, %s, %s, %s", addr->street, addr->city, addr->state, addr->zip);
  printf("\n");
}

typedef struct Store
{
  char* storeId;
  Address* storeAddr;
} Store;

Store *store;

Store* createStore(char* id, Address* addr)
{
  store = (Store*)malloc(sizeof(Store));
  store->storeId = id;
  store->storeAddr = addr;
  return store;
}

void StoreToString(Store* sto)
{
  printf("\nStore ID: %s", sto->storeId);
  AddressToString(sto->storeAddr);
}

typedef struct OrderItem
{
  char* orderItemId;
  struct OrderItem* next;
} OrderItem;

OrderItem* createOrderItem(char* id)
{
  OrderItem* item = (OrderItem*)malloc(sizeof(OrderItem));
  item->orderItemId = id;
  item->next = NULL;
  return item;
}

void OrderItemToString(OrderItem* item)
{
  printf("Order Item ID: %s", item->orderItemId);
}

typedef struct Order
{
  int size;
  OrderItem* start;
  OrderItem* end;
} Order;

Order *customerOrder;

Order* createOrder(OrderItem* item)
{
  Order* order = (Order*)malloc(sizeof(Order));
  order->size = 1;
  order->start = item;
  order->end = item;
  return order;
}

void enqueue(Order* order, OrderItem* item)
{
  order->end->next = item;
  order->end = item;
  order->size++;
}

OrderItem* dequeue(Order* order)
{
  OrderItem* temp = order->start;
  order->start = temp->next;
  order->size--;
  return temp;
}

int sizeOfQueue(Order* line)
{//returns the size of the specified queue
  return line->size;
}
_Bool isEmpty(Order* line)
{//returns a true boolean if the specified queue is empty
  if(line->size==0)
    return true;
  else
    return false;
}
void OrderToString(Order* order)
{
  printf("\nOrder: \n");
  OrderItem* current = order->start;
  if(current == NULL)
    printf("Error: list is empty.");
  while(current != NULL)
  {
    OrderItemToString(current);
    current = current->next;
  }
}

typedef struct Card
{
  char* ccn;
  char* experation;
  char* cvv;
  char* zip;
}Card;

Card *card;

Card* createCard(char* cn, char* exp, char* cv, char* z)
{
  Card* card = (Card*)malloc(sizeof(Card));
  card->ccn = cn;
  card->experation = exp;
  card->cvv = cv;
  card->zip = z;
  return card;
}
void CardToString(Card* card)
{
  printf("\nCARD: CCN: %s, ",card->ccn);
  printf("Expiration: %s, ",card->experation);
  printf("CVV: %s, ",card->cvv);
  printf("ZIP: %s\n",card->zip);
}

typedef struct Customer
{
  char* firstName;
  char* lastName;
  Address* customerAddr;
  char* email;
  char* phone;
  Card* payment;
}Customer;

Customer *customer;

Customer* createCustomer(char* fName, char* lName, Address* addr, char* e, char* pho, Card* pay)
{
  Customer* customer = (Customer*)malloc(sizeof(Customer));
  customer->firstName = fName;
  customer->lastName = lName;
  customer->customerAddr = addr;
  customer->email = e;
  customer->phone = pho;
  customer->payment = pay;
  return customer;
}
void CustomerToString(Customer* customer)
{
  printf("\nCustomer:\n");
  printf("First name: %s, ",customer->firstName);
  printf("Last name: %s",customer->lastName);
  AddressToString(customer->customerAddr);
  printf("Email: %s, ",customer->email);
  printf("Phone: %s",customer->phone);
  CardToString(customer->payment);
}


void parseNearbyStoreData(void *ptr, size_t size, size_t nmemb, void *stream){
    int length = 126;
    char str3[length];

    printf("\n\n");
    char * pch;
    pch = strstr (ptr,"\"StoreID");

    strncpy( str3, pch, length);
    str3[length] = "\0";

    int storeIDLength = 15;
    char StoreID[storeIDLength];
    strncpy( StoreID, pch, storeIDLength);
 
    char ID[4];
    for(int i = 0; i < 4; i++){
      ID[i] = StoreID[storeIDLength-4+i];
    }

    int count = 0; //like a boolean
    int commaCount = 0;
    for(int i = 0; i < length; i++){

      if(str3[i] == '"'){ 

        if(count == 4){
          printf("\n");
          count = 0;
        } else {
          count++;
        }
      } else if (str3[i] == '\\' && str3[i+1] == 'n'){
        printf("\n");
        i++;
      } else if (str3[i] == 'I' && str3[i+1] == 's'){
        i+=22;
      } else if (str3[i] == 'D' && str3[i+1] == 'e'){
        i+=11;
      } else if (str3[i] == ':'){
        printf(": ");
      }  else if (str3[i] == ',' && commaCount <2){
        commaCount++;
      } else if (str3[i] == ',' && commaCount ==2){
        printf("%c", str3[i]);
      } else {
        printf("%c",str3[i]);
      }

    }
  printf("\n");

}

void findClosest(){
  CURL *curl;
  CURLcode res;

  /* get a curl handle */
  curl = curl_easy_init();
  if (curl)
  {
    char* ughzip = (char*)malloc(sizeof(char));
    ughzip = locationZip;

    char *addy = (char*)malloc(sizeof(char));
    // addy =  concat("Herp", "derp");
    
    addy = concat("https://order.dominos.com/power/store-locator?s=&c=", ughzip);
    addy = concat(addy, "&type=Delivery");
    curl_easy_setopt(curl, CURLOPT_URL, addy);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, parseNearbyStoreData);
    curl_easy_perform(curl);
  }
  curl_global_cleanup();
}

void oldOrder(){

  CURL *curl;
  CURLcode res;

  /* get a curl handle */
  curl = curl_easy_init();
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, "https://order.dominos.com/power/validate-order");
  
    char mystr[2000] = "{\"Order\":{\"Address\":{\"Street\":\"301 EVERGREEN ST\",\"StreetNumber\":\"301\",\"StreetName\":\"EVERGREEN ST\",\"UnitType\":\"\",\"UnitNumber\":\"\",\"City\":\"WEST LAFAYETTE\",\"Region\":\"IN\",\"PostalCode\":\"47907\"},\"Coupons\":[],\"CustomerID\":\"\",\"Email\":\"jdhfghjkdfg@gmailcom\",\"Extension\":\"\",\"FirstName\":\"taylor\",\"LastName\":\"younkins\",\"LanguageCode\":\"en\",\"OrderChannel\":\"OLO\",\"OrderID\":\"gRXppWj3H4KTx9N2psQn\",\"OrderMethod\":\"Web\",\"Payments\":[{\"Type\":\"CreditCard\",\"Amount\":14.42,\"Number\":\"123123\",\"CardType\":\"\",\"Expiration\":\"3453\",\"SecurityCode\":\"123\",\"PostalCode\":\"47907\"}],\"Phone\":\"548358745\",\"Market\":\"UNITED_STATES\",\"Currency\":\"USD\",\"ServiceMethod\":\"Delivery\",\"SourceOrganizationURI\":\"order.dominos.com\",\"StoreID\":\"9674\",\"Tags\":{},\"Version\":\"1.0\",\"NoCombine\":true,\"Partners\":{},\"NewUser\":true,\"metaData\":{},\"BusinessDate\":\"2019-11-20\",\"EstimatedWaitMinutes\":\"0\",\"PriceOrderTime\":\"2019-11-20 22:46:38\",\"IP\":\"199.204.83.184\",\"Promotions\":{\"Redeemable\":[],\"AvailablePromos\":{\"EndOfOrder\":\"8130\"},\"Valid\":[]},\"AvailablePromos\":{\"EndOfOrder\":\"8130\"},\"PulseOrderGuid\":\"f48641ee-f9b0-42a4-9248-715f0aca23ae\",\"PriceOrderMs\":922,\"AmountsBreakdown\":{\"FoodAndBeverage\":\"10.99\",\"Adjustment\":\"0.00\",\"Surcharge\":\"0.00\",\"DeliveryFee\":\"2.49\",\"Tax\":0.94,\"Tax1\":0.94,\"Tax2\":0,\"Bottle\":0,\"Customer\":14.42,\"Savings\":\"0.00\"},\"Status\":1,\"StatusItems\":[{\"Code\":\"AutoAddedOrderId\"},{\"Code\":\"PriceInformationRemoved\"}],\"Products\":[]},\"Status\":1,\"Offer\":{\"CouponList\":[],\"ProductOffer\":\"\"},\"EmailHash\":null,\"StatusItems\":[{\"Code\":\"Warning\"}]}";
    // printf("%s", mystr);

    struct curl_slist *headers=NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Referer: https://order.dominos.com/en/pages/order");

    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE,8000L);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, mystr);

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    curl_easy_perform(curl); /* post away! */
    printf("\n kms\n");

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers); 

    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
    curl_easy_strerror(res));

  }
    curl_global_cleanup();
}

char* concat( char *s1,  char *s2)
{
    // printf("sjgfdldfjgdg");
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    // printf("sjgfdldfjgdg");
    return result;
}

void postOrder(){

  printf("\nwassup from place order\n");
    // CURLcode res;
    CURL *hnd = curl_easy_init();

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(hnd, CURLOPT_URL, "https://order.dominos.com/power/validate-order");

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "cache-control: no-cache");
    headers = curl_slist_append(headers, "Connection: keep-alive");
    headers = curl_slist_append(headers, "Content-Length: 1644");
    headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate");
    headers = curl_slist_append(headers, "Host: order.dominos.com");
    headers = curl_slist_append(headers, "Postman-Token: a67c9853-274f-4cef-b794-52b5fd71c1c7,7ba28974-0c4b-4bde-9200-9c9ac6508952");
    headers = curl_slist_append(headers, "Cache-Control: no-cache");
    headers = curl_slist_append(headers, "Accept: */*");
    headers = curl_slist_append(headers, "User-Agent: PostmanRuntime/7.19.0");
    headers = curl_slist_append(headers, "Referer: https://order.dominos.com/en/pages/order");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    char *postfields = (char*)malloc(sizeof(char));

    postfields = concat("{\"Order\":{\"Address\":{\"Street\":\"", street);
    postfields = concat(postfields, "\",\"StreetNumber\":\"\",\"StreetName\":\"\",\"UnitType\":\"\",\"UnitNumber\":\"\",\"City\":\"");
    postfields = concat(postfields, city);
    postfields = concat(postfields, "\",\"Region\":\"");
    postfields = concat(postfields, state);
    
    postfields = concat(postfields, "\",\"PostalCode\":\"");
    postfields = concat(postfields, zip);

    postfields = concat(postfields, "\"},\"Coupons\":[],\"CustomerID\":\"\",\"Email\":\"");
    postfields = concat(postfields, userEmail);

    postfields = concat(postfields, "\",\"Extension\":\"\",\"FirstName\":\"");
    postfields = concat(postfields, userFName);

    postfields = concat(postfields, "\",\"LastName\":\"");
    postfields = concat(postfields, userLName);

    postfields = concat(postfields, "\",\"LanguageCode\":\"en\",\"OrderChannel\":\"OLO\",\"OrderID\":\"Wr_Tz29AKs5wy6b2_0oi\",\"OrderMethod\":\"Web\",\"OrderTaker\":null,\"Payments\":[{\"Type\":\"CreditCard\",\"Amount\":14.42,\"Number\":\"");
    postfields = concat(postfields, userCardNum);
    
    postfields = concat(postfields, ",\",\"CardType\":\"\",\"Expiration\":\"");
    postfields = concat(postfields, userCardX);

    postfields = concat(postfields, "\",\"SecurityCode\":\"");
    postfields = concat(postfields, userCardSec);

    postfields = concat(postfields, "\",\"PostalCode\":\"47907\"}],\"Phone\":\"548358745\",\"Products\":[{\"AutoRemove\":false,\"Code\":\"14screen\",\"Qty\":1,\"ID\":1,\"isNew\":true,\"Options\":{\"C\":{\"1\\/1\":\"1\"},\"X\":{\"1\\/1\":\"1\"}}}],\"Market\":\"UNITED_STATES\",\"Currency\":\"USD\",\"ServiceMethod\":\"Delivery\",\"SourceOrganizationURI\":\"order.dominos.com\",\"StoreID\":\"9674\",\"Tags\":{},\"Version\":\"1.0\",\"NoCombine\":true,\"Partners\":{},\"NewUser\":true,\"metaData\":{},\"Amounts\":{\"Menu\":13.48,\"Discount\":0,\"Surcharge\":2.49,\"Adjustment\":0,\"Net\":13.48,\"Tax\":0.94,\"Tax1\":0.94,\"Tax2\":0,\"Bottle\":0,\"Customer\":14.42,\"Payment\":14.42},\"BusinessDate\":\"2019-11-20\",\"EstimatedWaitMinutes\":\"23-33\",\"PriceOrderTime\":\"2019-11-20 22:46:38\",\"IP\":\"199.204.83.184\",\"Promotions\":{\"Redeemable\":[],\"AvailablePromos\":{\"EndOfOrder\":\"8130\"},\"Valid\":[]},\"Status\":1,\"StatusItems\":[{\"Code\":\"PriceInformationRemoved\"}],\"AvailablePromos\":{\"EndOfOrder\":\"8130\"},\"PulseOrderGuid\":\"f48641ee-f9b0-42a4-9248-715f0aca23ae\",\"PriceOrderMs\":922,\"AmountsBreakdown\":{\"FoodAndBeverage\":\"10.99\",\"Adjustment\":\"0.00\",\"Surcharge\":\"0.00\",\"DeliveryFee\":\"2.49\",\"Tax\":0.94,\"Tax1\":0.94,\"Tax2\":0,\"Bottle\":0,\"Customer\":14.42,\"Savings\":\"0.00\"}}})");

    printf("postfields: %s", postfields);

    curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, postfields);

    FILE *f = fopen("target.txt", "wb");
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, f);

    CURLcode res = curl_easy_perform(hnd);


    if (res != CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
    curl_easy_strerror(res));
    } else {    
      printf("Order placed successfully. Estimated wait time: 20 minutes. Thank you for choosing Domino's!\n");
    }

    curl_easy_cleanup(hnd);
    curl_slist_free_all(headers); 
}

void printMenu(){

    printf("\n");
    #define CHUNK 2048 /* read 1024 bytes at a time */
    char buf[CHUNK];
    // FILE *file;
    size_t nread;

    FILE *readptr = fopen("menu.txt", "r");
    if (readptr) {
      while ((nread = fread(buf, 1, sizeof buf, readptr)) > 0)
      fwrite(buf, 1, nread, stdout); 
        printf("\n");
      fclose(readptr);
    } else {
      printf("menu not found.");
    }
    printf("\n");
}



void processOrder(){
    char temp;

    printf("To begin processing your order we'll need some basic information\n");
    printf("Street: ");
    scanf("%c",&temp);
    scanf("%[^\n]", street);

    printf("City: ");
    scanf("%c",&temp);
    scanf("%[^\n]", city);

    printf("Zip: ");
    scanf("%c",&temp);
    scanf("%[^\n]", zip);

    printf("State: ");
    scanf("%c",&temp);
    scanf("%[^\n]", state);

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

    postOrder();

}

void placeOrder(){
    char ans;
    printf("Begin your order by selecting items\n");
    printf("Enter items you want, press 0 to exit: ");
    scanf("%c",&ans);
    //this needs to be asking for peoples items one at a time, loop until they are done, creating + updating the LinkedList every time
    //andrew will fix this part
    /*
    while(ans != 0){
        scanf("%[^\n]", menuItems);
    }
    */

    //API code goes here
}


void searchNear(){
    char temp;

    printf("To find a location near you, please input your location\n");
    printf("Street address: ");
    scanf("%c",&temp);
    scanf("%[^\n]", locationAddr);

    printf("City: ");
    scanf("%c",&temp);
    scanf("%[^\n]", locationCity);

    //locationState
    printf("State: ");
    scanf("%c",&temp);
    scanf("%[^\n]", locationState);

    printf("Zip: ");
    scanf("%c",&temp);
    scanf("%s", locationZip);

    printf("The store closest to you is: ");
    findClosest();
}


void displayMenu(){
    char temp;
    char storeID[5];

    printf("Here is the menu selection from your nearest store\n");
    printf("Enter StoreID: ");
    scanf("%c",&temp);
    scanf("%[^\n]", storeID);

    printf("Menu for StoreID: %s\n", storeID);  //the value in location is completely a placeholder until we have the actual store ID
    printMenu();

}

int main () {
    int end = 0; 
    int choice = -1;

    printf("\nHi! Welcome to the Domino's Pizza Ordering Application!\n");
    do {
        printf("\nWhat would you like to do?\n1. Search for nearest store\n2. Display Menu\n3. Place Order\n4. Exit\n");
        printf("I'd like to choose option: ");
        scanf("%d", &choice);

        switch (choice){
            case 1:
                //search for nearest store
                searchNear();
                break;
            case 2:
                //display the menu for that store
                displayMenu();
                break;
            case 3:
                //place order for that store
                placeOrder();
                processOrder();
                break;
            case 4:
                //search for nearest store
                printf("Thank you for choosing Domino's!\n");
                break;
            default:
                printf("Invalid entry, please try again.");
                break;
        }
        // printf("\nWould you like to exit? (type 0 continue, 1 to exit): ");
        // scanf("%d", &end);

    } while (choice !=4);
}  //end of main
