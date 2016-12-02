#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

#define N 40000
#define M 50

int n, m;
int s[M][N];
string b[N]; // dla ka\u017cdego zawodnika ci\u0105g zerojedynkowy

void wczytaj_dane() {
   scanf("%d %d\n", &n, &m);
   int c;
   for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
         scanf("%d", &c);
         if (j != n - 1) scanf(" ");
         s[i][j] = c - 1;
      }
      if (i != m - 1) scanf("\n");
   }
}

void utworz_ciagi() {
   for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
         if (j < n / 2) b[s[i][j]] += '0';
         else b[s[i][j]] += '1';
      }
   }
}

bool posortuj_i_znajdz_te_same() {
   sort(b, b + n);
   for (int i = 0; i < n - 1; i++) if (b[i] == b[i + 1]) return false;
   return true;
}

int main() {
   wczytaj_dane();
   utworz_ciagi();
   
   if (posortuj_i_znajdz_te_same()) printf("TAK\n");
   else printf("NIE\n");
   
   return 0;
}
