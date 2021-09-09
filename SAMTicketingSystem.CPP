#include<fstream.h>
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<process.h>
#include<dos.h>
#include<stdio.h>
#include<graphics.h>
class plane                 // stores details of the planes
{
    char planename[50], start[50], destination[50];
     char nam[50], st[50], dest[50];
   public :
    int planeno;
    int pl;

    plane()                 // constructor
    {
       planeno=0;
       strcpy(planename," ");
       strcpy(start," ");
       strcpy(destination," ");
    }
    void getdata()         // get details of the plane
    {
       cout<<"Enter the following details..";
       cout<<"\n\n\n\t\tPlane Number : ";
       cin>>planeno;
       cout<<"\n\n\t\tPlane Name : ";
       gets(planename);
       cout<<"\n\n\t\tBoarding Point : ";
       gets(start);
       cout<<"\n\n\t\tDestination : " ;
       gets(destination);
    }
    void putdata()          // display details of the plane
    {
       cout<<"\n\n\t\tPlane Number : ";
       cout<<planeno;
       cout<<"\n\t\tPlane Name : ";
       puts(planename);
       cout<<"\n\t\tBoarding point : ";
       puts(start);
       cout<<"\n\t\tDestination : ";
       puts(destination);
    }

    void modify()        // used to modify any record
    {
       cout<<"\n\n\t\tPlane Number : ";
       cout<<planeno;
       cout<<"\n\t\tPlane Name : ";
       puts(planename);
       cout<<"\n\t\tBoarding point : ";
       puts(start);
       cout<<"\n\t\tDestination : ";
       puts(destination);
       cout<<"\n\n\tEnter new Details. " <<endl;
       cout<<"\n\n\t\tNew Plane No. :(Enter -1 to retain old one) ";
       cin>>pl;
       cout<<"\n\t\tNew Plane Name. :(Press '.' to retain old one) ";
       gets(nam);
       cout<<"\n\t\tNew Boarding Pt. :(press '.' to retain old one) " ;
       gets(st);
       cout<<"\n\tNew Destination. :(press '.' to retain old one) ";
       gets(dest);
       if(pl!= -1)
   planeno=pl;
       if(strcmp(nam,".")!=0)
   strcpy(planename,nam);
       if(strcmp(st,".")!=0)
   strcpy(start,st);
       if(strcmp(dest,".")!=0)
   strcpy(destination,dest);
    }

}p;        // object of class "plane"

class tickets             // stores details of tickets made
{
   int age,pn;
   char name[50],pname[50];
  public :
   int resno,seatno;     // reservation no.


   void get()             // get details of user for tickets
   {  resno=random(350-20+1)+20;
	seatno=random(100)+1;

      cout<<"\nEnter your details :-......";
      cout<<"\n\n\tName : ";
      gets(name);
      cout<<"\n\tAge : ";
      cin>>age;
      cout<<"\n\tPlane Number : ";
      cin>>pn;
      cout<<"\n\n\n\t\t\tWait till your ticket is being booked...";
      delay(700);
      cout<<"\n\n\t\tYour Reservation No. is : "<<resno;
      cout<<"\n\n\t\tYour Seat No is:"<<seatno;

   }
   void put()             // display details of tickets
   {
      cout<<"\nYour Details are : ...";
      cout<<"\n\n\tReservation No. : "<<resno;
      cout<<"\n\n\tSeat No. :"<<seatno;
      cout<<"\n\tName : "; puts(name);
      cout<<"\n\tAge : "<<age;
      cout<<"\n\tPlane No. :"<<pn;
     // cout<<"\n\tPlane Name:"<<planename;
   }

}t;       // object of class "tickets"

void write()     // writes details to file
{
    ofstream fout;
    fout.open("plane.dat", ios::out|ios::binary);
    if(!fout)
       cout<<"File can't be created";
    char ch='y';
    while(ch=='y' || ch=='Y')
    {  clrscr();
       gotoxy(0,10);
       p.getdata();
       fout.write((char*) &p, sizeof(p));
       cout<<"\n\n\n\n\t\tWant to enter more ? (y/n) ";
       cin>>ch;
    }
    fout.close();
}

