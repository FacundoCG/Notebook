// bellmanFord retorna un bool indicando si hay un ciclo negativo que es alcanzable desde v. Además, calcula la minima distancia desde v al resto de vértices
// Es útil cuando tenemos un grafo con aristas de peso negativo
// Suponemos que las distancias originalmente valen INF para todo vértice
bool bellmanFord(int v, int n, vector<pair<ll, edge>> &edges, vector<ll> &distances){
    distances[v] = 0;
    int m = edges.size();
    bool res = false;
	
	// Calculo las distancias
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++){
            ll weight = edges[j].first;
            edge e = edges[j].second;
            int w = e.first;
            int u = e.second;

            if (distances[w] != INF){ // Si estaba definida la distancia a este vértice
                ll newDistance = (ll) distances[w] + weight; 
                distances[u] = min(distances[u], newDistance);
            }
        }
    }
	
	// Chequeo si existe un ciclo negativo
    for (int j = 0; j < m; j++){
        ll weight = edges[j].first;
        edge e = edges[j].second;
        int w = e.first;
        int u = e.second;

        if (distances[w] != INF){
            ll newDistance = (ll) distances[w] + weight;
            if (newDistance < distances[u]){
                res = true;
                break;
            }
        }
    }

    return res;
}

// Es importante notar que tenemos que haber eliminado previamente todos los vertices y aristas que no son alcanzables desde v en el grafo transpuesto. Esto es porque podría haber un ciclo negativo en el grafo pero que no sea parte de los caminos de v a otro vértice.
