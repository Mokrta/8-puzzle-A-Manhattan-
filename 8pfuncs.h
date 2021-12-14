#ifndef _8PFUNCS_H_INCLUDED
#define _8PFUNCS_H_INCLUDED

#include <iostream>
#include <vector>
#include <map>

class Stan{
    std::vector<int> a = std::vector<int>(9);
public:
    Stan();
    Stan(std::vector<int>&A);
    Stan(const Stan& copy);
    inline void Swap(int a1, int a2);
    const std::vector<int> get_stan() const;
    Stan& operator=(const Stan&asnt);
    friend bool operator==(const Stan&l, const Stan&r);
    friend bool operator!=(const Stan&l, const Stan&r);
    inline int index_of (int f, const Stan& v) const;
    int distManhattan(const Stan& goal);
    void print();
};

class Neighbour{
    std::map<int, std::vector<int>> neighbours;
public:
    Neighbour();
    const std::vector<int> indexNeighbours(int index) const;

};

class Node{
    int level;
    Stan s;
    Node* parent;
public:
    Node(Stan S, int l, Node* p);
    void set_parent(Node* p);
    Node* get_parent();
    const Stan& get_stan() const;
    int get_level();
    void print(int n);
};

class Solver{
    const Stan& goal;
    std::vector<Node*> open_list;
    std::vector<Node*> closed_list;
    bool done;
public:
    Solver(const Stan& start, const Stan& g);
    void expand_node(Node* cur, const Neighbour& g);
    Node* next_node();
    bool is_solved();
};

// Goal(end) values
std::vector<int> goal_stan = {1,2,3,4,5,6,7,8,0};
const Stan& GOAL(goal_stan);


// INDIVIDUAL FUNCS
static bool is_solviable(const Stan& s){
    int c = 0;
    const std::vector<int> arr = s.get_stan();
    for(size_t i = 0; i < arr.size(); i++)
        for(size_t j = i+1; j < arr.size(); j++)
            if(arr[j]&&arr[i]&&arr[i]>arr[j]) c++;
    return (c%2==0);
}
bool first_less_second(Node*l, Node*r){
    Stan s1 = (*l).get_stan();
    Stan s2 = (*r).get_stan();
    int e1 = s1.distManhattan(GOAL)+(*l).get_level();
    int e2 = s2.distManhattan(GOAL)+(*r).get_level();
    return e1<e2;
}
inline bool isInArray(const Stan& s, const std::vector<Node*>& values){
	for(size_t i = 0; i < values.size(); ++i){
		if(s == values[i]->get_stan())
			return true;
	}
	return false;
}


Stan::Stan(){ for(int i = 0; i < 9; i++) a[i] = i; }
Stan::Stan(std::vector<int>&A) : a(A) { }
Stan::Stan(const Stan& cpy){ a = cpy.a; }
const std::vector<int> Stan::get_stan() const{ return a; }
inline void Stan::Swap(int a1, int a2){
    std::swap(a[a1], a[a2]);
}
Stan& Stan::operator=(const Stan&asnt){
    if(this!=&asnt){ a = asnt.a; }
    return *this;
}
bool operator==(const Stan&l, const Stan&r){
    return l.a==r.a;
}
bool operator!=(const Stan&l, const Stan&r){
    return l.a!=r.a;
}
inline int Stan::index_of (int f, const Stan& v)const{
    for(int i = 0; i < 9; i++) if(v.a[i]==f) return i;
    return -1;
}
int Stan::distManhattan(const Stan& goal){
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
const std::vector<int> Neighbour::indexNeighbours(int index)const{
    std::map<int, std::vector<int>>::const_iterator itr(neighbours.find(index));
    if (itr != neighbours.end()) return itr->second;
    static std::vector<int> s;
    return s;
}

Node::Node(Stan S, int l, Node* p){
    s = S;
    level = l;
    parent = p;
}
void Node::set_parent(Node* p){ parent = p; }
Node* Node::get_parent(){ return parent; }
const Stan& Node::get_stan() const{ return s; }
int Node::get_level(){ return level; }
void Node::print(int n){
    std::cout << n << " Node {\n";
    s.print();
    std::cout << "LVL: " << level << "\n}\n";
}

Solver::Solver(const Stan& start, const Stan& g):goal(g){
    Node *root(new Node(start, 0, NULL));
    open_list.push_back(root);
    done = 0;
}
void Solver::expand_node(Node* cur, const Neighbour& g){
    if(cur->get_stan()==GOAL){
        done = true;
        return;
    }
    int zero = (*cur).get_stan().index_of(0, (*cur).get_stan());
    const std::vector<int> nei = g.indexNeighbours(zero);
    for(size_t i = 0; i < nei.size();i++){
        Stan s = cur->get_stan();
        s.Swap(zero, nei[i]); /// !
        if(!isInArray(s, closed_list)){
            Node* n(new Node(s, cur->get_level()+1, cur));
            open_list.push_back(n);
        }

    }
}
Node* Solver::next_node(){
    auto min = open_list.begin();

    for(auto it = open_list.begin()+1; it < open_list.end(); it++)
        if(first_less_second(*it, *min)) min = it;

    Node*temp = *min;
    open_list.erase(min);
    closed_list.push_back(temp);
    return temp;
}
bool Solver::is_solved() { return done; }


#endif // 8PFUNCS_H_INCLUDED