void display()               //  display details of a file
{

    ifstream fin;
    fin.open("plane.dat", ios::in|ios::binary);
    if(!fin)
       cout<<"\n\n\n\n\n\n\t\tFile can't be opened " ;
       delay(1000);
    while(fin.read((char*)&p, sizeof(p)))
    {   p.putdata();
 getch();
 delay(500);
 cout<<"\n..................................................................\n";
 delay(400);
     }
    fin.close();
}

void add()                 // add record to the file
{

    ofstream fout;
    fout.open("plane.dat", ios::out|ios::app|ios::binary);
    if(!fout)
       cout<<"File can't be opened";
    char ch='y';
    while(ch=='y' || ch=='Y')
    {  clrscr();
       gotoxy(0,10);
       p.getdata();
       fout.write((char*) &p, sizeof(p));
       cout<<"\n\n\n\n\t\tWant to enter more ? (y/n) ";
       cin>>ch;
    }
    fout.close();
}

void search()         // search any record from the file
{
    ifstream fo;
    fo.open("plane.dat", ios::out|ios::binary);
    if(!fo)
       cout<<"\n\n\t\t\tFile Can't be Found ... ";
    delay(200);
    cout<<"\n\n\n\t\tEnter the Plane No. whose details you want to see . : ";
    int ps;
    cin>>ps;
    delay(400);
    while(!fo.eof())
    {
       fo.read((char*)&p, sizeof(p));
       if(p.planeno==ps)
       {
   delay(400);
   p.putdata();
   cout<<"\n\n\tPress 'Enter' .. ";
   getch();
   break ;
       }
       else
  cout<<"\n\n\n\t\tNo such Plane is in Service " ;
    }
    fo.close();
}

void mod()             // modify any record
{
   fstream fio;
   fio.open("plane.dat", ios::in|ios::out|ios::binary);
   int pno; long pos; char found='f';
   cout<<"\n\n\tEnter the Plane no. whose record is to be modified \n ";
   cin>>pno;
   while(!fio.eof())
   {
       pos=fio.tellg();
       fio.read((char *)&p, sizeof(p));
       if(p.planeno==pno)
       {
   p.modify();
   fio.seekg(pos);
   fio.write((char*) &p, sizeof(p));
   found='t' ;
   break ;
       }
   }
   if(found=='f')
      cout<<"\n\n\tRecord not found !!\n";
   fio.seekg(0);
   fio.close();
}

void del()              // delete any record
{
   ifstream fio;
   ofstream file;
   fio.open("plane.dat", ios::in|ios::binary);
   file.open("temp.dat", ios::out|ios::binary);
   int pn; char found='f', confirm='n';
   cout<<"\n\n\t\tEnter the Plane No. whose record is to be deleted \n ";
   cin>>pn;
   while(!fio.eof())
   {
      fio.read((char*)&p, sizeof(p));
      if(p.planeno==pn)
      {
  p.putdata();
  found='t';
  cout<<"\n\n\tAre you sure you want to delete this record? (y/n).. ";
  cin>>confirm ;
  if(confirm=='n')
       file.write((char*)&p, sizeof(p));
      }
      else
  file.write((char*)&p, sizeof(p));
   }
   if(found=='f')
   cout<<"\n\n\n\tRecord not found !! \n";
   fio.close();
   file.close();
   remove("plane.dat") ;
   rename("temp.dat", "plane.dat");
}

void reservation()                  // ticket reservation
{
   cout<<"\n\n\t\t\tREGISTER YOUR TICKETS!! ";
   char a;
   cout<<"\n\n\n\t\tWant to see details of flights available ?(y/n)";
   cin>>a;
   if(a=='y' | a=='Y')
   {   cout<<"\n..................................................................\n";
       display();
   }
   ofstream fo;
   fo.open("ticket.dat", ios::out|ios::binary);
   if(!fo)
      cout<<"file can't be opened..";
   char b='y';
   while(b=='y'|b=='Y')
   {  t.get();
      fo.write((char*)&t, sizeof(t));
      cout<<"\n\n\t\tWant to register more tickets ?(y/n)";
      cin>>b;
   }
   fo.close();
}

