// Las funciones suponen que los intervalos son válidos, es decir: p.first <= p.second
// Los intervalos descritos son de la forma: [p.first, p.second]

// Esta función chequea si dos intervalos son disjuntos
bool areDisjoint(pair<ll, ll> &p1, pair<ll, ll> &p2) {
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first;
    ll endingTimeP2 = p2.second;

    bool option1 = endingTimeP1 < startingTimeP2;
    bool option2 = endingTimeP2 < startingTimeP1;
    return option1 || option2;
}

// Esta función chequea si p1 está incluido en p2
bool isIncluded(pair<ll, ll> &p1, pair<ll, ll> &p2){
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first;
    ll endingTimeP2 = p2.second;

    bool res = startingTimeP2 <= startingTimeP1 && endingTimeP1 <= endingTimeP2;
    return res;
}

// Esta función chequea si x pertenece al intervalo p1
bool belongsToTheInterval(pair<ll, ll> &p1, ll x){
    ll startingTimeP1 = p1.first;
    ll endingTimeP1 = p1.second;
    return startingTimeP1 <= x && x <= endingTimeP1;
}

// Esta función chequea si el intervalo p1 está a la izquierda de p2, es decir: p1.second <= p2.first
bool estaALaIzquierda(pair<ll, ll> &p1, pair<ll, ll> &p2){
    ll endingTimeP1 = p1.second;
    ll startingTimeP2 = p2.first;
    return endingTimeP1 <= startingTimeP2;
}

// Esta función me retorna el tamaño de un intervalo. En caso de que el intervalo sea inválido, retorna 0
ll intervalSize(pair<ll,ll> &p1){
    ll endingTimeP1 = p1.second;
    ll startingTimeP1 = p2.first;
    ll res = (ll) endingTimeP1 - startingTimeP1 + 1;
    
    if (startingTimeP1 > endingTimeP1){
        res = 0;
    }

    return res;
}

// Esta función retorna la intersección entre dos intervalos. Chequear que la respuesta sea válida porque en caso de interseccion vacia te devuelve un intervalo invalido
pair<ll,ll> intersectionIntervals(pair<ll,ll> &p1, pair<ll,ll> &p2){
    pair<ll,ll> startingTimeP1 = p1.first;
    pair<ll,ll> endingTimeP2 = p1.second;
    pair<ll,ll> startingTimeP2 = p2.first;
    pair<ll,ll> endingTimeP2 = p2.second;

    pair<ll,ll> res = {max(startingTimeP1, startingTimeP2), min(endingTimeP1, endingTimeP2)};
    return res;
}

// Esta funcion me ordena los intervalos para tener primero a aquellos que terminan antes y en caso de empate al que empieza antes.
bool finishEarlier(pair<ll, ll> &p1, pair<ll, ll> &p2){
    ll endingTimeP1 = p1.second;
    ll endingTimeP2 = p2.second;

    if (endingTimeP1 < endingTimeP2){
        return true;
    } else if (endingTimeP1 > endingTimeP2){
        return false;
    }

    ll startingTimeP1 = p1.first;
    ll startingTimeP2 = p2.first;

    return startingTimeP1 < startingTimeP2;
}

// Esta funcion me sirve para ordenar los intervalos de forma que tengo primero a los que empiezan antes, y en caso de empate al que termina mas tarde lo tengo primero.
// Esto me garantiza que: intervalo[i] e intervalo[i+1] se relacionan como: intervalo[i+1] esta contenido en i, o esta superpuesto con intervalo[i+1] pero tiene una parte que no y que esta a la derecha de este.
// Ademas, si intervalo[i+1] e intervalo[i] son disjuntos se que intervalo[i+k] con k>1 tambien es disjunto con intervalo[i]
bool startEarlier(pair<ll,ll> &p1, pair<ll,ll> &p2){
    ll startingTimeP1 = p1.first;
    ll startingTimeP2 = p2.first;

    if (startingTimeP1 < startingTimeP2){
        return true;
    } else if (startingTimeP1 > startingTimeP2){
        return false;
    }

    ll endingTimeP1 = p1.second;
    ll endingTimeP2 = p2.second;

    return endingTimeP1 > endingTimeP2;
}

