#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Address
{
  char* street;
  char* city;
  char* state;
  char* zip;
}Address;
Address* createAddress(char* str, char* cit, char* sta, char* z)
{
  Address* addr = (Address*)malloc(sizeof(Address));
  addr->street = str;
  printf("address: %s", addr->street);
  addr->city = cit;
  addr->state = sta;
  addr->zip = z;
  return addr;
}
void AddressToString(Address* addr)
{
  printf("\nAddress: %s, %s, %s, %s", addr->street, addr->city, addr->state, addr->zip);
  printf("\n");
}

typedef struct Store
{
  char* storeId;
  Address* storeAddr;
}Store;
Store* createStore(char* id, Address* addr)
{
  Store* sto = (Store*)malloc(sizeof(Store));
  sto->storeId = id;
  sto->storeAddr = addr;
  return sto;
}
void StoreToString(Store* sto)
{
  printf("\nStore ID: %s", sto->storeId);
  AddressToString(sto->storeAddr);
}

typedef struct OrderItem
{
  char* orderItemId;
  OrderItem* next;
}OrderItem;
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
}Order;
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
/* Scrapped this method for now since theoretically shouldn't be done with a queue
OrderItem* removeById(Order* order, char* id)
{//removes a specific item based on its ID, should be used if part of an order is deleted
  OrderItem* current = order->start;
  OrderItem* tail = order->start;
  if(current == NULL)
  {
    printf("Error: list is empty.");
    break;
  }
  if(current->next == NULL)
  {
    while(current != NULL)
    {
      if(current->orderItemId == id)
      {
        ;
      }
      else
        current = current->next;
    }
  }
  else
  {
    current = current->next;
    while(current != NULL)
    {
      if(current->orderItemId == id)
      {
        ;
      }
      else
        current = current->next;
    }
  }
}*/
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

int main()
{
  ;
}
