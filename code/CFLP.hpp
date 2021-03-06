#ifndef CFLP_HPP
#define CFLP_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <string>
using std::cout;
using std::endl;
using std::fstream;
using std::vector;
using std::string;

struct facility {
    int capacity;
    int leftCapa;//剩余容量
    int openCost;
    facility(int capacity, int openCost) {
        this->capacity = capacity;
        this->openCost = openCost;
        this->leftCapa = capacity;
    }
};

struct customer {
    int demand;
    vector<int> assigncost;
    customer(int demand) {
        this->demand = demand;
    }
};

void readData(int i, int& facilityNum, int& costomerNum, vector<facility>& facilities, vector<customer>& costomers);

int readPrevResult(int i, bool greedy);

void writeNewResult(int i, string result, bool greedy);

int greedy(vector<bool>& open, vector<int>& assign, vector<facility>& facilities, vector<customer>& customers);

int SA(int i, vector<bool>& open, vector<int>& assign, vector<facility>& facilities, vector<customer>& customers);

#endif