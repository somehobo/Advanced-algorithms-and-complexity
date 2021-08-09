// CSCI 411 - Spring 2021
// Assignment 5 Skeleton
// Author: Carter Tillquist
// Feel free to use all, part, or none of this code for the coding problem on assignment 5.

#include <iostream>
#include <vector>
#include <limits.h>
#include <cmath>
using namespace std;

/*****************************************************************************************************
 * A simple struct to keep track of the sequence of hotels visited as well as the associated penalty *
 * seq - vector<int> - the sequence of hotels visited                                                *
 * penalty - int - the penalty associated with the sequence of hotels visited                        *
 * ***************************************************************************************************/
struct TripCost{
  vector<int> seq;
  int penalty;
};


/********************************************************************************************************
 * A simple struct to keep track of the minimum penalty and previous hotel for a potential ending hotel *
 * penalty - int - the minimum penalty associated with reaching this hotel                              *
 * prev - int - the hotel visited before this one                                                       *
 * ******************************************************************************************************/
struct HotelCell{
  int penalty;
  int prev;
};

/************************************************************************************************
 * Given a sequence of hotel distances and an ideal number of miles to travel per day, return a *
 * TripCost pointer representing the sequence of hotels to visit with minimum penalty           *
 * hotels - vector<int> - the number of miles to each hotel from the starting point of the trip *
 * m - int - the ideal number of miles to travel per day                                        *
 * **********************************************************************************************/
TripCost* hotelSequence(vector<int> hotels, int m){
  vector<HotelCell> dp;

  for(int i = 0; i < hotels.size(); i++){
    HotelCell temp;
    temp.prev = 0;
    dp.push_back(temp);
  }

  dp[0].penalty = pow(m, 2); //basecase = m^2, normal case = (m-x)^2
  dp[0].prev = -1;
  for(int i = 1; i < dp.size(); i++){
    int min = pow(m - hotels[i], 2);
    int previous = 0;
    for (int j = 0; j < i; j++) {//min of all prev
      int cur = dp[j].penalty + pow(m-(hotels[i] - hotels[j]), 2);
      if(cur <= min){
        min = cur;
        previous = j;
      }
    }
    dp[i].penalty = min;
    dp[i].prev = previous;
  }

  TripCost* product = new TripCost;
  HotelCell current = dp[dp.size()-1];
  product->penalty = current.penalty;
  //time for back tracking shenanigans
  product->seq.push_back(dp.size()-1);
  while(dp[current.prev].prev != -1){
    product->seq.insert(product->seq.begin(), current.prev);
    current = dp[current.prev];
  }
  return product;

}

int main(){
  //get the total number of hotels and the ideal number of miles traveled per day
  int n = -1, m = -1;
  cin >> n >> m;

  //collect the hotel distances
  vector<int> hotels(n);
  hotels.push_back(0);
  for(int i = 1; i <= n; i++){
    int d = -1;
    cin >> d;
    hotels[i] = d;
  }

  //determine the route that minimizes the overall penalty and print out the results
  TripCost* solution = hotelSequence(hotels, m);
  for (int i = 0; i < solution->seq.size(); i++){
    cout << solution->seq[i] << " ";
  }
  cout << endl;
  cout << solution->penalty << endl;

  return 0;
}
