#include <cassert>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include"lab3_new/exception.h"
//#include"Set.h"
#include"lab3_new/tree_bin.h"
#include"lab3_new/priorityQueue.h"

void test_insert() {
    //test 1
    BinaryTree<int> tr1;
    tr1.Insert(1);
    BinaryTree<int> res1{1};
    assert(tr1 == res1);
    // test 2
    tr1.Insert(5);
    tr1.Insert(7);
    BinaryTree<int> res2{1, 5, 7};
    assert(tr1 == res2);
}

void test_some_other_functions(){
    // testing GetMax
    BinaryTree<int> tr1 {6 ,2, 4, 5, 1 , 9};
    int res = tr1.GetMax();
    assert(res == 9);

    //testing find
    BinaryTree<int> tr2{7,3,4,5,1,2,9};
    BinaryTree<int>::Node* res1 = nullptr;
    res1 = tr2.find(7);
    assert(res1 -> getKey() == 7);
    res1 = tr2.find(5);
    assert(res1 -> getKey() == 5);
    res1 = tr2.find(6);
    assert(res1 == nullptr);

    //testing erase
    //1. delete sheet
    BinaryTree<int> tr3{2, 3, 1};
    BinaryTree<int> res3{2, 3};
    tr3.erase(1);
    assert(tr3 == res3);
    BinaryTree<int> res4{2};
    tr3.erase(3);
    assert(tr3 == res4);
    //2. delete node with childs
    BinaryTree<int> tr4{5,7,3,8,4,9,1};
    tr4.erase(3);
    BinaryTree<int> res5 {5, 8, 4, 1,7,9};
    assert(res5 == tr4);
}

//function to testing map
int mult(int a){
        return a * 2;
}
//function  to testing where
bool check(int a){
    if(a < 5){
        return true;
    }
    else{
        return false;
    }
}
//function to testing reduce
int summ(int a , int b){
    return a + b;
}
void test_walks_firmware(){
    // testing getSubTree
    BinaryTree<int> tr1{5 ,7, 3, 8,4,9,1};
    BinaryTree<int>* tr2 = tr1.geSubTree(3);
    BinaryTree<int> res1{3 ,4 , 1};
    assert(*tr2 == res1);
    delete(tr2);
    //try to get whole tree
    BinaryTree<int>* tr3 = tr1.geSubTree(5);
    BinaryTree<int> res2{5,7,3,8,4,9,1};
    assert(*tr3 == res2);
    delete tr3;
    
    //TESTING MAP
    BinaryTree<int>* tr4 = tr1.map(mult);
    BinaryTree<int> res3{10 , 14, 6, 16, 8 , 18, 2};
    assert(*tr4 == res3);
    delete tr4;

    // TESTING WHERE
    BinaryTree<int>* tr5 = tr1.where(check);
    BinaryTree<int> res4{3 , 4, 1};
    assert(*tr5 == res4);
    delete(tr5);

    // TESTING REDUCE
    int res5 = tr1.reduce(summ , 0);
    assert(res5 == 37);

    //TESTING GET_STRING
    // 1. "LNR" - walk
    string* str1 = tr1.getString("LNR");
    string str1_ans = "[[1](3){4}](5){[7](8){9}}";
    assert(*str1 == str1_ans);
    delete str1;
    // 2. "NRL" - walk
    string* str2 = tr1.getString("NRL");
    string str2_ans = "(5){(8){9}[7]}[(3){4}[1]]";
    assert(*str2 == str2_ans);
    delete str2;
}

void test_read_string(){
    // TESTING READ_STRING
    BinaryTree<int> tr1{1};
    BinaryTree<int>* res1 = tr1.readString("[[1](3){4}](5){[7](8){9}}", "LNR");
    string* str1 = res1->getString("LNR");
    assert(*str1 == "[[1](3){4}](5){[7](8){9}}");
    delete str1;
    delete res1;

    BinaryTree<int>* res2 = tr1.readString("(5){(8){9}[7]}[(3){4}[1]]" , "NRL");
    string* str2 = res2 -> getString("NRL");
    assert(*str2 == "(5){(8){9}[7]}[(3){4}[1]]");
    delete str2;
    delete res2;
}

//____TESTING_PRIORITY_QUEUE____//

void test_1(){
    // TESTING GET_COUNT
    priorityQueue<int> q1{5, 3,4,8,1,9};
    int size = q1.GetCount();
    assert(size == 6);

    //TESTING FIND_MAX
    int max = q1.findMax();
    assert(max == 9);

    // TESTING PUSH 
    q1.push(7);
    priorityQueue<int> res1{9, 1, 8,4,3,5,7};
    assert(q1 == res1);

    //  TESTING EXTRACT_MAX
    int x1 = q1.extractMax();
    priorityQueue<int> res2{1 ,8,4,3,5,7};
    assert(x1 == 9);
    assert(res2 == q1);

    //TESTING DELETE_MAX
    priorityQueue<int> q2{1 ,4,3,5,7,9};
    q2.deleteMax();
    priorityQueue<int> res3{1, 4,3,5,7};
    assert(q2 == res3);

    // TESTING INCREASE_KEY
    priorityQueue<int> q3{1 ,4,5,2,8};
    q3.increaseKey(4, 6);
    priorityQueue<int> res4{1, 6 ,5,2,8};
    assert(res4 == q3);

    // TESTING MAP
    priorityQueue<int> q4{5 ,4 ,6};
    priorityQueue<int> res5{10 , 8 ,12};
    priorityQueue<int>* res6 = q4.map(mult);
    assert(res5 == *res6);
    delete(res6);

    // TESTING WHERE
    priorityQueue<int> q5{6 , 1 ,2,8 ,3,4};
    priorityQueue<int>* res7 = q5.where(check);
    priorityQueue<int> res8 = {1 ,2, 3, 4};
    assert(*res7 == res8);
    delete(res7);

    //TESTING GET_SUB_QUEUE
    priorityQueue<int> q6{1, 2,3,4,5,6,7};
    priorityQueue<int>* res9 = q6.getSubQueue(3, 5);
    priorityQueue<int> res10 = {4 ,5 ,6};
    assert(res10 == *res9);
    delete(res9);

    //TESTING FIND_SUB_STR
    priorityQueue<int> q7{4,3,7,2,5,9,8,1,6};
    int* a= new int[3];
    a[0]= 5;
    a[1]= 6;
    a[2] = 7;
    int x3 = q7.findSubStr(a , 3);
    assert(x3 == 4);
    delete[] a;

    // TESTING MERGE_QUEUE
    priorityQueue<int> q8{3 ,2,6};
    priorityQueue<int> q9{1,4,5};
    priorityQueue<int>* res11 = q8.mergeQueue(&q9);
    priorityQueue<int> res12{1,2,3,4,5,6};
    assert(*res11 == res12);
    delete res11;

    //TESTING GET_IN_STRING
    priorityQueue<int> q10{1,2,3,4,5,6,7,8};
    string* str3 = q10.getInString();
    string real_str = "[[1](2){3}](4){[5](6){(7){8}}}";
    assert(*str3 == real_str);
    delete str3;
}