#include "Algorithme.h"
#include <vector>
#include <queue>

std::vector<int> Algorithme::demi_degre_interieur(std::vector<int> FS, std::vector<int> APS) {
    int n = APS[0];
    std::vector<int> ddi(n + 1, 0);

    for (int k = 1; k < FS[0]; k++) {
        if (FS[k] != 0) {
            ddi[FS[k]]++;
        }
    }

    ddi[0] = n;
    return ddi;
}

std::vector<int> Algorithme::demi_degre_exterieur(std::vector<int> FS, std::vector<int> APS) {
    int n = APS[0];
    std::vector<int> dde(n + 1, 0);

    for (int s = 1; s < n; s++) {
        dde[s] = APS[s + 1] - APS[s] - 1;
    }

    dde[n] = FS[0] - APS[n];
    dde[0] = n;
    return dde;
}

std::vector<int> Algorithme::descente_largeur(int r, std::vector<int> fs, std::vector<int> aps) {
    int n = aps[0];
    int i = 0, j = 1, k = 0, ifin, s, t, it;
    std::vector<int> fil(n + 1, 0);
    std::vector<int> dist(n + 1, -1);

    fil[0] = n;
    fil[1] = r;
    dist[0] = n;
    dist[r] = 0;

    while (i < j) {
        k++;
        ifin = j;
        while (i < ifin) {
            i++;
            s = fil[i];
            it = aps[s];
            t = fs[it];

            while (t > 0) {
                if (dist[t] == -1) {
                    j++;
                    fil[j] = t;
                    dist[t] = k;
                }
                t = fs[++it];
            }
        }
    }

    return dist;
}

void Algorithme::calcul_distance(Graphe *g) {
    int n = g->getApsElem(0);

    vector<vector<int>> Mat_dist(n+1, vector<int>(n+1, 0));
    Mat_dist[0][0] = n;

    for(int i = 1; i <= n; i++) {
        Mat_dist[i] = descente_largeur(i, g->getFs(), g->getAps());
    }

    string str = "";
    str += "------------Matrice des distances-------------\n";
    for(int a = 1; a < Mat_dist.size(); a++){
        str += "| ";
        for(int b = 1; b < Mat_dist[a].size(); b++){
            str += to_string(Mat_dist[a][b]) + "\t";
        }
        str += "|\n";
    }
    cout << str;
}


void Algorithme::empiler(int x,vector<int>& pilch){
    pilch[x] = pilch[0];
    pilch[0] = x;
}

vector<int> Algorithme::rang(vector<int> FS, vector<int> APS){
    int n = APS[0];
    int m = FS[0];
    int s, k, h, t;

    vector<int> rang(n+1);
    vector<int> pilch(n+1);
    vector<int> prem;

    vector<int> ddi = demi_degre_interieur(FS, APS);

    for(int i = 0;i <= n;i++){
        pilch[i] = 0;
    }
    rang[0] = n;
    for(s = 1;s <= n;s++){
        rang[s] = -1;
        if(ddi[s] == 0)
            empiler(s, pilch);
    }
    k = -1;
    s = pilch[0];
    prem.push_back(s);
    while(pilch[0] > 0){
        k++;
        pilch[0] = 0;

        while(s > 0){
            rang[s] = k;
            h = APS[s];
            t = FS[h];

            while(t > 0){
                ddi[t] = ddi[t] - 1;
                if(ddi[t] == 0){
                    empiler(t, pilch);
                }

                h++;
                t = FS[h];
            }

            s = pilch[s];
        }

        s = pilch[0];
        prem.push_back(s);
    }
    return rang;
}

void Algorithme::Prufer_decode(vector<int> t) {
    int m = t[0], n = m + 2;
    vector<int> s(n + 1, 0);

    for (int i = 1; i <= m; i++) {
        s[t[i]]++;
    }

    for (int k = 1; k <= m; k++) {
        for (int i = 1; i <= n; i++) {
            if (s[i] == 0) {
                cout << "[" << t[k] << " " << i << "] ";
                s[t[k]]++;
                s[i] = -1;
                break;
            }
        }
    }

    cout << "[ ";
    for (int i = 1; i <= n; i++) {
        if (s[i] == 0) {
            cout << i << " ";
        }
    }
    cout << "]" << endl;
}


