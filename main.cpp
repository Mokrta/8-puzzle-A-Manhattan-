#include "8pfuncs.h"

using namespace std;

int main()
{
    Neighbour g;
    vector<int> st = {4,7,2,1,8,5,6,0,3};
    Stan start(st);
    cout << "Start stan:\n";
    start.print();
    if(!is_solviable(start)){
        cout << "This stan is not solviable.\n";
        return 0;
    }
    cout << "== Solving... ==\n";
    Node* node;
    Solver solver(start, GOAL);
    int c = 0;
    while(!solver.is_solved()){
        node = solver.next_node();
        solver.expand_node(node, g);
        c++;
    }
    vector<Node*> result;
    Node*t = node;
    do{
        result.push_back(t);
        t = (*t).get_parent();
    }while(t!=NULL);
    cout << "\nThis stan can be solved in " << result.size()-1 << " moves:\n";
    for(auto it = result.rbegin(); it < result.rend(); it++){
        Stan temp = (*it)->get_stan();
        cout << "\n";
        temp.print();
    }
    cout << "\nGenerated and stored stans while solving: " << solver.get_closed_size();
    return 0;
}