void cancellation()          // ticket cancellation
{
    gotoxy(17,12);
    cout<<"Welcome to the TICKET CANCELLATION portal" ;
    cout<<"\n\n\n";
    ifstream fin;
    ofstream fo;
    fin.open("ticket.dat", ios::in|ios::binary);
    fo.open("temp.dat", ios::out|ios::binary);
    if(!fin)
 cout<<"\n\t\t\tFile can't be found ... ";
    if(!fo)
 cout<<"\n\t\t\tFile can't be opened....";
    cout<<"\n\n\t\tEnter the Reservation No.of the ticket which you want to cancel ";
    int rn;
    cin>>rn;
    delay(400);
    while(!fin.eof())
    {
 fin.read((char*)&t, sizeof(t));
 if(t.resno==rn)
 {
     t.put();
     delay(300);
     cout<<"\n\n\tDo you really want to cancel your ticket ?(y/n)";
     char r;
     cin>>r;
     if(r=='y'||r=='Y')
     {  cout<<"\n\n\t\t\tYour Ticket has been successfully cancelled ";
     }
     else
     {  fo.write((char*)&t, sizeof(t));
      }
      break ;
 }
 else
 {  cout<<"\n\n\t\tSorry!! No such reservation has been done...";
    fo.write((char*)&t, sizeof(t));
 }
    }
    delay(600);
    remove("ticket.dat");
    rename("temp.dat","ticket.dat");
    fin.close();
    fo.close();
}

void dispreserve()                // display records of tickets
{
   ifstream fin;
   fin.open("ticket.dat", ios::in|ios::binary);
   if(!fin)
       cout<<"\n\n\n\t\t\t File Can't Be opened .. ";
   gotoxy(13,15);
   cout<<"Enter the Reservation No. of the Ticket you Want to see  :  ";
   int res;
   cin>>res;
   int a=0;
   while(!fin.eof())
   {
       fin.read((char *)&t, sizeof(t));
       if(t.resno==res)
       { a=1;
  break ;
       }
       else
  a=4;
   }
   if(a==1)
   {  t.put();
      cout<<"\n\n\tPress Enter to go back to the menu . ";
      getch();
   }
   if(a==4)
     cout<<"\n\n\n\t\tNo such Reservation has been done . ";
   fin.close();
}
       // PROGRAM STARTS FROM HERE...

