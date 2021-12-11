#ifndef _8PFUNCS_H_INCLUDED
#define _8PFUNCS_H_INCLUDED

#include <iostream>
#include <vector>
#include <map>

std::vector<int> GOAL = {1, 2, 3, 4, 5, 6, 7, 8, 0};

class Stan{
    std::vector<int> a = std::vector<int>(9);
public:
    Stan();
    Stan(std::vector<int>&A);
    Stan(const Stan& copy);
    Stan& operator=(const Stan&asnt);
    friend bool operator==(const Stan&l, const Stan&r);
    friend bool operator!=(const Stan&l, const Stan&r);
    int index_of(int f, std::vector<int> &v);
    int distManhattan(std::vector<int> &goal);
    void print();
};

class Neighbour{
    std::map<int, std::vector<int>> neighbours;
public:
    Neighbour();
    const std::vector<int> indexNeighbours(int index);

};

class Node{
    int level;
    Stan s;
    Node* parent;
public:
    Node(Stan S, int l, Node* p);
    void set_parent(Node* p);
    Node* get_parent();
    const Stan& get_stan();
    int get_level();
    void print(int n);
};

Stan::Stan() { for(int i = 0; i < 9; i++) a[i] = i; }
Stan::Stan(std::vector<int>&A) : a(A) { }
Stan::Stan(const Stan& cpy) {
    a = cpy.a;
}
Stan& Stan::operator=(const Stan&asnt) {
    if(this!=&asnt){ a = asnt.a; }
    return *this;
}
bool operator==(const Stan&l, const Stan&r){
    return l.a==r.a;
}
bool operator!=(const Stan&l, const Stan&r){
    return l.a!=r.a;
}
int Stan::index_of(int f, std::vector<int>&v){
    for(int i = 0; i < 9; i++) if(v[i]==f) return i;
    return -1;
}
int Stan::distManhattan(std::vector<int>&goal){
    int d = 0;
    for(int i = 1; i < 9; i++) {
        d+=abs(index_of(i, a)/3 - index_of(i, goal)/3);
        d+=abs(index_of(i, a)%3 - index_of(i, goal)%3);
    }
    return d;
}
void Stan::print(){
    for(int i = 0; i < 9; i++){
        std::cout << a[i] << " ";
        if(i%3==2) std::cout << "\n";
    }
}

Neighbour::Neighbour(){
    neighbours.insert(std::make_pair(0, std::vector<int>{1, 3}));
    neighbours.insert(std::make_pair(1, std::vector<int>{0, 2, 4}));
    neighbours.insert(std::make_pair(2, std::vector<int>{1, 5}));
    neighbours.insert(std::make_pair(3, std::vector<int>{4, 0, 6}));
    neighbours.insert(std::make_pair(4, std::vector<int>{3, 5, 1, 7}));
    neighbours.insert(std::make_pair(5, std::vector<int>{4, 2, 8}));
    neighbours.insert(std::make_pair(6, std::vector<int>{7, 3}));
    neighbours.insert(std::make_pair(7, std::vector<int>{6, 8, 4}));
    neighbours.insert(std::make_pair(8, std::vector<int>{7, 5}));
}
const std::vector<int> Neighbour::indexNeighbours(int index){
    return neighbours[index];
}

Node::Node(Stan S, int l, Node* p){
    s = S;
    level = l;
    parent = p;
}
void Node::set_parent(Node* p){ parent = p; }
Node* Node::get_parent(){ return parent; }
const Stan& Node::get_stan(){ return s; }
int Node::get_level(){ return level; }
void Node::print(int n){
    std::cout << n << " Node {\n";
    s.print();
    std::cout << "LVL: " << level << "\n}\n";
}

// INDIVIDUAL FUNCS

bool compare(Node&l, Node&r){
    Stan s1 = l.get_stan();
    Stan s2 = r.get_stan();
    int e1 = s1.distManhattan(&GOAL)+l.get_level();
    int e2 = s2.distManhattan(&GOAL)+r.get_level();
    return 1;
}

#endif // 8PFUNCS_H_INCLUDED