void Algorithme:: prufer_encode(vector<int>& prf, Graphe& G) {
    int n = G.getMatriceElem(0, 0);
    prf.resize(n-2);
    prf[0] = n-2;
    int k = 1;

    while (k <= n-2) {
        int i = 1;
        while (G.getMatriceElem(i, 0) != 1) {
            i++;
        }
        int j = 1;
        while (G.getMatriceElem(i, j) != 1) {
            j++;
        }
        prf[k-1] = j;
        k++;

        G.setMatriceElem(i, j, 0);
        G.setMatriceElem(j, i, 0);
        G.setMatriceElem(i, 0, 0);
        G.setMatriceElem(j, 0, 0);
    }
}

void Algorithme:: Dijkstra(int s, Graphe *G, vector<int>& predecesseur, vector<int>& distance) {
    int ind, i, j = s, k, v;
    int n = G->getApsElem(0);
    int m = G->getFsElem(0) - n;

    vector<bool> inS(n + 2, false);

    for (i = 0; i <= n; i++) {
        predecesseur.push_back(s);
        inS[i] = false;
        distance.push_back(G->getCout(s, i));
    }

    distance[s] = 0;
    predecesseur[s] = 0;
    inS[s] = true;
    ind = n - 1;

    while (ind > 0) {
        m = MAXPOIDS;
        for (i = 1; i <= n; i++)
            if (inS[i] == false)
                if (distance[i] < m) {
                    m = distance[i];
                    j = i;
                }
        if (m == MAXPOIDS)
            return;

        inS[j] = true;
        ind--;
        k = G->getApsElem(j);

        while (G->getFsElem(k) != 0) {
            int fs_K = G->getFsElem(k);
            if (inS[fs_K] == false) {
                v = distance[j] + G->getCout(j, fs_K);

                if (v < distance[fs_K]) {
                    distance[fs_K] = v;
                    predecesseur[fs_K] = j;
                }
            }
            k++;
        }
    }

    cout << "\n distance : ";
    affiche_tab(distance);

    cout << "    pred : ";
    affiche_tab(predecesseur);
    cout << "     ins : ";
    affiche_tab_b(inS);
}

void Algorithme:: affiche_tab(vector<int> v) {
    cout << "|";
    for(int i = 1; i < v.size(); i++) {
        cout << v[i] << "|";
    }
}

void Algorithme:: affiche_tab_b(vector<bool> v) {
    cout << "|";
    for(int i = 1; i < v.size(); i++) {
        cout << v[i] << "|";
    }
}

void Algorithme:: Dantzig(vector<vector<int>> c){
    int n = c[0][0];
    int i, j, k;
    int x;

    // Matrice initiale
    cout << "------------Dantzig : Matrice initiale-------------\n";
    for(int a = 0; a < c.size(); a++){
        cout << "| ";
        for(int b = 0; b < c[a].size(); b++){
            cout << c[a][b] << "\t";
        }
        cout << "|\n";
    }
    cout << endl;

    for(k = 1; k < n; k++){
        for(i = 1; i <= k; i++){
            for(j = 1; j <= k; j++){
                if((x = c[i][j] + c[j][k+1]) < c[i][k+1]){
                    c[i][k+1] = x;
                }

                if((x = c[k+1][j] + c[j][i]) < c[k+1][i]){
                    c[k+1][i] = x;
                }
            }
            if((c[i][k+1] + c[k+1][i]) < 0){
                cout << "Circuit absorbant passant par " << i << " et " << k+1 << endl;
                return;
            }
        }

        for(i = 1; i <= k; i++){
            for(j = 1; j <= k; j++){
                if((x = c[i][k+1] + c[k+1][j]) < c[i][j]){
                    c[i][j] = x;
                }
            }
        }
    }

    // Matrice finale
    cout << "------------Dantzig : Matrice finale-------------\n";
    for(int a = 0; a < c.size(); a++){
        cout << "| ";
        for(int b = 0; b < c[a].size(); b++){
            cout << c[a][b] << "\t";
        }
        cout << "|\n";
    }
    cout << endl;
}


