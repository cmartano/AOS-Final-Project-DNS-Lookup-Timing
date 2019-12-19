#include<iostream>
#include <fstream>

using namespace std;

#define __TEST__

//////////////////////////////////////////////////////////////////////////
//  1  结点定义			_rbTreeNode
//////////////////////////////////////////////////////////////////////////

template <class T>
class rbtree;

template <class T>
struct _rbTreeNode{
    friend class rbtree<T>;
    T getkey(){
        return key;
    }
    string getvalue(){
        return value;
}
private:
    T key;
    string value;
    _rbTreeNode<T> *left;
    _rbTreeNode<T> *right;
    _rbTreeNode<T> *p;
    bool color;			// true == red  &&  false == black
};


//////////////////////////////////////////////////////////////////////////
//  2  红黑树类声明		rbtree
//////////////////////////////////////////////////////////////////////////


template <class T>
class rbtree{

public:
    rbtree()
            :nil( new _rbTreeNode<T> ), root( nil ) { nil->left = 0; nil->p = 0; nil->right = 0; nil->color = false; }
    void insert( T key, string value );
    _rbTreeNode<T> * search( T key );
    void erase( T key );

#ifdef __TEST__
    void display();
#endif

private:

#ifdef __TEST__
    void _display( _rbTreeNode<T> * );
#endif


    void leftRotate(  _rbTreeNode<T> * );
    void rightRotate(  _rbTreeNode<T> * );

    void rbDelete(  _rbTreeNode<T> * );
    void rbDeleteFixup(  _rbTreeNode<T> * );

    void rbInsertFixup( _rbTreeNode<T> * );

    _rbTreeNode<T>* treeSuccessor(  _rbTreeNode<T> * );

    _rbTreeNode<T> *nil;			//空结点
    _rbTreeNode<T> *root;

};


//////////////////////////////////////////////////////////////////////////
//  3  红黑树类成员定义
//////////////////////////////////////////////////////////////////////////


template <class T>
void rbtree<T>::insert( T key, string value ){
    _rbTreeNode<T>* t = new _rbTreeNode<T>;
    t->key = key;
    t->value= value;
    _rbTreeNode<T>* x = root;
    _rbTreeNode<T>* y = nil;
    while( x != nil ){
        y = x;
        if( key < x->key )
            x = x->left;
        else
            x = x->right;
    }
    t->p = y;
    if( y == nil )
        root = t;
    else{
        if ( t->key < y->key )
            y->left = t;
        else
            y->right = t;
    }
    t->left = nil;
    t->right = nil;
    t->color = true;
    rbInsertFixup( t );
}

