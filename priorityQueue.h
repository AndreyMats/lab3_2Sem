#pragma once 

#include<map>
#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<queue>
#include<initializer_list>
#include<stack>
#include<algorithm>
#include"exception.h"
#include"tree_bin.h"
#include"complex.h"
#include"Person.h"


using namespace std;

template<class T>
class priorityQueue{
private:
    BinaryTree<T>* items = nullptr;
public:
    priorityQueue();
    priorityQueue(T* items ,size_t count);
    priorityQueue(initializer_list<T> list);
    ~priorityQueue();
    T findMax();
    void push(T key);
    T extractMax();
    void deleteMax();
    int GetCount();
    void print();
    void increaseKey(T oldKey , T newKey);
    priorityQueue<T>* map(T (*func) (T));
    priorityQueue<T>* where(bool (*func) (T));
    T reduce(T (*func) (T , T) , T c);
    T* saveInString();
    priorityQueue<T>* getSubQueue(int startIndex , int endIndex);
    int findSubStr(T* subSeq , size_t size);
    priorityQueue<T>* mergeQueue(priorityQueue<T>* obj);
    string* getInString();
    bool operator==(priorityQueue<T>& obj);
};

template<typename T> int priorityQueue<T>::GetCount(){
    return this -> items -> count;
}
template<typename T> bool priorityQueue<T>::operator==(priorityQueue<T>& obj){
    if(this -> GetCount() != obj.GetCount()){
        return false;
    }
    int size = this -> GetCount();
    T* items1 = this -> items ->saveToString("LNR");
    T* items2 = obj.items->saveToString("LNR");
    for(int i = 0; i < size ; ++i){
        if(items1[i] != items2[i]){
            delete[] items1;
            delete[] items2;
            return false;
        }
    }
    delete[] items1;
    delete[] items2;
    return true;
}
template<typename T> priorityQueue<T>::priorityQueue(initializer_list<T> list){
    this -> items = new BinaryTree<T>(list);
}
template<typename T> priorityQueue<T>::~priorityQueue(){
    delete items;
}
template<typename T> priorityQueue<T>:: priorityQueue(){
    this -> items = new BinaryTree<T>;
}
template<typename T> priorityQueue<T>:: priorityQueue(T* items, size_t count){
    this -> items = new BinaryTree<T>(items , count);
}
template<typename T> T priorityQueue<T>:: findMax(){
    return this -> items -> GetMax();
}
template<typename T> void priorityQueue<T>::push(T key){
    this -> items -> Insert(key);
}
template<typename T> T priorityQueue<T>::extractMax(){
    T maxItem = this -> items -> GetMax();
    this -> items -> erase(maxItem);
    return maxItem;
}
template<typename T> void priorityQueue<T>::print(){
    this -> items-> printQueue();
}
template<typename T> void priorityQueue<T>::deleteMax(){
    this -> extractMax();
}
template<typename T> void priorityQueue<T>::increaseKey(T oldKey , T newKey){
    if(items -> find(oldKey) == nullptr){
        cout << "Item with this key don't find!\n";
        return;
    }
    this -> items->erase(oldKey);
    this -> items -> Insert(newKey);
}
template<typename T> priorityQueue<T>* priorityQueue<T>:: map(T (*func) (T)){
    priorityQueue<T>* resQueue = new priorityQueue<T>;
    delete resQueue -> items;
    resQueue -> items = this -> items -> map(func);
    return resQueue;
}
template<typename T> priorityQueue<T>* priorityQueue<T>::where(bool (*func) (T)){
    priorityQueue<T>* resQueue = new priorityQueue<T>;
    delete(resQueue -> items);
    resQueue -> items = this -> items -> where(func);
    return resQueue;
}
template<typename T> T priorityQueue<T>::reduce(T (*func) (T , T) , T c){
    T* string = this -> saveInString();
    if(string == nullptr){
        throw ExceptionError(2);
    }
    T res = func(string[0], c);
    for(int i = 1; i < this -> items -> count ; ++i){
        res =  func(string[i], res);
    }
    return res;
}
template<typename T> T* priorityQueue<T>:: saveInString(){
    return this -> items-> saveToString("LNR");
}
template<typename T> priorityQueue<T>* priorityQueue<T>::getSubQueue(int startIndex , int endIndex){
    T* string = this -> saveInString();
    if(string == nullptr){
        return nullptr;
    }
    if(startIndex < 0 || endIndex > this -> items -> count){
        throw ExceptionError(2);
    }
    priorityQueue<T>* resQueue = new priorityQueue<T>;
    for(int i = startIndex; i <= endIndex; ++i){
        resQueue-> items-> Insert(string[i]);
    }
    delete[] string;
    return resQueue;
}
template<typename T> int priorityQueue<T>::findSubStr(T* subSeq, size_t size){
    T* arr = this -> saveInString();
    if(!arr){
        return 0;
    }
    int curPos = 0;
    int countCoin = 1;
    while(curPos < this -> items -> count){
        if(arr[curPos] == subSeq[0]){
            for(int i = 1; i < size ; ++i){
                if(arr[curPos + i] == subSeq[i]){
                    countCoin ++;
                }
                else{
                    break;
                }
            }
            if(countCoin == size){
                delete[] arr;
                return curPos;
            }
            else{
                countCoin = 1;
            }
        }
        curPos++;
    }
    delete[] arr;
    return 0;
}
template<typename T> priorityQueue<T>* priorityQueue<T>::mergeQueue(priorityQueue<T>* obj){
    priorityQueue<T>* resQueue = new priorityQueue<T>;
    delete resQueue -> items;
    resQueue -> items = this-> items -> unification(obj -> items);
    return resQueue;
}
template<typename T> string* priorityQueue<T>::getInString(){
    return this -> items -> getString("LNR");
}
//