//---------------------------Tarjan-------------------------------------
void Algorithme ::traverse(int s, int p, int k, Graphe& g, vector<int>& num, vector<int>& ro, vector<bool>& entarj,
              vector<int>& tarj, vector<int>& pred, vector<int>& prem, vector<int>& pilch, vector<int>& cfc) {
    int t;
    p++;
    num[s] = p;
    ro[s] = p;
    tarj.push_back(s);
    entarj[s] = true;
    for (int r = g.getApsElem(s); (t = g.getFsElem(r)) != 0; r++) {
        if (num[t] == 0) {
            pred[t] = s;
            traverse(t, p, k, g, num, ro, entarj, tarj, pred, prem, pilch, cfc);
            if (ro[t] < ro[s])
                ro[s] = ro[t];
        } else {
            if ((num[t] < ro[s]) && entarj[t])
                ro[s] = num[t];
        }
    }

    if (ro[s] == num[s]) {
        k++;
        int last;
        do {
            last = tarj.back();
            entarj[last] = false;
            empiler(last, pilch);
            cfc[last] = k;
            tarj.pop_back();
        } while (last != s);

        prem[k] = pilch[0];
        pilch[0] = 0;
    }

    cout << "---------------Affichage intermediaire----------------" << endl;
    cout << "cfc : ";
    affiche_tab(cfc);
    cout << endl;
    cout << "num : ";
    affiche_tab(num);
    cout << endl;
    cout << "ro : ";
    affiche_tab(ro);
    cout << endl;
    cout << "pred : ";
    affiche_tab(pred);
    cout << endl;
    cout << "prem : ";
    affiche_tab(prem);
    cout << endl;
    cout << "pilch : ";
    affiche_tab(pilch);
    cout << endl;
    cout << "tarj : |";
    for (int i = 0; i < tarj.size(); i++) {
        cout << tarj[i] << "|";
    }
    cout << endl;
    cout << "entarj : ";
    affiche_tab_b(entarj);
    cout << endl;
    cout << "------------------------------------" << endl;
}

void Algorithme:: Tarjan(Graphe& g)
{
    int n = g.getApsElem(0);
    vector<int> prem(n+1);
    prem[0] = n;
    vector<int> pilch(n+1);
    for(int i = 0; i <= n; i++){
        pilch[i] = 0;
    }
    vector<int> cfc(n+1);
    cfc[0] = n;
    vector<int> pred(n+1);
    pred[0] = n;
    vector<int> tarj;
    vector<bool> entarj(n+1);
    entarj[0] = true;
    vector<int> num(n+1);
    num[0] = n;
    vector<int> ro(n+1);
    ro[0] = n;
    int p = 0;
    int k = 0;
    for (int i = 1; i <= n; i++)
    {
        num[i] = 0;
        pred[i] = 0;
        ro[i] = 0;
        entarj[i] = false;
        cfc[i] = i;
    }

    for(int s = 1; s <= n; s++){
        if (num[s] == 0)
        {
            cout << "traverse " << s << endl;
            traverse(s,p,k,g,num,ro,entarj,tarj,pred,prem,pilch,cfc);
        }
    }
    prem[0] = k;

    cout << "cfc : ";
    affiche_tab(cfc);
    cout << endl;
    cout << "num : ";
    affiche_tab(num);
    cout << endl;
    cout << "ro : ";
    affiche_tab(ro);
    cout << endl;
    cout << "pred : ";
    affiche_tab(pred);
    cout << endl;
    cout << "prem : ";
    affiche_tab(prem);
    cout << endl;
    cout << "pilch : ";
    affiche_tab(pilch);
    cout << endl;
    cout << "tarj : ";
    affiche_tab(tarj);
    cout << endl;
    cout << "entarj : ";
    affiche_tab_b(entarj);
    cout << endl;
}


void Algorithme:: graphe_reduit(vector<int>& prem, vector<int>& pilch, vector<int>& cfc, vector<int>& fs,
                   vector<int>& aps, vector<int>& fsr, vector<int>& apsr) {
    int s, kr = 1, nbc = prem[0];
    vector<bool> deja_mis(nbc+1);
    fsr.resize(fs[0]+1);
    apsr.resize(nbc+1);
    apsr[0] = kr;
    for (int i = 1; i < nbc; i++) {
        apsr[i] = kr;
        for (int j = 1; j <= nbc; j++) {
            deja_mis[j] = false;
        }
        deja_mis[i] = true;
        s = prem[0];
        while (s != 0) {
            for (int t = aps[s]; fs[t] != 0; t++) {
                if (deja_mis[cfc[fs[t]]] == false) {
                    fs[kr] = cfc[fs[t]];
                    kr++;
                    deja_mis[cfc[fs[t]]] = true;
                }
            }
            s = pilch[s];
        }
        fsr[kr] = 0;
        kr++;
    }
    fsr[0] = kr - 1;
}