template <class T>
_rbTreeNode<T> * rbtree<T>::search( T key ){
    _rbTreeNode<T> * x = root;
    while( x != nil && key != x->key ){
        if( key < x->key )
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

template <class T>
void rbtree<T>::erase( T key ){
    _rbTreeNode<T> * x = search( key );
    if( x != nil )
        rbDelete( x );
}

template <class T>
_rbTreeNode<T> * rbtree<T>::treeSuccessor( _rbTreeNode<T> *x ){
    if( x->right != nil ){
        while( x->left != nil )
            x = x->left;
        return x;
    }
    _rbTreeNode<T> * y = x->p;
    while( y != nil && x == y->right ){
        x = y;
        y = y->p;
    }
    return y;
}

template <class T>
void rbtree<T>::leftRotate( _rbTreeNode<T> *x ){		// x->right != nil
    _rbTreeNode<T> * y = x->right;
    if( x->p == nil )
        root = y;
    else{
        if( x == x->p->left )
            x->p->left = y;
        else
            x->p->right = y;
    }
    y->p = x->p;
    x->right = y->left;
    y->left->p = x;
    y->left = x;
    x->p = y;
}

template <class T>
void rbtree<T>::rightRotate( _rbTreeNode<T> *x ){
    _rbTreeNode<T> * y = x->left;
    if( x->p == nil )
        root = y;
    else{
        if( x->p->left == x )
            x->p->left = y;
        else
            x->p->right = y;
    }
    y->p = x->p;
    x->left = y->right;
    y->right->p = x;
    y->right = x;
    x->p = y;
}


template <class T>
void rbtree<T>::rbInsertFixup( _rbTreeNode<T> *z ){
    while( z->p->color  == true ){
        if( z->p == z->p->p->left ){
            _rbTreeNode<T> * y = z->p->p->right;
            if( y->color == true ){
                z->p->color = false;
                y->color = false;
                z->p->p->color = true;
                z = z->p->p;
            }
            else{
                if( z == z->p->right ){
                    z = z->p;
                    leftRotate( z );
                }//
                z->p->color = false;
                z->p->p->color = true;
                z->p->right->color = false;
                rightRotate( z->p->p );
            }
        }
        else{
            _rbTreeNode<T> * y = z->p->p->left;
            if( y->color == true ){
                z->p->color = false;
                y->color = false;
                z->p->p->color = true;
                z = z->p->p;
            }
            else{
                if( z == z->p->left ){
                    z = z->p;
                    rightRotate( z );
                }
                z->p->color = false;
                z->p->p->color = true;
                z->p->left->color = false;
                leftRotate( z->p->p );
            }
        }
    }
    root->color = false;
}


template <class T>
void rbtree<T>::rbDelete( _rbTreeNode<T> *z ){
    _rbTreeNode<T> * x = nil;
    _rbTreeNode<T> * y = nil;
    if( z->left == nil || z->right == nil )
        y = z;
    else
        y = treeSuccessor( z );
    if( y->left != nil )
        x = y->left;
    else
        x = y->right;
    x->p = y->p;
    if( y->p == nil )
        root = x;
    else{
        if( y == y->p->left )
            y->p->left = x;
        else
            y->p->right = x;
    }
    if( y != z )
        z->key = y->key;
    if( y->color == false )
        rbDeleteFixup( x );
    delete y;
}

template <class T>
void rbtree<T>::rbDeleteFixup(_rbTreeNode<T> * x){
    while( x != root && x->color == false ){
        _rbTreeNode<T> * w = 0;
        if( x->p->left == x ){
            w = x->p->right;
            if( w->color == true ){
                w->color = false;
                x->p->color = true;
                leftRotate( x->p );
                w = x->p->right;
            }
            if( w->left->color == false && w->right->color == false ){
                w->color = true;
                x = x->p;
            }
            else{
                if( w->right->color == false ){
                    w->left->color = false;
                    w->color = true;
                    rightRotate( w );
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = false;
                w->right->color = false;
                leftRotate( x->p );
                x = root;
            }
        }
        else{
            w = x->p->left;
            if( w->color == true ){
                w->color = false;
                x->p->color = true;
                rightRotate( x->p );
                w = x->p->left;
            }
            if( w->right->color == false && w->left->color == false ){
                w->color = true;
                x = x->p;
            }
            else{
                if( w->left->color == false ){
                    w->right->color = false;
                    w->color = true;
                    leftRotate( w );
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = false;
                w->left->color = false;
                rightRotate( x->p );
                x = root;
            }
        }
    }
    x->color = false;
}




#ifdef __TEST__

template <class T>
void rbtree<T>::display(){
    if( root != nil )
        _display( root );
    else
        cout << "Tree is empty! " << endl;
}

template <class T>
void rbtree<T>::_display( _rbTreeNode<T> * x ){
    if( x->left != nil )
        _display( x->left );
    if( x != nil ){
        cout << x->key << ' ';
        if( x->color == true )
            cout << "RED ";
        else
            cout << "BLACK ";
        if( x->p != nil )
            cout << x->p->key << ' ';
        else
            cout << "NULL ";
        if( x->left != nil )
            cout << x->left->key << ' ';
        else
            cout << "NULL ";
        if( x->right != nil )
            cout << x->right->key << ' ';
        else
            cout << "NULL ";
    }
    cout << endl;
    if( x->right != nil )
        _display( x->right );
}

#endif


//////////////////////////////////////////////////////////////////////////
//  4  测试程序			main()
//////////////////////////////////////////////////////////////////////////



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

    rbtree<int> rbt;
    for (int i=0;i<namelist.size();i++){
        rbt.insert(IPlist[i],namelist[i]);
    }



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
        _rbTreeNode<int> * x = rbt.search(inserts[i]);
        string domain = x->getvalue();
    }
    //end time
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";



    return 0;

}



//const int N = 1000000;

/*int main(){
    rbtree<int> test;
    srand(time(NULL));
    auto start = std::chrono::high_resolution_clock::now();
    int count = 1000;
    for ( int i = 0; i != N; ++i ){
        if (i % 1000 == 0) {
            count = 1000;
        }
        count -= 1;
        //int num =  (rand() % 1000)+1;
        test.insert(count);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    return 0;
}*/



