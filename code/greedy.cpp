#include "CFLP.hpp"
/*
* 贪心算法
* 主要思想：
* 每次进行一个分配操作，给一个customer分配一个facility
* 选取的标准：
* 1.首先facility容量要满足,customer未分配
* 2.性价比：(opencost + assigncost) / demand最小
* 已打开的facility的opencost为0
*/

int greedy(vector<bool>& open, vector<int>& assign, vector<facility>& facilities, vector<customer>& customers) {
    int totalCost = 0;
    while (true) {
        int performance = INT_MAX;
        int currAssignCost = INT_MAX;
        int select_i = -1, select_j = -1;
        for (int i = 0; i < customers.size(); ++i) {
            if (assign[i] != -1) continue;      //该customer已被分配过
            for (int j = 0; j < facilities.size(); ++j) {
                //更换当前最优操作
                if ((customers[i].assigncost[j] + facilities[j].openCost / customers[i].demand) < performance && 
                    facilities[j].capacity >= customers[i].demand) {
                    select_i = i;
                    select_j = j;
                    performance = customers[i].assigncost[j] + facilities[j].openCost / customers[i].demand;
                    currAssignCost = customers[i].assigncost[j] + facilities[j].openCost;
                }
            }
        }
        if (currAssignCost == INT_MAX || select_i == -1 || select_j == -1) break;//分配完成
        totalCost += currAssignCost;
        facilities[select_j].openCost = 0;
        facilities[select_j].capacity -= customers[select_i].demand;
        open[select_j] = true;
        assign[select_i] = select_j;
    }
    return totalCost;
}