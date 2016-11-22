#include "admin.cpp"
#include<iostream>
using namespace std;
char password[20];
char* getpass()
{
	char ch;
	cout<<"Enter password : ";
	ch=getch();
	int n=ch,i=0,flag=1;
	while(n!=10)
	{
		cout<<"*";
		password[i]=ch;
		i++;
		password[i]='\0';
		ch=getch();
		n=ch;
		flag=0;
	}
	cout<<"\n";
	return password;
}
int main()
{
	int ch,err=0,size,flag;
	char chk_id[20],admin_id[]="Admin";
	string chk_pass,admin_pass="opensesame";
	do
	{
		cout<<"\nMenu : \n1.Signup\n2.Login\n3.Exit\nEnter choice : ";
		cin>>ch;
		switch(ch)
		{
			case 1 : char in_ch;
				 u_inout.open("user_db.bin",ios::app|ios::in|ios::out|ios::binary);
				 cout<<"\nEnter your personal details\n";
				 err=usr.getdata();
				 if(err)
				 {
				 	break;
				 }
				 cout<<"\nIf you wish to re-enter details press Y or N to enter data into database : ";
				 cin>>in_ch;
				 usr.putdata();
				 if(in_ch=='Y')
				 {
				 	break;
				 }
				 u_inout.write((char*)&usr,sizeof(usr));
				 cout<<"\nRecord successfully written into the file\n";
				 u_inout.close();;
				 break;
			case 2 : flag=0;
				 cout<<"\nEnter user_id : ";
				 cin>>chk_id;
				 getch();
				 chk_pass=getpass();
				 //cout<<"\nUser_id : "<<chk_id<<"\nPassword : "<<chk_pass<<"\n";
				 if(!strcmp(chk_id,admin_id) && admin_pass==chk_pass)
				 {
				 	admin();
				 }
				 else
				 {
				 	u_inout.open("user_db.bin",ios::app|ios::in|ios::out|ios::binary);
				 	u_inout.seekg(0,ios::end);
				 	//cout<<"\nFile size : "<<u_inout.tellg()<<"\n";
				 	//cout<<"\nsizeof(usr) : "<<sizeof(usr)<<"\n";
				 	size=u_inout.tellg()/sizeof(usr);
				 	u_inout.seekg(0,ios::beg);
				 	//cout<<"\nSize : "<<size<<"\n";
				 	while(size)
				 	{
				 		u_inout.read((char*)&usr,sizeof(usr));
				 		string user_pass=usr.get_password();
				 		//cout<<"\nUser_id : "<<chk_id<<"\nPassword : "<<chk_pass<<"\n";
				 		if(!strcmp(chk_id,usr.get_id()) && chk_pass==user_pass)
				 		{
				 			usr.userfnc();
				 			flag=1;
				 			break;
				 		}
				 		size--;
				 	}
				 	if(!flag)
				 	{
				 		cout<<"\nEither userid/password is wrong or both are wrong\n";
				 	}
				 	u_inout.close();
				 }
				 break;
			case 3 : break;
			default : cout<<"\nInvalid choice\n";
				  break;
		}
	}while(ch!=3);
	return 0;
}







