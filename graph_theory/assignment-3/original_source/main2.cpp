#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define ST first
#define L first
#define R second
#define ND second
#define MP make_pair
#define PB push_back

typedef vector<int> VI;
typedef pair<int, int> PI;
typedef vector<PI> VPII;
typedef set<int> SI;
// typedef PI edge;
typedef long long LL;
typedef map<PI, int> MPII;
typedef map<PI, PI> MPP;

#ifdef DEBUG
const bool debug = true;
#else
const bool debug = false;
#endif
int n, m, k, l, test = 1;
const int INF = 1000 * 1000 * 1000;
const int MAKSN = 1000 * 100 + 13;
const PI noEdge = MP(-1, -1);

struct Interval {
    PI low, high;

    Interval() {
        low = high = noEdge;
    }

    Interval(PI l, PI h) {
        low = l;
        high = h;
    }

    bool operator==(const Interval& a) const {
        return (low == a.low && high == a.high);
    }

    bool isEmpty() {
        return (low == noEdge) && (high == noEdge);
    }
};

typedef pair<Interval, Interval> conflictPair;

string s1, s2;
int curNum = 0;
vector<string> names;
map<string, int> namesMap;

// Pair nesting_depth, v
VPII E[MAKSN];

VPII Edges;
VI roots;
int height[MAKSN];
PI parentEdge[MAKSN];
PI leftRef[MAKSN], rightRef[MAKSN];

MPP orient;
MPII lowpt, lowpt2, nestingDepth;

vector<conflictPair> S;
map<PI, conflictPair> stack_bottom;

MPP ref, lowpt_edge;
MPII side;

int target(PI edge) {
    return orient[edge].ND;
}

int source(PI edge) {
    return orient[edge].ST;
}

int addVertex(string name);

PI sPair(int a, int b) {
    return MP(min(a, b), max(a, b));
}

void readIn() {
    n = m = 0;
    string line;

    while (getline(cin, line)) {
        if (line[0] == '#' || !line.size())
            continue;

        stringstream ss(line);

        ss >> s1;
        ss >> s2;
        int a = addVertex(s1);
        int b = addVertex(s2);

        E[a].PB(MP(INF, b));
        E[b].PB(MP(INF, a));

        PI sp = sPair(a, b);
        Edges.PB(sp);
        side[sp] = 1;
        ref[sp] = noEdge;
        m++;
    }

    n = namesMap.size();
}

int addVertex(string name) {
    if (namesMap.count(name))
        return namesMap[name];

    names.PB(name);
    namesMap[name] = curNum;

    return curNum++;
}

void dfs1(int v) {
    PI e = parentEdge[v];

    REP(i, E[v].size()) {
        int to = E[v][i].ND;
        PI vw = sPair(v, to);
        if (orient.count(vw))
            continue;
        // else not oriented yet
        orient[vw] = MP(v, to);
        lowpt[vw] = height[v];
        lowpt2[vw] = height[v];

        if (height[to] == INF) {  // tree edge
            parentEdge[to] = vw;  // MP(v, to);
            height[to] = height[v] + 1;
            dfs1(to);
        }
        else  // back edge
            lowpt[vw] = height[to];

        nestingDepth[vw] = 2 * lowpt[vw];
        if (lowpt2[vw] < height[v])  // Chordal
            nestingDepth[vw]++;

        // Lowpoints of parent edge
        if (e != noEdge) {
            if (lowpt[vw] < lowpt[e]) {
                lowpt2[e] = min(lowpt[e], lowpt2[vw]);
                lowpt[e] = lowpt[vw];
            } 
            else if (lowpt[vw] > lowpt[e])
                lowpt2[e] = min(lowpt2[e], lowpt[vw]);
            else
                lowpt2[e] = min(lowpt2[e], lowpt2[vw]);
        }
    }
}

void updateNestingD() {
    REP(i, n) {
        REP(j, E[i].size()) {
            int to = E[i][j].ND;
            E[i][j].ST = nestingDepth[sPair(i, to)];
        }
    }
}

bool conflicting(Interval I, PI b) {
    return (!I.isEmpty() && lowpt[I.high] > lowpt[b]);
}

conflictPair top() {
    if (S.empty())
        return conflictPair();

    return S.back();
}

bool addConstraints(PI ei, PI e) {
    conflictPair P = MP(Interval(), Interval());

    do {  // merge return edges of ei into P.R
        if (S.empty())
            break;

        conflictPair Q = S.back();
        S.pop_back();

        if (!Q.L.isEmpty())
            swap(Q.L, Q.R);
        if (!Q.L.isEmpty()) {  // not planar
            return false;
        } 
        else {
            if (lowpt[Q.R.low] > lowpt[e]) {
                if (P.R.isEmpty())
                    P.R.high = Q.R.high;
                else
                    ref[P.R.low] = Q.R.high;

                P.R.low = Q.R.low;
            } 
            else {
                if (lowpt_edge.count(e))
                    ref[Q.R.low] = lowpt_edge[e];
            }
        }
    } while (!(top() == stack_bottom[ei]));

    // Merge into e1..i-1 into P.L
    while (conflicting(top().L, ei) || conflicting(top().R, ei)) {

        conflictPair Q = top();
        S.pop_back();

        if (conflicting(Q.R, ei))
            swap(Q.L, Q.R);
        if (conflicting(Q.R, ei)) {  // not planar
            return false;
        } 
        else {  // merge interval below lowpt(e_i) into P.R
            ref[P.R.low] = Q.R.high;

            if (Q.R.low != noEdge)
                P.R.low = Q.R.low;
        }

        if (P.L.isEmpty())
            P.L.high = Q.L.high;
        else
            ref[P.L.low] = Q.L.high;

        P.L.low = Q.L.low;
    }

    if (!(P.L.isEmpty() && P.R.isEmpty()))
        S.PB(P);

    return true;
}

