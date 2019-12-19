#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
using namespace std;

struct splay
{
    int key;
    string value;
    splay* lchild;
    splay* rchild;
};

class SplayTree
{
public:
    SplayTree()
    {
    }

    // RR(Y rotates to the right)
    splay* RR_Rotate(splay* k2)
    {
        splay* k1 = k2->lchild;
        k2->lchild = k1->rchild;
        k1->rchild = k2;
        return k1;
    }

    // LL(Y rotates to the left)
    splay* LL_Rotate(splay* k2)
    {
        splay* k1 = k2->rchild;
        k2->rchild = k1->lchild;
        k1->lchild = k2;
        return k1;
    }

    // An implementation of top-down splay tree
    splay* Splay(int key, splay* root)
    {
        if (!root)
            return NULL;
        splay header;
        /* header.rchild points to L tree;
        header.lchild points to R Tree */
        header.lchild = header.rchild = NULL;
        splay* LeftTreeMax = &header;
        splay* RightTreeMin = &header;
        while (1)
        {
            if (key < root->key)
            {
                if (!root->lchild)
                    break;
                if (key < root->lchild->key)
                {
                    root = RR_Rotate(root);
                    // only zig-zig mode need to rotate once,
                    if (!root->lchild)
                        break;
                }
                /* Link to R Tree */
                RightTreeMin->lchild = root;
                RightTreeMin = RightTreeMin->lchild;
                root = root->lchild;
                RightTreeMin->lchild = NULL;
            }
            else if (key > root->key)
            {
                if (!root->rchild)
                    break;
                if (key > root->rchild->key)
                {
                    root = LL_Rotate(root);
                    // only zag-zag mode need to rotate once,
                    if (!root->rchild)
                        break;
                }
                /* Link to L Tree */
                LeftTreeMax->rchild = root;
                LeftTreeMax = LeftTreeMax->rchild;
                root = root->rchild;
                LeftTreeMax->rchild = NULL;
            }
            else
                break;
        }
        /* assemble L Tree, Middle Tree and R tree */
        LeftTreeMax->rchild = root->lchild;
        RightTreeMin->lchild = root->rchild;
        root->lchild = header.rchild;
        root->rchild = header.lchild;
        return root;
    }

    splay* New_Node(int key, string value)
    {
        splay* p_node = new splay;
        if (!p_node)
        {
            fprintf(stderr, "Out of memory!\n");
            exit(1);
        }
        p_node->key = key;
        p_node->value = value;
        p_node->lchild = p_node->rchild = NULL;
        return p_node;
    }

    splay* Insert(int key, string value, splay* root)
    {
        static splay* p_node = NULL;
        if (!p_node)
            p_node = New_Node(key, value);
        else
            p_node->key = key;
        if (!root)
        {
            root = p_node;
            p_node = NULL;
            return root;
        }
        root = Splay(key, root);
        /* This is BST that, all keys <= root->key is in root->lchild, all keys >
        root->key is in root->rchild. */
        if (key < root->key)
        {
            p_node->lchild = root->lchild;
            p_node->rchild = root;
            root->lchild = NULL;
            root = p_node;
        }
        else if (key > root->key)
        {
            p_node->rchild = root->rchild;
            p_node->lchild = root;
            root->rchild = NULL;
            root = p_node;
        }
        else
            return root;
        p_node = NULL;
        return root;
    }

    splay* Delete(int key, splay* root)
    {
        splay* temp;
        if (!root)
            return NULL;
        root = Splay(key, root);
        if (key != root->key)
            return root;
        else
        {
            if (!root->lchild)
            {
                temp = root;
                root = root->rchild;
            }
            else
            {
                temp = root;
                /*Note: Since key == root->key,
                so after Splay(key, root->lchild),
                the tree we get will have no right child tree.*/
                root = Splay(key, root->lchild);
                root->rchild = temp->rchild;
            }
            free(temp);
            return root;
        }
    }

    splay* Search(int key, splay* root)
    {
        return Splay(key, root);
    }

    void InOrder(splay* root)
    {
        if (root)
        {
            InOrder(root->lchild);
            cout<< "key: " <<root->key;
            if(root->lchild)
                cout<< " | left child: "<< root->lchild->key;
            if(root->rchild)
                cout << " | right child: " << root->rchild->key;
            cout<< "\n";
            InOrder(root->rchild);
        }
    }
};

/*
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

    SplayTree st;
    splay *root;
    root = NULL;
    for (int i=0;i<namelist.size();i++){
        root=st.Insert(IPlist[i],namelist[i],root);
    }
    //st.InOrder(root);




        HashMap<string, int> percentdictionary(975);
    for (int j = 0; j <IPlist.size() ; ++j) {
        percentdictionary.put(namelist[j],percentList[j]);
        // int x = percentdictionary.getMapValue(namelist[j]);
        // cout << x <<endl;
    }

    //populate insert vector
    std::vector<int> inserts;
    for (int k = 0; k <percentList.size() ; ++k) {
        for (int j = 0; j <percentList[k] ; j++){
            inserts.push_back(IPlist[k]);
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
        splay* x = st.Search(inserts[i],root);
        string domain = x->value;
    }
    //end time
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";



    return 0;

}

*/

/*int main() {
    SplayTree st;
    splay *root;
    root = NULL;
    srand(time(NULL));
    auto start = std::chrono::high_resolution_clock::now();
    const int length = 1000000;
    int count = 1000;
    for (int i = 0; i < length; i++) {
        // int num =  (rand() % 1000)+1;
        //root = st.Insert(num, root);
        if (i % 1000 == 0) {
            count = 1000;
        }
        count -= 1;
        root = st.Insert(count, root);
        cout << count << " ";
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "Elapsed time: " << elapsed.count() << " s\n";
        return 0;
    }
}*/