#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "car.h"
#include "carManage.h"
#include "tools.h"
using namespace std;

// constructor
CarManage::CarManage() {
	this->m_path = "cars_fortest02.csv";
}

void CarManage::addCar() {
	system("cls");
	cout << "                          ******************************************************************" << endl;
	cout << "                          ***                         add a car entry                    ***" << endl;
	cout << "                          ******************************************************************" << endl;
	// (ID, make, model, year, mileage, available now, minimum rent period, maximum rent period.)
	string id, make, model, year, mileage, available, minperiod, maxperiod;
	Car c;
	cout << "please input the id of the car: " << endl;
	cin >> c.m_id;
	cout << "please input the car make: " << endl;
	cin >> c.m_make;
	cout << "please input the car model: " << endl;
	cin >> c.m_model;
	cout << "please input years of usage: " << endl;
	cin >> c.m_year;
	cout << "please input mileage of usage: " << endl;
	cin >> c.m_mileage;
	cout << "please input (0 or 1) if the car is available (0:NOT, 1:YES): " << endl;
	cin >> c.m_available;
	cout << "please input minimum of rent period: " << endl;
	cin >> c.min_rentPeriod;
	cout << "please input maximum of rent period: " << endl;
	cin >> c.max_rentPeriod;

	// check if the id already exists.
	Tools tls;
	if (tls.checkid(this->m_path, id) == 0) {
		cout << "this id do not exist!" << endl;
		return;
	}
	//save the data to the local file;
	ofstream ofs;
	ofs.open(this->m_path, ios::out | ios::app);
	if(!ofs.is_open()) {
		cout << "fail to open the file!" << endl;
		system("pause");
		system("cls");
		return;
	}
	ofs << c.m_id << "," << c.m_make << "," << c.m_model << "," << c.m_year << "," << c.m_mileage << "," << c.m_available << "," << c.min_rentPeriod << "," << c.max_rentPeriod << "," << endl;
	//for(map<string, Car>::iterator it = this->m_cars.begin(); it != this->m_cars.end(); it++) {
	//	ofs << it->second.m_id << "," << it->second.m_make << "," << it->second.m_model << "," << endl;
	//}
	ofs.close();
	// this->m_vcars.clear();

	cout << "This car has been added successfully!" << endl;
	system("pause");
	system("cls");

}
void CarManage::updateCar() {
	system("cls");
	cout << "                          ******************************************************************" << endl;
	cout << "                          ***                      update a car entry                    ***" << endl;
	cout << "                          ******************************************************************" << endl;
	// (ID, make, model, year, mileage, available now, minimum rent period, maximum rent period.)
	Car ci;
	cout << "please input the id of the car: " << endl;
	cin >> ci.m_id;
	// check if the car id exists;
	Tools tls;
	if (tls.checkid(this->m_path, ci.m_id) == 1) {
		cout << "this id do not exist in the file!" << endl;
		system("pause");
		return;
	}

	cout << "please input the car make: " << endl;
	cin >> ci.m_make;
	cout << "please input the car model: " << endl;
	cin >> ci.m_model;
	cout << "please input years of usage: " << endl;
	cin >> ci.m_year;
	cout << "please input mileage of usage: " << endl;
	cin >> ci.m_mileage;
	cout << "please input (0 or 1) if the car is available (0:NOT, 1:YES): " << endl;
	cin >> ci.m_available;
	cout << "please input minimum of rent period: " << endl;
	cin >> ci.min_rentPeriod;
	cout << "please input maximum of rent period: " << endl;
	cin >> ci.max_rentPeriod;

	// remove the original entry;
	ifstream ifs;
	ifs.open(this->m_path, ios::in);
	vector<Car> v_remains;  // after remove the target line
	Car c;
	string carData;
	while (getline(ifs, carData)) {
		int count = 0;
		int pos = -2;
		int start = 0;
		while (pos != -1) {
			pos = carData.find(",", start);
			string target = carData.substr(start, pos - start);
			if (target == ci.m_id && count == 0) {  // not put in v_remains
				// cout << "successfully updated this car!" << endl;
				break;
			}
			switch (count) {
			case 0:
				c.m_id = target;
				break;
			case 1:
				c.m_make = target;
				break;
			case 2:
				c.m_model = target;
				break;
			case 3:
				c.m_year = target;
				break;
			case 4:
				c.m_mileage = target;
				break;
			case 5:
				c.m_available = target;
				break;
			case 6:
				c.min_rentPeriod = target;
				break;
			case 7:
				c.max_rentPeriod = target;
				break;
			default:
				break;
			}
			start = pos + 1;
			count++;
		}
		if (count != 0) v_remains.push_back(c);
	}
	v_remains.push_back(ci);  // add the updated entry to the end.

	ifs.close();
	// clear file
	ofstream ofs;
	ofs.open(this->m_path, ios::trunc);
	ofs.close();
	// put v_remains into file
	Tools tls1;
	tls1.vcartofile(this->m_path, v_remains);

	cout << "successfully updated this car!" << endl;
	system("pause");
	system("cls");
}

