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
  vector<vector<int> >tracker;
  int upBound = target + 1;
  int tempBound = coins.size()+1;
  int max = coins[coins.size()-1];//for dynamically changing the array

  vector<int>baseCase(coins.size()+1, 0);
  baseCase[0] = 0;//0 money is 0 coins
  tracker.push_back(baseCase);
  //i use i a lot in for loops haha
  for (int i = 1; i < upBound; i++) {
    int ref = i;
    bool overStepped = false;
    if(i >= max){//max size of list is largest coin value to save space
      ref = max;
      overStepped = true;
    }
    vector<int> current(coins.size()+1, 0);
    current[0] = upBound;
    for (int j = 0; j < coins.size(); j++) {
      if(ref >= coins[j]){
        //set list to the least of two lists
        if(tracker[ref-coins[j]][0]+1 < current[0]){
          current = tracker[ref-coins[j]];
          current[0]++;//add one more TOTAL coins
          current[j+1]++;//add one more coin!
        }
      }
    }
    tracker.push_back(current);
    if(overStepped){//this deletes the first element in the list to save space
      tracker.erase(tracker.begin());
    }
  }

  vector<int> result = tracker[tracker.size()-1];
  result.erase(result.begin());
  return result;

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
