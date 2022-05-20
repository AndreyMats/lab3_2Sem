#pragma once 

#include<iostream>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include"exception.h"
#include"tree_bin.h"
#include"priorityQueue.h"
#include"complex.h"
#include"Person.h"

int ChooseType(){
    char var1;
    int var;
    cout << "Выберите хранимый тип данных:\n";
    cout << "1.Целые числа.\n";
    cout << "2.Вещественные числа.\n";
    cout << "3.Комплексные числа.\n";
    cout << "4.Строки.\n";
    cout << "5.Студент/преподаватель.\n";
    while(1){
        cin >> var1;
        var = var1 - '0';
        if(var >= 1 && var <= 5){break;}
        cout << "Некорректный ввод. Попробуйте снова.\n";
    }
    return var;
}

int operations(){
    cout <<"---------------------------\n";
    cout << "Достпуные операции:\n";
    cout << "1.Создание дерева(пустого).\n";
    cout << "2.Вставка элемента в дерево.\n";
    cout << "3.Удаление элемента из дерева(по ключу).\n";
    cout << "4.Операция map.\n";
    cout << "5.Операция where.\n";
    cout << "6.Слияние деревьев.\n";
    cout << "7.Извлечение поддерева(по заданному элемену).\n";
    cout << "8.Поиск на вхождение поддерева.\n";
    cout << "9.Поиск на вхождение элемента.\n";
    cout << "10.Сохранение в строку в соответствии с заданным обходом.\n";
    cout << "11.Чтение из строку в соответствии с заданным обходом.\n";
    cout << "12.Вывести содержимое дерева.\n";
    cout << "13.Выход.\n";
    int x;
    cin >> x;
    return x;
}

int getNumber_tree(int all_size){
    int res ;
    do{
        cout << "Введите номер дерева:\n";
        cin >> res;
    }while(res < 0 || res > all_size);
    return res;
}

template<typename T>
void Destructor(vector<BinaryTree<T>*>* v , int count){
    for(int i = 0; i < count; ++i){
        delete (*v)[i];
    }
}

template<typename T>
void make_tree(vector<BinaryTree<T>*>* v_init){
    BinaryTree<T>* new_tree = new BinaryTree<T>;
    v_init -> push_back(new_tree);
}

template<typename T>
void insert_in_tree(vector<BinaryTree<T>*>* v_init , int count_init){
    int number_tree = getNumber_tree(count_init);
    T key;
    cout << "Введите значение ключа, вставляемого элемента:\n";
    cin >> key;
    (*v_init)[number_tree - 1] -> Insert(key);
    cout << "Вставка элемента прошла успешно.\n";
}

template<typename T>
void print_tree(vector<BinaryTree<T>*>* v_init , int count_init){
    int number_tree = getNumber_tree(count_init);
    string* str = (*v_init)[number_tree - 1] -> getString("LNR");
    cout << *str << '\n';
    delete str;
}

template<typename T>
void delete_item(vector<BinaryTree<T>*>* v_init, int count_init){
    int number_tree = getNumber_tree(count_init);
    T key;
    cout << "Введите значение ключа, удаляемого элемента:\n";
    cin >> key;
    (*v_init)[number_tree - 1] -> erase(key);
}

int mult(int x){
    return x * 2;
}

template<typename T>
void map_on_tree(vector<BinaryTree<T>*>* v_init , int count_init){
    cout << "По умолчанию принимается функциия умножения на два(только для целых чисел).\n";
    int number_tr1 = getNumber_tree(count_init);
    BinaryTree<T>* resTr = (*v_init)[number_tr1 - 1] -> map(mult);
    v_init->push_back(resTr);
}

bool compare_with_ten(int x){
    if(x < 10){
        return true;
    }
    else return false;
}

template<typename T>
void where_on_tree(vector<BinaryTree<T>*>* v_init , int count_init){
    cout << "По умолчанию принимается функциия,сравнивающая целые числа с 10.\n";
    int number_tr = getNumber_tree(count_init);
    BinaryTree<T>* res_tr = (*v_init)[number_tr-1] -> where(compare_with_ten);
    v_init->push_back(res_tr);
}

