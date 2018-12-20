#include "CFLP.hpp"

int main() {
    int facilityNum, customerNum;
    vector<facility> facilities;
    vector<customer> customers;
    //获取数据
    io(facilityNum, customerNum, facilities, customers);
    /* cout << facilityNum << " " << customerNum << endl;
    for (int i = 0; i < facilityNum; ++i) {
        cout << facilities[i].capacity << " " << facilities[i].openCost << endl;
    }
    for (int i = 0; i < customerNum; ++i) {
        cout << customers[i].demand << " ";
        if (i % 10 == 9) cout << endl;
    }
    for (int i = 0; i < facilityNum; ++i) {
        for (int j = 0; j < customerNum; ++j) {
            cout << customers[j].assigncost[i] << " ";
            if (j % 10 == 9) cout << endl;
        }
    } */
    
}