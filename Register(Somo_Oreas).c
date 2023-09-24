#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#define MAX 1000

typedef struct REG{
    char name[50];
    int AccNo;
    char phone[20];
    char bday[20];
    char pin[7];
    int balance;
    int last;
}list;

list l;
list AccInfo[MAX];

char RegName[50];
char Regphone[20];
char Regbday[20];
char regPin[7];
char ConPin[7];
char* CDrive[2] = {"C:\\checkFd.dbf", "E:\\checkFd.dbf"};
char* Driver[2] = {"C:\\bank.dbf","E:\\bank.dbf"};
int regPinInt, regAccountNo, regBalance, ctr = -1, exist = 0, checkName = 0, checkPin = 0, pinCharacter = 0;

void makenull();
int insertCard();
void retrieve();
int checkFd();
void registration();
int isEmpty();
int isFull();
void insert();
int locate(int x);
void save();
void saveToCard();

int main(){
    int i;
    system("color 0B");
    makenull();
    if(insertCard()){
        _getch();
        system("cls");
        retrieve();
        printf("\t\t\t\t\t_______________________________________\n");
        printf("\t\t\t\t\t| < < < R E G I S T R A T I O N > > > |\n");
        printf("\t\t\t\t\t|_____________________________________|\n\n");
        registration();
    }
    i = remove(CDrive[ctr]);
    printf("Name: Somo, Herbenne Rey & Oreas, Nyl Bhoy\tBSIS - 2AB\n\nInstructor: Prof. Fernando Renegado\n");
    _getch();
    return 0;
}

void makenull(){
    l.last = -1;
}

int insertCard(){
    FILE *fp;
    printf("\t\t\t\t\t_______________________________________\n");
    printf("\t\t\t\t\t| < < < Please Insert Your Card > > > |\n");
    printf("\t\t\t\t\t|_____________________________________|\n\n");
    do{
        ctr = (ctr + 1) % 2;
        fp = fopen(CDrive[ctr],"w");
    }while(fp == NULL);
    fclose(fp);

    fp = fopen(Driver[ctr],"r");
    if(fp == NULL){
        printf("\t\t\t\t\t_______________________________________\n");
        printf("\t\t\t\t\t|        You Are Not Registered.      |\n");
        printf("\t\t\t\t\t|_____________________________________|\n\n");
        printf("\n\n\n\t\t\t\t\t\tP R E S S   A N Y   K E Y");
        return 1;
    }
    else{
        printf("\t\t\t\t\t_______________________________________\n");
        printf("\t\t\t\t\t|          You Are Registered.        |\n");
        printf("\t\t\t\t\t|_____________________________________|\n\n\n\n");
        return 0;
    }
    fclose(fp);
}

int checkFd(){
    FILE *fp;
    fp = fopen(CDrive[ctr],"r");
    if(fp == NULL)
        return 1;
    return 0;
    fclose(fp);
}

void retrieve(){
    FILE *fp;
    int i = 0;
    fp = fopen("acclist.dbf","r+");

    if (fp==NULL){
        printf("\t\t\t\t\t_______________________________________\n");
        printf("\t\t\t\t\t|   < < < DATA BASE IS EMPTY > > >    |\n");
        printf("\t\t\t\t\t|_____________________________________|\n\n");
        _getch();
        system("cls");
    }
    else{
        while(!feof(fp)){
            l.last++;
            fscanf(fp,"%d %[^\t]%d %[^\t] %[^\t] %[^\n]",&AccInfo[l.last].AccNo,AccInfo[l.last].name,&AccInfo[l.last].balance, AccInfo[l.last].phone, AccInfo[l.last].bday,AccInfo[l.last].pin);
        }
    }
    fclose(fp);
}

