//
// Created by Christian Martano on 12/9/19.
//
/*#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include "HashMap.h"
#include <chrono>

int main() {
    //initialize variables
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

    //file check
    if (inFile.is_open()) {
        std::cout << "File has been opened" << std::endl;
    } else {
        std::cout << "NO FILE HAS BEEN OPENED" << std::endl;
    }

    //read data from file
    while (getline(inFile, IP, ',')) {
        getline(inFile, name, ',');
        getline(inFile, percent);
        //get rid of the /r at the end of lines
        if (percent[percent.size() - 1] == '\r') {
            percent.resize(percent.size() - 1);
        }
        std::stringstream geek0(IP);
        std::stringstream geek1(percent);
        geek0 >> placeval0;
        geek1 >> placeval1;
        //populate vectors
        IPlist.push_back(placeval0);
        namelist.push_back(name);
        percentList.push_back(placeval1);
        count++;
    }

    //update percent values to the number of times it will appear in data, rounded to nearest whole number
    //multiply by 100 for approx 10K
    //multiply by 500 for approx 50k
    //multiply by 1000 for approx 100k
    //...
    for (int i = 0; i < percentList.size(); i++) {
        percentList[i] = round(percentList[i] * 10000);
        //std::cout << percentList[i] << std::endl;
    }

    inFile.close();


    //populating IPhashmap
    HashMap<string, int> IPdictionary(975);
    for (int j = 0; j <IPlist.size() ; ++j) {
        IPdictionary.put(namelist[j],IPlist[j]);
       // int x = IPdictionary.getMapValue(namelist[j]);
       // cout << x <<endl;
    }

    HashMap<string, int> percentdictionary(975);
    for (int j = 0; j <IPlist.size() ; ++j) {
        percentdictionary.put(namelist[j],percentList[j]);
       // int x = percentdictionary.getMapValue(namelist[j]);
       // cout << x <<endl;
    }

    //populate insert vector
    std::vector<string> inserts;
    for (int k = 0; k <percentList.size() ; ++k) {
        for (int j = 0; j <percentList[k] ; j++){
            inserts.push_back(namelist[k]);
            //cout <<inserts[j] << j << endl;
            //cout << ("Name: "+ namelist[k] + "\n");
            //cout << ("J: ") << j << "\n";
        }
        //cout << ("K: ") << k << "\n";
    }

    //check insert list
    /*for( int x; x<inserts.size();x++)
        cout<< (inserts[x] + '\n');


    //prints data set size
    cout << inserts.size() << endl;

    //start time
    srand(time(NULL));
    auto start = std::chrono::high_resolution_clock::now();
    for (int i; i<inserts.size(); i++){
        int num =  (rand() % 100028)+1;
        int x = IPdictionary.getMapValue(inserts[i]);
    }
    //end time
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";


    return 0;

} */





