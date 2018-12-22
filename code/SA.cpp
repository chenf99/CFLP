#include "CFLP.hpp"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cmath>
/*
* 模拟退火算法
* 主要思想:
* 两种策略：
*   1.随机选择两个customer交换分配到的facility
*   2.随机选择一个customer,分配到别的facility
*/

bool isValidSolution(const vector<bool>&, const vector<int>&, const vector<facility>&);

void randomInitSolution(vector<bool>&, vector<int>&, vector<facility>&, const vector<customer>&);

int SA(int i, vector<bool>& open, vector<int>& assign, vector<facility>& facilities, vector<customer>& customers) {
    double T = 1000;        //初温
    double T_end = 0.0001;  //末温
    int count = 1000;       //每个温度迭代次数

    //随机生成初始解
    randomInitSolution(open, assign, facilities, customers);
    int opencost = 0;
    for (int i = 0; i < facilities.size(); ++i) {
        if (open[i] == true) opencost += facilities[i].openCost;
    }
    vector<int> currAssign(assign);
    vector<bool> currOpen(open);
    vector<facility> currFacilities(facilities);
    int currCost = 0;
    for (int i = 0; i < customers.size(); ++i) currCost += customers[i].assigncost[currAssign[i]];
    for (int i = 0; i < open.size(); ++i) {
        if (open[i] == true) currCost += currFacilities[i].openCost;
    }
    while (T > T_end) {
        count = 100;
        while (count--) {
            //生成新解
            int select = rand() % 2;
            if (select == 1) {
                //随机交换assign的facility，不会改变curropen
                vector<int> tmpAssign(currAssign);
                vector<facility> tmpFacilities(currFacilities);
                int customer1 = rand() % customers.size();
                int customer2 = rand() % customers.size();
                if (customer1 != customer2) {
                    tmpFacilities[tmpAssign[customer1]].leftCapa += customers[customer1].demand;
                    tmpFacilities[tmpAssign[customer2]].leftCapa += customers[customer2].demand;
                    int tmp = tmpAssign[customer1];
                    tmpAssign[customer1] = tmpAssign[customer2];
                    tmpAssign[customer2] = tmp;
                    tmpFacilities[tmpAssign[customer1]].leftCapa -= customers[customer1].demand;
                    tmpFacilities[tmpAssign[customer2]].leftCapa -= customers[customer2].demand;
                }
                if (isValidSolution(open, tmpAssign, tmpFacilities)) {
                    int cost = 0;
                    for (int i = 0; i < customers.size(); ++i) {
                        cost += customers[i].assigncost[tmpAssign[i]];
                    }
                    for (int i = 0; i < open.size(); ++i) {
                        if (open[i] == true) cost += tmpFacilities[i].openCost;
                    }
                    int dE = cost - currCost;
                    if (dE < 0) {       //直接接受好的新解
                        currCost = cost;
                        currAssign = tmpAssign;
                        currFacilities = tmpFacilities;
                    }
                    else if (dE > 0) {
                        //以概率接受差的新解
                        double rd = rand() / (RAND_MAX + 1.0);//0到1的随机数
                        if (exp(-dE / T) > rd) {
                            currCost = cost;
                            currAssign = tmpAssign;
                            currFacilities = tmpFacilities;
                        }
                    }
                }
            }
            else {
                //随机让一个customer分配到别的facility
                int customer_select = rand() % customers.size();
                int facility_select = rand() % facilities.size();
                vector<int> tmpAssign(currAssign);
                vector<facility> tmpFacilities(currFacilities);
                vector<bool> tmpOpen(currOpen);
                tmpFacilities[tmpAssign[customer_select]].leftCapa += customers[customer_select].demand;
                //关闭facility
                if (tmpFacilities[tmpAssign[customer_select]].leftCapa == tmpFacilities[tmpAssign[customer_select]].capacity) {
                    tmpOpen[tmpAssign[customer_select]] = false;
                }
                tmpAssign[customer_select] = facility_select;
                if (tmpFacilities[facility_select].leftCapa > customers[customer_select].demand) {
                    tmpFacilities[facility_select].leftCapa -= customers[customer_select].demand;
                    tmpOpen[facility_select] = true;
                    int cost = 0;
                    for (int i = 0; i < customers.size(); ++i) {
                        cost += customers[i].assigncost[tmpAssign[i]];
                    }
                    for (int i = 0; i < open.size(); ++i) {
                        if (open[i] == true) cost += tmpFacilities[i].openCost;
                    }
                    int dE = cost - currCost;
                    if (dE < 0) {//直接接受好的新解
                        currCost = cost;
                        currAssign = tmpAssign;
                        currFacilities = tmpFacilities;
                        currOpen = tmpOpen;
                    }
                    else if (dE > 0) {
                        //以概率接受差的新解
                        double rd = rand() / (RAND_MAX + 1.0);//0到1的随机数
                        if (exp(-dE / T) > rd) {
                            currCost = cost;
                            currAssign = tmpAssign;
                            currFacilities = tmpFacilities;
                            currOpen = tmpOpen;
                        }
                    }
                }
            }
        }
        T = 0.99 * T;//降温
    }
    assign = currAssign;
    open = currOpen;
    facilities = currFacilities;
    return currCost;
}

bool isValidSolution(const vector<bool>& open, const vector<int>& assign, const vector<facility>& facilities) {
    for (int i = 0; i < assign.size(); ++i) {
        if (open[assign[i]] == true) {
            if (facilities[assign[i]].leftCapa < 0) return false;
        }
        else return false;
    }
    return true;
}

void randomInitSolution(vector<bool>& open, vector<int>& assign, vector<facility>& facilities, const vector<customer>& customers) {
    srand(time(NULL));
    while (true) {
        vector<facility> tmpFacilities(facilities);
        vector<bool> tmpOpen(open);
        for (int i = 0; i < assign.size(); ++i) {
            //生成0到open.size() - 1之间的随机数
            assign[i] = rand() % open.size();
            tmpOpen[assign[i]] = true;
            tmpFacilities[assign[i]].leftCapa -= customers[i].demand;
        }
        if (isValidSolution(tmpOpen, assign, tmpFacilities)) {
            open = tmpOpen;
            facilities = tmpFacilities;
            break;
        }
    }
}