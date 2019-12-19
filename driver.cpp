//
// Created by Christian Martano on 12/11/19.
//
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
/*
int main() {
    std::fstream inFile;
    std::string IP;
    std::string name;
    std::string percent;
    std::vector<int> IPlist;
    std::vector<std::string> namelist;
    std::vector<double> percentList;
    int count = 0;
    int placeval0;
    double placeval1;
    inFile.open("/Users/christianmartano/CLionProjects/AOS_Project_2/aos_project_2_data.csv");


    if (inFile.is_open()) {
        std::cout << "File has been opened" << std::endl;
    } else {
        std::cout << "NO FILE HAS BEEN OPENED" << std::endl;
    }


    while (getline(inFile, IP, ',')) {
        getline(inFile, name, ',');
        getline(inFile, percent);
        if (percent[percent.size() - 1] == '\r') {
            percent.resize(percent.size() - 1);
        }
        std::stringstream geek0(IP);
        std::stringstream geek1(percent);
        geek0 >> placeval0;
        geek1 >> placeval1;
        IPlist.push_back(placeval0);
        namelist.push_back(name);
        percentList.push_back(placeval1);
        count++;
    }
    
    for (int i=0; i<percentList.size();i++){
        percentList[i]= ceil(percentList[i]*100);
        std::cout << percentList[i]<< std::endl;

    }

    
    inFile.close();
    return 0;

}
*/
