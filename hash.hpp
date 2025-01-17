#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int strToAscii(string str)
{
    int tempKey=0;
    char ch;
    int a = str.length();

    for (int i = 0; i < a ; i++)
    {
        ch = str[i];
        tempKey += ch;
    }
    ch=tempKey;
    return tempKey;
}

struct hashVariable
{
    int count = 0;
    string var;
    int key = 0;
};

struct Node{
    hashVariable info;
    Node * link;
};

 bool compare(hashVariable item1,hashVariable item2){
        return (item1.count < item2.count);
    }

class hashTable
{
private:
   
public:
    
    int hash(int key) const {
        return key % tableSize;
    }

    int tableSize;
    Node** Arr;
    hashTable(int size){ //constructor

        tableSize = size;
        Arr = new Node*[tableSize];

        for (int i = 0; i < tableSize; ++i)
        {
            Arr[i] = nullptr;
        }
    }

    hashTable(){ //default constructor
        tableSize=31;
        Arr = new Node*[tableSize];

        for (int i = 0; i < tableSize; ++i)
        {
            Arr[i] = nullptr;
        }
    }

    void hashInsert(string data){
        int key = strToAscii(data);
        int index = hash(key);

        Node* newNode = new Node;
        newNode->info.var = data;
        newNode->info.key = index;
        newNode->link = nullptr;

        if (Arr[index] == nullptr) {
            Arr[index] = newNode;
        } 
        else {
            Node* current = Arr[index];
            while (current->link != nullptr) {
                
                if(current->info.var == newNode->info.var){
                    delete newNode;
                    current->info.count++;
                    return; // if it's the same as the ones we inserted before, there is no logic in continue while loop.
                   
                }
                
                current = current->link;
            }
            current->link = newNode;
        }

    }
    
    void hashMaxTen(){
        vector <hashVariable> heap;
        Node * current;
        hashVariable largest;
        
        for (int i = 0; i < tableSize; i++)
        {   
            current = Arr[i];

            while (current != nullptr)
            {  
                heap.push_back(current->info);
                current = current->link;
            }
        }

        make_heap(heap.begin(),heap.end(),compare);
        
        for (int i = 0; i < 10; i++)
        {
            pop_heap(heap.begin(),heap.end(),compare);

            largest = heap.back();

            cout << largest.var << " " << largest.count << " founded" << endl;

            heap.pop_back();    
        }
        
    }

    ~hashTable() {

        for (int i = 0; i < tableSize; ++i) {
            Node* current = Arr[i];


            while (current != nullptr) {
                Node* next = current->link;
                delete current;
                current = next;
            }

            Arr[i] = nullptr;
        }

        delete[] Arr;
    }//destructor
};