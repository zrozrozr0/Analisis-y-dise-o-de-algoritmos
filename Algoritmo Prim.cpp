#include<bits/stdc++.h>
using namespace std;

#define V 9		//No. de vertices

int selectMinVertex(vector<int>& value,vector<bool>& setMST)
{
	int minimum = INT_MAX;
	int vertex;
	for(int i=0;i<V;++i)
	{
		if(setMST[i]==false && value[i]<minimum)
		{
			vertex = i;
			minimum = value[i];
		}
	}
	return vertex;
}

void findMST(int graph[V][V])
{
	int parent[V];		//guarda el arbol o MST
	vector<int> value(V,INT_MAX);	//se usa para relacionar los bordes o aristas
	vector<bool> setMST(V,false);	//verdadero si - Vertex se incluye en el MST

	//Asumiendo que iniciamos en el nodo 0
	parent[0] = -1;	//iniciamos el nodo
	value[0] = 0;	//el nodo que tenga valor 0 se fija como el primero
	//Form MST with (V-1) edges
	for(int i=0;i<V-1;++i)
	{
		//se aplica el metodo voraz
		int U = selectMinVertex(value,setMST);
		setMST[U] = true;	//se incluye un nuevo vertex en el mst o arbol

		//se buscan las aristas y aun no se unen al arbol
		for(int j=0;j<V;++j)
		{
			/*  condiciones:-
			      1.arista se presenta como U a j.
			      2.Vertice no se incluye aun en el mst
			      3.el peso del arista es menor que el peso del vertice
			*/
			if(graph[U][j]!=0 && setMST[j]==false && graph[U][j]<value[j])
			{
				value[j] = graph[U][j];
				parent[j] = U;
			}
		}
	}
	//imprime el arbol o MST
	for(int i=1;i<V;++i)
		cout<<"U->V: "<<parent[i]<<"->"<<i<<"  wt = "<<graph[parent[i]][i]<<"\n";
}

int main()
 { 					 
  int graph[V][V] = { /* 0  1  2  3  4  5  6  7  8 */
				/*0*/	{0, 4, 0, 0, 0, 0, 0, 8, 0},
				/*1*/	{4, 0, 8, 0, 0, 0, 0, 11,0},
				/*2*/	{0, 8, 0, 7, 0, 4, 0,  0,2},
				/*3*/	{0, 0, 7, 0, 9, 14, 0, 0,0},
				/*4*/	{0, 0, 0, 9, 0, 10, 0, 0,0},
				/*5*/	{0, 4, 0, 14, 10, 0,2 ,0,0},
				/*6*/	{0, 0, 0, 0, 0, 2, 0, 1 ,6},
				/*7*/	{8, 11, 0, 0, 0, 0, 0, 0,8},
				/*8*/	{0, 0, 2, 0, 0, 0, 1, 7 ,0}};

	findMST(graph);	
	return 0;
}

