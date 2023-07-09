#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 10     //10 stocks
#define day 30      //30 days
typedef struct
{
    char name[15];  //name as a parameter is added for 2nd sub part of the question specially and also to print list of stocks
    float Open;
    float High;
    float Low;
    float Close;
    float Volume;
}Stock_Market;

typedef struct      //structure for overall performance 6th sub part
{
    char stock_n[15];   //stock name
    int sum;            //sum of percentage change of each day between specified date
}overperf;

const int monthDays[13] = { 0, 31, 59, 90, 120, 151, 181, 212, 243,273, 304, 334, 365 };
int checkYear(int year)
{
    if (year % 400 == 0)
        return 1;
    if (year % 100 == 0)
        return 0;
    if (year % 4 == 0)
        return 1;
    return 0;
}

int count(int a,int b,int c)            //program to calculate days from FIRST_DATE
{
	int dd,mm,yyyy;
	dd=01;
	mm=04;
	yyyy=2022;
	int sum_initial=0,sum_final=0,yd1,yd2;
	yd1=c-yyyy;
	sum_initial=sum_initial+yd1*365+monthDays[b-mm]+(a-dd)+yd1/4;
	return sum_initial;
}

float PerChange(float x,float y)    //function returning percentage change in stock price
{
    float ans;
    ans = 1.0*(y-x)*(100/x);
    return ans;
}

int sort(Stock_Market arr[size][day],int n)     //function for sorting stocks of particular day volume wise and if volumes are equal then according to closing price
{  
    Stock_Market ar[size][day],temp;            //taking temporary matrix of structure so that we get sorted data without affecting original data
    for(int i=0;i<size;i++)
    {
        ar[i][n] = arr [i][n];
    }
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size-i-1;j++)
        {
            if(ar[j][n].Volume < ar[j+1][n].Volume)
            {
                temp = ar[j+1][n];
                ar[j+1][n] = ar[j][n];
                ar[j][n]=temp;  
            }
            else if(ar[j][n].Volume == ar[j+1][n].Volume && ar[j][n].Close < ar[j+1][n].Close)
            {
                temp = ar[j+1][n];
                ar[j+1][n] = ar[j][n];
                ar[j][n]=temp;
            }
        }
    }
    printf("SORTED LIST OF STOCK-\n");
    for(int i=0;i<size;i++)     //prints stock name orderwise
    {
        printf("%d) %s\n",(i+1),ar[i][n].name);
    }
    return 0;
}

float proloss(float w, float r)     //function to return profit loss
{
    float x=r-w;
    return x;
}

float highper(Stock_Market arr[size][day],int st,int ed)        //function to print stock with highest profit percentage in given time interval
{
    int i,stock_no;
    float max=-101.0,pro1;
    for(i=0;i<size;i++)
    {
        pro1=(arr[i][ed].Close-arr[i][st].Open)*100/arr[i][st].Open;
        if(pro1>max)
        {
            max=pro1;
            stock_no=i;
        }
    }
    printf("Highest performing stock is %s with percentage %f\n",arr[stock_no][0].name,max);
    return 0;
}

float lowper(Stock_Market arr[size][day],int st,int ed)     //function to print stock with highest profit percentage in given time interval
{
    int i,stock_no;
    float low=101.0,pro1;
    for(i=0;i<2;i++)
    {
        pro1=(arr[i][ed].Close-arr[i][st].Open)*100/arr[i][st].Open;
        if(pro1<low)
        {
            low=pro1;
            stock_no=i;
        }
    }
    printf("Lowest performing stock is %s with percentage %f\n",arr[i][0].name,low);
    return 0;
}

int Ovper(Stock_Market arr[size][day],int st,int ed,overperf b[size])     //function to print stock order wise according to overall performance
{
    float temp;
    overperf s[size],t;         //taking temporary array of structure so that we get sorted data without affecting original data
    for(int i=0;i<size;i++)
    {
        s[i]=b[i];
    }
    for(int i=0;i<size;i++)
    {
        for(int j=st+1;j<ed;j++)
        {
            temp=(arr[i][j].Open-arr[i][j-1].Close)*100/arr[i][j-1].Close;
            s[i].sum=s[i].sum+temp;
        }
    }
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size-i-1;j++)
        {
            if(s[j].sum>s[i].sum)
            {
                t=s[j];
                s[j]=s[i];
                s[i]=t;
            }
        }
    }
    printf("\n UPDATED LIST OF STOCK-\n");
    for(int i=0;i<size;i++)
    {
        printf(" %d) %s\n",i+1,s[i].stock_n);
    }
    return 0;
}


