#include "the7.h"

// do not add extra libraries here

const int INF = 1e9; // Set a large value to represent infinity
void get_infection_scores(const std::vector<std::vector<std::pair<int, int>>>& network,
                          std::vector<float>& infection_scores)
{
     int n = network.size();
    std::vector<std::vector<int>> shortest_paths;
    shortest_paths.assign(n, std::vector<int>(n, INF));

    // Initialize shortest_paths with network
    for(int i = 0; i < n; ++i) {
        shortest_paths[i][i] = 0;
        for(auto &edge : network[i]) {
            int j = edge.first;
            int w = edge.second;
            shortest_paths[i][j] = w;
        }
    }
    
    int max_shortest_distance=0;
    // Floyd-Warshall algorithm
    for(int k = 0; k < n; ++k) {
        
        
        for(int i = 0; i < n; ++i) 
        {
            double temp =0;
            for(int j = 0; j < n; ++j) 
            {
                if((shortest_paths[i][j] > (shortest_paths[i][k] + shortest_paths[k][j]))) 
                {
                    shortest_paths[i][j] =  shortest_paths[i][k] + shortest_paths[k][j];
                }
                if( shortest_paths[i][j] != INF && max_shortest_distance<shortest_paths[i][j])
                {
                   max_shortest_distance = shortest_paths[i][j] ;
                }
            }
        }
        
        
    }

    for(int i = 0; i < n;i++)
    {
        double temp =0;
        for(int j = 0; j < n;j++)
        {
            if(shortest_paths[i][j] == INF)
            {
                temp += max_shortest_distance+1;
            }
            else if(i != j)
            {
                temp +=shortest_paths[i][j];
            }
        }
        infection_scores.push_back(1/(temp/(n-1)));
    }
}