void CarManage::removeCar() {
	system("cls");
	cout << "                          ******************************************************************" << endl;
	cout << "                          ***                      remove a car entry                    ***" << endl;
	cout << "                          ******************************************************************" << endl;

	cout << "please input the id of the car you want to remove: " << endl;
	string id;
	cin >> id;
	// check if the id exists in the file.
	Tools tls;
	if (tls.checkid(this->m_path, id) == 1) {
		cout << "this id do not exist in the file!" << endl;
		system("pause");
		return;
	}

	ifstream ifs;
	ifs.open(this->m_path, ios::in);
	vector<Car> v_remains;  // after remove the target line
	Car c;
	string carData;
	while(getline(ifs, carData)) {
		int count = 0;
		int pos = -2;
		int start = 0;
		while(pos!=-1) {
			pos = carData.find(",", start);
			string target = carData.substr(start, pos - start);
			if (target == id && count == 0) {  // not put in v_remains
				cout << "successfully remove this car!" << endl;
				break;
			}
			switch (count) {
			case 0:
				c.m_id = target;
				break;
			case 1:
				c.m_make = target;
				break;
			case 2:
				c.m_model = target;
				break;
			case 3:
				c.m_year = target;
				break;
			case 4:
				c.m_mileage = target;
				break;
			case 5:
				c.m_available = target;
				break;
			case 6:
				c.min_rentPeriod = target;
				break;
			case 7:
				c.max_rentPeriod = target;
				break;
			default:
				break;
			}
			start = pos + 1;
			count++;
		}
		if(count!=0) v_remains.push_back(c);
	}
	ifs.close();
	// clear file
	ofstream ofs;
	ofs.open(this->m_path, ios::trunc);
	ofs.close();
	// put v_remains into file
	Tools tls1;
	tls1.vcartofile(this->m_path, v_remains);
	system("pause");
	system("cls");
}

void CarManage::queryAllCars() {
	system("cls");
	cout << "                          ******************************************************************" << endl;
	cout << "                          ***                        query all cars                      ***" << endl;
	cout << "                          ******************************************************************" << endl;

	vector<string> tempV;
	string carData;
	ifstream ifs;
	ifs.open(this->m_path, ios::in);

	cout << "id, make, model, year, mileage, ifAvailable, min rent period, max rent period, " << endl;
	cout << "*******************************************************************************" << endl;
	while(getline(ifs, carData)) {
		if (carData.empty()) continue;
		cout << carData << endl;
	}
	ifs.close();

	system("pause");
	system("cls");
}
void CarManage::queryCar() {
	system("cls");
	cout << "                          ******************************************************************" << endl;
	cout << "                          ***                          query a car                       ***" << endl;
	cout << "                          ******************************************************************" << endl;

	ifstream ifs;
	ifs.open(this->m_path, ios::out);
	// if the file is empty
	char ch;
	ifs >> ch;
	if(ch == ifs.eof()) {
		cout << "no books in the file!" << endl;
		ifs.close();
		system("pause");
		return;
	}
	ifs.putback(ch);  //go back one char

	cout << "please input the id of the car:" << endl;
	string id;
	cin >> id;
	cout << "********************************************************************" << endl;
	// vector<string> v;
	string lineData;
	while (getline(ifs, lineData)) {
		int pos = -2;
		int start = 0;
		while (pos!=-1) {
			pos = lineData.find(",", start);
			string target = lineData.substr(start, pos - start);
			if (target == id) {
				cout << "id, make, model, year, mileage, ifAvailable, min rent period, max rent period, " << endl;
				cout << "*******************************************************************************" << endl;
				cout << lineData << endl;
				ifs.close();
				system("pause");
				system("cls");
				return;
			}
			start = pos + 1;
		}
	}
	cout << "no car with this id!" << endl;
	ifs.close();
	system("pause");
	system("cls");
}