int lowest(conflictPair P) {
    if (P.L.isEmpty())
        return lowpt[P.R.low];
    if (P.R.isEmpty())
        return lowpt[P.L.low];

    return min(lowpt[P.L.low], lowpt[P.R.low]);
}

void trimBackEdges(int u) {

    while (!S.empty() && lowest(top()) == height[u]) {

        conflictPair P = top();
        S.pop_back();

        if (P.L.low != noEdge)
            side[P.L.low] = -1;
    }

    if (!S.empty()) {
        conflictPair P = S.back();
        S.pop_back();

        while (P.L.high != noEdge && target(P.L.high) == u)
            P.L.high = ref[P.L.high];

        if (P.L.high == noEdge && P.L.low != noEdge) {
            ref[P.L.low] = P.R.low;
            side[P.L.low] = -1;
            P.L.low = noEdge;
        }

        S.PB(P);
    }
}

bool dfs2(int v) {
    PI e = parentEdge[v];
    REP(i, E[v].size()) {
        int to = E[v][i].ND;
        PI vw = sPair(v, to);

        if (orient[vw] != MP(v, to))  // We want only outgoing edges
            continue;

        stack_bottom[vw] = top();

        if (vw == parentEdge[to]) {  // Tree edge
            if (!dfs2(to))
                return false;
        } 
        else {  // back edge
            lowpt_edge[vw] = vw;
            conflictPair p;
            p.R = Interval(vw, vw);
            S.PB(p);
        }

        if (lowpt[vw] < height[v]) {  // has return edge, fix parent
            PI e1 = sPair(v, E[v][0].ND);

            if (vw == e1) {
                lowpt_edge[e] = lowpt_edge[e1];
            } 
            else {
                bool b = addConstraints(vw, e);
                if (!b)
                    return false;
            }
        }
    }

    if (e != noEdge) {

        int u = source(e);
        trimBackEdges(u);

        if (lowpt[e] < height[u]) {
            // if (!S.empty()) {
            PI hl = top().L.high;
            PI hr = top().R.high;

            if (hl != noEdge && (hr == noEdge || (lowpt[hl] > lowpt[hr])))
                ref[e] = hl;
            else

                ref[e] = hr;
            // }
        }
    }

    return true;
}

vector<PI> adjList[MAKSN];
// O(n^2), probably should speed up placing on the list somehow
void dfs3(int v) {

    REP(i, E[v].size()) {
        int to = E[v][i].ND;
        PI vw = sPair(v, to);

        // if (orient[vw] != MP(v, to)) // We want only outgoing edges
        // continue;

        if (vw == parentEdge[to]) {
            adjList[to].PB(vw);
            leftRef[v] = vw;
            rightRef[v] = vw;
            dfs3(to);
        } 
        else {
            if (side[vw] == 1) {  // place  vw behind rightRef[to]
                bool inserted = false;

                for (vector<PI>::iterator it = adjList[to].begin();
                     it != adjList[to].end(); it++) {
                    if ((*it) == rightRef[to]) {
                        adjList[to].insert(it + 1, vw);
                        inserted = true;
                        break;
                    }
                }

                if (!inserted)
                    adjList[to].PB(vw);
            } 
            else {  // place vw before leftRef[to]
                bool insert = false;

                vector<PI>::iterator it = adjList[to].begin();
                for (; it != adjList[to].end(); it++) {
                    if ((*it) == leftRef[to]) {
                        insert = true;
                        break;
                    }
                }

                if (it == adjList[to].begin() || insert == false)
                    adjList[to].insert(adjList[to].begin(), vw);
                else
                    adjList[to].insert(it - 1, vw);

                leftRef[to] = vw;
            }
        }
    }
}

int sign(PI e) {

    if (ref[e] != noEdge) {
        side[e] = side[e] * sign(ref[e]);
        ref[e] = noEdge;
    }

    return side[e];
}

void printEmbedding();

void solve() {

    if (m > 3 * n - 6) {
        cout << "NIE\n";
        return;
    }

    REP(i, n) {
        sort(E[i].begin(), E[i].end());
    }

    // Orientation
    REP(i, n) {
        if (height[i] == INF) {
            height[i] = 0;
            roots.PB(i);
            dfs1(i);
        }
    }

    updateNestingD();

    // Testing
    REP(i, n) {
        sort(E[i].begin(), E[i].end());
    }

    REP(i, roots.size()) {
        if (!dfs2(roots[i])) {
            cout << "NIE\n";
            return;
        }
    }

    // Embedding
    cout << "TAK\n";

    REP(i, n) {
        REP(j, E[i].size()) {
            PI cur = sPair(i, E[i][j].ND);
            nestingDepth[cur] = nestingDepth[cur] * sign(cur);
        }
    }

    updateNestingD();

    REP(i, n) {
        sort(E[i].begin(), E[i].end());
    }

    REP(i, roots.size()) {
        dfs3(roots[i]);
    }

    printEmbedding();
}

void printEmbedding() {

    REP(i, n) {
        cout << names[i] << ": ";

        REP(j, adjList[i].size()) {

            PI cur = adjList[i][j];
            if (j)
                cout << " ";
            if (cur.ST == i)
                cout << names[cur.ND];
            else
                cout << names[cur.ST];
        }
        cout << "\n";
    }
}

void zeruj() {
    REP(i, MAKSN) {
        height[i] = INF;
        parentEdge[i] = noEdge;
    }
}

int main() {
    ios_base::sync_with_stdio(0);

    zeruj();
    readIn();
    solve();

    return 0;
}