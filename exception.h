#pragma once 

#include<iostream>

using namespace std;

class ExceptionError{
public:
    ExceptionError(int x){
        if(x == 1){
            cout << "Memory allocation error!\n";
        }
        if(x == 2){
            cout << "Incorrect use of function!\n";
        }
    }
};