void CarManage::rentCar() {
	system("cls");
	cout << "                          ******************************************************************" << endl;
	cout << "                          ***                        rent a car                          ***" << endl;
	cout << "                          ******************************************************************" << endl;
	this->queryAllCars();
	
	string id, sdate, period, state;  // id, start date, rental period, handling state
	cout << "please input the id of the car you want to rent: " << endl;
	cin >> id;
	cout << "please input the start date you want to rent: (format: 2022-01-10)" << endl;
	cin >> sdate;
	cout << "please input how many months you want to rent: ( 1=< period <= 9 )" << endl;
	cin >> period;
	state = "wait";
	// add this application into booking.csv
	ofstream ofs;
	ofs.open("booking.csv", ios::out | ios::app);
	ofs << id << "," << this->m_user << "," << sdate << "," << period << "," << state << endl;
	ofs.close();

	cout << "The rental application has been uploaded. It might take one or two days for processing." << endl;
	system("pause");
	system("cls");
}

void CarManage::handleBooking() {
	system("cls");
	cout << "                          ******************************************************************" << endl;
	cout << "                          ***         for admin to handle booking requests               ***" << endl;
	cout << "                          ******************************************************************" << endl;

	ifstream ifs;
	ifs.open("booking.csv", ios::out);
	string lineData;
	vector<string> sv;  // to store updated line data
	Tools tls2;
	tls2.filetomcar(this->m_path, this->m_cars);  // save to CarManage.m_cars
	tls2.mcartofile("testforhandlebooking.csv", this->m_cars);
	// check users' request line by line
	while (getline(ifs, lineData)) {
		int count = 0;
		int pos = -2;
		int start = 0;
		string carid, username, sdate, period, state;
		// save file line data to variants
		while (pos != -1) {
			pos = lineData.find(",", start);
			string target = lineData.substr(start, pos - start);
			switch(count) {
			case(0):
				carid = target;
				break;
			case(1):
				username = target;
				break;
			case(2):
				sdate = target;
				break;
			case(3):
				period = target;
				break;
			case(4):
				state = target;
				break;
			default:
				// cout << "error default" << endl;
				break;
			}
			start = pos + 1;
			count++;
		}
		// cout << "after assign values : " << carid << username << sdate << period << state << endl;
		// query and update the car entry
		ifstream ifs1;
		ifs1.open(this->m_path, ios::out);
		cout << "************************************************************************************************************************" << endl;
		string lineData1;
		int flag = 1;  // if getline continue, or if id was found;
		while (getline(ifs1, lineData1)) {
			int count1 = 0;
			int pos1 = -2;
			int start1 = 0;
			while (pos1 != -1 && flag==1) {
				pos1 = lineData1.find(",", start1);
				string target1 = lineData1.substr(start1, pos1 - start1);
				if (count1==0 && target1 == carid) {  // check if this entry available
					if (this->m_cars[carid].m_available == "0") {  // carid exists, but not avaible
						flag = 2;
						state = "fail";
						cout << username << ", " << carid << " is not available!" << endl;
					}
					else {  // booking success
						flag = 3;
						state = "success";
						this->m_cars[carid].m_available = "0";
						cout << "booking sucess!" << endl;
					}
					break;
				}
				start1 = pos1 + 1;
				count1++;
			}
		}
		if (flag==1) cout << "no car with this car id! " << "application username: " << username << ", " << "application car id: " << carid << endl;
		ifs1.close();

		sv.push_back(carid + "," + username + "," + sdate + "," + period + "," + state + ",");
		cout << carid + "," + username + "," + sdate + "," + period + "," + state + "," << endl;
	}
	ifs.close();

	// rewrite file booking.csv from vector<string> sv
	ofstream ofs;
	ofs.open("booking.csv", ios::out);
	for (vector<string>::iterator it = sv.begin(); it != sv.end(); it++) {
		ofs << *it << endl;
	}
	ofs.close();
	sv.clear();

	// rewrite car file from map<string, Car> m_cars
	tls2.mcartofile(this->m_path, this->m_cars);
	system("pause");
	system("cls");
}