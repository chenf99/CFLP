#include "CFLP.hpp"

int main() {
    for (int i = 1; i <= 71; ++i) {
        int facilityNum, customerNum;
        vector<facility> facilities;
        vector<customer> customers;
        //获取数据
        readData(i, facilityNum, customerNum, facilities, customers);
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
        bool isGreedy = false;//使用贪心算法还是SA算法
        vector<bool> open(facilityNum, false);
        vector<int> assign(customerNum, -1);
        clock_t start = clock();
        int totalcost = isGreedy ? greedy(open, assign, facilities, customers) : SA(i, open, assign, facilities, customers);
        clock_t end = clock();
        //输出结果
        cout << "P" + std::to_string(i) + " result:" << endl;
        cout << "Total cost: " << totalcost << endl;
        cout << "Open status: " << endl;
        for (int i = 0; i < facilityNum; ++i) cout << (int)open[i] << " ";
        cout << "\nAssignment of customer:" << endl;
        for (int i = 0; i < customerNum; ++i) cout << assign[i] << " ";
        cout <<"\nRunning Time : "<< (end - start) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms\n" << endl;

        //记录历史最优解
        int previousCost = readPrevResult(i, isGreedy);
        if (previousCost > totalcost) {
            string writeStr = std::to_string(totalcost) + "\n";
            for (int i = 0; i < facilityNum; ++i) writeStr += std::to_string((int)open[i]) + " ";
            writeStr += "\n";
            for (int i = 0; i < customerNum; ++i) writeStr += std::to_string(assign[i]) + " ";
            writeNewResult(i, writeStr, isGreedy);
        }
    }
    return 0;
}