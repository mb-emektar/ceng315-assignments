#include "the6.h"

// do not add extra libraries here
#define INF 1000000000

int find_structure(std::vector< std::vector<std::pair<int,int> > >& bond_energies, std::vector< std::vector<std::pair<int,int> > >& lowest_energy_structure) {
    int num_nodes = bond_energies.size();
    lowest_energy_structure.clear();
    lowest_energy_structure.resize(num_nodes);

    std::vector<int> key(num_nodes, INF);
    std::vector<int> parent(num_nodes, -1);
    std::vector<bool> inMST(num_nodes, false);

    std::priority_queue< std::pair<int, int>, std::vector <std::pair<int, int>> , std::greater<std::pair<int, int>> > pq;

    key[0] = 0;
    pq.push(std::make_pair(0, 0));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto x : bond_energies[u]) {
            int v = x.first;
            int weight = x.second;

            if (inMST[v] == false && key[v] > weight) {
                key[v] = weight;
                pq.push(std::make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    int total_cost = 0;
    for (int i = 1; i < num_nodes; ++i) {
        lowest_energy_structure[parent[i]].push_back(std::make_pair(i, key[i]));
        lowest_energy_structure[i].push_back(std::make_pair(parent[i], key[i]));
        total_cost += key[i];
    }

    return total_cost;
}

void dfs(int node, int depth, int& max_depth, int& max_node, std::vector< std::vector<std::pair<int,int> > > &adjacency_list_in, std::vector<bool>& visited) {
    visited[node] = true;
    if (depth > max_depth)
        {
        max_depth = depth;
        max_node = node;
    }
    for (auto& neighbour : adjacency_list_in[node])
    {
        if (!visited[neighbour.first])
            {
            dfs(neighbour.first, depth + 1, max_depth, max_node, adjacency_list_in, visited);
        }
    }
}

int find_longest_chain(std::vector< std::vector<std::pair<int,int> > >& molecule_structure, std::vector<int>& chain){
    int n = molecule_structure.size();
    std::vector<bool> visited(n, false);
    int max_depth = -1;
    int max_node = -1;
    dfs(0, 0, max_depth, max_node, molecule_structure, visited);
    std::fill(visited.begin(), visited.end(), false);
    max_depth = -1;
    dfs(max_node, 0, max_depth, max_node, molecule_structure, visited);
    chain.resize(max_depth + 1);
    chain[max_depth] = max_node;
    for (int i = max_depth - 1; i >= 0; --i) {
        for (auto& neighbour : molecule_structure[max_node])
        {
            if (visited[neighbour.first])
            {
                chain[i] = neighbour.first;
                max_node = neighbour.first;
                break;
            }
        }
    }
    return chain.size();
}
