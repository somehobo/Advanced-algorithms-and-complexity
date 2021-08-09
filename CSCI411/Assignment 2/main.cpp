// CSCI 411 - Spring 2021
// Assignment 2 Skeleton
// Author: Carter Tillquist
// Feel free to use all, part, or none of this code for the coding problem on assignment 2.

#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <algorithm>
using namespace std;

/******************************************************************************
 * A simple Node struct                                                       *
 * id - int - the id or name of the node                                      *
 * dist - int - the distance from some given node to this node                *
 * inI - bool - true if the node is a member of the set I and false otherwise *
 * visited - bool - whether or not this node has been visited                 *
 * ****************************************************************************/
struct Node {
    int id;
    int dist;
    bool inI;
    bool visited;
};

/**************************************************************************
 * A simple Edge struct                                                   *
 * from - Node* - the node where this edge starts                         *
 * to - Node* - the node where this edge ends                             *
 * weight - int - the weight of this edge                                 *
 * ************************************************************************/
struct Edge {
    Node* from;
    Node* to;
    int weight;
};

/*****************************************************************************************************************
 * Given a graph, find the set of nodes that belong to the set I, that is, the set of vertices v such that there *
 * is at least one path of length negative infinity ending at v.                                                 *
 * A - vector<vector<Edge*>> - an adjacency list representation of a graph where each element is a weighted edge *
 * return - vector<int> - the integer ids of nodes in the set I                                                  *
 * ***************************************************************************************************************/
 bool contains(vector<int> cycle, int v){//helper function: tells me if something
                                        // is in the array or not
   for (int i = 0; i < cycle.size(); i++) {
     if(cycle[i] == v){
       return true;
     }
   }
   return false;
 }

vector<int> findSetI(vector<vector<Edge*> > A){
    vector<int> cycle;//will eventually contain the nodes that have a -inf path
    int parents[A.size()];//parents list adapted from dfs for this
    for(int i = 0; i < A.size(); i++){//set all parents to a node that cant exist
      parents[i] = -1;
    }

    parents[0] = 1; // set the first parent equal to itself
    A[0][1]->from->dist = 0;//source node with dist 0 to start off bellman
                            //cause im lazy and dont want to write an if statement

    int x;
    for(int i = 0; i < A.size(); i++){
      x = -1;// if a distance is updated, this will reflect that, BIG BRAIN
      for (int j = 1; j < A.size(); j++) {//for each vertex in the adjacency list
        for(int w = 0; w < A[j].size(); w++){//check each edge and update distances
          if(A[j][w]->from->dist + A[j][w]->weight < A[j][w]->to->dist){
            A[j][w]->to->dist = A[j][w]->from->dist + A[j][w]->weight;
            parents[A[j][w]->to->id] = A[j][w]->from->id;
            x = A[j][w]->to->id;
          }
        }
      }
    }

    if(x == -1){//no further distances updated
      return cycle;
    } else {

      for(int v = x; ; v = parents[v]){//loops through the cycle until everything is
                                // put into the list. SO COOL
        cycle.push_back(v);
        if (contains(cycle, parents[v]) && cycle.size() > 1)
          break;
      }
      for(int i = 1; i < A.size(); i++){// add any other paths that werent cought
        if(!contains(cycle, i)){
          for(int j = 0; j < cycle.size(); j++){
            if(parents[i] == cycle[j]){
              cycle.push_back(i);
            }
          }
        }
      }
      return cycle;
    }


}



int main(){
    //get the number of nodes and number of edges from cin separated by a space
    int n = -1, m = -1;
    cin >> n >> m;

    //add the nodes to an adjacency list
    //in this case, A[i] is a vector of all edges leaving A[i]
    //note that A[0] is a list of self loops representing all nodes in the graph
    //these are not actual edges in the graph, just a way to keep track of all nodes
    //Furthermore, A[0][0] is a dummy edge with a dummy node
    //this means that A[i] is the node with id i where ids start at 1
    vector<vector<Edge*> > A(n+1);
    A[0].push_back(new Edge());
    for (int i=1; i<n+1; i++){
        Node* v = new Node();
        v->id = i;
        v->dist = 10000000;
        v->inI = false;
        v->visited = false;
        Edge* e = new Edge();
        e->from = v;
        e->to = v;
        e->weight = 0;
        A[0].push_back(e);
    }

    //get edges from cin and add them to the adjacency list
    //the start, end, and weight of a single edge are on the same line separated by spaces
    int u = -1, v = -1, w = -1;
    for (int i=0; i<m; i++){
        cin >> u >> v >> w;
        Edge* e = new Edge();
        e->from = A[0][u]->from;
        e->to = A[0][v]->to;
        e->weight = w;
        A[u].push_back(e);
    }

    //find nodes belonging to the set I and print them out in ascending order
    vector<int> I = findSetI(A);
    sort(I.begin(), I.end());
    for (int i=0; i<(int)I.size()-1; i++){
        cout << I[i] << " ";
    }
    if (I.size() > 1){ cout << I[I.size()-1] << endl; }

    return 0;
}
