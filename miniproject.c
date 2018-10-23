#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<malloc.h>

static int orders=100;

/*for linked list*/
struct item{
     char name[10];
     int price;
     int orders;
     struct item *next;
};

/*for queue of orders*/
struct queue{
    int orderNo;
    struct queue *next;
};


struct item *start=NULL;

struct queue *head=NULL;
struct queue *tail=NULL;

//basic functions
void addItem(char n[],int p);
void enqueue(int orderNo);
int dequeue();    //returns order no.

void create();
void menu();
void takeOrder();
void showStatus();

//admin functions
void addItem_admin();
void adminStatus();
void adminLogin();


void addItem(char n[],int p){

//printf("inside add item\n");
	struct item *ptr,*new_item;
	new_item=(struct item *)malloc(sizeof(struct item));
  //	new_item->name=n;
	new_item->price=p;
	strcpy(new_item->name,n);
	new_item->orders=0;
	new_item->next=NULL;

	//traversing
	if(start==NULL){
        start=new_item;
	}else{
	 ptr=start;
	 while(ptr->next!=NULL){
	  	ptr=ptr->next;
	 }
	ptr->next=new_item;
	}
}

void enqueue(int orderNo){
    struct queue *new_order;
    new_order=(struct queue *)malloc(sizeof(struct queue));
    new_order->orderNo=orderNo;
    new_order->next=NULL;

    if(head==NULL){     //queue is empty
            head=new_order;
            tail=head;

    }else{    //only one order is in queue
            tail->next=new_order;
            tail= tail->next;
    }
}

int dequeue(){
  struct queue *ptr;

    if(head==NULL){  //queue empty
        return -1;
    }else if(head==tail){    //single element
          ptr=head;
          head=NULL;
          tail=NULL;
    }else{
        ptr=head;
        head=head->next;
    }

    return ptr->orderNo;

}

void addItem_admin(){

	char n[10];
	int p;
	printf("enter name of the ice cream\n");
	scanf("%s",&n);
	printf("enter amount\n");
	scanf("%d",&p);
    addItem(n,p);

}

void create(){
	printf("menu  created\n");
	int i=0;
	char name[10];
	char arr_n[10][10]={"a1","b2","c3","d4","e5","f6","g7","h8","i9","j0"};
	int arr_p[]={10,20,30,40,50,60,70,80,90,100};
	for(i=0;i<10;i++){
		strcpy(name,arr_n+i);
	//	printf("string copied %s",arr_n+i);
		addItem(name,arr_p[i]);
	//	printf("added note\n");
	}
}

void menu(){
	struct item *ptr;
	ptr=start;

	while(ptr!=NULL){
		printf("%s \t %d\n",ptr->name,ptr->price);
		ptr=ptr->next;
	}

    takeOrder();
}

void takeOrder(){
    struct item *iceCream;
    iceCream=start;
    int choice,orderNO;
    char again;
    printf("enter ice cream no.\n");
    scanf("%d",&choice);

    choice--;
    while(choice>0){
        choice--;
        iceCream=iceCream->next;

    }
    printf("you selected %s\n",iceCream->name);
    iceCream->orders+=1;
    orderNO=orders++;
    printf("your order no is %d\n",orderNO);
    enqueue(orderNO);
//    printf("do yo want to order again (y/n)?\n");
//    scanf("%d",&again);
//    if(again=='y'){
//        takeOrder();
//    }else{
//       printf("going back....");
//    }
}

void showStatus(){
    struct queue *ptr;
    ptr=head;
     printf("pending\n");
    while(ptr!=NULL){
        printf("%d\n",ptr->orderNo);
        ptr=ptr->next;
    }

}

void adminStatus(){
    struct item *iceCream;
    int price,orders,total,sale=0;
    char name[10];
    iceCream=start;


    printf("product\tprice\torders\ttotal\n");
    while(iceCream!=NULL){
         strcpy(name,iceCream->name);
         price =iceCream->price;
         orders=iceCream->orders;
         total = price*orders;
        printf("%s\t%d\t%d\t%d\n",name,price,orders,total);
        sale+=total;
        iceCream=iceCream->next;
    }
    printf("total sale = %d\n",sale);
}

void adminLogin(){
    char pass[10];
    char password[]="aaa";
    int result=-1,c;
    printf("enter password for admin\n");
    scanf("%s",&pass);
    //gets(pass);
    result=strcmp(pass,password);
    if(result!=0){
        printf("incorrect password\n");

    }else{
        do{
            printf("1.status\t2.add item\t3.logout\n");
            scanf("%d",&c);
            switch(c){
                case 1:adminStatus();

                    break;
                case 2:addItem_admin();
                    break;
                case 3:break;

            }
        }while(c!=3);
    }
}

int main()
{
	int c;
    create();
	//addItem("banana",10);
	do{
		printf("1. MENU AND ORDER\t2. ORDER STATUS\t3. ADMIN LOGIN\t4. EXIT\n");
		printf("enter choice\n");
		scanf("%d",&c);
		switch(c)
		{
			case 1: menu();
			break;
			case 2: showStatus();
			break;
			case 3: adminLogin();
			break;
			case 4:break;
		}

	}
	while(c!=4);

}

