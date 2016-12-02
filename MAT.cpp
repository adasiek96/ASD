#include <iostream>
#include <string>

using namespace std;

#define MAX (int)1e6

int t[MAX];

int main() {
	string s;
	getline(cin, s);
	
	int n = s.length();
	int d = MAX, idx = 0;
	while (s[idx] == '*') idx++;
	
	char c = s[idx];
	for (int i = idx + 1; i < n; i++) {
		if (s[i] != '*' && s[i] != c) {
			d = min(i - idx, d);
			idx = i;
			c = s[i];
		}
		else if (s[i] != '*' && s[i] == c) idx = i;
	}
	
	int wynik;
	if (d == MAX) wynik = 1;
	else wynik = n + 1 - d;
	
	cout << wynik << endl;
	
	return 0;
}