void registration(){
    int end;
    do{
        end = 1;
        l.last++;
        checkName = 0;
        printf("\n\t\t\t\tNAME: ");
        scanf(" %[^\n]s",RegName);
        printf("\t\t\t\t_____________________________________\n");
        strlwr(RegName);
        printf("\n\t\t\t\tPHONE No: ");
        scanf(" %[^\n]s",Regphone);
        printf("\t\t\t\t_____________________________________\n");
        strlwr(Regphone);
        printf("\n\t\t\t\tBIRTHDAY: ");
        scanf(" %[^\n]s",Regbday);
        printf("\t\t\t\t_____________________________________\n");
        strlwr(Regbday);
        do{
            srand(time(0));
            regAccountNo = 10000+(rand()%90000);
        }while(locate(1));
        printf("\t\t\t\tAcc No: %d\n",regAccountNo);
        printf("\t\t\t\t_____________________________________\n");
       do{
            printf("\t\t\t\tInitial Deposit: ");
            scanf("%d",&regBalance);
            printf("\t\t\t\t_____________________________________\n");
            if(regBalance < 5000){
                printf("\t\t\t\tSorry Initial Deposit Must be 4999+\n");
                printf("\t\t\t\t_____________________________________\n");
            }
            else{
                break;
            }
        }while(1);

        do{
            printf("\t\t\t\tPIN NUMBER: ");
            checkPin = 0;
            pinCharacter = 0;
            for(int i = 0; i < 6; i++){
                regPin[i] = _getch() + 9;
                putchar('*');
                putchar(' ');
            }
            regPin[6] = '\0';
            printf("\n\t\t\t\t_____________________________________\n");
            printf("\t\t\t\tCONFIRM PIN: ");
            for(int i = 0; i < 6; i++){
                ConPin[i] = _getch() + 9;
                putchar('*');
                putchar(' ');
            }
            ConPin[6] = '\0';
            printf("\n\t\t\t\t_____________________________________\n");

            end = strcmp(ConPin,regPin);

            for(int i = 0; i < 6; i++){
                if(isdigit(ConPin[i] - 9)  == 0){
                    pinCharacter = 1;
                    break;
                }
            }

            if(end != 0){
                printf("\t\t\t\tYour PIN does Not MATCH\n");
                printf("\t\t\t\tPLEASE PRESS ANY KEY\n");
                _getch();
            }

            else if(locate(0) && checkPin == 1){
                printf("\t\t\t\tYour PIN is Not Unique\n");
                _getch();
            }
            else if(pinCharacter == 1){
                printf("\t\t\t\tYour Pin Has a Character.\n");
                _getch();
            }

        }while(end != 0 || checkPin || pinCharacter);

        if(locate(0) && checkName == 1){
            l.last--;
            printf("\t\t\t\tThis Account is Already Exits");
            _getch();
            system("cls");
        }

    }while(checkName);

    if(isFull()){
        printf("\t\t\t\t\t_______________________________________\n");
        printf("\t\t\t\t\t|   < < < DATA BASE IS FULL > > >     |\n");
        printf("\t\t\t\t\t|_____________________________________|\n\n");
    }
    else
        insert();
}

int isEmpty(){
    return(l.last == 0);
}

int isFull(){
    return(l.last == MAX);
}

void insert(){
    if(checkFd()){
        printf("\t\t\t\t\t_______________________________________\n");
        printf("\t\t\t\t\t|    < < < FLASH DRIVE ERROR > > >    |\n");
        printf("\t\t\t\t\t|_____________________________________|\n\n");
        exit(0);
    }
    strcpy(AccInfo[l.last].name,RegName);
    strcpy(AccInfo[l.last].phone,Regphone);
    strcpy(AccInfo[l.last].bday,Regbday);
    AccInfo[l.last].AccNo = regAccountNo;
    AccInfo[l.last].balance = regBalance;
    strcpy(AccInfo[l.last].pin,regPin);
    printf("\t\t\t\t\t_______________________________________\n");
    printf("\t\t\t\t\t|      You Are Now Registered!!       |\n");
    printf("\t\t\t\t\t|_____________________________________|\n\n\n");
    save();
    saveToCard();
}

int locate(int x){
    if(x == 0){
        for(int i = 0; i < l.last + 1; i++){
            if(strcmp(AccInfo[i].name,RegName) == 0 || strcmp(AccInfo[i].pin,regPin) == 0){
                if(strcmp(AccInfo[i].name,RegName) == 0)
                    checkName = 1;
                if(strcmp(AccInfo[i].pin,regPin) == 0)
                    checkPin = 1;
                return 1;
            }
        }
        return 0;
    }
    else if(x == 1){
        for(int i = 0; i < l.last + 1; i++){
            if(AccInfo[i].AccNo == regAccountNo)
                return 1;
        }
        return 0;
   }
}

void save(){
    FILE *fp;
    fp = fopen("acclist.dbf","w");
    for(int i = 0; i <= l.last; i++){
        fprintf(fp,"%d\t%s\t%d\t%s\t%s\t%s",AccInfo[i].AccNo,AccInfo[i].name,AccInfo[i].balance, AccInfo[i].phone, AccInfo[i].bday, AccInfo[i].pin);
        if(i != l.last)
            fprintf(fp,"\n");
    }
    fclose(fp);
}

void saveToCard(){
    FILE *fp;
    fp = fopen(Driver[ctr],"w");
    fprintf(fp,"%d\t%s",regAccountNo,regPin);
    fclose(fp);
}

