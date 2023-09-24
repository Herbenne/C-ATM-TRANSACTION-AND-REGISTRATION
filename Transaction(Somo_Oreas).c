#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#define MAX 1000

typedef struct data{
    char name[50];
    char pin[7];
    char phone[20];
    char bday[20];
    int acountNo;
    int balance;
    int last;
}list;

list l;
list accountInfo[MAX];

char inputPin[7];
char regPin[7];
char confirmPin[7];
char pinFromCard[7];
char* checkDrives[2] = {"C:\\checkFd.dbf", "E:\\checkFd.dbf"};
char* drives[2] = {"C:\\bank.dbf","E:\\bank.dbf"};
int accountNoFromCard, regAccountNo, regBalance, accountIndex, otherAccIndex, ctr = -1, exist = 0, checkName = 0, checkPin = 0, pinCharacter = 0;

void makenull();
void retrieve();
int insertCard();
int checkFd();
void pinEnter();
int transaction();
int isEmpty();
int isFull();
void insert();
int locate();
void save();
void saveToCard();
void checkPinFromCard();
int confirmTransaction(int x, int y, int len);

void gotoxy(int x, int y);
COORD coord = {0,0};
void clear(char *label);
void printToxy(int x, int y, char* label);

int main()
{
    int i;
    system("color 0B");
    makenull();
    retrieve();
    if(insertCard()){
        pinEnter();
        accountIndex = locate(1);
        do{
            _getch();
            system("cls");
            system("color 0B");

        }while(transaction());
    }
    i = remove(checkDrives[ctr]);
    printf("Name: Somo, Herbenne Rey & Oreas, Nyl Bhoy\tBSIS - 2AB\n\nInstructor: Prof. Fernando Renegado\n\n");
    _getch();
    return 0;
}

void makenull(){
    l.last = -1;
}

void retrieve(){
    FILE *fp;
    int i = 0;
    fp = fopen("acclist.dbf","r+");

    if (fp==NULL){
        printf("\t\t\t\t\t_______________________________________\n");
        printf("\t\t\t\t\t|   < < < DATA BASE IS EMPTY > > >    |\n");
        printf("\t\t\t\t\t|_____________________________________|\n\n");
        printf("You Must Register First");
        _getch();
        exit(0);
    }
    else{
        while(!feof(fp)){
            l.last++;
            fscanf(fp,"%d %[^\t]%d %[^\t] %[^\t] %[^\n]",&accountInfo[l.last].acountNo,accountInfo[l.last].name,&accountInfo[l.last].balance,accountInfo[l.last].phone, accountInfo[l.last].bday, accountInfo[l.last].pin);
        }
    }
    fclose(fp);
}

int insertCard(){
    FILE *fp;
    printf("\t\t\t\t\t_______________________________________\n");
    printf("\t\t\t\t\t| < < < Please Insert Your Card > > > |\n");
    printf("\t\t\t\t\t|_____________________________________|\n\n");
    do{
        ctr = (ctr + 1) % 2;
        fp = fopen(checkDrives[ctr],"w");
    }while(fp == NULL);
    fclose(fp);

    fp = fopen(drives[ctr],"r");
    if(fp == NULL){
        printf("\t\t\t\t\t_______________________________________\n");
        printf("\t\t\t\t\t|        You Are Not Registered       |\n");
        printf("\t\t\t\t\t|_____________________________________|\n\n");
        return 0;
    }
    else{
        while(!feof(fp))
            fscanf(fp,"%d %[^\n]",&accountNoFromCard,pinFromCard);

        for(int i = 0; i < l.last + 1; i++){
            if(strcmp(accountInfo[i].pin,pinFromCard) == 0 && accountInfo[i].acountNo == accountNoFromCard){
                printf("\t\t\t\t\t_______________________________________\n");
                printf("\t\t\t\t\t|          You Are Registered.        |\n");
                printf("\t\t\t\t\t|_____________________________________|\n\n");
                return 1;
            }
        }
        printf("\t\t\t\t\t_______________________________________\n");
        printf("\t\t\t\t\t|      You Are Not Registered!!!.     |\n");
        printf("\t\t\t\t\t|_____________________________________|\n\n");
        return 0;
    }
    fclose(fp);
}

