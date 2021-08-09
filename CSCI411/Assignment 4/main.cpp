// CSCI 411 - Fall 2020
// Assignment 4 Skeleton
// Author: Carter Tillquist
// Feel free to use all, part, or none of this code for the coding problem on assignment 4

#include <iostream>
#include <vector>
#include <string>
using namespace std;



/*******************************************************************************************
 * A simple struct to describe alignments. Insertions are denoted with an underscore ("_") *
 * a, b - strings - two strings representing an alignment. The strings being aligned may   *
 *                - be extracted by removing underscores                                   *
 * score - float - the score of the alignment given costs associated with insertions,      *
 *                 deletions, and substitutions                                            *
 * *****************************************************************************************/
struct Alignment{
  string a;
  string b;
  float score;
};

/***************************************************************************************
 * A simple struct to keep track of subproblem solutions                               *
 * act - string - the action taken to reach this Cell: "match", "ins", "del", or "sub" *
 * score - float - the score of the alignment of prefixes up to this point given costs *
 *                 associated with insertions, deletions, and substitutions            *
 * *************************************************************************************/
struct Cell{
  string act;
  float score;
};
void myMin(int i, int j, vector<vector<Cell> > &dp, float ins, float del, float sub);


/*************************************************************************************
 * Given two strings a and b along with costs associated with insertions, deletions, *
 * and substitutions, find an optimal alignment (of minimum cost) of a and b         *
 * a, b - strings - two strings for which we want an alignment                       *
 * ins, del, sub - floats - the cost of performing insertion, deletion, and          *
 *                          substitution opertations respectively on string a        *
 * return - Alignment* - an optimal alignment of a and b given the matrix T along    *
 *                       with the score or cost of the alignment                     *
 * ***********************************************************************************/
Alignment* editDistance(string a, string b, float ins, float del, float sub){
  vector<vector<Cell> > dp;
  //make the base array
  for (int i = 0; i <= a.size(); i++) {//size+1 because of base case
    vector<Cell> inner(b.size()+1); //because of base case
    dp.push_back(inner);
  }
  //base case
  dp[0][0].act = "match";
  dp[0][0].score = 0;

  //fill b = null to save run time
  for(int i = 1; i < a.size()+1; i++){
    dp[i][0].act = "del";
    dp[i][0].score = dp[i-1][0].score + del;
  }

  //fill a = null to save run time
  for(int i = 1; i < b.size()+1; i++){
    dp[0][i].act = "ins";
    dp[0][i].score = dp[0][i-1].score + ins;
  }

  //meat and potatoes
  for (int i = 1; i < a.size()+1; i++) {
    for(int j = 1; j < b.size()+1; j++){
      if(a[i-1] == b[j-1]){//i-1, j-1 because of base case in dp array
        dp[i][j].act = "match";
        dp[i][j].score = dp[i-1][j-1].score;
      } else {
        myMin(i, j, dp, ins, del, sub);
      }
    }
  }

  //back track
  int indexX = a.size();
  int indexY = b.size();
  Cell current = dp[indexX][indexY];
  Alignment *product = new Alignment;
  product->score = current.score;
  string myA = "";
  string myB = "";
  while(indexX > 0 || indexY > 0){
    //cout<<indexX<<" "<<indexY<<endl;
    string curAct = current.act;
    if(curAct == "match" || curAct == "sub"){
      myA.insert(myA.begin(), a[indexX-1]);
      myB.insert(myB.begin(), b[indexY-1]);
      indexX--;
      indexY--;
    } else if(curAct == "ins"){
      myA.insert(myA.begin(), '_');
      myB.insert(myB.begin(), b[indexY-1]);
      indexY--;
    } else if(curAct == "del"){
      myA.insert(myA.begin(), a[indexX-1]);
      myB.insert(myB.begin(), '_');
      indexX--;
    }
    current = dp[indexX][indexY];

  }
  product->a = myA;
  product->b = myB;
  return product;
}

void myMin(int i, int j, vector<vector<Cell> > &dp, float ins, float del, float sub){
  if(dp[i-1][j-1].score + sub <= dp[i-1][j].score + del){
    if(dp[i-1][j-1].score + sub <= dp[i][j-1].score + ins){
      dp[i][j].act = "sub";
      dp[i][j].score = dp[i-1][j-1].score + sub;
    } else {
      dp[i][j].act = "ins";
      dp[i][j].score = dp[i][j-1].score + ins;
    }
  } else {
    if(dp[i][j-1].score + ins < dp[i-1][j].score + del){
      dp[i][j].act = "ins";
      dp[i][j].score = dp[i][j-1].score + ins;
    } else{
      dp[i][j].act = "del";
      dp[i][j].score = dp[i-1][j].score + del;
    }
  }
}

int main(){
  //get the number of tests
  int n = -1;
  cin >> n;

  //get the costs associated with insertions, deletions, and substitutions
  int ins = -1, del = -1, sub = -1;
  cin >> ins >> del >> sub;

  //for each test, print the resulting alignment along with its score
  for (int i = 0; i < n; i++){
    string a = "", b = "";
    cin >> a >> b;

    Alignment* align = editDistance(a, b, ins, del, sub);
    cout << align->a << endl;
    cout << align->b << endl;
    cout << align->score << endl;
  }

  return 0;
}
