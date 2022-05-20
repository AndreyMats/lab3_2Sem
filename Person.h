#pragma once

#include<iostream>
#include<cstring>
#include<string>

using namespace std;

struct Person{ 
    private:
        string firstName;
        string middleName;
        string lastName;
        int age = 0;
        int PersonId = 0;
    public:
    Person(){};
    Person(const Person &obj){
        this -> firstName = obj.firstName;
        this -> middleName = obj.middleName;
        this -> lastName = obj.lastName;
        this -> age = obj.age;
        this -> PersonId = obj.PersonId;
    }
    Person(string s1 , string s2, string s3, int age , int id){
        this -> firstName = s1;
        this -> middleName = s2;
        this -> lastName = s3;
        this -> age = age;
        this -> PersonId = id;
    }
    string GetFirstName(){
        return this -> firstName;
    }
    string GetMiddleName(){
        return this -> middleName;
    }
    string GetLastName(){
        return this -> lastName;
    }
    int GetAge(){
        return this -> age;
    }
    int GetId(){
        return this -> PersonId;
    }
    bool operator==(const Person &obj){
        if(this -> PersonId == obj.PersonId){
            return true;
        }
        else{
            return false;
        }
    }
    bool operator!=(const Person &obj){
        return !(*this == obj);
    }
};