int checkFd(){
    FILE *fp;
    fp = fopen(checkDrives[ctr],"r");
    if(fp == NULL){
        printf("\t\t\t\tF L A S H   D R I V E   E R R O R");
        return 1;
    }
    return 0;
    fclose(fp);
}

void pinEnter(){
    int i = 0;
    do{
        if(i == 3){
            printf(" LOOGING OUT . . .");
            exit(0);
        }
        printf("\t\t\t\tPIN NUMBER: ");
        for(int i = 0; i < 6; i++){
            inputPin[i] = _getch() + 9;
            putchar('*');
            putchar(' ');
        }
        inputPin[6] = '\0';

        if(strcmp(inputPin,pinFromCard) != 0){
        printf("\n\t\t\t\t\t_______________________________________\n");
        printf("\t\t\t\t\t|              Invalid PIN            |\n");
        printf("\t\t\t\t\t|_____________________________________|\n\n");
            _getch();
        }
        i++;
    }while(strcmp(inputPin,pinFromCard) != 0);
    system("pause");
}

int locate(int x){

    if(x == 0){
        for(int i = 0; i < l.last + 1; i++){
            if(strcmp(accountInfo[i].pin,regPin) == 0){
                checkPin = 1;
                return 1;
            }
        }
        return 0;
    }
    else if(x == 1){
        for(int i = 0; i < l.last + 1; i++){
            if(accountInfo[i].acountNo == accountNoFromCard)
                return i;
        }
        return 0;
   }
   else if(x == 2){
        for(int i = 0; i < l.last + 1; i++){
            if(accountInfo[i].acountNo == regAccountNo){
                otherAccIndex = i;
                return 0;
            }
        }
        return 1;
   }
}

