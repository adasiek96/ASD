#include <cstdio>
#include <iostream>
using namespace std;

#define MAX (int)1e6

int n, m, c[MAX], z[MAX];
unsigned long long t[MAX];
int w[4][MAX];

void wczytaj_dane() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &c[i]);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) scanf("%d", &z[i]);
}

void utworz_sumy_czesciowe() {
	t[n - 1] = c[n - 1];
	for (int i = n - 2; i >= 0; i--) t[i] = c[i] + t[i + 1];
}

void utworz_max_min_n_parz() {
	w[0][0] = -1;
	w[2][0] = -1;
	for (int i = 1; i < n; i++) {
		if (c[i - 1] % 2 != 0) {
			w[0][i] = c[i - 1];
			w[2][i] = w[2][i - 1];
		}
		else {
			w[0][i] = w[0][i - 1];
			w[2][i] = c[i - 1];
		}
	}
	
	if (c[n - 1] % 2 != 0) {
		w[1][n - 1] = c[n - 1];
		w[3][n - 1] = -1;
	}
	else {
		w[1][n - 1] = -1;
		w[3][n - 1] = c[n - 1];
	}
	for (int i = n - 2; i >= 0; i--) {
		if (c[i] % 2 != 0) {
			w[1][i] = c[i];
			w[3][i] = w[3][i + 1];
		}
		else {
			w[1][i] = w[1][i + 1];
			w[3][i] = c[i];
		}
	}
}

int roznica(int i) {
	int x, y;
	if (w[3][i] == -1 || w[0][i] == -1) x = -1;
	else x = w[3][i] - w[0][i];
	if (w[1][i] == -1 || w[2][i] == -1) y = -1;
	else y = w[1][i] - w[2][i];
	
	if (x == -1 && y == -1) return -1;
	else if (x == -1) return y;
	else if (y == -1) return x;
	else return min(x, y);
}

void odpowiedz() {
	for (int i = 0; i < m; i++) {
		if (t[n - z[i]] % 2 == 1) cout << t[n - z[i]] << endl;
		else if (roznica(n - z[i]) == -1) cout << -1 << endl;
		else cout << t[n - z[i]] - roznica(n - z[i]) << endl;
	}
}

int main() {
	wczytaj_dane();
	utworz_sumy_czesciowe();
	utworz_max_min_n_parz();
	odpowiedz();
	
	return 0;
}
