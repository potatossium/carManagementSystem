#pragma once
#include <iostream>
using namespace std;
#include "car.h"

class Tools {
public:
	Tools();  // constructor
	int checkid(string path, string id);  // to check if there would be same id.
	void vcartofile(string path, vector<Car>& v);  // to put a vector of cars into csv file path line by line.
	void mcartofile(string path, map<string, Car>& c);
	void filetomcar(string path, map<string, Car>& m);
};