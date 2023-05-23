#include <iostream>
#include <omp.h>
#include <bits/stdc++.h>

using namespace std;

class Graph
{
public:
    int vertices = 6;
    int edges = 5;

    vector<vector<int>> graph = {{1}, {0, 2, 3}, {1, 4, 5}, {1, 4}, {2, 3}, {2}};
    vector<bool> visited;

    void printGraph()
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << i << " -> ";
            for (auto j = graph[i].begin(); j != graph[i].end(); j++)
            {
                cout << *j << " ";
            }
            cout << endl;
        }
    }

    void initializeVisited()
    {
        visited.assign(vertices, false);
    }

    void dfs(int i)
    {
        stack<int> s;
        s.push(i);
        visited[i] = true;

        while (s.empty() != true)
        {
            int current = s.top();
            cout << current << " ";
            s.pop();
            for (auto j = graph[current].begin(); j != graph[current].end(); j++)
            {
                if (visited[*j] == false)
                {
                    s.push(*j);
                    visited[*j] = true;
                }
            }
        }
    }

    void parallel_dfs(int i)
    {
        stack<int> s;
        s.push(i);
        visited[i] = true;

        while (s.empty() != true)
        {
            int current = s.top();
            cout << current << " ";
#pragma omp critical
            s.pop();

#pragma omp parallel for
            for (auto j = graph[current].begin(); j != graph[current].end(); j++)
            {
                if (visited[*j] == false)
                {
#pragma omp critical
                    s.push(*j);
                    visited[*j] = true;
                }
            }
        }
    }

    void bfs(int i)
    {
        queue<int> q;
        q.push(i);
        visited[i] = true;

        while (!q.empty())
        {
            int current = q.front();
            cout << current << " ";
            q.pop();

            for (auto j = graph[current].begin(); j != graph[current].end(); j++)
            {
                if (visited[*j] == false)
                {
                    q.push(*j);
                    visited[*j] = true;
                }
            }
        }
    }

    void parallel_bfs(int i)
    {
        queue<int> q;
        q.push(i);
        visited[i] = true;

        while (!q.empty())
        {
            int current = q.front();
            cout << current << " ";

#pragma omp critical
            q.pop();

#pragma omp parallel for
            for (auto j = graph[current].begin(); j != graph[current].end(); j++)
            {
                if (visited[*j] == false)
                {
                    q.push(*j);
                    visited[*j] = true;
                }
            }
        }
    }
};

int main()
{
    Graph g;
    cout << "Adjacency List: " << endl;
    g.printGraph();

    g.initializeVisited();
    cout << "DFS: " << endl;
    auto start = chrono::high_resolution_clock::now();
    g.dfs(0);
    cout << endl;
    auto end = chrono::high_resolution_clock::now();
    cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    g.initializeVisited();
    cout << "Parallel DFS: " << endl;
    start = chrono::high_resolution_clock::now();
    g.parallel_dfs(0);
    cout << endl;
    end = chrono::high_resolution_clock::now();
    cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    g.initializeVisited();
    cout << "BFS: " << endl;
    start = chrono::high_resolution_clock::now();
    g.bfs(0);
    cout << endl;
    end = chrono::high_resolution_clock::now();
    cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    g.initializeVisited();
    cout << "Parallel BFS: " << endl;
    start = chrono::high_resolution_clock::now();
    g.parallel_bfs(0);
    cout << endl;
    end = chrono::high_resolution_clock::now();
    cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
}
