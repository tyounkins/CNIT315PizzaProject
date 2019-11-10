#include <stdio.h>
#include <curl/curl.h>

int main () {

    printf("hello\n");    
    printf("lets do some test api calls :)\n");
     CURL *curl;
  CURLcode res;
 
  /* get a curl handle */ 
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */ 
    curl_easy_setopt(curl, CURLOPT_URL, "https://order.dominos.com/power/store-locator?s=&c=47906&type=Delivery");
    /* Now specify the POST data */ 
    // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "?s=&c=47906&type=Delivery"); 
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);

    printf(res);

    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
    return 0;
}