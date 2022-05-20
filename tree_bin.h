#pragma once 

#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<queue>
#include<map>
#include<stack>
#include<initializer_list>
#include<algorithm>
#include"exception.h"
#include"complex.h"
#include"Person.h"

using namespace std;

template <typename T>
class BinaryTree{
    template<typename T1>
    friend class priorityQueue;
public:
    struct Node{
        friend class BinaryTree<T>;
    private:
        T key;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        Node* nill = nullptr;
        size_t height = 1;
    public:
        Node(){}
        Node(T key){
            this -> key = key;
            this -> left = nullptr;
            this -> right = nullptr;
            this -> parent = nullptr;
            this -> height = 1;
        }
        T getKey(){
            return this -> key;
        }
    };
    BinaryTree();
    BinaryTree(T* items , size_t count);
    BinaryTree(const BinaryTree<T>& obj);
    BinaryTree(initializer_list<T> list);
    ~BinaryTree();
    void Insert(T item);
    Node* find(T key);
    void erase(T key);
    void BalanceTree();
    void RoundWalk(void (*visit) (Node*), string order);
    void firmware(string order);
    void print();
    BinaryTree<T>* geSubTree(T key);
    BinaryTree<T>* map(T (*func) (T));
    BinaryTree<T>* where(bool (*func) (T));
    T reduce(T (*func) (T , T), T c);
    BinaryTree<T>* merge(const BinaryTree<T>& obj , T (*func) (T , T));
    Node* findSubTree(BinaryTree<T>* obj);
    BinaryTree<T>* readString( string items, string order);
    T GetMax();
    T* saveToString(string order);
    string* getString(string order);
    bool operator==(const BinaryTree<T>& obj);
    BinaryTree<T>* unification(BinaryTree<T>* obj);
private:
    Node* root = nullptr;
    Node* head = nullptr;
    size_t count = 0;
    Node* Search(Node* node , T key);
    void Transplant(Node* node1 , Node* node2);
    size_t bfactor(Node* node);
    void changeHeight(Node* node);
    void RightRotate(Node* node);
    void LeftRotate(Node* node);
    void BigLeftRotate(Node* node);
    Node* Minimum(Node* node);
    Node* Maximum(Node* node);
    void BigRightRotate(Node* node);
    void BalanceNode(Node* node);
    void Round(Node* node , void (*visit) (Node*), string order);
    void walkWithQueue(Node* node, string order , queue<Node*>* st);
    void InorderStep(Node* node);
    void printQueue();
    void helpTosaveString(Node* node , string* str , string c1, string c2, string order);
    void helpToReadString(BinaryTree<T>* tree, string items , string order);
    pair<int , int> findChar(char c1 ,char c2,  string items , int pos);
    pair<int , int> findRoot(string items);
};

