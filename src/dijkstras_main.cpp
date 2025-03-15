#include "dijkstras.h"


int main(int argc, char *argv[]) {
    string filename = get_arg(argc, argv, "src/small.txt");
    vector<int> previous;
    Graph G;
    file_to_graph(filename, G);
    vector<int> distance = dijkstra_shortest_path(G, 0, previous);
    for (int dest = 0; dest < G.numVertices; ++dest) {
        vector<int> path = extract_shortest_path(distance, previous, dest);
        print_path(path, distance[dest]);
    }
    return 0;
}