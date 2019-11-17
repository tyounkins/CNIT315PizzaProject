#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

void parseNearbyStoreData(void *ptr, size_t size, size_t nmemb, void *stream){
    // printf("whats up");
    // printf("my string:\n %s\n\n",ptr);
    int length = 126;
    char str3[length];

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

    // printf("\nstr3:%s\n\n", str3);
    // printf("\nHelp\n");

    // printf(")

    int count = 0; //like a boolean
    int commaCount = 0;

    for(int i = 0; i < length; i++){
      // printf("Hello");

      if(str3[i] == '"'){ //|| str3[i] == '{' 

        if(count == 4){
          printf("\n");
          count = 0;
        } else {
          count++;
        }
      
        // printf("flag is : %d", flag);
      } else if (str3[i] == '\\' && str3[i+1] == 'n'){
        printf("\n");
        i++;
      } else if (str3[i] == 'I' && str3[i+1] == 's'){
        i+=22;
      } else if (str3[i] == ':'){
        printf(": ");
      }  else if (str3[i] == ',' && commaCount <2){
        commaCount++;
        // printf("%c", str3[i]);
      } else if (str3[i] == ',' && commaCount ==2){
        // commaCount++;
        printf("%c", str3[i]);
        // printf(""); //print nothing
      } else {
        printf("%c",str3[i]);
      }

    }
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

int main()
{

  printf("hello\n");
  printf("lets do some test api calls :)\n");
  CURL *curl;
  CURLcode res;

  /* get a curl handle */
  curl = curl_easy_init();
  if (curl)
  {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
    curl_easy_setopt(curl, CURLOPT_URL, "https://order.dominos.com/power/store-locator?s=&c=47907&type=Delivery");
    /* Now specify the POST data */
    
    // printf("\n\n\ntest\n");

    /* Perform the request, res will get the return code */

    //writes out the response to target.txt


    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, parseNearbyStoreData);
    res = curl_easy_perform(curl);

    //post
    // curl_easy_setopt(curl, CURLOPT_URL, "https://order.dominos.com/power/store/${storeID}/menu?lang=EN&structured=true");
    // curl_easy_setopt(curl, CURLOPT_URL, "https://order.dominos.com/power/store/9674/menu?lang=en&structured=true");
    // curl_easy_setopt(curl, CURLOPT_IGNORE_CONTENT_LENGTH, 1L);

    // FILE *f = fopen("target.txt", "wb");
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, f);

    // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, parseStoreMenuData);


    // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "?s=&c=47906&type=Delivery");
        // res = curl_easy_perform(curl);



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

    // printf("help %s", HELP);
    // res = curl_easy_perform(curl);

    //implemenet a way to filter down curl_easy_perform

    /* Check for errors */
    // if (res != CURLE_OK)
    //   fprintf(stderr, "curl_easy_perform() failed: %s\n",
    //           curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
}