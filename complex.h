#pragma once
#include<iostream>
#include<cstring>
#include<vector>
#include<map>

using namespace std;

struct Complex{
    double re = 0.0;
    double im = 0.0;
    Complex(int a , int b){
        this -> re = a;
        this -> im = b;
    }
    Complex(const Complex& obj){
        this -> re = obj.re;
        this -> im = obj.im;
    }
    Complex& operator +=(const int& a){
        this -> re += a;
        this -> im += a;
        return *this;
    }
    Complex& operator +=(const Complex& z){
        this -> re += z.re;
        this -> im += z.im;
        return *this;
    }
    Complex operator+(const Complex& z){
        Complex copy = *this;
        copy += z;
        return copy;
    }
    Complex& operator++(){
        (*this) += 1;
        return *this;
    }
    Complex operator++(int){
       Complex copy = *this;
        ++(*this);
        return copy;
    }
    bool operator<(const Complex& b){
        return (this -> re)*(this -> re) + (this -> im) * (this -> im) < b.re * b.re + b.im* b.im;
    }
    bool operator>(Complex& z){
        Complex copy = *this;
        return z < copy;
    }
    bool operator==(Complex& z){
        if(re == z.re && im == z.im){
            return true;
        }
        else{
            return false;
        }
    }
    bool operator!=(Complex& z){
        return !(*this==z);
    }
};