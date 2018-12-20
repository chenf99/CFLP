#ifndef CFLP_HPP
#define CFLP_HPP

#include <iostream>
#include <fstream>
#include <vector>
using std::cout;
using std::endl;
using std::fstream;
using std::vector;

struct facility {
    bool isOpen;
    int capacity;
    int openCost;
    facility(int capacity, int openCost) {
        this->capacity = capacity;
        this->openCost = openCost;
    }
};

struct customer {
    int demand;
    vector<int> assigncost;
    customer(int demand) {
        this->demand = demand;
    }
};

void io(int& facilityNum, int& costomerNum, vector<facility>& facilities, vector<customer>& costomers);

#endif