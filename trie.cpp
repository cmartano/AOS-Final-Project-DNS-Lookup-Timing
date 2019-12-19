//
// Created by Christian Martano on 11/19/19.
//
// C++ implementation of search and insert
// operations on Trie
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    int value;

    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key, int value)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
    pCrawl->value=value;
}

// Returns true if key presents in trie, else
// false
int search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl->value);
}


#include <fstream>
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

    struct TrieNode *root = getNode();
    for (int i=0;i<namelist.size();i++){
        insert(root,namelist[i],IPlist[i]);
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
    for( int x; x<inserts.size();x++) {
        // cout<< (inserts[x] + '\n');
    }


    //prints data set size
    cout << inserts.size() << endl;


    //start time
    srand(time(NULL));
    auto start = std::chrono::high_resolution_clock::now();
    for (int i; i<inserts.size(); i++){
        int x = search(root,inserts[i]);

    }
    //end time
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";



    return 0;

}



// Driver
/*int main()
{
    // Input keys (use only 'a' through 'z'
    // and lower case)
    string keys[] = {"the", "a", "there",
                     "answer", "any", "by",
                     "bye", "their", "these" };
    int n = sizeof(keys)/sizeof(keys[0]);

    struct TrieNode *root = getNode();

    // Construct trie
    for (int i = 0; i < n; i++)
        insert(root, keys[i]);

    // Search for different keys
    if (search(root, "the")) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    search(root, "these")? cout << "Yes\n" :
    cout << "No\n";
    return 0;
}
 */


