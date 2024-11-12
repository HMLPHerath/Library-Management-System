#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct books{
    int id;
    char bookname[50];
    char authorname[50];
    char date[15];

}b;

struct student{
    int id;
    char sname[50];
    char sclass[50];
    int sroll;
    char bookname[50];
    char date[15];
}s;

FILE *fp;

int main(){

    int ch;
    {
        system("cls");
        printf("<== Library Management System ==>\n");
        printf("1.Add Book\n");
        printf("2.View Book List\n");
        printf("3.Remove Book\n");
        printf("4.Issue Book\n");
        printf("5.Issue Book List\n");
        printf("0.Exit\n\n");
        printf("Enter your choice:");
        scanf("%d",&ch);
    }

    switch(ch){
    case 0:
        exit(0);
        break;

    case 1:
        addbook();
        break;

    case 2:
        viewbooklist();
        break;

    case 3:
        removebook();
        break;

    case 4:
        issuebook();
        break;

    case 5:
        viewissuebooklist();
        break;


    default:
        printf("Invalid Choice...\n\n");

    }

    return 0;
}

void addbook() {
    //char myDate[12];
    //time_t t= time(NULL);
    //struct tm tm = *localtime(&t);
    //sprintf(myDate, tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900 );
    //strcpy(b.date, myDate);

    fp = fopen("books.txt","ab");//open file

    //book details addeed

    printf("Enter Book id:");
    scanf("%d",&b.id);

    printf("Enter Book name:");
    fflush(stdin);
    gets(b.bookname);

    printf("Enter Author name:");
    fflush(stdin);
    gets(b.authorname);

    printf("Book Added Successfully");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);


}

void viewbooklist() {
    system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n\n","Book id","Book Name","Author","Date");

    fp = fopen("books.txt","rb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        printf("%-10d %-30s %-20s %s\n", b.id, b.bookname, b.authorname, b.date);
    }
    fclose(fp);
}



void removebook(){
    int id, f=0;
    system("cls");
    printf("<== Remove Book ==>\n\n");
    printf("Enter id to remove book:");
    scanf("%d",&id);

    FILE *ft;

    fp = fopen("books.txt","rb");
    ft = fopen("tmp.txt", "wb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(id == b.id){
            f = 1;
        }else{
            fwrite(&b, sizeof(b), 1, ft);
        }

    }

    if(f ==1){
        printf("\n\nBook Deleted Successfully");
    }else{
        printf("\n\n NO Book Found!");
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("tmp.txt","books.txt");

}


void issuebook(){
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(b.date, myDate);

    int f = 0;

    system("cls");
    printf("<== Issue Books ==>\n\n");
    printf("Enter Book id to issue:");
    scanf("%d", &s.id);

    //check if we have book of given id

    fp = fopen("books.txt", "rb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(b.id == s.id){
            strcpy(s.bookname, b.bookname);
            f = 1;
            break;
        }
    }

    if(f==0){
        printf("No Book found with this id\n");
        printf("Ples try again...\n\n");
        return;
    }
    fp =fopen("issue.txt", "ab");
    printf("Enter Student ID:");
    scanf("%d",&s.id);

    fp = fopen("issue.txt", "ab");
    printf("Enter Student Name:");
    fflush(stdin);
    gets(s.sname);

    fp = fopen("issue.txt", "ab");
    printf("Enter Student Class:");
    fflush(stdin);
    gets(s.sclass);

    fp = fopen("issue.txt", "ab");
    printf("Enter Student Roll:");
    scanf("%d", &s.sroll);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}


void viewissuebooklist(){
    system("cls");
    printf("<== Issued Book List ==>\n\n");
    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n\n", "S_Id", "S_Name", "Class", "Roll", "Book Name", "Date");

    fp = fopen("issue.txt","rb");

    while(fread(&s, sizeof(s), 1, fp) == 1){
            printf("%-10d %-30s %-20s %-10d %-30s %s\n\n\n", s.id, s.sname, s.sclass, s.sroll, s.bookname, s.date);
    }
    fclose(fp);

}
