#include <iostream>
#include "systemPage.h"
#include "carManage.h"
using namespace std;

int main()
{
	SystemPage sp;  // create an instance

	while (1) 
	{
		sp.loginPage();  // login page

		switch (getchar()) 
		{
		case '1':  // admin login
			sp.adminProcess();     
			break;
		case '2':  // user login
			sp.userProcess();
			break;
		case '3':  // user signup
			sp.addUser();
			break;
		case '\n':
			break;
		default:
			cout << "wrong input! please input 1, 2 or 3;" << endl;
			system("pause");
			break;
		}
	}

	system("pause");
	return 0;
}