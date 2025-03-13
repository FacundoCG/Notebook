// Time Complexity: O(|E|*log(|E|))
// Obs: I don't need the adjList if I can work with the number of vertices
// Obs: I suppose that the edges are already sorted for all the methods.

// Normal Kruskal
void kruskal(int n, vector<pair<int, edge>> &edges){
    DisjSet trees(n);
    
    for (auto &p: edges){
        edge e = p.second;
        int weight = p.first;
        int v = e.first;
        int u = e.second;

        if (trees.find(u) != trees.find(v)){ 
            trees.Union(v, u);
        }
    }
}

// This algorithm calculates the weight of an AGM.
ll weightOfAGM(int n, vector<pair<ll, edge>> &edges){
    ll res = 0;
    DisjSet trees(n);
    
    for (auto &p: edges){
        edge e = p.second;
        ll weight = p.first;
        int v = e.first;
        int u = e.second;

        if (trees.find(u) != trees.find(v)){
            res += weight; 
            trees.Union(v, u);
        }
    }

    return res;
}
