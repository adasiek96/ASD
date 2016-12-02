#include <cstdio>

using namespace std;

#define MAX (int)3e6

struct trux {
	int l, r, counter;
	char c;
};

int n, m, l, r;
char c;
trux tab[MAX];

void wczytaj_dane() {
	scanf("%d\n%d\n", &n, &m);
}

void init(int idx, int l, int r) {
	tab[idx].c = 'C';
	tab[idx].l = l;
	tab[idx].r = r;
	tab[idx].counter = 0;
	if (l < r) {
		init(2 * idx, l, (l + r) / 2);
		init(2 * idx + 1, (l + r) / 2 + 1, r);
	}
}

void inicjuj_drzewo() {
	init(1, 1, n);
}

void insert(int idx) {
	if (r < tab[idx].l || l > tab[idx].r) return;
	if (l <= tab[idx].l && r >= tab[idx].r) {
		if (c == 'C') tab[idx].counter = 0;
		else tab[idx].counter = tab[idx].r - tab[idx].l + 1;
		tab[idx].c = c;
	}
	else {
		if (tab[idx].c != '?') {
			tab[2 * idx].c = tab[2 * idx + 1].c = tab[idx].c;
			if (tab[idx].c != 'C') {
				tab[2 * idx].counter = tab[2 * idx].r - tab[2 * idx].l + 1;
				tab[2 * idx + 1].counter = tab[2 * idx + 1].r - tab[2 * idx + 1].l + 1;
			}
			else tab[2 * idx].counter = tab[2 * idx + 1].counter = 0;
			tab[idx].c = '?';
		}
		insert(2 * idx);
		insert(2 * idx + 1);
		tab[idx].counter = tab[2 * idx].counter + tab[2 * idx + 1].counter;
	}
}

int odpowiedz() {
	insert(1);
	return tab[1].counter;
}

void wczytujac_zapytania_oblicz_wynik() {
	int w;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %c", &l, &r, &c);
		w = odpowiedz();
		printf("%d\n", w);
	}
}

int main() {
	wczytaj_dane();
	inicjuj_drzewo();
	wczytujac_zapytania_oblicz_wynik();

	return 0;
}