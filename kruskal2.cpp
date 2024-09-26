

// Kruskal's algorithm in C++

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define edge pair<int, int>

class Graph {
   private:
  vector<pair<int, edge> > G;  // grafica
  vector<pair<int, edge> > T;  // arbol
  int *parent;
  int V;  // numero de vertices o nodos en la grafica
   public:
  Graph(int V);
  void AddWeightedEdge(int u, int v, int w);
  int find_set(int i);
  void union_set(int u, int v);
  void kruskal();
  void print();
};
Graph::Graph(int V) {
  parent = new int[V];

  for (int i = 0; i < V; i++)
    parent[i] = i;

  G.clear();
  T.clear();
}
void Graph::AddWeightedEdge(int u, int v, int w) {
  G.push_back(make_pair(w, edge(u, v)));
}
int Graph::find_set(int i) {
  // si i se tiene conectado a si mismo
  if (i == parent[i])
    return i;
  else
    // se busca la conexion de i
    return find_set(parent[i]);
}

void Graph::union_set(int u, int v) {
  parent[u] = parent[v];
}
void Graph::kruskal() {
  int i, uRep, vRep;
  sort(G.begin(), G.end());  // aumenta el peso
  for (i = 0; i < G.size(); i++) {
    uRep = find_set(G[i].second.first);
    vRep = find_set(G[i].second.second);
    if (uRep != vRep) {
      T.push_back(G[i]);  // se añade al arbol
      union_set(uRep, vRep);
    }
  }
}
void Graph::print() {
  cout << "Edge :"
     << " Weight" << endl;
  for (int i = 0; i < T.size(); i++) {
    cout << T[i].second.first << " - " << T[i].second.second << " : "
       << T[i].first;
    cout << endl;
  }
}

int main() {
  Graph g(9);
  g.AddWeightedEdge(0, 1, 4);
  g.AddWeightedEdge(0, 7, 8);
  g.AddWeightedEdge(1, 2, 8);
  g.AddWeightedEdge(1, 7, 11);
  g.AddWeightedEdge(2, 3, 7);
  g.AddWeightedEdge(2, 5, 4);
  g.AddWeightedEdge(2, 8, 2);
  g.AddWeightedEdge(3, 4, 9);
  g.AddWeightedEdge(4, 5, 10);
  g.AddWeightedEdge(5, 3, 14);
  g.AddWeightedEdge(5, 6, 2);
  g.AddWeightedEdge(6, 7, 1);
  g.AddWeightedEdge(6, 8, 6);
  g.AddWeightedEdge(7, 1, 2);
  g.AddWeightedEdge(8, 9, 7);
  g.kruskal();
  g.print();
  return 0;
}
