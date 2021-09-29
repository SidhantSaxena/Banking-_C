#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <MMsystem.h>


struct loan_details{
 char acc_number[10];
 float loan_amt;
 int loan_period;	
};


struct Bank_detail{
   char acc_holder_name[30];
   char acc_number[10];
	char acc_holder_address[100];
   char acc_password[10];
   float available_balance;
   int loan_status;
};
long int rec_size=sizeof(struct Bank_detail);


void Create_new_account();
void Cash_Deposit(char[]);
void Cash_withdrawal(char[]);
void Account_information(char[]);
void Login();
void Home_page(char[]);
void Loan(char[]);
void Loan_apply(char[]);
void Loan_Details(char[]);
void display_options();
void Transfer_money(char[]);


int main()
{  
	PlaySound(TEXT("C:\\Users\\SAXENA\\Desktop\\my files\\GCET\\PPS btech\\Banking\\newfolfd\\intro_final"),NULL,SND_SYNC);
    char option;
    while(1){
    	system("cls");
    	system("color 4E");
       printf("\n***** Welcome to GCET Bank Application *****\n");
       display_options();
       printf("Please enter any options (1/2/3) ");
       printf("to continue : ");
		option = getch();
        switch(option)
        {
          case '1': Create_new_account();
                    break;
          case '2': Login();
                    break;
           case '3': exit(0);
                    break;
          default : printf("Please enter one of the options");
                    printf("(1/2/3) to continue \n ");
					break;
        }
	}
    return 0;
}

/*Function to display available options in this application*/

void display_options()
{
    printf("\n1. Create new account \n");
    printf("2. Login \n");
    printf("3. Leave Application \n");
}

/* Function to create new account */

void Create_new_account()
{	
	system("cls");
	system("color 8F");
	char ch;
	int i;
	char filename[20];
	struct Bank_detail member;
   fflush(stdin);     
   printf("\nEnter the account holder name    : ");
   gets(member.acc_holder_name);
   printf("\nEnter the account number(1 to 9): ");
   for(i=0;i<10;i++){
   	scanf("%c",&member.acc_number[i]);
   }
   member.acc_number[i]='\0';
   strcpy(filename,member.acc_number);
   strcat(filename,".txt");
   printf("\nEnter the preffered account password(10 characters): ");
   for(i=0;i<10;i++){
   	ch=getch();
   	member.acc_password[i]=ch;
   	printf("*");
   }
   member.acc_password[i]='\0';
   printf("\n\nEnter the account holder pin address : ");
   for(i=0;i<6;i++){
   	scanf("%c",&member.acc_holder_address[i]);
   }
   member.acc_holder_address[i]='\0';
   member.available_balance=1000;
   member.loan_status=0;
   FILE *fp;
   printf("%s",filename);
   fp=fopen(filename,"wb+");
   if(fp==NULL){
   	printf("Error in creating bank account");
   	getch();
   	system("cls");
   	return;
   }
	fwrite(&member,sizeof(member),1,fp);
	   printf("\nAccount has been created successfully \n\n");
	   printf("Account holder name    : %s \n" , member.acc_holder_name);
	   printf("\nAccount number         : %.*s \n" ,10, member.acc_number);
	   printf("\nAccount holder pin address : %s \n" , member.acc_holder_address);
	   printf("\nAvailable balance      : %f \n" ,  member.available_balance);
	   fclose(fp);
	   getch();
	return;
}



