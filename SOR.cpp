#include <cstdio>

using namespace std;

#define MAX 1000

// 0 - końcowa liczba jest na początku
// 1 - końcowa liczba jest na końcu
int t[MAX], tab[MAX][MAX][2], n;

void wczytaj_dane() {
   scanf("%d", &n);
   for (int i = 0; i < n; i++) {
      scanf("%d", &t[i]);
   }
}

void oblicz(int i, int j) {
   if (t[i] < t[i + 1]) tab[i][j][0] += tab[i + 1][j][0];
   if (t[i] < t[j]) tab[i][j][0] += tab[i + 1][j][1];
   tab[i][j][0] = tab[i][j][0] % (int)1e9;
   if (t[j] > t[i]) tab[i][j][1] += tab[i][j - 1][0];
   if (t[j] > t[j - 1]) tab[i][j][1] += tab[i][j - 1][1];
   tab[i][j][1] = tab[i][j][1] % (int)1e9;
}

void wypelnij_tabele() {
   for (int i = 0; i < n; i++) {
      tab[i][i][0] = 1;
      tab[i][i][1] = 0;
   }
   int j = 1;
   for (int k = 1; k < n; k++) {
      for (int j = k; j < n; j++) {
         //printf("%d, %d\n", j - k, j);
         oblicz(j - k, j);
      }
   }
}

int main() {
   wczytaj_dane();
   wypelnij_tabele();
   printf("%d\n", (tab[0][n - 1][0] + tab[0][n - 1][1]) % (int)1e9);
   return 0;
}


