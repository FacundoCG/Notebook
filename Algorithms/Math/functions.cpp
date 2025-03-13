
// Función para obtener todos los divisores de un número N
// Complejidad temporal: O(sqrt(N))
vector<ll> divisorsOf(ll N){
	vector<ll> divisors;
	ll sqrtOfN = sqrt(N);
	
	for(ll i = 1; i <= sqrtOfN; i++){
		if (N % i == 0){
			divisors.pb(i);
			if (i != N/i){
				divisors.pb(N/i);
			}
		}
	}
	
	return divisors;
}
