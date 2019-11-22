#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

void parseNearbyStoreData(void *ptr, size_t size, size_t nmemb, void *stream){
    // printf("whats up");
    // printf("my string:\n %s\n\n",ptr);
    int length = 126;
    char str3[length];

    printf("\n\n");

    // strncpy ( str3, ptr, 70 );
    // str3[70] = '\0';   /* null characte
    // r manually added */
    // printf("\n\nthis is my string: %s", str3);

    // char str[] ="This is a simple string";
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
    // printf("\nID:%s\n", ID);

    int count = 0; //like a boolean
    int commaCount = 0;
    printf("\nfuck off seg fault");
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
    printf("\nfuck off seg fault");
  printf("\n");

}

void parseStoreMenuData(void *ptr, size_t size, size_t nmemb, void *stream){
    printf("order menu data\n\n");

    //for some reason this ptr is not receiving the entire size 
    // printf("my string:\n %s\n\n",ptr);


    char * pch = strstr (ptr,"PreconfiguredProducts");

    printf("SUPPPPPP\n\n\n%s",pch);

    int length = 1000;
    char str3[length];
    strncpy(str3, pch, length);
    // str3[length] = "\0";

    printf("\nstr3:%s\n\n", str3);

}

void findClosest(){
  CURL *curl;
  CURLcode res;

  /* get a curl handle */
  curl = curl_easy_init();
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, "https://order.dominos.com/power/store-locator?s=&c=47907&type=Delivery");

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, parseNearbyStoreData);
    curl_easy_perform(curl);
  }
  curl_global_cleanup();
}

void placeOrder(){

  CURL *curl;
  CURLcode res;

  /* get a curl handle */
  curl = curl_easy_init();
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, "http://order.dominos.com/power/validate-order");
    // char fuckyou[2000]= "{\"Order\":{\"Address\":{\"Street\":\"301 EVERGREEN ST\",\"StreetNumber\":\"301\",\"StreetName\":\"EVERGREEN ST\",\"UnitType\":\"\",\"UnitNumber\":\"\",\"City\":\"WEST LAFAYETTE\",\"Region\":\"IN\",\"PostalCode\":\"47907\"},\"Coupons\":[],\"CustomerID\":\"\",\"Email\":\"jdhfghjkdfg@gmailcom\",\"Extension\":\"\",\"FirstName\":\"taylor\",\"LastName\":\"younkins\",\"LanguageCode\":\"en\",\"OrderChannel\":\"OLO\",\"OrderID\":\"\",\"OrderMethod\":\"Web\",\"OrderTaker\":null,\"Payments\":[],\"Phone\":\"548358745\",\"Products\":[{\"AutoRemove\":false,\"Code\":\"14screen\",\"Qty\":1,\"ID\":1,\"isNew\":true,\"Options\":{\"C\":{\"1\\/1\":\"1\"},\"X\":{\"1\\/1\":\"1\"}}}],\"Market\":\"\",\"Currency\":\"\",\"ServiceMethod\":\"Delivery\",\"SourceOrganizationURI\":\"order.dominos.com\",\"StoreID\":\"9674\",\"Tags\":{},\"Version\":\"1.0\",\"NoCombine\":true,\"Partners\":{},\"NewUser\":true,\"metaData\":{},\"Amounts\":{},\"BusinessDate\":\"\",\"EstimatedWaitMinutes\":\"\",\"PriceOrderTime\":\"\"}}";
    char fuckyou[2000] = "{\"Order\":{\"Address\":{\"Street\":\"301 EVERGREEN ST\",\"StreetNumber\":\"301\",\"StreetName\":\"EVERGREEN ST\",\"UnitType\":\"\",\"UnitNumber\":\"\",\"City\":\"WEST LAFAYETTE\",\"Region\":\"IN\",\"PostalCode\":\"47907\"},\"Coupons\":[],\"CustomerID\":\"\",\"Email\":\"jdhfghjkdfg@gmailcom\",\"Extension\":\"\",\"FirstName\":\"taylor\",\"LastName\":\"younkins\",\"LanguageCode\":\"en\",\"OrderChannel\":\"OLO\",\"OrderID\":\"gRXppWj3H4KTx9N2psQn\",\"OrderMethod\":\"Web\",\"Payments\":[{\"Type\":\"CreditCard\",\"Amount\":14.42,\"Number\":\"123123\",\"CardType\":\"\",\"Expiration\":\"3453\",\"SecurityCode\":\"123\",\"PostalCode\":\"47907\"}],\"Phone\":\"548358745\",\"Market\":\"UNITED_STATES\",\"Currency\":\"USD\",\"ServiceMethod\":\"Delivery\",\"SourceOrganizationURI\":\"order.dominos.com\",\"StoreID\":\"9674\",\"Tags\":{},\"Version\":\"1.0\",\"NoCombine\":true,\"Partners\":{},\"NewUser\":true,\"metaData\":{},\"BusinessDate\":\"2019-11-20\",\"EstimatedWaitMinutes\":\"0\",\"PriceOrderTime\":\"2019-11-20 22:46:38\",\"IP\":\"199.204.83.184\",\"Promotions\":{\"Redeemable\":[],\"AvailablePromos\":{\"EndOfOrder\":\"8130\"},\"Valid\":[]},\"AvailablePromos\":{\"EndOfOrder\":\"8130\"},\"PulseOrderGuid\":\"f48641ee-f9b0-42a4-9248-715f0aca23ae\",\"PriceOrderMs\":922,\"AmountsBreakdown\":{\"FoodAndBeverage\":\"10.99\",\"Adjustment\":\"0.00\",\"Surcharge\":\"0.00\",\"DeliveryFee\":\"2.49\",\"Tax\":0.94,\"Tax1\":0.94,\"Tax2\":0,\"Bottle\":0,\"Customer\":14.42,\"Savings\":\"0.00\"},\"Status\":1,\"StatusItems\":[{\"Code\":\"AutoAddedOrderId\"},{\"Code\":\"PriceInformationRemoved\"}],\"Products\":[]},\"Status\":1,\"Offer\":{\"CouponList\":[],\"ProductOffer\":\"\"},\"EmailHash\":null,\"StatusItems\":[{\"Code\":\"Warning\"}]}";
    printf("%s", fuckyou);

    struct curl_slist *headers=NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Referer: https://order.dominos.com/en/pages/order");

    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, sizeof(fuckyou));

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fuckyou);

    curl_easy_perform(curl); /* post away! */
    printf("\n kms");

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers); 

    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
    curl_easy_strerror(res));

  }
    curl_global_cleanup();
}