float avg(Stock_Market arr[size][day],int start,int end,int date)       //function to print average of particular date and between given stipulated time
{
    float avg1,avg2,Num1,Num2=0,Den1;
    int i,j;
    for(i=0;i<size;i++)
    {
        Num1 = 0,Den1 = 0,avg1 = 0;
        for(j=0;j<=date;j++)
        {
            int stock_price = (arr[i][j].Open + arr[i][j].Close)/2;
            Num1 = Num1 + (arr[i][j].Volume)*(stock_price);
            Den1 = Den1 + arr[i][j].Volume;
        }
        avg1 = (1.0)*(Num1/Den1);
        printf("%f is the average for %s \n", avg1,arr[i][0].name);
    }
    printf("\n");

    for(i=0;i<size;i++)
    {
        Num1 = 0,Den1 = 0,avg1 = 0;
        for(j=start;j<=end;j++)
        {
            int stock_price = (arr[i][j].Open + arr[i][j].Close)/2;
            Num1 = Num1 + (arr[i][j].Volume)*(stock_price);
            Den1 = Den1 + arr[i][j].Volume;
        }
        avg1 = (1.0)*(Num1/Den1);
        Num2 = Num2 + avg1;
    }
    avg2 = (1.0)*(Num2/size);
    printf("%f is the average of average \n", avg2);
    return 0;
}
int main()
{
    FILE *fp;
    Stock_Market a[size][day];
    overperf b[size];
    fp = fopen("data.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file\n");
        return 1;
    }
    for(int x=0;x<size;x++)
    {
        for(int y=0;y<day;y++)
        {
            fscanf(fp, "%f,%f,%f,%f,%f\n", &a[x][y].Open, &a[x][y].High,&a[x][y].Low,&a[x][y].Close,&a[x][y].Volume);
        }
    }

    fclose(fp);
    int i=0,j;
    for(j=0;j<day;j++)                      //assigning name of stock to each element of matrix a of structure Stock_Market
    {
        strcpy(a[0][j].name,"SBIN");
    }
    strcpy(b[0].stock_n,"SBIN");            //assigning name of stock to each element of array b of structure overperf
    for(j=0;j<day;j++)
    {
        strcpy(a[1][j].name,"TATAMOTORS");
    }
    strcpy(b[1].stock_n,"TATAMOTORS");
    for(j=0;j<day;j++)
    {
        strcpy(a[2][j].name,"PNB");
    }
    strcpy(b[2].stock_n,"PNB");
    for(j=0;j<day;j++)
    {
        strcpy(a[3][j].name,"YESBANK");
    }
    strcpy(b[3].stock_n,"YESBANK");
    for(j=0;j<day;j++)
    {
        strcpy(a[4][j].name,"TECHM");
    }
    strcpy(b[4].stock_n,"TECHM");
    for(j=0;j<day;j++)
    {
        strcpy(a[5][j].name,"INFY");
    }
    strcpy(b[5].stock_n,"INFY");
    for(j=0;j<day;j++)
    {
        strcpy(a[6][j].name,"TCS");
    }
    strcpy(b[6].stock_n,"TCS");
    for(j=0;j<day;j++)
    {
        strcpy(a[7][j].name,"TITAN");
    }
    strcpy(b[7].stock_n,"TITAN");
    for(j=0;j<day;j++)
    {
        strcpy(a[8][j].name,"ONGC");
    }
    strcpy(b[8].stock_n,"ONGC");
    for(j=0;j<day;j++)
    {
        strcpy(a[9][j].name,"IOC");
    }
    strcpy(b[9].stock_n,"IOC");

    int d1,m1,y1,d2,m2,y2,l=1;
    while(l==1)
    {
        int choice;
        printf("\n");
        printf("1. Percentage change in stock price :\n");
        printf("2. Sort given data :\n");
        printf("3. Profit/Loss on two days :\n");
        printf("4. Highest performing stock :\n");
        printf("5. Lowest performing stock :\n");
        printf("6. Stocks acording to increasing overall performance :\n");
        printf("7. Average value of stocks :\n");
        printf("8. Exit :\n");
        printf("\nEnter Your Choice :\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: //1. Percentage change in stock price
            {
                int c; 
                printf("Enter the start_date and end_date :\n");
                scanf("%d %d %d %d %d %d",&d1,&m1,&y1,&d2,&m2,&y2);
                int start_day1=count(d1,m1,y1);
                int end_day1=count(d2,m2,y2);
                if(end_day1-start_day1<day)
                {
                    printf("LIST OF STOCKS:\n");
                    for(int i=0;i<size;i++)
                    {
                        printf("%d) %s\n",i+1,a[i][0].name);
                    }
                    printf("Enter stock no: \n");
                    scanf("%d",&c);
                    float ans=PerChange(a[c-1][start_day1].Open,a[c-1][end_day1].Close);
                    printf("Percent change=%f\n",ans);
                }
                else
                {
                    printf("WRONG INPUT\n");
                }
                printf("Press 1 to go back to menu\n");
                printf("Press 0 to exit\n");
                scanf("%d",&l);
                if(l==0)
                {
                    printf("Thank you for using our program\n");
                }
                break;
            }
            case 2:     //2. Sort given data
            {
                printf("Enter the date :");
                scanf("%d%d%d",&d1,&m1,&y1);
                int date=count(d1,m1,y1);
                sort(a,date);
                printf("Press 1 to go back to menu\n");
                printf("Press 0 to exit\n");
                scanf("%d",&l);
                if(l==0)
                {
                    printf("Thank you for using our program\n");
                }
                break;
            }

            case 3:         //3. Profit/Loss on two days
            {
                printf("Enter the start_date and end_date:\n");
                scanf("%d %d %d %d %d %d",&d1,&m1,&y1,&d2,&m2,&y2);
                int start_day=count(d1,m1,y1);
                int end_day=count(d2,m2,y2);
                if(end_day-start_day<day)
                {
                    int no_of_stocks,z=0,c;
                    printf("ENTER NO OF STOCKS:");
                    scanf("%d",&no_of_stocks);
                    while(z<no_of_stocks)
                    {
                        for(int i=0;i<size;i++)
                        {
                            printf("%d. %s\n",(i+1),a[i][0].name);
                        }
                        printf("Enter Stock Number:");
                        scanf("%d",&c);
                        float diff=proloss(a[c-1][start_day].Open,a[c-1][end_day].Close);
                        if(diff>0)
                        {
                            printf("Profit = %f\n",diff);
                        }
                        else if(diff<0)
                        {
                            printf("Loss = %f\n",diff);
                        }                        
                        else
                        {
                            printf("No Profit No Loss\n");
                        }
                        z++;
                    }
                }
                else
                {
                    printf("WRONG INPUT\n");
                }
                printf("Press 1 to go back to menu\n");
                printf("Press 0 to exit\n");
                scanf("%d",&l);
                if(l==0)
                {
                    printf("Thank you for using our program\n");
                }
                break;
            }

            case 4:         //4. Highest performing stock
            {
                printf("Enter the start_date and end_date:\n");
                scanf("%d %d %d %d %d %d",&d1,&m1,&y1,&d2,&m2,&y2);
                int start_day1=count(d1,m1,y1);
                int end_day1=count(d2,m2,y2);
                if(end_day1-start_day1<day)
                {
                    highper(a,start_day1,end_day1);
                }
                else
                {
                    printf("WRONG INPUT\n");
                }
                printf("Press 1 to go back to menu\n");
                printf("Press 0 to exit\n");
                scanf("%d",&l);
                if(l==0)
                {
                    printf("Thank you for using our program\n");
                }
                break;
            }

            case 5:         //5. Lowest performing stock
            {
                printf("Enter the start_date and end_date:\n");
                scanf("%d %d %d %d %d %d",&d1,&m1,&y1,&d2,&m2,&y2);
                int start_day1=count(d1,m1,y1);
                int end_day1=count(d2,m2,y2);
                if(end_day1-start_day1<day)
                {
                    lowper(a,start_day1,end_day1);
                }
                else
                {
                    printf("WRONG INPUT\n");
                }
                printf("Press 1 to go back to menu\n");
                printf("Press 0 to exit\n");
                scanf("%d",&l);
                if(l==0)
                {
                    printf("Thank you for using our program\n");
                }
                break;
            }
            case 6:         //6. Stocks acording to increasing overall performance
            {
                printf("Enter the start_date and end_date:\n");
                scanf("%d %d %d %d %d %d",&d1,&m1,&y1,&d2,&m2,&y2);
                int start_day1=count(d1,m1,y1);
                int end_day1=count(d2,m2,y2);
                if(end_day1-start_day1<day)
                {
                    Ovper(a,start_day1,end_day1,b);
                }
                else
                {
                    printf("WRONG INPUT\n");
                }
                printf("Press 1 to go back to menu\n");
                printf("Press 0 to exit\n");
                scanf("%d",&l);
                if(l==0)
                {
                    printf("Thank you for using our program\n");
                }
                break;
            }
            case 7:         //7. Average value of stocks
            {
                int d6,m6,y6,d7,m7,y7,d8,m8,y8,date,start_day,end_day;
                printf("Enter the date upto which you want to calculate the average :");
                scanf(" %d %d %d", &d6,&m6,&y6);
                printf("Enter the start_date and end_date :");
                scanf(" %d %d %d %d %d %d ",&d7,&m7,&y7,&d8,&m8,&y8);
                date = count(d6,m6,y6);
                start_day = count(d7,m7,y7);
                end_day = count(d8,m8,y8);
                if(end_day-start_day<day)
                {
                    avg(a,start_day,end_day,date);
                }
                else
                {
                    printf("WRONG INPUT\n");
                }
            }
            default :
            {
                printf("Thank you for using our program\n");
                exit(0);
            }
        }
    }
}