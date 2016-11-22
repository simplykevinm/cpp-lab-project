#include<iostream>
#include<string.h>
using namespace std;
class item
{
	char uid[10];
	char pid[10];
	char pname[20];
	char cat[30];
	char desc[100];
	public:
		void get_item()
		{
			cout<<"\nEnter product ID : ";
			cin>>pid;
			cout<<"\nEnter product name : ";
			cin>>pname;
			cout<<"\nEnter category : ";
			cin>>cat;
			cout<<"\nEnter description : ";
			cin>>desc;
		}
		void set_uid(char *user_id)
		{
			strcpy(uid,user_id);
		}
		void put_item()
		{
			cout<<"\nUser ID : "<<uid;
			cout<<"\nProduct ID : "<<pid;
			cout<<"\nProduct name : "<<pname;
			cout<<"\nCategory : "<<cat;
			cout<<"\nDescription : "<<desc;
			cout<<"\n";
		}
		char* get_pname()
		{
			return pname;
		}
		char* get_uid()
		{
			return uid;
		}
		char* get_pid()
		{
			return pid;
		}
}itm,itm_arr[50];








