//#ifndef systemPage
//#define systemPage
#pragma once
#include <iostream>
using namespace std;
#include "carManage.h"

class SystemPage {
public:
	int loginFlag;  // 0 = logout state
	CarManage m_cm;
	
	SystemPage();  // constructor
	void mainMenu();  // main menu
	void adminProcess();  // admin process
	void userProcess();  // user process
	void loginPage();  // login board
	void adminLogin();
	void userMenu();
	void adminMenu();  // admin menu

	void addUser();  // for user signup
};

// #endif