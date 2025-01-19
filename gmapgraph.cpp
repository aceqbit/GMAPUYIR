#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, 
                         unordered_map<int, pair<int, int>> &restrictions, 
                         int src, int vehicleWeight, int vehicleHeight,unordered_map<int,int>&fuel) {
        int V = adj.size(); 
        vector<int> disTo(V, INT_MAX); 
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 

        disTo[src] = 0;       
        pq.push({0, src});    

        while (!pq.empty()) {
            int d = pq.top().first; 
            int n = pq.top().second; 
            pq.pop();

            if (d > disTo[n]) continue;

            for (auto it : adj[n]) {
                int v = it.first; 
                int w = it.second; 

                int newDist = d + w; 

                if (restrictions.count(v)) {
                    int maxWeight = restrictions[v].first;
                    int maxHeight = restrictions[v].second;

                    if (vehicleWeight > maxWeight || vehicleHeight > maxHeight) {
                        newDist += 100;
                    }
                }
                if (fuel.count(v)){
                    int fl=fuel[v];
                    
                    if(fl==0){
                        newDist+=150;
                    }
                }
                if (newDist < disTo[v]) {
                    disTo[v] = newDist;
                    pq.push({newDist, v});
                }
            }
        }
        return disTo;
    }
};

int main() {
    vector<vector<pair<int, int>>> adj = {
        {{1, 5}, {2, 10}}, 
        {{2, 3}, {3, 8}},  
        {{3, 2}, {4, 4}},  
        {{5, 6}},          
        {{5, 3}},          
        {}                
    };

    unordered_map<int, pair<int, int>> restrictions = {
        {2, {10, 4}},  
        {3, {5, 3.5}}, 
        {4, {15, 4.2}} 
    };
    unordered_map<int,int>fuel={
        {0,1},
        {1,2},
        {2,0},
        {3,1},
        {4,2},
    };
    
    int vehicleWeight = 12;
    int vehicleHeight = 4;  

    Solution sol;

    vector<int> distances = sol.dijkstra(adj, restrictions, 0, vehicleWeight, vehicleHeight,fuel);

    cout << "Shortest distances from node 0 to all other nodes:" << endl;
    for (int i = 0; i < distances.size(); ++i) {
        if (distances[i] == INT_MAX) {
            cout << "Node " << i << ": No path" << endl;
        } else {
            cout << "Node " << i << ": " << distances[i] << " km" << endl;
        }
    }
    cout<<"shortest distance from startting position to target is "<<distances[distances.size()-1];
    return 0;
}
