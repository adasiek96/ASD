#include <iostream>

using namespace std;

#define MAX_M 500
#define MAX_N 40
#define MOD 4
#define FOR(x, n) for(int x = 0; x < n; x++)

int m, n, M[MAX_M][MAX_N], T[MOD][MAX_N][MOD][MAX_N];

void wczytaj_dane() {
	scanf("%d %d", &m, &n);
	FOR(i, m) FOR(j, n)
		scanf("%d", &M[i][j]);
}

void zainicjuj() {
	FOR(i1, m) FOR(j1, n) FOR(i2, m) FOR(j2, n) {
		if (i1 == i2 && j1 == j2) T[i1 % MOD][j1][i2 % MOD][j2] = -1;
		else if (i1 == 0 && i2 == 0) T[i1 % MOD][j1][i2 % MOD][j2] = M[i1][j1] + M[i2][j2];
	}		
}

bool istnieje(int h1, int d1, int h2, int d2) {
	if (h1 < 0 || h1 >= m) return false;
	if (h2 < 0 || h2 >= m) return false;
	if (d1 < 0 || d1 >= n) return false;
	if (d2 < 0 || d2 >= n) return false;
	return true;
}

int w_max(int w, int h1, int d1, int h2, int d2) {
	if (istnieje(h1, d1, h2, d2)) w = max(w, T[h1 % MOD][d1][h2 % MOD][d2]);
	return w;
}

// krok 2: scalanie
void scalanie(int h, int d1, int d2) {
	int w = -1, h1 = h - 1;
	for (int i1 = d1 - 2; i1 <= d1 + 2; i1++)
		for (int h2 = h - 3; h2 <= h - 2; h2++)
			for (int i2 = d2 - 1; i2 <= d2 + 1; i2++) 
				w = w_max(w, h1, i1, h2, i2);
	T[h % MOD][d1][h % MOD][d2] = w + M[h][d1] + M[h][d2];
}

void pom(int h1, int d1, int d2, int h2) {
	for (int i = d1 - 2; i <= d1 + 2; i++)
		if (istnieje(h1 + 1, i, h2, d2) && istnieje(h1, d1, h2, d2)) {
			int a = T[h1 % MOD][d1][h2 % MOD][d2] + M[h1 + 1][i];
			int *b = &(T[(h1 + 1) % MOD][i][h2 % MOD][d2]);
			*b = max(a, *b);
		}
}

// krok 1: liczenie dla pierwszej œcie¿ki
void liczenie_pierwszej(int h, int d1, int d2) {
	pom(h, d1, d2, h);
	for (int i = d1 - 2; i <= d1 + 2; i++) {
		pom(h + 1, i, d2, h);
	}
}

void wykonaj_dynamika() {
	for (int h = 0; h <= m - 2; h++)
		FOR(i, n) FOR(j, n) 
			if (i != j) {
				liczenie_pierwszej(h, i, j);
				scalanie(h + 1, i, j);
			}
}

int wynik() {
	int w = -1;
	FOR(i, n) FOR(j, n)
		w = max(w, T[(m - 1) % MOD][i][(m - 1) % MOD][j]);
	return w;
}

int main() {
	wczytaj_dane();
	zainicjuj();
	wykonaj_dynamika();
	
	cout << wynik() << endl;
//
//	FOR(h1, m) FOR(d1, n) FOR(d2, n) {
//		cout << "T(" << h1 << ", " << d1 << ", " << h1 << ", " << d2 << ") = " << T[h1][d1][h1][d2] << endl;
//	}
//	
//	scalanie(2, 3, 0);
//	cout << T[2][3][0][4] << endl;
//	cout << T[4][1][2][2] << endl;
//	cout << T[3][1][3][3] << endl;
//	cout << T[4][3][3][3] << endl;
//	cout << T[5][3][5][2] << endl;
	return 0;
}