void printOrder(){
#define CHUNK 2048 /* read 1024 bytes at a time */
    char buf[CHUNK];
    // FILE *file;
    size_t nread;

    // printf("the fuck is going on.");

    FILE *readptr = fopen("menu.txt", "r");
    // file = fopen("test.txt", "r");
    if (readptr)
    {
      while ((nread = fread(buf, 1, sizeof buf, readptr)) > 0)

        // printf("%s", );
      fwrite(buf, 1, nread, stdout); 
        printf("\n");
      fclose(readptr);
    }
}


int main()
{

  printf("hello\n");
  printf("lets do some test api calls :)\n");
  placeOrder();


   /* free the header list */

    //post
    // curl_easy_setopt(curl, CURLOPT_URL, "https://order.dominos.com/power/store/${storeID}/menu?lang=EN&structured=true");
    // curl_easy_setopt(curl, CURLOPT_URL, "https://order.dominos.com/power/store/9674/menu?lang=en&structured=true");
    // curl_easy_setopt(curl, CURLOPT_IGNORE_CONTENT_LENGTH, 1L);

    // FILE *f = fopen("target.txt", "wb");
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, f);

    // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, parseStoreMenuData);


    // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fuckyou);
        // res = curl_easy_perform(curl);



    // printf("help %s", HELP);
    // res = curl_easy_perform(curl);

    //implemenet a way to filter down curl_easy_perform

    /* Check for errors */
    // if (res != CURLE_OK)
    //   fprintf(stderr, "curl_easy_perform() failed: %s\n",
    //           curl_easy_strerror(res));

    /* always cleanup */
    // curl_easy_cleanup(curl);
  

  return 0;
}