template<typename T> bool BinaryTree<T>::operator==(const BinaryTree<T>& obj){
    if(this -> count != obj.count){
        return false;
    }
    queue<Node*> q1;
    queue<Node*> q2;
    if((!root && obj.root) || (root && !obj.root) || (!root && !obj.root)){
        return false;
    }
    q1.push(this -> root);
    q2.push(obj.root);
    while(q1.size() != 0){
        Node* tmp1 = q1.front();
        q1.pop();
        Node* tmp2 = q2.front();
        q2.pop();
        if(tmp1 -> key != tmp2-> key){
            return false ;
        }
        else{
            if((tmp1 -> left && !tmp2->left)||(!tmp1->left && tmp2->left)){
                return false;
            }
            if((tmp1->right && !tmp2-> right)|| (!tmp1->right && tmp2->right)){
                return false;
            }
            if(tmp1-> left && tmp2 -> left){
                q1.push(tmp1 -> left);
                q2.push(tmp2 -> left);
            }
            if(tmp1 -> right && tmp2 -> right){
                q1.push(tmp1 -> right);
                q2.push(tmp2 -> right);
            }
        }
    }
    return true;
}
template<typename T> BinaryTree<T>::~BinaryTree(){
    if(!root){return;}
    queue<Node*> q;
    q.push(root);
    while(q.size() != 0){
        Node* tmp = q.front();
        q.pop();
        if(tmp -> left){
            q.push(tmp -> left);
        }
        if(tmp -> right){
            q.push(tmp -> right);
        }
        delete tmp;
    }
}
template<typename T> BinaryTree<T>::BinaryTree(initializer_list<T> list){
    for(auto element:list){
        this -> Insert(element);
    }
}
template<typename T> BinaryTree<T>:: BinaryTree(){}
template <typename T> typename BinaryTree<T>::Node* BinaryTree<T>:: Minimum(Node* node){
    if(node -> left == nullptr){
        return node;
    }
    return Minimum(node -> left);
}
template <typename T> typename BinaryTree<T>::Node* BinaryTree<T>:: Maximum(Node* node){
    if(node -> right == nullptr){
        return node;
    }
    return Maximum(node -> right);
}
template <typename T> T BinaryTree<T>:: GetMax(){
    return this -> Maximum(this -> root) -> key;
}
template <typename T> BinaryTree<T>::BinaryTree(const BinaryTree<T>& obj){
    queue<Node*> q;
    q.push(obj.root);
    while(q.size() != 0){
        Node* tmp = q.front();
        q.pop();
        this -> Insert(tmp -> getKey());
        if(tmp -> left){
            q.push(tmp -> left);
        }
        if(tmp -> right){
            q.push(tmp -> right);
        }
    }
}
template <typename T> void BinaryTree<T>:: Insert(T item){
    if(this -> find(item)){
        cout << "Item already exist!\n";
        return;
    }
    Node* newNode =  new Node;
    newNode -> key = item;
    newNode -> height = 1;
    Node* prevNode = nullptr;
    Node* curNode = root;
    while(curNode != nullptr){
        prevNode = curNode;
        if(item < curNode -> key){
            curNode = curNode -> left;
        }
        else{
            curNode = curNode -> right;
        }
    }
    newNode -> parent = prevNode;
    if(prevNode == nullptr){
        this -> root = newNode;
    }
    else if(item < prevNode -> key){
        prevNode -> left = newNode;
    }
    else{
        prevNode -> right = newNode;
    }
    Node* tmpNode = newNode;
    while(tmpNode){
        BalanceNode(tmpNode);
        tmpNode = tmpNode -> parent;
    }
    this -> count +=1;
}
template <typename T> BinaryTree<T>:: BinaryTree(T* items , size_t count){
    for(int i = 0; i < count; ++i){
        this -> Insert(items[i]);
    }
}
template <typename T> typename BinaryTree<T>::Node* BinaryTree<T>:: find(T key){
    return Search(this -> root , key);
}
template <typename T> typename BinaryTree<T>::Node* BinaryTree<T>:: Search(Node* node , T key){
    if(node == nullptr || node -> key == key){
        return node;
    }
    if(key < node -> key){
        return Search(node -> left , key);
    }
    else{
        return Search(node -> right , key);
    }
}
template <typename T> void BinaryTree<T>:: erase(T key){
    Node* delNode = this -> find(key);
    if(delNode == nullptr){return;}
    else{
        if(delNode -> left == nullptr){
            Transplant(delNode , delNode -> right);
        }
        else if(delNode -> right == nullptr){
            Transplant(delNode , delNode -> right);
        }
        else{
            Node* newNode = Minimum(delNode -> right);
            if(delNode != newNode -> parent){
                Transplant(newNode , newNode -> right);
                newNode -> right = delNode -> right;
                (newNode -> right) -> parent = newNode;
            }
            Transplant(delNode , newNode);
            newNode -> left = delNode-> left;
            newNode -> left -> parent = newNode;
        }
    }
    delete(delNode);
    this -> count -= 1;
    Node* min = Minimum(root);
    while(min){
        BalanceNode(min);
        min = min -> parent;
    }
}
template <typename T> void BinaryTree<T>:: Transplant(Node* node1 , Node* node2){
    if(node1 -> parent == nullptr){
        this -> root = node2;
    }
    else if(node1 == (node1 -> parent) -> left){
        (node1 -> parent) -> left = node2;
    }
    else {
        (node1 -> parent) -> right = node2;
    }
    if(node2 != nullptr){
        node2 -> parent = node1 -> parent;
    }
}
template <typename T> size_t BinaryTree<T>::bfactor(Node* node){
    if(!node){
        throw ExceptionError(2);
    }
    int heightR = 0;
    int heightL = 0;
    if(node -> right){
        heightR = (node -> right) -> height;
    } 
    if(node -> left){
        heightL = (node -> left) -> height;
    }
    return heightR - heightL;
}
template <typename T> void BinaryTree<T>:: changeHeight(Node* node){
    if(!node){return;}
    int heightL = 0;
    int heightR = 0;
    if(node -> left){
        heightL = (node -> left) -> height;
    }
    if(node -> right){
        heightR = (node -> right) -> height;
    }
    node -> height = max(heightL , heightR) + 1;
}
template <typename T> void BinaryTree<T>::RightRotate(Node* node){
    if(node -> parent){
        if(node == (node -> parent) -> left){
            (node -> parent) -> left = node -> left;
        }
        else{
            (node -> parent) -> right = node -> left;
        }
    }
    if(node == this -> root){
        this -> root = node -> left;
    }
    Node* tmp = node -> left;
    node -> left = tmp -> right;
    tmp -> right = node;
    tmp -> parent = node -> parent;
    node -> parent = tmp;
    if(node -> left){
        (node -> left) -> parent = node;
    }
    changeHeight(node);
    changeHeight(tmp);
}
template <typename T> void BinaryTree<T>::LeftRotate(Node* node){
    if(node -> parent){
        if(node == (node -> parent) -> left){
            (node -> parent) -> left = node -> right;
        }
        else{
            (node -> parent) -> right = node -> right;
        }
    }
    if(node == this -> root){
        this -> root = node -> right;
    }
    Node* tmp = node -> right;
    node -> right = tmp -> left;
    tmp -> left = node;
    tmp -> parent = node  -> parent;
    node -> parent = tmp;
    if(node -> right){
        (node -> right) -> parent = node;
    }
    changeHeight(node);
    changeHeight(tmp);
}
template <typename T> void BinaryTree<T>:: BigLeftRotate(Node* node){
    this -> RightRotate(node -> right);
    this -> LeftRotate(node);
}
template <typename T> void BinaryTree<T>:: BigRightRotate(Node* node){
    this -> LeftRotate(node -> left);
    this -> RightRotate(node);
}
template <typename T> void BinaryTree<T>:: BalanceTree(){
    Node** itemsPtr = new Node*[this -> count];
    int cur = 0;
    if(!itemsPtr){throw ExceptionError(1);}
    queue<Node*> q;
    if(!(this -> root)){return;}
    q.push(this -> root);
    while(q.size() != 0){
        Node* tmp = q.front();
        q.pop();
        itemsPtr[cur++] = tmp;
        if(tmp -> left){
            q.push(tmp -> left);
        }
        if (tmp -> right){
            q.push(tmp -> right);
        }
    }
    //We get array ptr on nodes of tree and starting balance
    for(int i = 0; i < count; ++i){
        BalanceNode(itemsPtr[count -1 - i]);
        string str = *(this -> getString("LNR"));
        cout << str << '\n';
    }
}
template<typename T> void BinaryTree<T>:: BalanceNode(Node* node){
    changeHeight(node);
    if(this -> bfactor(node) == 2){
        int var = bfactor(node ->right);
        if(var == 0 || var == 1){
            this -> LeftRotate(node);
        }
        else if(var == -1){
            this  -> BigLeftRotate(node);
        }
    }
    if(this -> bfactor(node) == -2){
        int var = bfactor(node -> left);
        if(var == 0 || var == -1){
            this -> RightRotate(node);
        }
        else if(var == 1){
            this -> BigRightRotate(node);
        }
    }
}
template<typename T> void BinaryTree<T>::RoundWalk(void (*visit) (Node*), string order ){
    for(int index = 0; index < order.size(); ++index){
        switch(order[index]){
            case 'N':
                visit(this -> root);
                break;
            case 'L':
                Round(root -> left, visit , order);
                break;
            case 'R':
                Round(root -> right , visit , order);
                break;
        }
    }
}
template<typename T> void BinaryTree<T>::Round(Node* node , void (*visit) (Node*), string order){
    if(!node){return;}
    queue<Node*>* q = new queue<Node*>;
    walkWithQueue(node , order , q);
    while(!(q->empty())){
        Node* tmp = q->front();
        q->pop();
        visit(tmp);
    }
    delete(q);
}
template<typename T> void BinaryTree<T>::walkWithQueue(Node* node, string order , queue<Node*>* st){
    if(!node){return;}
    for(int index = 0; index < order.size(); ++index){
        switch(order[index]){
            case 'N':
                st->push(node);
                break;
            case 'L':
                walkWithQueue(node -> left, order ,st);
                break;
            case 'R':
                walkWithQueue(node -> right ,order , st);
                break;
        }
    }
}
template<typename T> void BinaryTree<T>::firmware(string order){
    queue<Node*>* q = new queue<Node*>;
    walkWithQueue(this -> root, order, q);
    if(q->empty()){return;}
    Node* post = q -> front();
    q->pop();
    this -> head = post;
    Node* prev = nullptr;
    while(!(q ->empty())){
        prev = q -> front();
        q-> pop();
        post -> nill = prev;
        post = prev;
    }
}
template<typename T> void BinaryTree<T>::print(){
   if(!head){return;}
   Node* tmp = this -> head;
    while(tmp){
        cout << tmp -> getKey();
        tmp = tmp -> nill;
    } 
}
template<typename T> BinaryTree<T>* BinaryTree<T>::geSubTree(T key){
    Node* tmp = this -> find(key);
    if(!tmp){return nullptr;}
    BinaryTree<T>* resTree = new BinaryTree<T>;
    queue<Node*>* q = new queue<Node*>;
    walkWithQueue(tmp , "NLR" , q);
    int length = q->size();
    for(int i = 0; i < length; ++i){
        Node* cur = q -> front();
        q -> pop();
        resTree-> Insert(cur -> getKey());
    }
    delete q;
    return resTree;
}
template<typename T> BinaryTree<T>* BinaryTree<T>::map(T (*func) (T)){
    if(!root){return nullptr;}
    BinaryTree<T>* resTree = new BinaryTree<T>(*this);
    if(!resTree){throw ExceptionError(1);}
    queue<Node*> q;
    q.push(resTree -> root);
    while(q.size() != 0){
        Node* tmp = q.front();
        q.pop();
        tmp -> key = func(tmp -> getKey());
        if(tmp -> left){
            q.push(tmp -> left);
        } 
        if(tmp -> right){
            q.push(tmp -> right);
        }
    }
    return resTree;
}
template<typename T> BinaryTree<T>* BinaryTree<T>::where(bool (*func) (T)){
    BinaryTree<T>* resTree = new BinaryTree<T>;
    if(!resTree){throw ExceptionError(1);}
    queue<Node*> q;
    q.push(this -> root);
    while(q.size() != 0){
        Node* tmp = q.front();
        q.pop();
        if(func(tmp -> getKey())){
            resTree -> Insert(tmp -> getKey());
        }
        if(tmp -> left){
            q.push(tmp -> left);
        }
        if(tmp -> right){
            q.push(tmp -> right);
        }
    }
    return resTree;
}
template<typename T> T BinaryTree<T>::reduce(T (*func) (T , T) , T c){
    queue<Node*> q;
    T res;
    q.push(this -> root);
    while(q.size() != 0){
        Node* tmp = q.front();
        q.pop();
        if(tmp == root){
            res = func(root -> getKey(), c);
        }
        else{
            res = func(tmp -> getKey(), res);
        }
        if(tmp -> left){
            q.push(tmp -> left);
        }
        if(tmp -> right){
            q.push(tmp -> right);
        }
    }
    return res;
}
template<typename T> BinaryTree<T>* BinaryTree<T>:: merge(const BinaryTree<T>& obj , T (*func)(T,T)){
    queue<Node*> q1;
    queue<Node*> q2;
    int cur1 = 0;
    int cur2 = 0;
    int tek = 0;
    int count = max(obj.count , this -> count);
    if(!(this -> root) && obj.root){
        BinaryTree<T>* resTree = new BinaryTree<T>(obj);
        return resTree;
    }
    if(!(obj.root) && this -> root){
        BinaryTree<T>* resTree = new BinaryTree<T>(*this);
    }
    if(!(obj.root) && !(this -> root)){
        return nullptr;
    }
    BinaryTree<T>* resTree = new BinaryTree<T>;
    q1.push(this -> root);
    q2.push(obj.root);
    Node* tmp1 = nullptr;
    Node* tmp2 = nullptr;
    while(q1.size() != cur1 && q2.size() != cur2){
        tmp1 = q1.front();
        q1.pop();
        tmp2 = q2.front();
        q2.pop();
        if(!tmp1 && tmp2){
            cur1 -=1 ;
            resTree -> Insert(tmp2 -> getKey());
            q1.push(nullptr);
            q1.push(nullptr);
            cur1 += 2;
            if(tmp2 -> left){
                q2.push(tmp2 -> left);
            }
            else{
                q2.push(nullptr);
                cur2 += 1;
            }
            if(tmp2 -> right){
                q2.push(tmp2 -> right);
            }
            else{
                q2.push(nullptr);
                cur2 += 1;
            }
        }
        if(!tmp2 && tmp1){
            cur2 -= 1;
            resTree -> Insert(tmp1 -> getKey());
            q2.push(nullptr);
            q2.push(nullptr);
            cur2 += 2;
            if(tmp1 -> left){
                q1.push(tmp1 -> left);
            }
            else{
                q1.push(nullptr);
                cur1 += 1;
            }
            if(tmp1 -> right){
                q1.push(tmp1 -> right);
            }
            else{
                q1.push(nullptr);
                cur1 += 1;
            }
        }
        if(tmp1 && tmp2){
            resTree -> Insert(func(tmp1 -> getKey(), tmp2 -> getKey()));
            if(tmp1 -> left){
                q1.push(tmp1 -> left);
            }
            else{
                q1.push(nullptr);
                cur1 += 1;
            }
            if(tmp1 -> right){
                q1.push(tmp1 -> right);
            }
            else{
                q1.push(nullptr);
                cur1+=1;
            }
            if(tmp2 -> left){
                q2.push(tmp2 -> left);
            }
            else{
                q2.push(nullptr);
                cur2 += 1;
            }
            if(tmp2 -> right){
                q2.push(tmp2 -> right);
            }
            else{
                q2.push(nullptr);
                cur2 += 1;
            }
        }
    }
    if(cur1 != q1.size()){
        while(q1.size() != 0){
            tmp1 = q1.front();
            q1.pop();
            if(tmp1){
                resTree -> Insert(tmp1 -> getKey());
                if(tmp1 -> left){
                    q1.push(tmp1 -> left);
                }
                if(tmp1 -> right){
                    q1.push(tmp1 -> right);
                }
            }
        }
    }
    if(cur2 != q2.size()){
        while(q2.size() != 0){
            tmp2 = q2.front();
            q2.pop();
            if(tmp2){
                resTree -> Insert(tmp2 -> getKey());
                if(tmp2 -> left){
                    q1.push(tmp2 -> left);
                }
                if(tmp2 -> right){
                    q1.push(tmp2 -> right);
                }
            }
        }
    }
    return resTree;
}
template<typename T> typename BinaryTree<T>::Node* BinaryTree<T>::findSubTree(BinaryTree<T>* obj){
    Node* tmp = this -> find(obj -> root -> key);
    if(!tmp){
        cout << "Does not contain subtree!\n";
        return nullptr;
    }
    queue<Node*> q1;
    queue<Node*> q2;
    q1.push(tmp);
    q2.push(obj -> root);
    while(q1.size() != 0){
        Node* cur1 = q1.front();
        q1.pop();
        Node* cur2 = q2.front();
        q2.pop();
        if(cur1 && !cur2){return nullptr;}
        if(!cur1 && cur2){return nullptr;}
        if(cur1 && cur2){
            if(cur1 -> key != cur2 -> key){
                cout << "Does not contain subtree!\n";
                return nullptr;
            }
            q1.push(cur1 -> left);
            q1.push(cur1 -> right);
            q2.push(cur2 -> left);
            q2.push(cur2 -> right);
        }
    }
    return tmp;
}
template<typename T> pair<int , int> BinaryTree<T>:: findChar(char c1 ,char c2,  string items, int pos){
    int res1 = 0;
    int res2 = 0;
    for(int i = pos; i < items.size(); ++i){
        if(items[i] == c1){
            res1 = i;
            break;
        }
    }
    int tmp = 0;
    int flag = 0;
    for(int i = res1 + 1; i < items.size() ; ++i){
        if(items[i] == c1){
            tmp++;
        }
        if(items[i] == c2){
            tmp--;
        }
        if(tmp == -1 ){
            res2 = i;
            break;
        }
    }
    pair<int, int> res(res1 , res2);
    return res;
}
template<typename T> pair<int , int> BinaryTree<T>:: findRoot(string items){
    int tmp = 0;
    int res1 , res2 ;
    for(int i =0; i < items.size(); ++i){
        if(items[i] == '[' || items[i] == '{' ){tmp ++;}
        if(items[i] == ']' || items[i] == '}' ){tmp --;}
        if(items[i] == '(' && tmp == 0){
            res1 = i;
            int cur = i + 1;
            while(items[cur] != ')'){
                cur++;
            }
            res2 = cur;
            break;
        }
    }
    pair<int , int> res(res1 , res2);
    return res;
}
template<typename T> void BinaryTree<T>::helpToReadString(BinaryTree<T>* tree, string items, string order){
    if(isdigit(items[0])){
        int x = items[0] - '0';
        tree -> Insert(x);
        return;
    }
    pair<int , int> rootP = findRoot(items);
    int root = items[rootP.first+1] - '0';
    tree -> Insert(root);
    int pos = 0;
    pair<int , int> leftP , rightP;
    string str1, str2;
    for(int index = 0; index < order.size(); ++index){
        switch(order[index]){
            case 'N':
                break;
            case 'L':
                leftP = findChar('[' , ']', items , pos);
                pos = leftP.second;
                if(leftP.second - leftP.first - 1 < 0){
                    break;
                }
                str1 = items.substr(leftP.first + 1, (leftP.second - leftP.first - 1));
                helpToReadString(tree , str1 , order);
                break;
            case 'R':
                rightP = findChar('{' , '}', items , pos);
                pos = rightP.second;
                if(rightP.second - rightP.first - 1 < 0){
                    break;
                }
                str2 = items.substr(rightP.first + 1, (rightP.second - rightP.first -1));
                helpToReadString(tree , str2 , order);
                break;
        }
    }
}
template<typename T> BinaryTree<T>* BinaryTree<T>:: readString(string items , string order){
    if(items.size() == 0){
        return nullptr;
    }
    BinaryTree<T>* resTr = new BinaryTree<T>;
    helpToReadString(resTr , items , order);
    return resTr;
}
template<typename T> T* BinaryTree<T>:: saveToString(string order){
    if(!(this -> root)){return nullptr;}
    queue<Node*>* q = new queue<Node*>;
    this -> walkWithQueue(this -> root , order, q);
    int size = q->size();
    T* resItems = new T[size];
    for(int i = 0; i < size; ++i){
        Node* tmp = q -> front();
        q -> pop();
        resItems[i] = tmp -> key;
    }
    delete q;
    return resItems;
}
template<typename T> void BinaryTree<T>:: InorderStep(Node* node){
    if(node != nullptr){
       InorderStep(node -> left);
       cout << node -> key;
       InorderStep(node-> right);
   } 
}
template<typename T> void BinaryTree<T>:: printQueue(){
   this -> InorderStep(this -> root);
}
template<typename T> void BinaryTree<T>:: helpTosaveString(Node* node , string* str , string c1 , string c2, string order){
    if(node -> left || node -> right){
        c1 = "(";
        c2 = ")";
    }
    for(int index = 0; index < order.size(); ++index){
        switch(order[index]){
            case 'N':
                if(node -> left == nullptr && node -> right == nullptr){
                    *str += to_string(node -> key);   
                }
                else{
                    *str = *str + string(c1) + to_string(node -> key) + string(c2);
                }
                break;
            case 'L':
                if(!(node -> left)){break;}
                *str += "[";
                helpTosaveString(node -> left , str ,  "[" , "]", order);
                *str += "]";
                break;
            case 'R':
                if(!(node -> right)){break;}
                *str += "{";
                helpTosaveString(node -> right, str , "{" , "}", order);
                *str += "}";
                break;
        }
    }
}
template<typename T> string* BinaryTree<T>::getString(string order){
    string* resStr = new string;
    helpTosaveString(this -> root , resStr, "(", ")", order);
    return resStr;
}
template<typename T> BinaryTree<T>* BinaryTree<T>::unification(BinaryTree<T>* obj){
    BinaryTree<T>* resQueue = new BinaryTree<T>;
    queue<Node*> q1;
    queue<Node*> q2;
    q1.push(this -> root);
    q2.push(obj -> root);
    while(q1.size() != 0 && q2.size() != 0){
        Node* tmp1 = q1.front();
        q1.pop();
        Node* tmp2 = q2.front();
        q2.pop();
        resQueue -> Insert(tmp1 -> key);
        resQueue -> Insert(tmp2 -> key);
        if(tmp1 -> left){
            q1.push(tmp1 -> left);
        }
        if(tmp1 -> right){
            q1.push(tmp1 -> right);
        }
        if(tmp2 -> left){
            q2.push(tmp2 -> left);
        }
        if(tmp2 -> right){
            q2.push(tmp2 -> right);
        }
    }
    return resQueue;
}
//