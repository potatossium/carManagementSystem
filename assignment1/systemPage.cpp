#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>
using namespace std;
#include "carManage.h"
#include "systemPage.h"

// constructor
SystemPage::SystemPage() {
	this->loginFlag = 0;  // logout state
}

void SystemPage::adminMenu() {
	system("cls");
	cout << "                          *******************************************************************" << endl;
	cout << "                          ***                             ADMIN MENU                      ***" << endl;
	cout << "                          *******************************************************************" << endl;
	cout << "                          ***          1.add car             2.remove car                 ***" << endl;
	cout << "                          ***                                                             ***" << endl;
	cout << "                          ***          3.update car          4.query all cars             ***" << endl;
	cout << "                          ***                                                             ***" << endl;
	cout << "                          ***          5. query a car        6. handle bookings           ***" << endl;
	cout << "                          ***                                                             ***" << endl;
	cout << "                          ***                           0.EXIT                            ***" << endl;
	cout << "                          ***                                                             ***" << endl;
	cout << "                          *******************************************************************" << endl;
}
void SystemPage::userMenu() {
	cout << "                          ******************************************************************" << endl;
	cout << "                          ***                       USER MENU                            ***" << endl;
	cout << "                          ******************************************************************" << endl;
	cout << "                          ***           1.query all cars       2.query car by id         ***" << endl;
	cout << "                          ***                                                            ***" << endl;
	cout << "                          ***           3.car rental                                     ***" << endl;
	cout << "                          ***                                                            ***" << endl;
	cout << "                          ***           0.exit                                           ***" << endl;
	cout << "                          ***                                                            ***" << endl;
	cout << "                          ******************************************************************" << endl;
}

void SystemPage::loginPage() {
	system("cls");
	cout << "                          ******************************************************************" << endl;
	cout << "                          ***                          Login Board                       ***" << endl;
	cout << "                          ******************************************************************" << endl;
	cout << "                          ***    1. admin login      2.user login      3.user signup     ***" << endl;
	cout << "                          ******************************************************************" << endl;

	cout << "please enter 1, 2 or 3: " << endl;
}

