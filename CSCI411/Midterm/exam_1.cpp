#include <iostream>
#include <vector>
#include <string>
#include <algorithm>    // std::sort

using namespace std;


int LPS(string s){
  string r = s;
  int n = s.size()+1;
  reverse(s.begin(), s.end());
  int dp[n][n];
  //set first column and row to 0
  for(int i = 0; i < n; i++){
    dp[i][0] = 0;
    dp[0][i] = 0;
  }
  for(int x = 1; x < n; x++){
    for(int y = 1; y < n; y++){
      if(r[y-1] == s[x-1]){
        dp[x][y] = dp[x-1][y-1] + 1;
      } else{
        dp[x][y] = max(dp[x-1][y], dp[x][y-1]);
      }
    }
  }
  return dp[s.size()][s.size()];
}

int main(){
  //get the total number of test sequences
  int n = -1;
  cin >> n;

  //read each test sequence and print the length of the longest palindromic subsequence
  for (int i = 0; i < n; i++){
    string s = "";
    cin >> s;
    cout << LPS(s) << endl;
  }

  return 0;
}
