#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>
#include<process.h>
#include<windows.h>

static int orders=100;

/*for linked list*/
struct item{
     char name[11];
     int price;
     int orders;
     struct item *next;
};

/*for queue of orders*/
struct queue{
    int orderNo;
    struct queue *next;
};

struct complete{
    int orderNo;
    struct queue *next;
};

struct item *start=NULL;
struct complete *c_start;
struct queue *head=NULL;
struct queue *tail=NULL;

//basic functions
void addItem(char n[],int p);
void enqueue(int orderNo);
int dequeue();    //returns order no.
void addCompleted(int orderNo);
int itemsSize();
int queueSize();

void create();
void menu();
void takeOrder();
void showStatus();

//admin functions
void addItem_admin();
void deleteItem();
void adminStatus();
void adminLogin();
void changeStatus();
void gotoxy(int x,int y);
void welcome();
int peekQueue();

int itemsSize(){
    int c=0;
    struct item *ptr;
    ptr=start;
    while(ptr!=NULL){
        c++;
        ptr=ptr->next;
    }

    return c;
}

int queueSize(){
    int c=0;
    struct queue *ptr;
    ptr=head;
    while(ptr!=NULL){
        c++;
        ptr=ptr->next;
    }
    return c;
}

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

void welcome(){
	int i,k=6,r,q;
	gotoxy(40,5);
	for(i=0;i<=50;i++)
	printf("*");
	for(i=0;i<20;i++)
	{
	gotoxy(40,k);
	printf("*");
	gotoxy(90,k);
	printf("*");
	printf("\n");
	k++;
	}
	gotoxy(41,25);
	for(i=0;i<=49;i++)
	printf("*");
	gotoxy(45,7);

	printf("**** WELCOME TO NCN ICE CREAM PALOUR****");
	gotoxy(50,8);
	printf("what we offer?");
	gotoxy(45,9);
	printf("->fast service");
	gotoxy(45,10);
	printf("->hygine");
	gotoxy(45,11);
	printf("->order tracking system");


		gotoxy(50,14);
	printf("menu is being loaded....");
	gotoxy(50,15);
	for(r=0;r<=20;r++)
	{
		for(q=0;q<=10000000;q++);
		printf("%c",177);

	}
    gotoxy(50,16);
    printf("press any key to start");

	getch();
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

void addCompleted(int orderNO){
    struct complete *new_complete ;
    new_complete =(struct complete *)malloc(sizeof(struct complete));
    new_complete->orderNo=orderNO;
    new_complete->next=c_start;
    c_start=new_complete;

}

void addItem_admin(){

	char n[10];
	int p;
	printf("enter name of the ice cream\n");
	scanf("%s",&n);
	printf("enter amount\n");
	scanf("%d",&p);
    addItem(n,p);
    printf("%s was added in the menu",n);
    getch();
}

void deleteItem(){
    int k=1,choice;
	struct item *ptr,*pre;
	ptr=start;
	printf("********************************\n");
	printf("sr no.\t   flavours\t price\n");
	printf("********************************\n");
	while(ptr!=NULL){

		printf("%d\t   %s\t  %d rs\n\n",k,ptr->name,ptr->price);
		ptr=ptr->next;
		k++;
	}

	ptr=start;
	printf("select the item to delete ,0 to go back\n");
	scanf("%d",&choice);
	if(choice<=itemsSize() && choice>0){
        choice--;
        while(choice>0){
            choice--;
            pre=ptr;
            ptr=ptr->next;
        }

        printf("are you sure you want to delete %s? (1/0)",ptr->name);
        scanf("%d",&choice);
        if(choice==1){
            pre->next=ptr->next;
            free(ptr);
            printf("item was deleted");
            getch();
        }
	}
	else{
	    system("cls");
        printf("please select between 1 to %d\n",itemsSize());
        deleteItem();
	}
}

void create(){

	int i=0;
	char name[100];
	char arr_n[11][100]={"mango      ","sitaphal   ","litchi     ","coconut    ","jackfruit  ","kesar pista","chickoo    ","chocobite  ","kaju kismis","anjeer     "};
	int arr_p[]={60,50,50,70,50,60,70,50,70,70};
	for(i=0;i<10;i++){
		strcpy(name,arr_n+i);
	//	printf("string copied %s",arr_n+i);
		addItem(name,arr_p[i]);
	//	printf("added note\n");
	}
}

void menu(){
	int k=1;
	struct item *ptr;
	ptr=start;
	printf("********************************\n");
	printf("sr no.\t   flavours\t price\n");
	printf("********************************\n");
	while(ptr!=NULL){

		printf("%d\t   %s\t  %d rs\n\n",k,ptr->name,ptr->price);
		ptr=ptr->next;
		k++;
	}

    takeOrder();
    getch();
}

void takeOrder(){
    struct item *iceCream;
    iceCream=start;
    int choice,orderNO;
    char again;
    printf("enter ice cream no.\n");
    scanf("%d",&choice);

    if(choice<=itemsSize() && choice>0){
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
    }else{
        printf("please select between 1 to %d",itemsSize());
        takeOrder();
    }
}

void showStatus(){
	char c;
    struct queue *ptr;
    ptr=head;
     printf("pending\n");
    while(ptr!=NULL){
        printf("%d\n",ptr->orderNo);
        ptr=ptr->next;
    }

        ptr=c_start;
     printf("\ncompleted\n");
    while(ptr!=NULL){
        printf("%d\n",ptr->orderNo);
        ptr=ptr->next;
    }

    getch();
}

void adminStatus(){
    struct item *iceCream;
    int price,orders,total,sale=0;
    char name[11];
    iceCream=start;


    printf("product        price  orders    total\n");
    while(iceCream!=NULL){
         strcpy(name,iceCream->name);
         price =iceCream->price;
         orders=iceCream->orders;
         total = price*orders;
        printf("%s  \t%d\t%d\t%d\n",name,price,orders,total);
        sale+=total;
        iceCream=iceCream->next;
    }
    printf("total sale = %d\n",sale);
    getch();
}

void adminLogin(){
    char pass[10];
    char password[]="qwerty";
    int result=-1,c;
    int p=0;
    printf("enter password for admin\n");

	do{
		pass[p]=getch();
		if(pass[p]!='\r'){
			printf("*");
		}
		p++;
	}while(pass[p-1]!='\r');
	pass[p-1]='\0';
	//printf("\nYou have entered %s as password.",pass);
//	getch();
   // scanf("%s",&pass);
    //gets(pass);
    result=strcmp(pass,password);
    if(result!=0){
        printf("incorrect password\n");

    }else{
        do{
            system("cls");
            printf("\n\n1.inventory\t2.add item\t3.delete item\t4.change status \t5.logout\n");
            scanf("%d",&c);
            switch(c){
                case 1:adminStatus();
                    break;
                case 2:addItem_admin();
                    break;
                case 3:deleteItem();
                    break;
                case 4:changeStatus();
                    break;
				case 5:break;
                default:;
            }
        }while(c!=5);
    }

}

void changeStatus(){
    int c=-1,c1=0,orderNo;
     system("cls");
     showStatus();
    while((c!=0) && (queueSize()>0)){
        c1=peekQueue();

    	if(c!=1){

        	printf("press 1 to complete order %d \n 0 to exit\n",c1);
        	//getch();
        	fflush(stdout);
        	scanf(" %d",&c);
    	}
		if (c==1){
            orderNo=dequeue();
            addCompleted(orderNo);
            system("cls");
            printf("order no %d was completed\n",orderNo);
            showStatus();

        }else{
            break;
        }
//        system("cls");
//        showStatus();
        c1=peekQueue();
        printf("press 1 to complete order %d \n 0 to exit\n",c1);
        fflush(stdout);
        scanf("%d",&c);
    }
    //while(c!=0);

    if(queueSize()<=0){

        printf("\nthere are no pending orders\n");
    }

}

void gotoxy(int x,int y){
	COORD coord;
	HANDLE a;
	coord.X=x;
	coord.Y=y;
	a=GetStdHandle(STD_OUTPUT_HANDLE);

SetConsoleCursorPosition(a,coord);

}


int peekQueue(){
    return head->orderNo;

}

int main()
{
	int c;
	welcome();
    create();

	do{
        system("cls");
        printf("items in menu %d \t pending orders %d\n",itemsSize(),queueSize());
		printf("********main menu*********\n\n");
		printf("     1. MENU AND ORDER\n\n     2. ORDER STATUS\n\n     3. ADMIN LOGIN\n\n     4. EXIT\n\n");
		printf("     enter choice\n");
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