int transaction(){
    char choice;
    int end;
    printf("\t\t\t\t\t\t< < < TRANSACTION > > >\n\n");
                    printf("\t\t_______________________");
                    printf("\n\t\t|  [A]Balance Inquiry |\n");
                    printf("\t\t|_____________________|\n");

                    printf("\t\t\t_______________________");
                    printf("\n\t\t\t|   [B]Deposit        |\n");
                    printf("\t\t\t|_____________________|\n");

                    printf("\t\t\t\t_______________________");
                    printf("\n\t\t\t\t|   [C]Withdraw       |\n");
                    printf("\t\t\t\t|_____________________|\n");

                    printf("\t\t\t\t\t_______________________");
                    printf("\n\t\t\t\t\t|      [D]Transfer    |\n");
                    printf("\t\t\t\t\t|_____________________|\n");

                    printf("\t\t\t\t\t\t_______________________");
                    printf("\n\t\t\t\t\t\t|   [E]Change PIN     |\n");
                    printf("\t\t\t\t\t\t|_____________________|\n");

                    printf("\t\t\t\t\t\t\t_______________________");
                    printf("\n\t\t\t\t\t\t\t|      [X]EXIT        |\n");
                    printf("\t\t\t\t\t\t\t|_____________________|\n");
    printf("\n\t\t\t\tCHOICE : ");
    scanf(" %c",&choice);
    if(choice == 'c' || choice == 'C'){
        if(accountInfo[accountIndex].balance != 0){
            do{
                printf("\n\t\t\t\t\t_______________________________________\n");
                printf("\t\t\t\t\t|          AMOUNT OF WIHDRAW          |\n");
                printf("\t\t\t\t\t|_____________________________________|\n\n");
                printf("\t\t\t\t\tEnter Amount: Php  ");
                scanf("%d",&regBalance);
                if(regBalance > accountInfo[accountIndex].balance){
                    printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|                AMOUNT               |\n");
                    printf("\t\t\t\t\t|         GREATER THAN BALANCE        |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|_____________________________________|\n\n");
                    _getch();
                }
                else if(regBalance < 0){
                    printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|           NEGATIVE BALANCE          |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|_____________________________________|\n\n");
                    _getch();
                }
                else if(regBalance == 0){
                    printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|              INVALID!!!             |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|_____________________________________|\n\n");
                    _getch();
                }
            }while(regBalance > accountInfo[accountIndex].balance || regBalance < 0 || regBalance == 0);
            if(confirmTransaction(44,11,76)){
                if(checkFd()){
                    exit(0);
                }
                accountInfo[accountIndex].balance -= regBalance;
                system("color 0B");
                printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|              SUCCESS!!!             |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|_____________________________________|\n\n");
            }
            else{
                printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|              CANCELLED              |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|_____________________________________|\n\n");
            }
        }
        else{
            printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
            printf("\t\t\t\t\t|                                     |\n");
            printf("\t\t\t\t\t|                                     |\n");
            printf("\t\t\t\t\t|              NO BALANCE             |\n");
            printf("\t\t\t\t\t|                                     |\n");
            printf("\t\t\t\t\t|                                     |\n");
            printf("\t\t\t\t\t|_____________________________________|\n\n");
        }
    }
    else if(choice == 'b' || choice == 'B'){
        do{
            printf("\n\t\t\t\t\t_______________________________________\n");
            printf("\t\t\t\t\t|          AMOUNT OF DEPOSIT          |\n");
            printf("\t\t\t\t\t|_____________________________________|\n\n");
            printf("\t\t\t\t\tEnter Amount: Php  ");
            scanf("%d",&regBalance);
            if(regBalance < 0){
                printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|           NEGATIVE BALANCE          |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|_____________________________________|\n\n");
                _getch();
            }
            else if(regBalance == 0){
                 printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                 printf("\t\t\t\t\t|                                     |\n");
                 printf("\t\t\t\t\t|               INVALID               |\n");
                 printf("\t\t\t\t\t|                                     |\n");
                 printf("\t\t\t\t\t|                                     |\n");
                 printf("\t\t\t\t\t|                                     |\n");
                 printf("\t\t\t\t\t|_____________________________________|\n\n");
                _getch();
            }
        }while(regBalance < 0 || regBalance == 0);
        if(confirmTransaction(44,11,76)){
                if(checkFd()){
                    exit(0);
                }
                system("color 0B");
                accountInfo[accountIndex].balance += regBalance;
                printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|              SUCCESS!!!             |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|_____________________________________|\n\n");
            }
        else{
            printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
            printf("\t\t\t\t\t|                                     |\n");
            printf("\t\t\t\t\t|                                     |\n");
            printf("\t\t\t\t\t|              CANCELLED              |\n");
            printf("\t\t\t\t\t|                                     |\n");
            printf("\t\t\t\t\t|                                     |\n");
            printf("\t\t\t\t\t|_____________________________________|\n\n");
        }
    }
    else if(choice == 'a' || choice == 'A'){
        if(checkFd()){
            exit(0);
        }
        printf("\n\t\t\t\t\t_______________________________________\n");
        printf("\t\t\t\t\t|            Your Balance             |\n");
        printf("\t\t\t\t\t|_____________________________________|\n\n");
        printf("\t\t\t\t\tBalance: Php  %d", accountInfo[accountIndex].balance);
    }

    else if(choice == 'd' || choice == 'D'){
        if(l.last > 0){
            if(accountInfo[accountIndex].balance != 0){
                do{
                    otherAccIndex = -1;
                    printf("\n\t\t\t\t\t_______________________________________\n");
                    printf("\t\t\t\t\t|            FUND TRANSFER            |\n");
                    printf("\t\t\t\t\t|_____________________________________|\n\n");
                    printf("\t\t\t\t\tEnter Account No. you want to Transfer:  ");
                    scanf("%d",&regAccountNo);
                    if(locate(2)){
                        printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                        printf("\t\t\t\t\t|                                     |\n");
                        printf("\t\t\t\t\t|          ACC NO. DOESN'T            |\n");
                        printf("\t\t\t\t\t|              EXIST                  |\n");
                        printf("\t\t\t\t\t|                                     |\n");
                        printf("\t\t\t\t\t|                                     |\n");
                        printf("\t\t\t\t\t|_____________________________________|\n\n");
                        _getch();
                    }
                    else if(accountInfo[accountIndex].acountNo == accountInfo[otherAccIndex].acountNo){
                        otherAccIndex = -1;
                        printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                        printf("\t\t\t\t\t|                                     |\n");
                        printf("\t\t\t\t\t|               INVALID               |\n");
                        printf("\t\t\t\t\t|              ACC NUMBER             |\n");
                        printf("\t\t\t\t\t|                                     |\n");
                        printf("\t\t\t\t\t|                                     |\n");
                        printf("\t\t\t\t\t|_____________________________________|\n\n");
                        _getch();
                    }
                    else{
                        do{
                            printf("\n\t\t\t\t\t_______________________________________\n");
                            printf("\t\t\t\t\t|            FUND TRANSFER            |\n");
                            printf("\t\t\t\t\t|_____________________________________|\n\n");
                            printf("\t\t\t\t\tEnter Amount Balance:  ");
                            scanf("%d",&regBalance);
                            if(regBalance > accountInfo[accountIndex].balance){
                                printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                                printf("\t\t\t\t\t|                                     |\n");
                                printf("\t\t\t\t\t|               DOES NOT              |\n");
                                printf("\t\t\t\t\t|               ENOUGH                |\n");
                                printf("\t\t\t\t\t|               BALANCE               |\n");
                                printf("\t\t\t\t\t|                                     |\n");
                                printf("\t\t\t\t\t|_____________________________________|\n\n");
                                _getch();
                            }
                            else if(regBalance < 0){
                                printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                                printf("\t\t\t\t\t|                                     |\n");
                                printf("\t\t\t\t\t|               NEGATIVE              |\n");
                                printf("\t\t\t\t\t|                 ENTRY               |\n");
                                printf("\t\t\t\t\t|                                     |\n");
                                printf("\t\t\t\t\t|                                     |\n");
                                printf("\t\t\t\t\t|_____________________________________|\n\n");
                                _getch();
                            }
                            else if(regBalance == 0){
                                printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                                printf("\t\t\t\t\t|                                     |\n");
                                printf("\t\t\t\t\t|               INVALID               |\n");
                                printf("\t\t\t\t\t|                                     |\n");
                                printf("\t\t\t\t\t|                                     |\n");
                                printf("\t\t\t\t\t|                                     |\n");
                                printf("\t\t\t\t\t|_____________________________________|\n\n");
                                _getch();
                            }
                        }while(regBalance < 0 || regBalance > accountInfo[accountIndex].balance || regBalance == 0);
                    }
                }while(otherAccIndex == -1);
                if(confirmTransaction(44,11,76)){
                    if(checkFd()){
                        exit(0);
                    }
                    system("color 0B");
                    accountInfo[accountIndex].balance -= regBalance;
                    accountInfo[otherAccIndex].balance += regBalance;
                    printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|              SUCCESS!!!             |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|_____________________________________|\n\n");
                }
                else{
                    printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|              CANCELLED              |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|_____________________________________|\n\n");
                }
            }
            else{
                printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|              NO BALANCE             |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|_____________________________________|\n\n");
            }
        }
        else if(l.last == 0){
                printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|         THERE'S NO ACCOUNT          |\n");
                printf("\t\t\t\t\t|            IN THE LIST              |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|_____________________________________|\n\n");
        }
    }

    else if(choice == 'e' || choice == 'E'){
        do{
            if(checkFd()){
                exit(0);
            }
            checkPinFromCard();
            do{
                printf("\n\t\t\t\t\t_______________________________________\n");
                printf("\t\t\t\t\t|            CHANGE PIN               |\n");
                printf("\t\t\t\t\t|_____________________________________|\n\n");
                printf("\t\t\t\t\tEnter Current PIN:  ");

                for(int i = 0; i < 6; i++){
                    inputPin[i] = _getch() + 9;
                    putchar('*');
                    putchar(' ');
                }
                printf("\n\t\t\t\t\t_____________________________________\n");
                if(strcmp(inputPin,pinFromCard) != 0){
                    printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|               INVALID               |\n");
                    printf("\t\t\t\t\t|                 PIN                 |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|                                     |\n");
                    printf("\t\t\t\t\t|_____________________________________|\n\n");
                    _getch();
                }
            }while(strcmp(inputPin,pinFromCard) != 0);
            printf("\t\t\t\t\tEnter new PIN:  ");
            for(int i = 0; i < 6; i++){
                regPin[i] = _getch() + 9;
                putchar('*');
                putchar(' ');
            }
            regPin[6] = '\0';
            printf("\n\t\t\t\t\t_____________________________________\n");
            printf("\t\t\t\t\tConfirm new PIN:  ");
            for(int i = 0; i < 6; i++){
                confirmPin[i] = _getch() + 9;
                putchar('*');
                putchar(' ');
            }
            confirmPin[6] = '\0';

            end = strcmp(confirmPin,regPin);

            checkPin = 0;
            pinCharacter = 0;

            for(int i = 0; i < 6; i++){
                if(isdigit(confirmPin[i] - 9)  == 0){
                    pinCharacter = 1;
                    break;
                }
            }

            if(end != 0){
                printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|               PIN DID               |\n");
                printf("\t\t\t\t\t|               NOT MATCH             |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|_____________________________________|\n\n");
                _getch();
            }

            else if(locate(0) && checkPin == 1){
                printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|               YOUR PIN IS           |\n");
                printf("\t\t\t\t\t|               TOO COMMON            |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|_____________________________________|\n\n");
                _getch();
            }

            else if(pinCharacter == 1){
                printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|               YOUR PIN HAS          |\n");
                printf("\t\t\t\t\t|               A CHARACTER           |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|                                     |\n");
                printf("\t\t\t\t\t|_____________________________________|\n\n");
                _getch();
            }

        }while(end != 0 || checkPin || pinCharacter);
        if(checkFd()){
            exit(0);
        }
        system("color 0B");
        strcpy(accountInfo[accountIndex].pin,regPin);
        ("S U C C E S S ! ! !");
        saveToCard();
    }

    else if(choice == 'x' || choice == 'X'){
        printf("Thank You For Using Our BANK\n\n\n");
        return 0;
    }
    else{
        printf("\n\n\n\n\n\n\n\t\t\t\t\t_______________________________________\n");
        printf("\t\t\t\t\t|                                     |\n");
        printf("\t\t\t\t\t|               INVALID               |\n");
        printf("\t\t\t\t\t|                 CHOICE              |\n");
        printf("\t\t\t\t\t|                                     |\n");
        printf("\t\t\t\t\t|                                     |\n");
        printf("\t\t\t\t\t|_____________________________________|\n\n");
    }
    save();
    return 1;
}

