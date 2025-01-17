#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include "hash.hpp"

using namespace std::chrono;

class temp{
    
    public:
    string link,temp1,temp2,temp3,temp4,temp5;
    fstream file;
    void print();
    string StrP();
    bool isComplete = 0;
}obj;

string temp::StrP(){
 
        if(!file.eof()){
        getline(file,temp1,'T');
        getline(file,temp2,' ');
        getline(file,link,' ');
        getline(file,temp3,' ');
        getline(file,temp4,' ');
        getline(file,temp5,'\n');
        }

        else{
        isComplete = 1;
        }

    return link;

}

struct umapVariable
{
    string link;
    int count = 0;
};

void addUmap(unordered_map<string, umapVariable> &umap,string match){
    
    if (umap.find(match) == umap.end())
    {
        umapVariable* pair = new umapVariable;
        pair -> link = match;
        pair -> count++;
        umap[match] = *pair;
    }
    else {
        umap[match].count++;
    }
}

bool comparing(umapVariable item1,umapVariable item2){
    return (item1.count < item2.count);
}

void sortUmap(vector<umapVariable>& sortArray,unordered_map<string,umapVariable> &umap){

    unordered_map<string,umapVariable>::iterator p;

    for (p = umap.begin(); p != umap.end(); p++)
    {
        sortArray.push_back(p->second);
    }

    sort(sortArray.begin(),sortArray.end(),comparing);    
}

int main(){

    auto start = high_resolution_clock::now(); // Begginning of execution
    vector<umapVariable> sortArray;
    unordered_map<string, umapVariable> unorderedMap;
    hashTable myTable;
    temp data_file;
    auto lastItem = sortArray.rbegin();

    data_file.file.open("access_log", ios::in);

    while (!data_file.isComplete)
    {
        data_file.StrP();
        myTable.hashInsert(data_file.link);
    }
    //It will insert all log elements and gather it together

    myTable.hashMaxTen();
   
    
    auto stop = high_resolution_clock::now(); // End of execution

    auto duration = duration_cast<seconds>(stop - start);
    std::cout << "Elapsed time with hash table: " << duration.count() << "  seconds" << endl << endl;

    data_file.file.close();


    

    data_file.isComplete = 0;
    
    start = high_resolution_clock::now();

    vector<umapVariable> sortArrayUmap;

    data_file.file.open("access_log", ios::in);

    while (!data_file.isComplete)
    {
        data_file.StrP();
        addUmap(unorderedMap,data_file.link);
    }

    sortUmap(sortArrayUmap,unorderedMap);

    lastItem = sortArrayUmap.rbegin();

    for (int i = 0; i < 10; i++)
    {
        cout << lastItem->link << " " << lastItem->count << " founded " << endl;
        lastItem++;
    }
    

    stop = high_resolution_clock::now(); // End of execution
    duration = duration_cast<seconds>(stop - start);
    cout << "Elapsed time with unordered map: " << duration.count() << "  seconds" << endl;

    data_file.file.close();

    return 0;
}