void Login(){
	struct Bank_detail member;
	system("cls");
	system("color 8F");
	int i;
	char ch,filename[20],c;
	char acc_num[10],pass[10];
	printf("\nEnter Account Number:\n");
	gets(acc_num);
	strcpy(filename,acc_num);
   	strcat(filename,".txt");
	FILE *fp;
   	fp=fopen(filename,"rb+");
   	if(fp==NULL){
	   	printf("Error in Loging in the bank account");
	   	getch();
	   	return;
   }
   		 while(fread(&member,sizeof(member),1,fp)){
                        if(strncpy(acc_num,member.acc_number,10)){
							break;
                        }
            }
		printf("\nEnter Password:\n");
   		for(i=0;i<10;i++){
		   	ch=getch();
		   	pass[i]=ch;
		   	printf("*");
		}
		pass[i]='\0';
   		if(strcmp(pass,member.acc_password)==0){
			Home_page(acc_num);
		}
		else{
			printf("Wrong Password");
			printf("\nDo wish return to Main Page(Y/N):");
			scanf("%c",&c);
			if(c=='Y'|| c=='y'){
				return;
			}else{
				Login();
			}
		}
}



void Home_page(char acc_num[10]){
	system("cls");
	system("color 1B");
    char option;
    while(1)
    {	printf("\n1. Account Information \n");
	    printf("\n2. Cash Withdrawal \n");
	    printf("\n3. Cash Deposit \n");
	    printf("\n4. Loan Options \n");
	    printf("\n5. Transfer money \n");
		printf("\n6. Log off");
       	printf("\n\nPlease enter any options (1/2/3/4/5/6): ");
        option = getch();
        switch(option)
        {
          case '1': Account_information(acc_num);
                    break;
          case '2': Cash_withdrawal(acc_num);
                    break;
          case '3': Cash_Deposit(acc_num);
                    break;
          case '4': Loan(acc_num);
                    break;
          case '5': Transfer_money(acc_num);
		  case '6': main();
          default : system("cls");
                    break;
        }
    }
    
}



void Account_information(char acc_num[10]){
	struct Bank_detail member;
	system("color 8B");
	system("cls");
	FILE *fp;
	acc_num[10]='\0';
	char c,filename[20];
	strcpy(filename,acc_num);
   strcat(filename,".txt");
   fp=fopen(filename,"rb");
   if(fp==NULL){
   	printf("Error in opening bank account");
   	getch();
   	system("cls");
   	return;
   } 
   while(fread(&member,sizeof(member),1,fp)){
   						//printf("%s   %s",acc_num,member.acc_number);
                        if(strncmp(acc_num,member.acc_number,10)==0){
							break;
                        }
            }
    int n=sizeof(member);
    fseek(fp,-n,1);
    printf("\n\nAccount holder name    : %s \n" , member.acc_holder_name);
	printf("\nAccount number         : %.*s \n" ,10,member.acc_number);
	printf("\nAccount holder pin address : %s \n" , member.acc_holder_address);
	printf("\nAvailable balance      : %f \n" ,  member.available_balance);
	printf("\nLoan status            : %d \n",member.loan_status);
   	fclose(fp);
   	printf("\nDo wish return to Home Page(Y/N):");
	scanf("%c",&c);
	if(c=='Y' || c=='y'){
		Home_page(acc_num);
	}else{
		Account_information(acc_num);
	}
}

// Function to deposit amount in an account

void Cash_Deposit(char acc_num[10])
{	system("cls");
	system("color 4A");
	struct Bank_detail member;
	char c,filename[20];
   float add_money;
   strcpy(filename,acc_num);
   strcat(filename,".txt");
	FILE *fp;
   fp=fopen(filename,"rb+");
   	if(fp==NULL){
	   	printf("Error in opening bank account");
	   	Home_page(acc_num);
	}
	while(fread(&member,sizeof(member),1,fp)){
                        if(strncmp(acc_num,member.acc_number,10)==0){
                         	break;
                        }
            }
   printf("\nThe current balance for account %s is %f \n", 
   acc_num, member.available_balance);
   printf("\nEnter money you want to deposit :  ");
   scanf("%f",&add_money);
   member.available_balance+=add_money;
	printf("\nThe current balance for account %s is %f \n", 
   acc_num, member.available_balance);
   int n=sizeof(member);
   fseek(fp,-n,1);
   fwrite(&member,sizeof(member),1,fp);
	fclose(fp);
	getch();
	Home_page(acc_num);
   
}
// Function to withdraw amount from an account


