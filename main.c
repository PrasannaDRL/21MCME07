#include "buyer.h"
#include "shopkeeper.h"
#include <stdio.h>
#include <stdlib.h>



int main(){
    printf("Welcome to E-Commerce Store!!!\n\n\n");
    int choice = 'Y';
    int sid = -1;
    while(1){
        int role = -999;
        printf("Enter 1 for Shopkeeper login and 2 for Buyer login\n\n");
        scanf("%d",&role);
        if(role == 1){
            printf("Enter your id");
            scanf("%d",&sid);
            if(checkShopkeeper(sid) == 1){
                choice = 'Y';
                printf("Successful login!!");
                while(choice == 'Y'){
                    int todo = -98;
                    printf("\nHello shopkeeper\n\nEnter:\n1. To view orders\n2. To view items\n3. To add item\n4. To remove item\n5. To update item\n6.To view reports\n");
                    scanf("%d",&todo);
                    if(todo == 1){
                        printf("buyername itemId quantityTaken totalPrice orderDate\n");
                        viewOrders(sid);
                    }else if(todo == 2){
                        printf("Shopkeeper_id itemid itemname quantity price\n");
                        viewItems(sid);
                    }else if(todo == 3){
                        addItem(sid);
                    }else if(todo == 4){
                        int itemId;
                        printf("Enter item id:");
                        scanf("%d",&itemId);
                        removeItem(itemId,sid);
                    }else if(todo == 5){
                        int itemId;
                        printf("Enter item id to update:");
                        scanf("%d",&itemId);
                        updateItem(itemId,sid);
                    }else if(todo == 6){
                        char startDate[100];
                        char endDate[100];

                        // Take input for start and end date
                        printf("Enter the start date(dd/mm/yyyy):");
                        scanf("%s",startDate);

                        printf("Enter the end date(dd/mm/yyyy):");
                        scanf("%s",endDate);
                        viewReports(sid,startDate,endDate);
                    }else{
                        printf("Invalid choice!!\n");
                    }
                    printf("Do you want to continue(Y/N)\n");
                    scanf(" %c",&choice);
                }
                printf("Logged out successfully!\n");
            }else{
                char login = 'N';
                printf("You are not registered\n");
                printf("Do you want to register?(Y/N)");
                scanf(" %c",&login);
                if(login == 'Y'){
                    char *name = (char *)malloc(100 * sizeof(char));
                    printf("\n Enter your name");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    fgets(name, 100, stdin);
                    printf("\nYour id is: %d",addShopkeeper(name));
                    printf("%s",name);
                }
            }
        }else if(role == 2){
            printf("Hello buyer!!\n");
            int bid;
            printf("Enter your id");
            scanf("%d",&bid);
            if(checkBuyer(bid) == 1){
                choice = 'Y';
                while(choice == 'Y'){
                    printf("\nItems available:\n");
                    printf("Shopkeeper_id itemid itemname quantity price\n");
                    FILE *fp = fopen("data.txt","r");

                    char buffer[100];
                    // Skip the first line
                    fgets(buffer,sizeof(buffer),fp);

                    int shkId, id;
                    char name[100];
                    int quantity;
                    int price;

                    while (fscanf(fp, "%d %d %s %d %d", &shkId, &id, name, &quantity, &price) == 5) {
                        printf("%d %d %s %d %d\n",shkId, id, name, quantity, price);
                    }   
                    int todo = -98;
                    printf("\nEnter:\n1. To add to cart\n2. To place order\n3. To view cart\n");
                    scanf("%d",&todo);
                    if(todo == 1){
                        int itemid,sid,quantityTaken;
                        printf("Enter itemid and shopkeeper id to add item to cart");
                        scanf("%d %d",&itemid,&sid);
                        printf("Enter the quantity");
                        scanf("%d",&quantityTaken);
                        addtocart(itemid,sid,bid,quantityTaken);
                    }else if(todo == 2){
                        // printf("Shopkeepers available:\n");
                        // printf("Name id\n");
                        // FILE *fp = fopen("sklist.txt","r");
                        // int id;
                        // char skname[100];

                        // while(fscanf(fp,"%d %s",&id,skname) == 2){
                        //     printf("%s %d\n",skname,id);
                        // }

                        // printf("\n Enter the shopkeeper id u want to buy from");
                        // scanf("%d",&id);
                        
                        // if(checkShopkeeper(id) == 1){
                        //     int itemId,quantity;
                        //     printf("Shopkeeper_id itemid itemname quantity price\n");
                        //     viewItems(id);
                        //     printf("Enter the item id:");
                        //     scanf("%d",&itemId);
                        //     printf("Enter the item quantity:");
                        //     printf("%d",&quantity);
                            
                        //     makeOrder(itemId,id,quantity,skname);
                        // }else{
                        //     printf("The shopkeeper isn't available");
                        // }
                        float gst = 18; // fixing gst at 18%
                        printf("%d %f",bid,gst);
                        makeOrder(gst,bid);
                    }else if(todo == 3){
                        viewcart(bid);
                    }else{
                        printf("Invalid choice!!");
                    }
                    printf("Do you want to continue(Y/N)\n");
                    scanf(" %c",&choice);
                }
            }else{
                char login = 'N';
                printf("You are not registered\n");
                printf("Do you want to register?(Y/N)");
                scanf(" %c",&login);
                if(login == 'Y'){
                    char *name = (char *)malloc(100 * sizeof(char));
                    printf("\n Enter your name");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    fgets(name, 100, stdin);
                    printf("\nYour id is: %d",addBuyer(name));
                }
            }
        }else{
            printf("Invalid choice\n");
        }
    }
}