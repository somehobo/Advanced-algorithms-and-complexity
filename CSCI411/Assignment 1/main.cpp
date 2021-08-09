// CSCI 411 - Fall 2020
// Assignment 1 Skeleton
// Author: Carter Tillquist
// Feel free to use all, part, or none of this code for the coding problem on assignment 1.

#include <iostream>
#include <vector>
using namespace std;



/**************************************************************************
 * A simple Node struct                                                   *
 * id - int - the id or name of the node                                  *
 * SCC - int - the strongly connected component that this node belongs to *
 * visited - bool - whether or not this node has been visited             *
 * ************************************************************************/
struct Node {
    int id;
    int SCC;
    bool visited;
};

/**************************************************************************************************
 * A simple struct of strongly connected component (SCC) graph nodes                              *
 * id - int - the id or name of the node (this corresponds to the SCC id)                         *
 * size - int - the number of nodes from the original graph that belong to this SCC               *
 * hasInEdges - bool - true if there are edges with end points in this SCC and false otherwise    *
 * hasOutEdges - bool - true if there are edges with start points in this SCC and false otherwise *
 * ************************************************************************************************/
struct SCCNode {
    int id;
    int size;
    bool hasInEdges;
    bool hasOutEdges;
};

/***************************************************************************************
 * Given the adjacency list of a graph, generate a new adjacency list with the         *
 * same nodes but with edges reversed                                                  *
 * A - vector<vector<Node*> > - an adjacency list representation of a graph. Note that  *
 *   A[0] is a list of all the Nodes in the graph with an additional dummy Node at     *
 *   A[0][0]. As a result, A[i] are the neighbors of the Node with id i where these    *
 *   ids go from 1 to n, the size of the graph.                                        *
 * return - vector<vector<Node*> > - an adjacency list of a new graph equivalent to the *
 *        original but with edges reversed.                                            *
 * *************************************************************************************/


vector<vector<Node*> > reverseEdges(vector<vector<Node*> > A){
    vector<vector<Node*> > R;
    vector<Node*> temp;
    //cause seg fault ding dong
    for(int i = 0; i < A.size(); i++){
      R.push_back(temp);
    }
    for(int i = 0; i < A[0].size(); i++){
      R[0].push_back(A[0][i]);
    }
    for(int i = 1; i < A.size(); i++){
      for( int j = 0; j < A[i].size(); i++){
        cout<<"counting"<<endl;
        R[A[i][j]->id].push_back(R[0][i]);
      }
    }
    //under this is printing
    for (int i = 0; i < A.size(); i++) {
      for(int j = 0; j < A[i].size(); j++){
        cout<<A[i][j]->id;
      }
      cout<<endl;
    }
    cout<<"BREAK"<<endl;
    for (int i = 0; i < R.size(); i++) {
      for(int j = 0; j < R[i].size(); j++){
        cout<<R[i][j]->id;
      }
      cout<<endl;
    }
    return R;
}

/********************************************************************************************************
 * A variation of DFS for the first pass over a graph looking for strongly connected components.        *
 * The goal is to fill the vector L with nodes in decreasing order with respect to finishing time       *
 * A - vector<vector<Node*> > - an adjacency list                                                        *
 * v - Node* - the start node for the DFS                                                               *
 * &L - vector<Node*> - a list of nodes to be filled in decreasing order with respect to finishing time *
 * ******************************************************************************************************/


void DFSSCC(vector<vector<Node*> > A, Node* u, vector<Node*> &L){
  for (int i = 0; i < A[u->id].size(); i++) {
    Node* v = A[u->id][i];
   if(v->visited == false){
     v->visited = true;
     DFSSCC(A, v, L);
   }
  }
    L.push_back(u);
    return;
  }


/******************************************************************************************************************
 * A variation of DFS for the second pass over a graph looking for strongly connected components.                 *
 * There are three goals (1) to label nodes with a SCC id (2) to generate nodes of a SCC metagraph (3) and to     *
 * determine which nodes in this metagraph have incoming and outgoing edges.                                      *
 * A - vector<vector<Node*> > - an adjacency list representing the transpose or edge reverse of the original graph *
 * v - Node* - the start node for the DFS                                                                         *
 * scc - int - the current strongly connected component id                                                        *
 * &SCCs - vector<SCCNode*> - the nodes of a SCC metagraph                                                        *
 ******************************************************************************************************************/
void DFSAssign(vector<vector<Node*> > A, Node* v, int scc, vector<SCCNode*> &SCCs){
    //YOUR CODE HERE

    //so confused
}

/******************************************************************************************************
 * Find the strongly connected components (SCCs) of a graph. The SCC of each Node is added to the SCC *
 * member of the Node struct. In addition, a vector of SCCNode* is returned.                          *
 * A - vector<vector<Node*> > - an adjacency list                                                      *
 * return - vector<SCCNode*> - a vector of nodes in the SCC metagraph of A                            *
 * ****************************************************************************************************/
vector<SCCNode*> SCC(vector<vector<Node*> > A){
  vector<SCCNode*> SCCs;
  vector<vector<Node*> > gR = reverseEdges(A);
  for (int i = 0; i < A[0].size(); i++) {
    cout<<A[0][i]->SCC<<endl;
    cout<<A[0].size()<<endl;
    if(A[0][i]->SCC == -1){
      vector<Node *> L;
      vector<Node*> L2;
      DFSSCC(A, A[0][i], L);
      DFSSCC(gR, A[0][i], L2);
      for (int u = 0; u < A[0].size(); u++) {
        if(gR[0][u]->visited && A[0][u]->visited){
          A[0][u]->SCC = A[0][i]->id;
          SCCNode* temp = new SCCNode;
          temp->id = A[0][i]->id;
          SCCs.push_back(temp);
          cout<<"assigning node "<<A[0][u]->id<<" to "<<A[0][i]->id<<endl;
        }
      }
    }
  }
  return SCCs;
//   function SCCGraph ( G )
// for v ∈ G
// v . SCC = NULL
// GR = reverseEdges ( G )
// for v ∈ G
// if v . SCC = NULL
// DFS (G , v )
// DFS (GR , v )
// for u ∈ G
// if u . visited = True and uR . visited = True
// u . SCC = v
// return G
}

/************************************************************************************************
 * Given the adjacency list representation of a graph, print the number of nodes that belong to *
 * the three sets A, B, and C as described in assignment 1                                      *
 * A - vector<vector<Node*> > - an adjacency list                                                *
 * **********************************************************************************************/
void printSetSizes(vector<vector<Node*> > A){
  vector<Node *> L;
  vector<SCCNode*> scc = SCC(A);
  for (int i = 0; i < scc.size(); i++) {
    cout<<scc[i]->id<<endl;
  }
}

int main(){
    //get the number of nodes and number of edges from cin separated by a space
    int n = -1, m = -1;
    cin >> n >> m;

    //add the nodes to an adjacency list
    //note that A[0] is a list of nodes with a dummy node in A[0][0]
    //this means that A[i] is the node with id i where ids start at 1
    vector<vector<Node*> > A(n+1);
    A[0].push_back(new Node());
    for (int i=1; i<n+1; i++){
        Node* v = new Node();
        v->id = i;
        v->SCC = -1;
        v->visited = false;
        A[0].push_back(v);
    }

    //get edges from cin and add them to the adjacency list
    //the start and end of a single edge are on the same line separated by a space
    int u = -1, v = -1;
    for (int i=0; i<m; i++){
        cin >> u >> v;
        A[u].push_back(A[0][v]);
    }

    //call printSetSizes to determine the size of the sets A, B, and C and print the results
    printSetSizes(A);

    return 0;
}
