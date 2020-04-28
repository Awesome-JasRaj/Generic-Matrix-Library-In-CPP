#include "matrix_library.h"
using namespace std;
void init();
void opr();
int main()
{
	int choice;
	while(true)
	{
		cout<<"\tWELCOME! MAKE A CHOICE!"<<endl;
		cout<<"------->PRESS 1 FOR INITIALIZATION AND ITERATORS"<<endl;
		cout<<"------->PRESS 2 TO CARRY OUT MATRIX OPERATIONS"<<endl;
		cout<<"------->PRESS 3 TO EXIT" << endl;
		cout<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1: init();
					break;
			case 2: opr();
					break;
			case 3: return 0;
			default: cout<<"Please enter a valid option"<<endl;
		}
	}
}