void checkPinFromCard(){
    FILE* fp;
    fp = fopen(drives[ctr],"r");
    while(!feof(fp))
            fscanf(fp,"%d %[^\n]",&accountNoFromCard,pinFromCard);
}

int confirmTransaction(int x, int y, int len){
    char input;
    for(int i = y; i < y + 8; i++)
        printToxy(x,i,"                                ");
    for(int i = x; i < len; i++){
        printToxy(i,y - 1,"_");
        printToxy(i,y + 2,"_");
        printToxy(i, y + 7,"_");
    }
    for(int i = y; i < y + 8; i++){
        printToxy(x - 1,i,"|");
        printToxy(len,i,"|");
    }
    printToxy(x + 6,y + 1,"CONFIRM TRANSACTION?");
    printToxy(x + 5,y + 5,"[Y] YES       [N] NO");
    do{
        input = _getch();
        if(input == 'Y' || input == 'y' || input == 'N' || input == 'n'){
            system("cls");
            if(input == 'Y' || input == 'y')
                return 1;
            else if(input == 'N' || input == 'n')
                return 0;
        }
    }while(input != 'Y' || input != 'y' || input != 'N' || input != 'n');
}

void save(){
    FILE *fp;
    fp = fopen("acclist.dbf","w");
    for(int i = 0; i <= l.last; i++){
        fprintf(fp,"%d\t%s\t%d\t%s\t%s\t%s",accountInfo[i].acountNo,accountInfo[i].name,accountInfo[i].balance,accountInfo[i].phone,accountInfo[i].bday,accountInfo[i].pin);
        if(i != l.last)
            fprintf(fp,"\n");
    }
    fclose(fp);
}

void saveToCard(){
    FILE *fp;
    fp = fopen(drives[ctr],"w");
    fprintf(fp,"%d\t%s",accountInfo[accountIndex].acountNo,regPin);
    fclose(fp);
}

void gotoxy(int x, int y){
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void printToxy(int x, int y, char* label){
    gotoxy(x,y);
    printf("%s",label);
}

void clear(char *label){
    if(strcmp(label,"result") == 0){
        printToxy(25,17,"                                                       ");
        printToxy(53,17,"- - -");
    }
    else if(strcmp(label,"result2") == 0){
        printToxy(32,22,"                                                       ");
        printToxy(57,22,"- - -");
    }
    else if(strcmp(label,"enter") == 0)
        printToxy(31,18,"                                                       ");
    else if(strcmp(label,"pinBoxes") == 0)
        printToxy(52, 13,"                 ");
}