// Esta función calcula el máximo número de intervalos disjuntos
ll maximumNumberOfDisjointIntervals(vector<pair<ll, ll>> &intervals){
    int n = intervals.size();
    if (n == 0) return 0;

    sort(all(intervals), finishEarlier);
    pair<ll, ll> lastInterval = intervals[0];
    int res = 1;

    forsn(i,1,n){
        pair<ll, ll> currentInterval = intervals[i];

        if (areDisjoint(currentInterval,lastInterval)){
            lastInterval = currentInterval;
            res++;
        }
    }

    return res;
}

// Esta funcion se encarga de devolverme un arreglo de intervalos en el que ninguno contiene al otro y se conservan solo los intervalos mas grandes. Es decir, si A1 estaba incluido en A2, agrego a A2 a B
vector<pair<ll,ll>> eliminateRedundantIntervals(vector<pair<ll,ll>> &A){
    vector<pair<ll,ll>> B;
    sort(all(A), startEarlier);
    int n = A.size();

    if (n == 0){
        return B;
    }

    pair<ll,ll> lastInterval = A[0];
    B.pb(lastInterval);

    forsn(i, 1, n){
        if(!isIncluded(A[i], lastInterval)){
            lastInterval = A[i];
            B.pb(lastInterval);
        }
    }

    return B;
}

// Esta función me retorna un intervalo redundante de mi arreglo. Un intervalo está redundante si está contenido entre 1 o más intervalos del arreglo
pair<ll, ll> redundantInterval(vector<pair<ll, ll>> &intervals){
    int n = intervals.size();
    pair<ll, ll> res = {UNDEFINED, UNDEFINED}; // Inicialmente supongo que no existe intervalo redundante

    sort(all(intervals), startEarlier);

    forn(i, n-1){
        pair<ll, ll> currentInterval = intervals[i];
        pair<ll, ll> nextInterval = intervals[i+1];

        if (isIncluded(nextInterval, currentInterval)){ // Si el intervalo siguiente está contenido en el actual, entonces es redundante
            res = nextInterval;
            break;
        } else if (i+2 <= n-1){ // Si el intervalo siguiente no está contenido en el actual, chequeo si está contenido entre el actual y el siguiente a él
            pair<ll, ll> laterInterval = intervals[i+2];

            if (belongsToTheInterval(currentInterval, nextInterval.first)){ // Chequeo si una parte del intervalo siguiente está contenido en el actual
                // Esto es lo que me falta contener del intervalo siguiente
                pair<ll,ll> newInterval = {currentInterval.second + 1, nextInterval.second};

                if (isIncluded(newInterval, laterInterval)){ // Chequeo si dicha parte está contenido en el intervalo siguiente a él
                    res = nextInterval;
                    break;
                }
            }

        }
    }

    return res;
}

ll interseccionMasGrande(vector<pair<ll,ll>> &A, vector<pair<ll,ll>> &B) {
    vector<pair<ll,ll>> A1 = eliminateRedundantIntervals(A);
    vector<pair<ll,ll>> B1 = eliminateRedundantInterals(B);

    int n = A1.size();
    int m = B1.size();
    ll res = 0;

    int i = 0;
    int j = 0;
	
    while (i < n && j < m){
        ll sizeIntersection = sizeInterval(intersectionIntervals(A1[i], B1[j]));
        res = max(res, sizeIntersection);
		
		// Si un intervalo p1 está incluido en p2, entonces p2 va a ser más útil para la siguiente búsqueda ya que es más grande que p1. Por lo tanto, lo voy a guardar y voy a adelantar al arreglo que contenía a p1
        if (isIncluded(A1[i], B1[j])){ // En este caso, es preferible continuar con el siguiente intervalo de A ya que el de B es más grande
            i++;
        } else if (isIncluded(B1[j], A1[i])){
            j++;
        // Si un intervalo p1 está a la izquierda de un intervalo p2, entonces voy a mantener a p2 y adelantar al arreglo de p1 ya que el siguiente intervalo de dicho arreglo podría tener una mejor intersección con p1
        } else if (estaALaIzquierda(A1[i], B1[j])){
            i++;
        } else {
            j++;
        }

    }

    return res;
}