void SystemPage::userProcess() {
	system("cls");
	cout << "this is user process" << endl;

	string username;
	string password;
	cout << "please input your username:" << endl;
	cin >> username;
	cout << "please input your password:" << endl;
	cin >> password;
	cout << endl;

	// check if username and password exists in the users.csv
	ifstream ifs;
	ifs.open("users.csv", ios::out);
	string lineData;
	string usn, pwd;  // store user info extracted from the file.
	while (getline(ifs, lineData)) {
		int count = 0;
		int pos = -2;
		int start = 0;
		while(pos != -1) {
			pos = lineData.find(",", start);
			string target = lineData.substr(start, pos - start);
			if (count == 0) usn = target;
			if (count == 1 && usn==username) {  // username matched
				pwd = target;
				if (password == pwd) this->loginFlag = 1;
				break;
			}
			start = pos + 1;
			count++;
		}
	}
	ifs.close();
	// return to login page if not match
	if (this->loginFlag == 0) {
		cout << "wrong username or password!" << endl;
		system("pause");
		system("cls");
		return;
	}
	this->loginFlag = 0;
	// save the user_name to CarManage obj m_cm
	this->m_cm.m_user = username;
	// show usermenu
	while (1) {
		system("cls");
		this->userMenu();

		switch (getchar()) {
		case '1':  // query all cars
			this->m_cm.queryAllCars();
			break;
		case '2':  // query a car by id
			this->m_cm.queryCar();
			break;
		case '3':  // borrow a car
			this->m_cm.rentCar();
			break;
		case '0':  // return to main menu
			return;
			break;
		case '\n':
			break;
		default:
			cout << "wrong input! please input 0, 1, 2 or 3;" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

}

void SystemPage::adminLogin() {
	// read admin info from the local .txt file
	ifstream ifs;
	ifs.open("admin.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "failed to open the file! it might be wrong file path." << endl;
		system("pause");
		return;
	}
	string data;
	vector<string> v;
	while (ifs >> data) {  // read and put file info into data
		int pos = 0;
		int start = 0;
		while (pos != -1) {
			pos = (int)data.find(",", start);  // find the position of comma
			string target = data.substr(start, pos - start);  // string before comma, [ )
			v.push_back(target);
			// cout << target << endl;
			start = pos + 1;  // renew the start point
		}
	}
	ifs.close();

	string name;  // name
	char pwd[10];  // passwords
	cout << "please input the admin's name:" << endl;
	cin >> name;
	int i = 0;
	cout << "please input the admin's password ( <=9 characters ):" << endl;

	while (i < 9 && (pwd[i] = _getch()) && pwd[i] != '\r') {  // \r = "enter"
		printf("*");  // cover the pwd
		i++;
	}
	cout << endl;
	pwd[i] = 0;   // end of a string \0
	string password(pwd);

	// compare 
	if (name == v[0] && password == v[1]) {
		cout << "login success!" << endl;
		this->loginFlag = 1;
		system("pause");
		return;
	}
	else {
		cout << "incorrect username or password" << endl;
		system("pause");
		return;
	}
}
void SystemPage::adminProcess() {
	this->adminLogin();

	if(this->loginFlag == 0) {
		return;
	}
	this->loginFlag = 0;

	while(1) {
		this->adminMenu();

		switch (getchar()) {
		case '1':  // add cars
			this->m_cm.addCar();
			break;
		case '2':  // remove cars
			this->m_cm.removeCar();
			break;
		case '3':  // update car entry
			this->m_cm.updateCar();
			break;
		case '4':  // query all cars
			this->m_cm.queryAllCars();
			break;
		case '5':  // query a car entry
			this->m_cm.queryCar();
			break;
		case '6':  // handle booking applications
			this->m_cm.handleBooking();
			break;
		case '0':  // return to main menu
			cout << "bye bye!" << endl;
			return;
			break;
		case '\n':
			break;
		default:
			cout << "wrong input! please input 0, 1, 2, 3, 4, 5, or 6: " << endl;
			system("pause");
			break;
		}
	}


}

void SystemPage::addUser() {
	// show signup board
	system("cls");
	cout << "                          ******************************************************************" << endl;
	cout << "                          ***                        user signup                         ***" << endl;
	cout << "                          ******************************************************************" << endl;
	// input id number
	cout << "please input your id:" << endl;
	string id;
	cin >> id;
	// check if idCard is valid
	for (int i = 0; i < id.length(); i++) {
		if (!(id[i] <= '9' && id[i] >= '0') && !(id[i] <= 'Z' || id[i] >= 'A') && !(id[i] <= 'z' || id[i] >= 'a')) {  // not valid
			cout << "invalid id! id must be numbers or letters." << endl;
			system("pause");
			return;
		}
	}
	// create the pwd
	string pwd1;
	string pwd2;
	cout << "please create your password:" << endl;
	cin >> pwd1;
	cout << "please type your password again:" << endl;
	cin >> pwd2;
	if (pwd1 != pwd2) {
		cout << "passwords do not match!" << endl;
		cout << "please retry" << endl;
		system("pause");
		system("cls");
		return;
	}
	// check if the id already exists
	ifstream ifs;
	ifs.open("users.csv", ios::out);
	if (!ifs.is_open()) {
		cout << "error occurs while opening the file!" << endl;
		system("pause");
		return;
	}
	else
	{
		string userData;
		while (ifs >> userData)
		{
			int pos = -1;
			int start = 0;
			while (1)
			{
				pos = userData.find(",", start);
				if (pos == -1)
				{
					break;
				}
				else
				{
					string target = userData.substr(start, pos - start);
					if (target == id)
					{
						cout << "This id has been signed up!" << endl;
						system("pause");
						system("cls");
						return;
					}
				}
				start = pos + 1;
			}
		}
	}
	// sign up success --- put new user into local files.
	ofstream ofs;
	ofs.open("users.csv", ios::in | ios::app);
	if (!ofs.is_open()) {
		cout << "" << endl;
		system("pause");
		return;
	}
	ofs << id << "," << pwd1 << "," << endl;
	ofs.close();
	cout << "sign up success!" << endl;
	system("pause");
}