void Cash_withdrawal(char acc_num[10])
{	system("cls");
	system("color 4A");
	struct Bank_detail member;
	char c,filename[20];
   	float withdraw_money;
	FILE *fp;
	strcpy(filename,acc_num);
   strcat(filename,".txt");
   	fp=fopen(filename,"rb+");
   	if(fp==NULL){
	   	printf("Error in opening bank account");
	   	Home_page(acc_num);
	}
			while(fread(&member,sizeof(member),1,fp)){
                        if(strncmp(acc_num,member.acc_number,10)==0){
                         	break;
                        }
            }	
   printf("\nThe current balance for account %s is %f \n", 
   acc_num, member.available_balance);
   printf("\nEnter money you want to withdraw from account ");
   scanf("%f",&withdraw_money);
   member.available_balance=member.available_balance-withdraw_money;
	printf("\nThe current balance for account %s is %f \n",acc_num, member.available_balance);
	int n=sizeof(member);
	fseek(fp,-n,1);
   fwrite(&member,sizeof(member),1,fp);
	fclose(fp);
	getch();
	Home_page(acc_num);


}



void Loan(char acc_num[10]){
	
	int ch;
	system("cls");
	system("color 3F");
	while(1){
	printf("\n\n>>Press 1 to apply for a loan\n");
	printf("\n\n>>Press 2 for Checking Loan details\n");
	printf("\n\n>>Press 3 for returning to Home page\n");
	printf("\nEnter:");
	scanf("%d",&ch);
	switch(ch){
		case 1: Loan_apply(acc_num);
				break;
		case 2: Loan_Details(acc_num);
				break;
		case 3: Home_page(acc_num);
				break;
		default:system("cls");
				printf("Select from given choices");
				break;
	}
 }
	
}



void Loan_Details(char acc_num[10]){
	struct loan_details holder;
	system("cls");
	system("color 3F");
	FILE *fp;
	char c;
	char filename[20];
	strcpy(filename,acc_num);
	strcat(filename,"_Loan");
   strcat(filename,".txt");
	fp=fopen(filename,"ab+");
	if(fp==NULL){
		printf("Error Accessing Details");
		Loan(acc_num);
	}
    while(fread(&holder,sizeof(holder),1,fp)){
                        if(strncpy(acc_num,holder.acc_number,10)){
							break;
                        }
            }
    int n=sizeof(holder);
    fseek(fp,-n,1);
	printf("\nAccount number         : %.*s \n" ,10,holder.acc_number);
	printf("\nLoan Amount			   : %f \n" , holder.loan_amt);
	printf("\nLoan period(years)     : %d \n",holder.loan_period);
    printf("\nDo wish return to Loan Page(Y/N):");
	getch();
	Loan(acc_num);
	
	
}



