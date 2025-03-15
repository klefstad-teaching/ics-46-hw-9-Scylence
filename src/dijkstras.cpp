#include "dijkstras.h"
#include <queue>


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    using Vertex = int;
    int n = G.numVertices;

    vector<int> distance(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);

    // Create Node to store in priority queue
    struct Node {
        Vertex vertex;
        int weight;
        Node(Vertex v, int w) : vertex{v}, weight{w} {}
    };
    auto compare_weight = [](const Node& a, const Node& b) {return a.weight > b.weight;};
    priority_queue<Node, vector<Node>, decltype(compare_weight)> pq(compare_weight);
    pq.push(Node(source, 0));
    
    distance[source] = 0;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        Vertex u = current.vertex;

        if (visited[u]) continue;

        visited[u] = true;

        for (const Edge& edge: G[u]) {
            Vertex v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] and distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) return path;  // If distance to dest = INF, then there's no path to dest
    for (int v = destination; v != -1; v = previous[v])
        path.push_back(v);
    int n = path.size();
    for (int i = 0; i < n/2; ++i)
        swap(path[i], path[n-i-1]);
    return path;
}

void print_path(const vector<int>& v, int total) {
    for (const int& vertex: v)
        cout << vertex << ' ';
    cout << endl << "Total cost is " << total << endl;
}
