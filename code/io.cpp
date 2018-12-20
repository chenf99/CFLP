#include "CFLP.hpp"
using namespace std;

void io(int i, int& facilityNum, int& customerNum, vector<facility>& facilities, vector<customer>& customers) {
    string fileName = "Instances/p" + std::to_string(i);
    fstream infile(fileName, ios::in);
    if (!infile) {
        cout << "open file error!" << endl;
        exit(1);
    }
    infile >> facilityNum >> customerNum;
    //读取facility数据
    int count = facilityNum;
    while (count--) {
        int capacity, opencost;
        infile >> capacity >> opencost;
        facilities.push_back(facility(capacity, opencost));
    }
    //读取顾客demand数据
    count = customerNum;
    while (count--) {
        float demand;
        infile >> demand;
        customers.push_back(customer((int)demand));
    }
    //读取顾客assigncost数据
    for (int i = 0; i < facilityNum; ++i) {
        for (int j = 0; j < customerNum; ++j) {
            float assigncost;
            infile >> assigncost;
            customers[j].assigncost.push_back((int)assigncost);
        }
    }
    infile.close();
}