#include <cstdio>

using namespace std;

#define MAX_N (int)2e4 + 1
#define MAX_K 11
#define MOD (int)1e9

int n, k, T[MAX_N], INV[MAX_K][MAX_N], DRZ[2 * MAX_N], size = 1;

void wczytaj_dane() {
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) scanf("%d", &T[i]);
}

void inicjuj() {
	for (int i = 0; i < n; i++) INV[1][i] = 1;
	while (size < n) size *= 2;
}

void zeruj() {
	for (int i = 0; i < 2 * size; i++) DRZ[i] = 0;
}

int sumuj_wieksze_niz(int y) {
	int p = size + y - 1;
	unsigned long long ret = 0;
	while (p > 1) {
		if (p % 2 == 0) {
			ret += DRZ[p + 1];
			ret %= MOD;
		}
		p /= 2;
	}
	return ret;
}

void wstaw(int x, int war) {
	int p = size + x - 1;
	while (p > 0) {
		DRZ[p] += war;
		DRZ[p] %= MOD;
		p /= 2;
	}

}

void oblicz_drzewo() {
	for (int kk = 2; kk <= k; kk++) {
		for (int i = 0; i < n; i++) {
			INV[kk][i] = sumuj_wieksze_niz(T[i]);
			wstaw(T[i], INV[kk - 1][i]);
		}
		zeruj();
	}
}

void oblicz_wynik() {
	unsigned long long ret = 0;
	for (int i = 0; i < n; i++) {
		ret += INV[k][i];
		ret %= MOD;
	}
	printf("%d", ret);
}

int main() {
	wczytaj_dane();
	inicjuj();
	oblicz_drzewo();
	oblicz_wynik();
	
	return 0;
}
