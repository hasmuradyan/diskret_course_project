#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool hasCycle(int currentVertex, const vector<vector<int>>& adjacencyList, vector<bool>& visited, int parent) 
{
    visited[currentVertex] = true;  //Marks the current vertex as visited.

    for (int neighbor : adjacencyList[currentVertex]) 
    {
        if (!visited[neighbor]) 
        {
            if (hasCycle(neighbor, adjacencyList, visited, currentVertex))
            {
                return true;
            }
        }
        else if (neighbor != parent)
        {
            return true;
        }
    }

    return false;
}

bool isSimpleGraph(const vector<pair<int, int>>& edges, int numVertices)
{
    vector<vector<int>> adjacencyList(numVertices);
    for (const auto& edge : edges) 
    {
        adjacencyList[edge.first].push_back(edge.second);
        adjacencyList[edge.second].push_back(edge.first);
    }

    vector<bool> visited(numVertices, false);

    for (int i = 0; i < numVertices; ++i) 
    {
        if (!visited[i])
        {
            if (hasCycle(i, adjacencyList, visited, -1))
            {
                return false;
            }
        }
    }

    return true;
}

// Function to perform Depth-First Search (DFS)
void dfs(int currentVertex, const vector<pair<int, int>>& edges, vector<int>& currentChain, vector<vector<int>>& chains) 
{
    currentChain.push_back(currentVertex);

    for (const auto& edge : edges) 
    {
        if (edge.first == currentVertex) 
        {
            dfs(edge.second, edges, currentChain, chains);
        }
    }

    chains.push_back(currentChain);
    currentChain.pop_back();
}

int main() {
    vector<pair<int, int>> edges;

    // Enter the connected vertices in pairs and in order
    cout << "Enter connected vertices (enter -1 to stop):" << endl;
    int v1, v2;
    while (true)
    {
        cin >> v1;
        if (v1 == -1) 
        {
            break;
        }
        cin >> v2;
        edges.push_back({ v1, v2 });
    }

    // Get the maximum vertex value to determine the number of vertices
    int maxVertex = 0;
    for (const auto& edge : edges) 
    {
        maxVertex = max(maxVertex, max(edge.first, edge.second));
    }
    int numVertices = maxVertex + 1;

    // Check if the graph is simple
    if (!isSimpleGraph(edges, numVertices))
    {
        cout << "The graph is not simple. It contains cycles." << endl;
        return 0;
    }

    vector<vector<int>> chains;
    vector<int> currentChain;

    // Perform DFS to find all simple chains
    for (const auto& edge : edges)
    {
        dfs(edge.first, edges, currentChain, chains);
    }

    // Find the longest simple chain
    vector<int> longestChain;
    for (const auto& chain : chains) 
    {
        if (chain.size() > longestChain.size()) 
        {
            longestChain = chain;
        }
    }

    // Output the longest chain
    cout << "Longest simple chain: ";
    for (int vertex : longestChain) 
    {
        cout << vertex << " ";
    }
    cout << endl;

    // Calculate the length of the longest chain
    int length = longestChain.size();
    cout << "Length of the longest simple chain: " << length << endl;

    return 0;
}

