#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
using namespace std;
#include "tools.h"
#include "car.h"

// constructor
Tools::Tools() {

}

int Tools::checkid(string path, string id) {  // to check if the input id conflict with ids in the existing file.
	ifstream ifs;
	ifs.open(path, ios::out);
	if (!ifs.is_open()) {
		cout << "error occurs while opening the file!" << endl;
		system("pause");
		ifs.close();
		return 0;
	}
	else {
		string fileData;
		while (ifs >> fileData)
		{
			int pos = -1;
			int start = 0;
			while (1)
			{

				pos = fileData.find(",", start);
				if(pos == -1) {
					break;
				}
				else
				{
					string target = fileData.substr(start, pos - start);
					if(target == id) {
						ifs.close();
						return 0;
					}
				}
				start = pos + 1;
			}
		}

	}
	ifs.close();
	return 1;
}

void Tools::vcartofile(string path, vector<Car>& v) {
	ofstream ofs;
	ofs.open(path, ios::out);
	for (vector<Car>::iterator it = v.begin(); it != v.end(); it++) {
		ofs << it->m_id << "," << it->m_make << "," << it->m_model << "," << it->m_year << "," << it->m_mileage << "," << it->m_available << "," << it->min_rentPeriod << "," << it->max_rentPeriod << "," << endl;
	}
	ofs.close();
	v.clear();
}

void Tools::mcartofile(string path, map<string, Car>& c) {
	ofstream ofs;
	ofs.open(path, ios::out);
	for (map<string, Car>::iterator it = c.begin(); it != c.end(); it++) {
		ofs << it->second.m_id << "," << it->second.m_make << "," << it->second.m_model << "," << it->second.m_year << "," << it->second.m_mileage << "," << it->second.m_available << "," << it->second.min_rentPeriod << "," << it->second.max_rentPeriod << "," << endl;
	}
	ofs.close();
	// c.clear();
}

void Tools::filetomcar(string path, map<string, Car>& m) {
	ifstream ifs;
	ifs.open(path, ios::in);
	Car c;
	string carData;
	while (getline(ifs, carData)) {
		int count = 0;
		int pos = -2;
		int start = 0;
		while (pos != -1) {
			pos = carData.find(",", start);
			string target = carData.substr(start, pos - start);
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
		m.insert(pair<string, Car>{c.m_id, c});  // insert this line data to map
	}
	ifs.close();
}