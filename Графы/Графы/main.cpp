//
//  main.cpp
//  Графы
//
//  Created by Хто Я on 22.12.2022.
//

#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int src, dest, weight;
    char orient;
};
 
typedef pair<int, int> Pair;

class Graph
{
public:
    vector<vector<Pair>> adjList;
    vector<vector<int>> adjList1;
 
    Graph(vector<Edge> const &edges, int n, char orient)
    {
        adjList.resize(n);
 
        for (auto &edge: edges)
        {
            if (orient == 'y')
                adjList[edge.src].push_back(make_pair(edge.dest, edge.weight));
            else
            {
                adjList[edge.src].push_back(make_pair(edge.dest, edge.weight));
                adjList[edge.dest].push_back(make_pair(edge.src, edge.weight));
            }
        }
    }
    
    Graph(vector<Edge> const &edges1, int n)
    {
        adjList1.resize(n);
     
        for (auto &edge: edges1)
            adjList1[edge.src].push_back(edge.dest);
    }
};

void addEdge(vector<Edge> &edges)
{
    Edge lol;
    
    cout << endl << " Вводите смежные вершины:" << endl << "  > ";
    cin >> lol.src;
    cout << "  > ";
    cin >> lol.dest;
    cout << "  > ";
    cin >> lol.weight;
        
    edges.push_back(lol);
}

void printGraph(Graph const &graph, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "  " << i << " -> ";
        for (Pair v: graph.adjList[i])
            cout << v.first << ", ";
        cout << endl;
    }
}

void DFS(Graph const &graph1, int v, vector<bool> &discovered, vector<int> &departure, int &time)
{
    discovered[v] = true;
 
    for (int u: graph1.adjList1[v])
    {
        if (!discovered[u])
            DFS(graph1, u, discovered, departure, time);
    }
 
    departure[v] = time++;
    //cout << v;
}

bool isDAG(Graph const &graph1, int n)
{
    vector<bool> discovered(n);
    vector<int> departure(n);
    int time = 0;
 
    for (int i = 0; i < n; i++)
    {
        if (!discovered[i])
            DFS(graph1, i, discovered, departure, time);
    }
    cout << endl << " Глубина графа: " << time << endl;
 
    for (int u = 0; u < n; u++)
    {
        for (int v: graph1.adjList1[u])
        {
            if (departure[u] <= departure[v])
                return false;
        }
    }

    return true;
}
 
int main()
{
    int node, conect;
    char orient = ' ';
    vector<Edge> edges = {
        {0, 1, 4}, {0, 3, 6}, {1, 2, 3}, {1, 3, 10}, {3, 2, 6}, {3, 4, 13}, {3, 0, 5}, {5, 6, 1}, {6, 3, 2}
    };
    /* = {
        {0, 1, 4}, {0, 3, 6}, {1, 2, 3}, {1, 3, 10}, {3, 2, 6}, {3, 4, 13}, {5, 6, 1}, {6, 3, 2}, {5, 4, 9}
    };*/
    
    cout << endl << " Кол-во вершин:" << endl << "  > ";
    cin >> node;
    cout << endl << " Кол-во ребер:" << endl << "  > ";
    cin >> conect;
    cout << endl << " Граф ориентированный (y/n)?" << endl << "  > ";
    cin >> orient;
    
    /*for (int i = 0; i < conect; i++) {
        addEdge(edges);
    }*/
    cout << endl << "--------------------------------" << endl;
 
    Graph graph(edges, node, orient);
 
    cout << endl << " Вывод списка смежных вершин графа:" << endl;
    printGraph(graph, node);
    
    vector<Edge> edges1 = edges;
    
    Graph graph1(edges1, node);
    
    if (isDAG(graph1, node))
        cout << endl << " Граф ациклический!" << endl << endl;
    else
        cout << endl << " Граф не ациклический!" << endl << endl;
 
    return 0;
}
