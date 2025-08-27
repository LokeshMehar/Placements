#include <bits/stdc++.h>
using namespace std;

string addStrings(string num1, string num2) {
	string result = "";
	int carry = 0;
	int i = num1.length() - 1;
	int j = num2.length() - 1;
	
	while (i >= 0 || j >= 0 || carry) {
		int sum = carry;
		if (i >= 0) sum += num1[i--] - '0';
		if (j >= 0) sum += num2[j--] - '0';
		
		result = char(sum % 10 + '0') + result;
		carry = sum / 10;
	}
	
	return result;
}

string fibbo(int n, vector<string>& dp) {
	if (n == 1 || n == 2) {
		return "1";
	}
	if (dp[n] != "-1") return dp[n];
	
	return dp[n] = addStrings(fibbo(n-1, dp), fibbo(n-2, dp));
}

int main() {
	int n;
	cin >> n;
	cout << endl;
	vector<string> dp(n+1, "-1");
	cout << fibbo(n, dp);
	return 0;
}
