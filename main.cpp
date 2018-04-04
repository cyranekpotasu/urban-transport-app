#include <iostream>
#include <iomanip>

using namespace std;

int n;                   // Liczba wierzchołków
char ** A;               // Macierz sąsiedztwa
bool * visited;          // Tablica odwiedzin

// Rekurencyjna procedura przejścia w głąb
//----------------------------------------
void DFS(int v)
{
  int i;

  visited[v] = true;     // Zaznaczamy węzeł jako odwiedzony
  cout << setw(3) << v;  // Przetwarzamy węzeł (wypisujemy jego numer)

// Rekurencyjnie odwiedzamy nieodwiedzonych sąsiadów

  for(i = 0; i < n; i++)
    if((A[v][i] == 1) && !visited[i]) DFS(i);
}
int main() {
    int m,i,j,v1,v2;

  cin >> n >> m;         // Czytamy liczbę wierzchołków i krawędzi

  A = new char * [n];    // Tworzymy tablicę wskaźników
  visited = new bool[n]; // Tworzymy tablicę odwiedzin

  for(i = 0; i < n; i++)
    A[i] = new char[n];  // Tworzymy wiersze

  // Macierz wypełniamy zerami

  for(i = 0; i < n; i++)
  {
    visited[i] = false;  // Zerujemy tablicę odwiedzin
    for(j = 0; j < n; j++) A[i][j] = 0;
  }

  // Odczytujemy kolejne definicje krawędzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzchołek startowy i końcowy krawędzi
    A[v1][v2] = 1;      // Krawędź v1->v2 obecna
  }

  cout << endl;

  // Przechodzimy graf w głąb

  DFS(0);

  // Usuwamy macierz

  for(i = 0; i < n; i++) delete A[i];
  delete [] A;
  delete [] visited;

  cout << endl;

    
    return 0;
}