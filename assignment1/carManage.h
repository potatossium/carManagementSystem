#pragma once

#include <map>
#include <vector>
using namespace std;
#include "car.h"

class CarManage {
public:
	CarManage();
	string m_user;
	vector<Car> m_vcars;
	string m_path;  // file path of cars' data
	map<string, Car> m_cars;  // each item is <id, Car>
	void addCar();
	void updateCar();
	void removeCar();
	void queryAllCars();
	void queryCar();
	void rentCar();
	void handleBooking();
};