template<typename T>
void merge_tree(vector<BinaryTree<T>*>* v_init , int count_init){
    cout << "Первое дерево:\n";
    int num1 = getNumber_tree(count_init);
    cout << "Второе дерево:\n";
    int num2 = getNumber_tree(count_init);
    BinaryTree<T>* res_tr = (*v_init)[num1 - 1] -> unification((*v_init)[num2 -1]);
    v_init->push_back(res_tr);
}

template<typename T>
void get_sub_tree(vector<BinaryTree<T>*>* v_init , int count_init){
    int num_tree = getNumber_tree(count_init);
    cout << "Введите значение ключа.\n";
    T key;
    cin >> key;
    BinaryTree<T>* res_tr = (*v_init)[num_tree-1] -> geSubTree(key);
    v_init -> push_back(res_tr);
}

template<typename T>
void find_sub_tree(vector<BinaryTree<T>*>* v_init, int count_init){
    cout << "Дерево для поиска.\n";
    int num1 = getNumber_tree(count_init);
    int num2 = getNumber_tree(count_init);
    void* tmp = (*v_init)[num1 -1] -> findSubTree((*v_init)[num2 - 1]);
    if(tmp){
        cout << "Дерево было найдено.\n";
    }
    else{
        cout << "Дерево не было найдено.\n";
    }
}

template<typename T>
void find_item(vector<BinaryTree<T>*>* v_init, int count_init){
    int num_tr = getNumber_tree(count_init);
    T key;
    cout << "Введите значение ключа, элемента для поиска:\n";
    cin >> key;
    void* ptr = (*v_init)[num_tr -1]-> find(key);
    if(ptr){
        cout << "Элемента найден.\n";
    }
    else{
        cout << "Элемент не найден.\n";
    }
}

template<typename T>
void save_in_string(vector<BinaryTree<T>*>* v_init , int count_init){
    int num_tr = getNumber_tree(count_init);
    cout << "Введите порядок обхода:\n";
    string str;
    cin >> str;
    string* resStr = (*v_init)[num_tr-1]-> getString(str);
    cout << *resStr << '\n';
    delete resStr;
}

template<typename T>
void read_string(vector<BinaryTree<T>*>* v_init , int count_init){
    if(count_init == 0){return;}
    string order;
    cout << "Введите порядок обхода:\n";
    cin >> order;
    string items;
    cout << "Введите строку для считывания.\n";   
    cin >> items;
    BinaryTree<T>* resTr = (*v_init)[0] -> readString(items , order);
    v_init-> push_back(resTr);
}

void menu_int(){
    int var_op;
    vector<BinaryTree<int>*> v_init;
    int count_init = 0;
    do{
        var_op = operations();
        switch(var_op){
            case 1:
                make_tree(&v_init);
                count_init++;
                break;
            case 2:
                insert_in_tree(&v_init , count_init);
                break;
            case 3:
                delete_item(&v_init , count_init);
                break;
            case 4:
                map_on_tree(&v_init , count_init);
                count_init++;
                break;
            case 5:
                where_on_tree(&v_init, count_init);
                count_init++;
                break;
            case 6:
                merge_tree(&v_init , count_init);
                count_init++;
                break;
            case 7:
                get_sub_tree(&v_init , count_init);
                count_init++;
                break;
            case 8:
                find_sub_tree(&v_init, count_init);
                break;
            case 9:
                find_item(&v_init , count_init);
                break;
            case 10:
                save_in_string(&v_init , count_init);
                break;
            case 11:
                read_string(&v_init , count_init);
                count_init++;
                break;
            case 12:
                print_tree(&v_init , count_init);
                break;
            case 13:
                break;
            default:
                cout << "Введено некорректное значение.Повторите попытку.\n";
        }
        
    }while(var_op != 13);
    Destructor(&v_init , count_init);
}


void menu(){
    int varType = ChooseType();
    switch(varType){
        case 1:
            menu_int();
            break;
        case 2:
            //menu_float();
            break;
        case 3:
            //menu_complex();
            break;
        case 4:
            //menu_string();
            break;
        case 5:
            //menu_person();
            break;
    }
}