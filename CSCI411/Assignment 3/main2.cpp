// CSCI 411 - Fall 2020
// Assignment 3 Skeleton
// Author: Carter Tillquist
// Feel free to use all, part, or none of this code for the coding problem on assignment 3.

#include <iostream>
#include <vector>
using namespace std;

/*****************************************************************************************
 * A simple struct to keep track of subproblem solutions                                 *
 * numCoins - int - the total number of coins required to solve a subproblem             *
 * lastCoin - int - the denomination of the last node added to arrive at this solution   *
 *                  notice that, in the context of an array of subproblems R where loc   *
 *                  is the index of this ChangeCell, loc-lastCoin is the position of the *
 *                  subproblem on which this solution is based                           *
 * ***************************************************************************************/
struct ChangeCell{
  int numCoins;
  int lastCoin;
};

/*****************************************************************************************************
 * Given a target amount of money and a vector of available coin denominations, determine the number *
 * of each coin denomination required to reach the target such that the total number of coins used   *
 * is minimized                                                                                      *
 * target - int - the target amount of money                                                         *
 * coins - vector<int> - a vector of integers representing available coin denominations. Assume that *
 *                       these denominations are sorted from least to greatest                       *
 * return - vector<int> - a vector of integers of the same size as coins representing the number of  *
 *                        each type of coin required to reach the target                             *
 * ***************************************************************************************************/
vector<int> makeChange(int target, vector<int> coins){
  vector<ChangeCell >tracker;
  int upBound = target + 1;
  int tempBound = coins.size()+1;

  ChangeCell baseCase;
  baseCase.numCoins = 0;
  baseCase.lastCoin = -1;
  tracker.push_back(baseCase);
  for (int i = 0; i < target; i++) {
    ChangeCell value;
    value.numCoins = upBound;
    value.lastCoin = 0;
    tracker.push_back(value);
  }
  //i use i a lot in for loops haha
  for (int i = 1; i < upBound; i++) {
    for (int j = 0; j < coins.size(); j++) {
      if(i >= coins[j]){
        //set list to the least of two lists
        if(tracker[i-coins[j]].numCoins+1 < tracker[i].numCoins){
          tracker[i].numCoins = tracker[i-coins[j]].numCoins+1;
          tracker[i].lastCoin = j;
        }
      }
    }
  }

  //assemble the list now from back pointers
  vector<int> results(coins.size(), 0);
  int index = target;
  ChangeCell current = tracker[target];
  if(current.numCoins < upBound){
    while (current.lastCoin != -1) {
      results[current.lastCoin]++;
      target -= coins[current.lastCoin];
      current = tracker[target];
    }
  } else{
    cout<<"bitchass"<<endl;
  }
  return results;

}

int main(){
  //get the number of coin denominations and the number of target amounts
  int n = -1, m = -1;
  cin >> n >> m;

  //collect the available coin denominations in a vector
  vector<int> coins;
  int v = -1;
  for (int i = 0; i < n; i++){
    cin >> v;
    coins.push_back(v);
  }

  //determine the number of each type of coin required for each target amount
  for (int i = 0; i < m; i++){
    int target = -1;
    cin >> target;
    vector<int> results = makeChange(target, coins);
    for (int j = 0; j < results.size()-1; j++){
      cout << results[j] << " ";
    }
    cout << results[results.size()-1] << endl;
  }

  return 0;
}