void Loan_apply(char acc_num[10]){
	struct Bank_detail member;
	struct loan_details holder;
	system("cls");
	system("color 3F");
	char ch,filename[20],c;
	int count=0,v;
	float salary;
	float amt;
	strcpy(filename,acc_num);
	strcat(filename,".txt");
	FILE *fp2;
	fp2=fopen(filename,"rb+");
   	if(fp2==NULL){
   		if(fp2==NULL){
	   	printf("Error in opening bank account");
	   	return;
		}
	}while(fread(&member,sizeof(member),1,fp2)){
                        if(strncmp(acc_num,member.acc_number,10)==0){
							break;
                        }
            }
    v=sizeof(member);
    fseek(fp2,-v,1);
	if(member.loan_status==0){
		printf("\nAccount Holder's salary(p.m):\n");
		scanf("%f",&salary);
		if(salary>=40000){
			printf("\n1.Loan Amount Eligible:%f\tLoan Period:%d year\n",salary*10.8,1);
			count+=1;
		}
		if(salary>=100000){
			count+=1;
			printf("\n2.Loan Amount Eligible:%f\tLoan Period:%d years\n",salary*20.4,4);
		}
		if(salary>=500000){
			count+=1;
			printf("\n3.Loan Amount Eligible:%f\tLoan Period:%d years\n",salary*27.3,6);
		}
		if(count>0){
				FILE *fp;
				char filename2[20];
				strcpy(filename2,acc_num);
				strcat(filename2,"_Loan");
				strcat(filename2,".txt");
				fp=fopen(filename2,"rb+");
				if(fp==NULL){
					fp=fopen(filename2,"wb+");
					if(fp==NULL){
						printf("Error Accesing");
						Loan(acc_num);
					}
				}
				strcpy(holder.acc_number,acc_num);
				printf("\n\nSelect from the given option(press for 4 to go back to Home page):");
				ch=getch();
				switch(ch){
					case '1':	holder.loan_amt=salary*10.8;
							  	holder.loan_period=1;
							  	member.loan_status=1;
								break;
					case '2':	if(count>1){
								holder.loan_amt=salary*20.4;
							  	holder.loan_period=4;
							  	member.loan_status=1;
								}else{
									system("cls");
									printf("Not Selected from given choices");
								}
								break;  	
					case '3':	if(count>2){
								holder.loan_amt=salary*27.3;
							  	holder.loan_period=6;
							  	member.loan_status=1;
								}else{
									system("cls");
									printf("Not Selected from given choices");
								}
								break;
					case '4': Home_page(acc_num);
								break;
					default:system("cls");
							printf("Not Selected from given choices");
							getch();
							Loan_apply(acc_num);
				}
				int n=sizeof(member);
				fseek(fp,-n,1);
	  			fwrite(&member,sizeof(member),1,fp2);
				fwrite(&holder,sizeof(holder),1,fp);
				fclose(fp);
			
		}else{
			printf("Not Eligible");
		}	
	}else{
			printf("Not Eligible");
		}
	fclose(fp2);
	if(member.loan_status==1){
	printf("\nLoan Succesfully Applied");
	}
	c=getch();
	Loan(acc_num);
}



void Transfer_money(char acc_num[]){
	system("cls");
	system("color F3");
	int money;
	struct Bank_detail member,member2;
	char c,filename[20],filename2[20],acc_num2[10];
   	float withdraw_money;
	FILE *fp,*fp2;
	strcpy(filename,acc_num);
    strcat(filename,".txt");
   	fp=fopen(filename,"rb+");
   	if(fp==NULL){
	   	printf("Error in opening bank account");
	   	Home_page(acc_num);
	}		
	while(fread(&member,sizeof(member),1,fp)){
                        if(strncmp(acc_num,member.acc_number,10)==0){
                         	break;
                        }
            }	
   printf("\nThe current balance for account %s is %f \n", acc_num, member.available_balance);
   printf("\nTransfer to Account Number:");
   scanf("%s",acc_num2);
   strcpy(filename2,acc_num2);
   strcat(filename2,".txt");
   fp2=fopen(filename2,"rb+");
   	if(fp2==NULL){
	   	printf("Error in connecting the bank account");
	   	getch();
	   	Home_page(acc_num);
	}
	printf("\nEnter money to be transfered:");
	scanf("%d",&money);
	while(fread(&member2,sizeof(member2),1,fp2)){
                        if(strncmp(acc_num,member2.acc_number,10)==0){
                         	break;
                        }
    }
    member.available_balance-=money;
    member2.available_balance+=money;
    int n=sizeof(member);
	fseek(fp,-n,1);
	fseek(fp2,-n,1);
   	fwrite(&member,sizeof(member),1,fp);
   	fwrite(&member2,sizeof(member2),1,fp2);
	fclose(fp);
	fclose(fp2);
	printf("\nTransfer Successfull...");
	getch();
	Home_page(acc_num);
	
}