void main()
{
   textcolor(BLACK);               // graphics for colors
   textbackground(RED);
   clrscr();


  textcolor(RED);
  textbackground(BLACK);
  clrscr();
  delay(300);
  gotoxy(2,10);
  cout<<"......................................................................";
  delay(200);
  gotoxy(16,15);
  cout<<" \" S A M ' S   A I R L I N E   S E R V I C E S \"" ;
  delay(160);
  gotoxy(2,20);
  cout<<"......................................................................";
  delay(500);
  for(int s=3; s<70 ; s++)
  {
     gotoxy(s,24);
     cout<<"-->";
     delay(40);
  }
   for( s=0; s<70 ; s++)
  {
     gotoxy(s,26);
     cout<<">";
     delay(40);
  }
  delay(1200);

  textcolor(WHITE);
  textbackground(BLACK);
  clrscr();

   clrscr();
   for(int i=1, j=15; i<20, j<35 ; i++, j++)
   {
       gotoxy(i,j);
       cout<<"|";
       delay(120);
   }
   delay(200);
   for(i=69; i>20; i--)
   {
       gotoxy(i,35);
       cout<<"|";
       delay(60);
   }

   for(i=51, j=15; i<70, j<35 ; i++, j++)
    {
       gotoxy(i,j);
       cout<<"|";
       delay(120);
   }

   for(i=51; i>0; i--)
   {
       gotoxy(i,15);
       cout<<"|";
       delay(60);
   }

   gotoxy(9,18);
   delay(300);
   cout<<"C R E D I T S : - ";
   delay(500);
   gotoxy(12,21);
   cout<<"Mr. REGURAMAN R";
   delay(400);
   cout<<"\n\t - for regular guidance and great concepts \n\t\t of classes and data file handling ";
   delay(600);
   gotoxy(15,27);
   textcolor(GREEN);
   textbackground(BLACK);
   cout<<"\n\n\n\t\tPROJECT DONE BY: ";
   cout<<"\n\n\t\t  Arvind.S, Manoj Balaji, Sehaj Singh";
   delay(3500);

   textcolor(GREEN);
   textbackground(BLACK);
   clrscr();
   gotoxy(12,16);
   cout<<"Select your TYPE .. . .";
   cout<<"\n\n\n\n\t\t\t => (1.)  ADMINISTRATOR .. ";
   cout<<"\n\n\t\t\t => (2.)  USER ..  ";
   cout<<"\n\n\t\t\t Enter 0 if u want to exit ";
   int den;
   cout<<"\n\n\n\t\tEnter : ";
   cin>>den ;
   textcolor(GREEN);
   textbackground(BLACK);
   clrscr();
   if(den==0)
   {
       cout<<"\n\n\t\t\tExiting from the software ... ";
	delay(600);
	cout<<"\n\n\n\n\n\n\t\tHave a nice day!";
	delay(700);
	exit(0);

   }

   else if(den==2)
   {

  char ch='y';
  while(ch=='y'||ch=='Y')
  {
  delay(1200);
  textcolor(RED);
  textbackground(BLACK);
  clrscr();
  cout<<"\n\n\n\n\n\n";
  cout<<"\t\t\t\t F.R.I.D.A.Y"<<endl;
  cout<<"\t\t\tUSER TICKET RESERVATION PORTAL"<<endl;
  cout<<"*************************************************************************";
  cout<<"\n\n\n\t\t\t\t\t\tM E N U !!! ";
  cout<<"\n\n\t\t\t(1.) Display Flight Details . ";
  cout<<"\n\n\t\t\t(2.) Reserve a Ticket . ";
  cout<<"\n\n\t\t\t(3.) Display your Ticket . ";
  cout<<"\n\n\t\t\t(4.) Cancel a Ticket . ";
  cout<<"\n\n\t\t\t(5.) Exit . ";
  cout<<"\n\n\n";
  cout<<"*************************************************************************";
  int choice;
  delay(500);
  cout<<"\n\n\n\t\t\t\t\tEnter your choice... : ";
  cin>>choice ;
  delay(1300);
  clrscr();
  switch(choice)
  {
      case 1 : display();
    break ;
      case 2 : reservation();
    break ;
      case 3 : dispreserve();
    break ;
      case 4 : cancellation();
    break ;
      case 5 : cout<<"\n\n\t\t\tExiting from the software ... ";
	delay(600);
	cout<<"\n\n\n\n\n\n\t\tThanks for trying out F.R.I.D.A.Y";
	delay(700);
	exit(0);
	break ;
      default : cout<<"\n\n\n\t\t\tUnknown choice...";
 delay(500);
 cout<<"\n\n\t\t\tWant to enter the choice again?(y/n)";
 cin>>ch;
    }
  }
}

else if(den==1)
{
   int k=0;
   while(k<4)
   {textcolor(GREEN);
   textbackground(BLACK);
   clrscr();
   cout<<"\n\n\n\n\n\n\n";
   cout<<"..................................................................";
   delay(300);
   cout<<"\n\n\n";
   cout<<"\t\t\t\tJ.A.R.V.I.S";
   cout<<"\n\t\tJUST A RATHER VERY INTELLIGENT SYSTEM";
   cout<<"\n\n\t\tAdmin Login Management Portal";
   delay(300);
   cout<<"\n\n\n\t\t\tEnter your password to continue......";
   char p[7],p1[7],p2[7],pass[7];
   strcpy(p,"wakanda");
   strcpy(p1,"nymeria");
   strcpy(p2,"blackop");
   pass[0]=getch();
   cout<<"*";
   pass[1]=getch();
   cout<<"*";
   pass[2]=getch();
   cout<<"*";
   pass[3]=getch();
   cout<<"*";
   pass[4]=getch();
   cout<<"*";
   pass[5]=getch();
   cout<<"*";
   pass[6]=getch();
   cout<<"*";
   pass[7]='\0';
  /* cout<<"*";
   pass[8]=getch();
   cout<<"*";
   pass[9]=getch();
   cout<<"*";
   pass[10]=getch();
   cout<<"*";
   pass[11]=getch();
   cout<<"*";
   pass[12]=getch();
   cout<<"*";
   pass[8]='\0';
  cout<<"*";
   pass[14]='\0';*/
   getch();
   cout<<"\n\n\n\n";
   delay(500);
   cout<<"\n\n\n\n\t\t\t\tChecking your password ";
   delay(300);
   cout<<".";
   delay(300);
   cout<<".";
   delay(300);
   cout<<".";
   delay(300);
   cout<<".";
   delay(300);
   cout<<".";
   delay(300);
   cout<<"\b\b\b\b\b";
   cout<<"     ";
   cout<<"\b\b\b\b\b";
   delay(300);
   cout<<".";
   delay(300);
   cout<<".";
   delay(300);
   cout<<".";
   delay(300);
   cout<<".";
   delay(300);
   cout<<".";
   delay(300);

   if(strcmp(pass,p)==0)
   {   delay(1200);
       textcolor(GREEN);
       textbackground(BLACK);
       cout<<"\n\n\n\t\tWelcome back,Arvind !!! ";
       k=4;
   }
   else if(strcmp(pass,p1)==0)
   {   delay(1200);
       textcolor(BLUE);
       textbackground(BLACK);
       cout<<"\n\n\n\t\tWelcome back,Sehaj !!! ";
       k=4;
   }
   else if(strcmp(pass,p2)==0)
   {   delay(1200);
       textcolor(RED);
       textbackground(BLACK);
       cout<<"\n\n\n\t\tWelcome back,Manoj !!! ";
       k=4;
   }
   else
   {
      cout<<"\n\n\t\tWant to enter password again ?(y/n) : ";
      char g;
      cin>>g;
      if(g=='y'|g=='Y')
 k++;
      else
      {
   cout<<"\n\n\t\t\tExiting from the software....";
   delay(1000);
   exit(0);
      }
   }
}
  char ch1='y';
  while(ch1=='y'||ch1=='Y')
  {
  delay(1200);
  textcolor(GREEN);
  textbackground(BLACK);
  clrscr();
  cout<<"\n\n\n\n\n\n";
  cout<<"*************************************************************************";
  cout<<"\n\n\n\t\t\t\t\tM E N U !!! ";
  cout<<"\n\n\t\t\t(1.) Create Brand New File .";
  cout<<"\n\n\t\t\t(2.) Display Flight Details . ";
  cout<<"\n\n\t\t\t(3.) Add Record . ";
  cout<<"\n\n\t\t\t(4.) Search a Data . ";
  cout<<"\n\n\t\t\t(5.) Modify a Record . ";
  cout<<"\n\n\t\t\t(6.) Delete a Record . ";
  cout<<"\n\n\t\t\t(7.) Exit.";
  cout<<"\n\n\n";
  cout<<"*************************************************************************";
  int choice1;
  delay(500);
  cout<<"\n\n\n\t\t\t\t\tEnter your choice... : ";
  cin>>choice1 ;
  delay(1300);
  clrscr();
  switch(choice1)
  {
      case 1 : write();
    break ;
      case 2 : display();
    break ;
      case 3 : add();
    break ;
      case 4 : search();
    break ;
      case 5 : mod();
    break ;
      case 6 : del();
    break ;

      case 7 : cout<<"\n\n\t\t\tExiting from the software ... ";
	delay(600);
	cout<<"\n\n\n\n\n\n\t\t\t\tThanks for trying out J.A.R.V.I.S!";
	delay(700);
	exit(0);
	break ;
      default : cout<<"\n\n\n\t\t\tUnknown choice...";
 delay(500);
 cout<<"\n\n\t\t\tWant to enter the choice again?(y/n)";
 cin>>ch1;
    }
  }
}
  getch();
}
