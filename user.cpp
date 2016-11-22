#include<iostream>
#include<string.h>
#include<fstream>
#include<termios.h>
#include "item.cpp"
using namespace std;

static struct termios old, new1;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< to use getch() and getche() >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new1 = old; /* make new settings same as old settings */
  new1.c_lflag &= ~ICANON; /* disable buffered i/o */
  new1.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new1); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}

fstream i_inout;
fstream u_inout;

class user:public item
{
	char phone[11];
	char id[10];
	char pass[20];
	char name[20];
	char mail[40];
	char city[20];
	char l_mark[20];
	public:
		int getdata();
		/*{
			int size;
			user tmp_usr;
			cout<<"\nEnter id : ";
			cin>>id;
			ifstream u_in;
			u_in.open("user_db.bin",ios::in|ios::binary);
			u_in.seekg(0,ios::end);
			size=u_in.tellg()/sizeof(usr);
			u_in.seekg(0,ios::beg);
			//cout<<"\nSize : "<<size<<"\n";
			while(size)
			{
				u_in.read((char*)&tmp_usr,sizeof(usr));
				size--;
			}
			getch();
			if(get_pass())
			{
				return 1;
			}
			cout<<"Enter name : ";
			cin>>name;
			cout<<"Enter phone : ";
			cin>>phone;
			cout<<"Enter mail : ";
			cin>>mail;
			cout<<"Enter city : ";
			cin>>city;
			cout<<"Enter l_mark : ";
			cin>>l_mark;
			return 0;	
		}*/
		int get_pass()
		{
			char ch;
			cout<<"Enter password : ";
			ch=getch();
			int n=ch,i=0,flag=1;
			while(n!=10)
			{
				cout<<"*";
				pass[i]=ch;
				i++;
				pass[i]='\0';
				ch=getch();
				n=ch;
				flag=0;
			}
			cout<<"\n";
			return flag;
		}
		void putdata()
		{
			cout<<"\nUser ID : "<<id;
			cout<<"\nUser name : "<<name;
			cout<<"\nPhone : "<<phone;
			cout<<"\nE-mail : "<<mail;
			cout<<"\nCity : "<<city;
			cout<<"\nLandmark : "<<l_mark;
			cout<<"\n";
		}
		/*void filewr()
		{write to file using this pointer
			//this->putdata();
			u_inout.open("user_db.bin",ios::app|ios::in|ios::out|ios::binary);
			u_inout.write((char*)this,sizeof(this));
			cout<<"\nRecord successfully written into the file\n";
			u_inout.close();
		}
		void filerd()
		{
			u_inout.open("user_db.bin",ios::app|ios::in|ios::out|ios::binary);
			u_inout.read((char*)this,sizeof(this));
			u_inout.close();
		}*/
		char* get_id()
		{
			return id;
		}
		char* get_password()
		{
			return pass;
		}
		void userfnc();
}usr,usr_arr[10];
int user::getdata()
{
	int size;
	user tmp_usr;
	cout<<"\nEnter id : ";
	cin>>id;
	ifstream u_in;
	u_in.open("user_db.bin",ios::in|ios::binary);
	u_in.seekg(0,ios::end);
	size=u_in.tellg()/sizeof(usr);
	u_in.seekg(0,ios::beg);
	//cout<<"\nSize : "<<size<<"\n";
	while(size)
	{
		u_in.read((char*)&tmp_usr,sizeof(usr));
		if(!strcmp(id,tmp_usr.get_id()))
		{
			cout<<"\nUser-ID already exists, choose another one\n";
			return 1;
		}
		size--;
	}
	u_in.close();
	getch();
	if(get_pass())
	{
		cout<<"\nInvalid password entry\n";
		return 1;
	}
	cout<<"Enter name : ";
	cin>>name;
	cout<<"Enter phone : ";
	cin>>phone;
	cout<<"Enter mail : ";
	cin>>mail;
	cout<<"Enter city : ";
	cin>>city;
	cout<<"Enter l_mark : ";
	cin>>l_mark;
	return 0;	
}
void user::userfnc()
{
	int ch,size,flag=0,size1,i;
	char chk_item[20],in_ch,chk_pid[10];
	ofstream i2_out;
	do
	{
		cout<<"\nMENU\n1.Search for an item\n2.Add item\n3.View items\n4.Delete item\n5.Exit\nEnter choice : ";
		cin>>ch;
		switch(ch)
		{
			case 1 : flag=0;
				 i_inout.open("item_db.bin",ios::app|ios::in|ios::out|ios::binary);
				 cout<<"\nEnter name of item : ";
				 cin>>chk_item;
				 i_inout.seekg(0,ios::end);
				 //cout<<"\nFile size : "<<i_inout.tellg()<<"\n";
				 //out<<"\nsizeof(itm) : "<<sizeof(itm)<<"\n";
				 size=i_inout.tellg()/sizeof(itm);
				 //cout<<"\nSize : "<<size<<"\n";
				 i_inout.seekg(0,ios::beg);
				 while(size)
				 {
				 	//cout<<"\nInside while\n";
				 	i_inout.read((char*)&itm,sizeof(itm));
				 	if(!strcmp(chk_item,itm.get_pname()) && strcmp(this->id,itm.get_uid())!=0)
				 	{
				 		itm.put_item();
				 		flag=1;
				 		cout<<"\nDo you want details on this user....?(Y/N) : ";
				 		cin>>in_ch;
				 		if(in_ch=='Y')
				 		{
				 			user temp_usr;
				 			fstream u2_inout;
				 			u2_inout.open("user_db.bin",ios::app|ios::in|ios::out|ios::binary);
				 			u2_inout.seekg(0,ios::end);
				 			//cout<<"\nFile size : "<<u2_inout.tellg()<<"\n";
				 			///cout<<"\nsizeof(usr) : "<<sizeof(usr)<<"\n";
				 			size=u2_inout.tellg()/sizeof(usr);
				 			//cout<<"\nSize : "<<size<<"\n";
				 			u2_inout.seekg(0,ios::beg);
				 			while(size)
				 			{
				 				u2_inout.read((char*)&temp_usr,sizeof(usr));
				 				if(!strcmp(itm.get_uid(),temp_usr.get_id()))
				 				{
				 					temp_usr.putdata();
				 					break;
				 				}
				 				size--;
				 			}
				 			u2_inout.close();
				 		}
				 		break;
				 	}
				 	//itm.put_item();
				 	size--;
				 }
				 if(!flag)
				 {
				 	cout<<"\nNo item found\n";
				 }
				 i_inout.close();
				 break;
			case 2 : itm.get_item();
				 itm.set_uid(this->id);
				 itm.put_item();
				 i_inout.open("item_db.bin",ios::app|ios::in|ios::out|ios::binary);
				 i_inout.write((char*)&itm,sizeof(itm));
				 i_inout.close();
				 break;
			case 3 : flag=0;
				 i_inout.open("item_db.bin",ios::app|ios::in|ios::out|ios::binary);
				 i_inout.seekg(0,ios::end);
				 //cout<<"\nFile size : "<<i_inout.tellg()<<"\n";
				 //cout<<"\nsizeof(itm) : "<<sizeof(itm)<<"\n";
				 size=i_inout.tellg()/sizeof(itm);
				 //cout<<"\nSize : "<<size<<"\n";
				 i_inout.seekg(0,ios::beg);
				 while(size)
				 {
				 	i_inout.read((char*)&itm,sizeof(itm));
				 	if(!strcmp(this->id,itm.get_uid()))
				 	{
				 		itm.put_item();
				 		flag=1;
				 	}
				 	size--;
				 }
				 if(!flag)
				 {
				 	cout<<"\nNo items found\n";
				 }
				 i_inout.close();
				 break;
			case 4 : cout<<"\nEnter product ID : ";
				 cin>>chk_pid;
				 i_inout.open("item_db.bin",ios::app|ios::in|ios::out|ios::binary);
				 i_inout.seekg(0,ios::end);
				 size=i_inout.tellg()/sizeof(itm);
				 size1=size;
				 i_inout.seekg(0,ios::beg);
				 i=0;
				 flag=0;
				 //cout<<"\nSize : "<<size<<"\n";
				 while(size)
				 {
				 	i_inout.read((char*)&itm_arr[i],sizeof(itm));
				 	size--;
				 	i++;
				 	flag=1;
				 }
				 if(!flag)
				 {
				 	cout<<"\nNo items found\n";
				 }
				 i_inout.close();
				 i2_out.open("item_db.bin",ios::out|ios::binary);
				 i=0;
				 flag=0;
				 //cout<<"\nSize1 : "<<size1<<"\n";
				 while(size1)
				 {
				 	size1--;
				 	//cout<<"\nInside while\n";
				 	if(!strcmp(chk_pid,itm_arr[i].get_pid()) && !strcmp(this->id,itm_arr[i].get_uid()))
				 	{
				 		//cout<<"\nInside if\n";
				 		i++;
				 		flag=1;
				 		continue;
				 	}
				 	//cout<<"\nWriting content\n";
				 	//cout<<"\nPut pointer : "<<u2_out.tellp()<<"\n";
				 	i2_out.write((char*)&itm_arr[i],sizeof(itm));
				 	i++;
				 }
				 if(flag)
				 {
				 	cout<<"\nContents successfully deleted\n";
				 }
				 else
				 {
				 	cout<<"\nItem not found\n";
				 }
				 i2_out.close();
				 break;
			case 5 : 
				 break;
			default : cout<<"\nInvalid choice\n";
				  break;
		}
	}while(ch!=5);
}
/*int main()
{
	char str[10],ch;
	int err;
	err=usr.getdata();
	if(err)
	{
		cout<<"\nInvalid password entered\n";
		return 0;
	}
	usr.putdata();
	usr.filewr();
	usr.filerd();
	usr.putdata();
	cout<<"\n\n";
	i_inout.close();
	return 0;
}*/















