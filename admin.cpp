#include<iostream>
#include "user.cpp"
using namespace std;
void admin()
{
	int ch,size,flag,i,size1;
	char chk_id[10];
	ofstream u2_out;
	ofstream i2_out;
	do
	{
		cout<<"\nMENU\n1.Display all users\n2.Display all items\n3.Delete user and contents\n4.Exit\nEnter choice : ";
		cin>>ch;
		switch(ch)
		{
			case 1 : flag=0;
				 u_inout.open("user_db.bin",ios::app|ios::in|ios::out|ios::binary);
				 u_inout.seekg(0,ios::end);
				 //cout<<"\nFile size : "<<u_inout.tellg()<<"\n";
				 //cout<<"\nsizeof(usr) : "<<sizeof(usr)<<"\n";
				 size=u_inout.tellg()/sizeof(usr);
				 u_inout.seekg(0,ios::beg);
				 //cout<<"\nSize : "<<size<<"\n";
				 //cout<<"ID\tNAME\t\t\tPHONE\t\tE-MAIL\t\t\t\tCITY\t\t\tLANDMARK\n";
				 while(size)
				 {
				 	u_inout.read((char*)&usr,sizeof(usr));
				 	usr.putdata();
				 	size--;
				 	flag=1;
				 }
				 if(!flag)
				 {
				 	cout<<"\nNo users registered\n";
				 }
				 u_inout.close();
				 break;
			case 2 : flag=0;
				 i_inout.open("item_db.bin",ios::app|ios::in|ios::out|ios::binary);
				 i_inout.seekg(0,ios::end);
				 size=i_inout.tellg()/sizeof(itm);
				 i_inout.seekg(0,ios::beg);
				 while(size)
				 {
				 	i_inout.read((char*)&itm,sizeof(itm));
				 	itm.put_item();
				 	flag=1;
				 	size--;
				 }
				 if(!flag)
				 {
				 	cout<<"\nNo items found\n";
				 }
				 i_inout.close();
				 break;
			case 3 : flag=0;
				 cout<<"\nEnter the user-id : ";
				 cin>>chk_id;
				 u_inout.open("user_db.bin",ios::app|ios::in|ios::out|ios::binary);
				 u_inout.seekg(0,ios::end);
				 size=u_inout.tellg()/sizeof(usr);
				 size1=size;
				 u_inout.seekg(0,ios::beg);
				 i=0;
				 //cout<<"\nSize : "<<size<<"\n";
				 while(size)
				 {
				 	u_inout.read((char*)&usr_arr[i],sizeof(usr));
				 	size--;
				 	i++;
				 	flag=1;
				 }
				 if(!flag)
				 {
				 	cout<<"\nNo users registered\n";
				 }
				 u_inout.close();
				 u2_out.open("user_db.bin",ios::out|ios::binary);
				 i=0;
				 flag=0;
				 //cout<<"\nSize1 : "<<size1<<"\n";
				 while(size1)
				 {
				 	size1--;
				 	//cout<<"\nInside while\n";
				 	if(!strcmp(chk_id,usr_arr[i].get_id()))
				 	{
				 		//cout<<"\nInside if\n";
				 		i++;
				 		flag=1;
				 		continue;
				 	}
				 	//cout<<"\nWriting content\n";
				 	//cout<<"\nPut pointer : "<<u2_out.tellp()<<"\n";
				 	u2_out.write((char*)&usr_arr[i],sizeof(usr));
				 	i++;
				 }
				 if(flag)
				 {
				 	cout<<"\nUser successfully deleted\n";
				 }
				 u2_out.close();
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
				 	cout<<"\nInside while\n";
				 	if(!strcmp(chk_id,itm_arr[i].get_uid()))
				 	{
				 		cout<<"\nInside if\n";
				 		i++;
				 		flag=1;
				 		continue;
				 	}
				 	cout<<"\nWriting content\n";
				 	cout<<"\nPut pointer : "<<u2_out.tellp()<<"\n";
				 	i2_out.write((char*)&itm_arr[i],sizeof(itm));
				 	i++;
				 }
				 if(flag)
				 {
				 	cout<<"\nContents successfully deleted\n";
				 }
				 i2_out.close();
				 break;
			case 4 : break;
			default : cout<<"\nInvalid choice\n";
				  break;
		}
	}while(ch!=4);
}