void graphe_reduit(vector<int>& prem, vector<int>& pilch, vector<int>& cfc, vector<int>& fs,
                   vector<int>& aps, vector<int>& fsr, vector<int>& apsr)
{
    int s, kr = 1, nbc = prem[0];
    vector<bool> deja_mis(nbc + 1);
    fsr.resize(fs[0] + 1);
    apsr.resize(nbc + 1);
    apsr[0] = kr;
    for (int i = 1; i < nbc; i++)
    {
        apsr[i] = kr;
        for (int j = 1; j <= nbc; j++)
        {
            deja_mis[j] = false;
        }
        deja_mis[i] = true;
        s = prem[0];
        while (s != 0)
        {
            for (int t = aps[s]; fs[t] != 0; t++)
            {
                if (deja_mis[cfc[fs[t]]] == false)
                {
                    fs[kr] = cfc[fs[t]];
                    kr++;
                    deja_mis[cfc[fs[t]]] = true;
                }
            }
            s = pilch[s];
        }
        fsr[kr] = 0;
        kr++;
    }
    fsr[0] = kr - 1;
}

void Algorithme:: base_Greduit(vector<int>& apsr, vector<int>& fsr, vector<int>& br)
{
    int nr = apsr[0];
    br.resize(nr + 1);
    vector<int> ddir(nr + 1);
    for (int i = 0; i <= nr; i++)
        ddir[i] = 0;
    for (int kr = 1; kr <= fsr[kr]; kr++)
        ddir[fsr[kr]] = fsr[kr] + 1;
    int nb = 0;
    for (int c = 1; c <= nr; c++)
        if (ddir[c] == 0)
            br[++nb] = c;
    br[0] = nb;
}

void Algorithme:: edition_bases(vector<int>& prem, vector<int>& pilch, vector<int>& br)
{
    int nb = br[0];
    vector<int> Base(nb + 1);
    Base[0] = nb;
    int p = 1;
    int som = prem[br[1]];
    while (p >= 1)
    {
        if ((p <= nb) && (som != 0))
        {
            Base[p] = som;
            p++;
            if (p <= nb)
                som = prem[br[p]];
            else
            {
                string str = "";
                str += "------------Tarjan : edition des bases-------------\n";
                str += "| ";
                for (int i = 0; i < Base.size(); i++)
                {
                    str += Base[i];
                }
                str += "| \n";
            }
        }
        else
        {
            p--;
            som = pilch[Base[p]];
        }
    }
}

//------------------------------------------------end Tarjan------------------------------------------------------


void Algorithme:: ordonnancementt(vector<int>& fp, vector<int>& app, vector<int>& d, vector<int>& fpc, vector<int>& appc, vector<int>& lc) {
    int n = app[0];
    int m = fp[0];
    fpc.resize(m + 1);
    appc.resize(n + 1);
    appc[0] = n;
    lc.resize(n + 1);
    lc[0] = n;

    int kc, t, lg;

    lc[1] = 0;
    fpc[1] = 0;
    appc[1] = 1;

    kc = 1;
    for (int s = 2; s <= n; s++) {
        lc[s] = 0;
        appc[s] = kc + 1;
        for (int k = app[s]; (t = fp[k]) != 0; k++) {
            lg = lc[t] + d[t];
            if (lg > lc[s]) {
                if (lg > lc[s]) {
                    lc[s] = lg;
                    kc = appc[s];
                    fpc[kc] = t;
                }
                else {
                    kc++;
                    fpc[kc] = t;
                }
            }
        }
        kc++;
        fpc[kc] = 0;
    }
    fpc[0] = kc;
}

void Algorithme:: fusionner(int i, int j, vector<int>& prem, vector<int>& pilch, vector<int>& cfc, vector<int>& nbElem) {
    if (nbElem[i] < nbElem[j]) {
        int aux = i;
        i = j;
        j = aux;
    }

    int s = prem[j];
    cfc[s] = i;
    while (pilch[s] != 0) {
        s = pilch[s];
        cfc[s] = i;
    }

    pilch[s] = prem[i];
    prem[i] = j;
    nbElem[i] += nbElem[j];
}



/*void kruskal(Graphe &g, vector<pair<int, pair<int, int>>> &res){
    int n = g.getApsElem(0);
    vector<int> T(n+1);

    for(int i=1;i<=n;i++){
        T[i]=i;
    }

    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq;

    for(int i=1;i<=n;i++){
        for(int r=g.getApsElem(i);r!=0;r=g.getFsElem(r)){
            int v = g.getVsElem(r);
            int p = g.getCoutElem(r);
            pq.push(make_pair(p,make_pair(i,v)));
        }
    }

    while(!pq.empty()){
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        int p = pq.top().first;
        pq.pop();
        if(T[u]!=T[v]){
            res.push_back(make_pair(p,make_pair(u,v)));
            int k = T[v];
            for(int i=1;i<=n;i++){
                if(T[i]==k){
                    T[i]=T[u];
                }
            }
        }
    }
}*/





