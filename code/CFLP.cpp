#include "CFLP.hpp"

int main() {
    for (int i = 1; i <= 71; ++i) {
        int facilityNum, customerNum;
        vector<facility> facilities;
        vector<customer> customers;
        //获取数据
        io(i, facilityNum, customerNum, facilities, customers);
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
        vector<bool> open(facilityNum, false);
        vector<int> assign(customerNum, -1);
        clock_t start = clock();
        int totalcost = greedy(open, assign, facilities, customers);
        clock_t end = clock();
        cout << "P" + std::to_string(i) + " result:" << endl;
        cout << "Total cost: " << totalcost << endl;
        cout << "Open status: " << endl;
        for (int i = 0; i < facilityNum; ++i) cout << (int)open[i] << " ";
        cout << "\nAssignment of customer:" << endl;
        for (int i = 0; i < customerNum; ++i) cout << assign[i] << " ";
        cout <<"\nRunning Time : "<< (end - start) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms\n" << endl;
    }
    return 0;
}