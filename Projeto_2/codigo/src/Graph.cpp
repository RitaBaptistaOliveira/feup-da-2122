#include "src/Graph.h"

#include <climits>
#include <queue>

Graph::Graph() : n(0), nodes(1), minDuration(-1) {}

void Graph::setSize(int num) {
    n = num;
    nodes = vector<Node>(num + 1);
}

void Graph::addEdge(int src, int dest, int capacity, int duration) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({dest, capacity, duration});
}

//Scenario 1.1 and 1.2

int Graph::scenario1_1(int src, int target) {
    int cap = widestPath(src, target);

    if (nodes[target].parent == -1) return -1;
    list<int> path;
    computePath(target, path);

    cout << "Caminho: ";
    displayPath(path, cap);

    return 0;
}

int Graph::scenario1_2(int src, int target) {
    list<int> shortPath, capPath;
    int shortCap, maxCap;

    //Computes the shortest path using the bfs and calculates the maximum-minimum capacity of that path
    shortPath = bfs_path(src, target);
    if (nodes[target].parent == -1) return -1;

    shortCap = INT_MAX;
    auto it = shortPath.rbegin();
    int lastNode = *it;
    it++;
    while (it != shortPath.rend()) {
        for (auto &e: nodes[*it].adj) {
            if (e.dest == lastNode && shortCap >= e.capacity) {
                shortCap = e.capacity;
                break;
            }
        }
        lastNode = *it;
        it++;
    }

    //Computes the maximum-minimum capacity of the graph and the path
    maxCap = widestPath(src, target);
    if (nodes[target].parent == -1) return -1;

    computePath(target, capPath);

    //Chooses the best solutions
    if (shortPath.size() <= capPath.size() && shortCap == maxCap) {
        cout << "Caminho: ";
        displayPath(shortPath, shortCap);
    } else if (shortPath.size() == capPath.size() && shortCap < maxCap) {
        cout << "Caminho: ";
        displayPath(capPath, maxCap);
    } else {
        cout << "Caminho com maior capacidade: ";
        displayPath(capPath, maxCap);
        cout << "Caminho mais curto: ";
        displayPath(shortPath, shortCap);
    }
    return 0;
}

int Graph::widestPath(int src, int target) {

    vector<int> cap(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        nodes[i].parent = -1;
        cap[i] = 0;
    }
    cap[src] = INT_MAX;

    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<>> Q;

    Q.push(make_pair(0,src));

    cap[src] = INT_MAX;

    while (!Q.empty()) {
        pair<int,int> temp = Q.top();
        int u = temp.second;

        Q.pop();

        for (auto &edge: nodes[u].adj) {
            int capacity = max(cap[edge.dest], min(cap[u], edge.capacity));
            if (capacity > cap[edge.dest]) {
                cap[edge.dest] = capacity;
                nodes[edge.dest].parent = u;
                Q.push(make_pair(capacity,edge.dest));
            }
        }
    }
    return cap[target];

}

void Graph::bfs(int src) {
    for (int i = 1; i <= n; i++) {
        nodes[i].visited = false;
        nodes[i].parent = -1;
    }

    queue<int> q;
    q.push(src);
    nodes[src].visited = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &e: nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].parent = u;
                nodes[w].visited = true;
            }
        }
    }
}

list<int> Graph::bfs_path(int src, int target) {
    bfs(src);

    list<int> path;
    if (nodes[target].parent == -1) return path;
    computePath(target, path);

    return path;
}

void Graph::computePath(int target, list<int> &path) {
    int last = target;
    while (last != -1) {
        path.push_front(last);
        last = nodes[last].parent;
    }
}

void Graph::displayPath(list<int> &path, int cap) {
    for (auto x: path)
        cout << x << " ";
    cout << "\n";
    cout << "Capacidade: " << cap << "\n\n";
}

//Scenario 2.1, 2.2 and 2.3

void Graph::scenario2_1_2(int src, int target, int size) {
    for (int v = 1; v <= n; v++) {
        for (auto &edge: nodes[v].adj) {
            edge.flow = 0;
        }
    }
    vector<list<int>> paths;
    bool maxReached = false;
    int maxFlow = 0;
    do {
        maxFlow = edmondsKarpAlt(src, target, size, paths, maxReached, maxFlow);
        displayPaths(paths, maxFlow);
        //printGraph();

        if(maxReached){
            cout << "A dimensao do grupo (" << maxFlow << ") e maxima!\n";
        }
        else{
            int increment;
            do{
                cout << "Quer aumentar a dimensao do grupo em quantas pessoas(0 para sair)?";
                cin >> increment;
            } while(isalpha(increment));
            if(increment == 0)
                maxReached = true;
            else size += increment;
        }
    } while(!maxReached);
}

void Graph::scenario2_3(int src, int target) {
    for (int v = 1; v <= n; v++) {
        for (auto &edge: nodes[v].adj) {
            edge.flow = 0;
        }
    }
    vector<list<int>> paths;
    int maxFlow = edmondsKarp(src, target, paths);

    cout << "Paths:\n";
    displayPaths(paths, maxFlow);
    //printGraph();
}

bool Graph::bfsFF(int src, int target) {
    for (int v = 1; v <= n; v++) {
        nodes[v].visited = false;
        nodes[v].parent = -1;
    }
    queue<int> q;
    q.push(src);
    nodes[src].visited = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &e: nodes[u].adj) {
            if (e.capacity == e.flow) //if the edge is "full", skip it
                continue;
            int w = e.dest;
            if (!nodes[w].visited) {
                if (w == target) { //reached the target node
                    nodes[w].parent = u;
                    return false; //there might still be more paths
                }
                q.push(w);
                nodes[w].parent = u;
                nodes[w].visited = true;
            }
        }
    }

    return true; //there are no paths to the target node
}

int Graph::edmondsKarp(int src, int target, vector<list<int>> &paths) {
    int maxFlow = 0;
    bool maxReached = bfsFF(src, target);

    while (!maxReached) {
        int pathFlow;
        EK(src, target, paths, maxFlow, pathFlow);

        updateFlow(src, target, pathFlow);

        maxReached = bfsFF(src, target);
    }

    return maxFlow;
}

int Graph::edmondsKarpAlt(int src, int target, int groupSize, vector<list<int>> &paths, bool &maxReached, int &maxFlow) {
    maxReached = bfsFF(src, target);
    while (!maxReached) {
        int pathFlow;

        EK(src, target, paths, maxFlow, pathFlow);

        if (maxFlow > groupSize) {
            maxFlow -= pathFlow;
            updateFlow(src, target, groupSize - maxFlow);
            return groupSize;
        } else if (maxFlow == groupSize) {
            updateFlow(src, target, pathFlow);
            return maxFlow;
        } else {
            updateFlow(src, target, pathFlow);
        }

        maxReached = bfsFF(src, target);
    }
    return maxFlow;
}

void Graph::EK(int src, int target, vector<list<int>> &paths, int &maxFlow, int &pathFlow) {
    pathFlow = INT_MAX;
    list<int> path;
    for (int i = target; i != src; i = nodes[i].parent) {
        int u = nodes[i].parent;
        for (auto &e: nodes[u].adj) {
            if (e.dest == i) {
                pathFlow = min(pathFlow, e.capacity - e.flow);
                if (path.empty()) {
                    path.push_back(i);
                    path.push_back(u);
                } else path.push_back(u);
            }
        }
    }
    paths.push_back(path);
    maxFlow += pathFlow;
}

void Graph::printGraph() {
    cout << "Grafo:\n";
    for (int i = 1; i <= n; i++) {
        for (auto e: nodes[i].adj) {
            cout << "Origem: " << i << " Destino: " << e.dest << " Capacidade: " << e.capacity << " Fluxo: " << e.flow<< "\n";
        }
    }
    cout << "\n";
}

void Graph::displayPaths(vector<list<int>> &paths, int flow) {
    for (auto &path: paths) {
        auto it = path.rbegin();
        while(it != path.rend()) {
            cout << *it << " ";
            it++;
        }
        cout << "\n";
    }
    cout << "Fluxo: " << flow << "\n\n";
}

void Graph::updateFlow(int src, int target, int flow) {
    for (int i = target; i != src; i = nodes[i].parent) {
        int u = nodes[i].parent;
        for (auto &e: nodes[u].adj) {
            if (e.dest == i) {
                e.flow += flow;
            }
        }
    }
}

//Scenario 2.4 and 2.5

vector<int> Graph::earliestStart(bool print) {
    vector<int> earliestStart(n + 1);
    vector<int> grauE(n + 1); // entrada
    queue<int> S;
    minDuration = -1;
    int vf = -1;
    for (int i = 1; i <= n; i++) {
        earliestStart[i] = 0;
        nodes[i].parent = -1;
        grauE[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (auto edge: nodes[i].adj) {
            grauE[edge.dest] += 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (grauE[i] == 0)
            S.push(i);
    }
    int v;
    while (!S.empty()) {
        v = S.front();
        S.pop();
        if (minDuration < earliestStart[v]) {
            minDuration = earliestStart[v];
            vf = v;
        }
        for (auto edge: nodes[v].adj) {
            if (earliestStart[edge.dest] < earliestStart[v] + edge.duration) {
                earliestStart[edge.dest] = earliestStart[v] + edge.duration;
                nodes[edge.dest].parent = v;
            }
            grauE[edge.dest] -= 1;
            if (grauE[edge.dest] == 0) {
                S.push(edge.dest);
            }
        }
    }
    if (print) {
        cout << "Duracao minima: " << minDuration << "\nCaminho: " << vf << "  ";
        while (vf != 1) {
            cout << nodes[vf].parent << "  ";
            vf = nodes[vf].parent;
        }
        cout << "\n\n";
    }
    return earliestStart;
}

vector<int> Graph::latestFinish() {
    vector<int> latestFinish(n + 1);
    vector<int> grauS(n + 1, 0); // saida
    queue<int> S;

    for (int i = 1; i <= n; i++) {
        latestFinish[i] = minDuration;
        grauS[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (auto edge: nodes[i].adj) {
            grauS[edge.dest] += 1;
        }
    }

    Graph g = transposeGraph();

    for (int i = n; i > 0; i--) {
        if (grauS[i] != 0) {
            S.push(i);
        }
    }

    int v;

    while (!S.empty()) {
        v = S.front();
        S.pop();
        for (auto edge: g.nodes[v].adj) {
            if (latestFinish[edge.dest] > latestFinish[v] - edge.duration) {
                latestFinish[edge.dest] = latestFinish[v] - edge.duration;
            }
            grauS[edge.dest] -= 1;
            if (grauS[edge.dest] == 0) {
                S.push(edge.dest);
            }
        }
    }
    return latestFinish;
}

Graph Graph::transposeGraph() {
    Graph g;
    g.setSize(n);

    for (int i = 1; i < n; i++) {
        for (auto edge: nodes[i].adj) {
            g.addEdge(edge.dest, i, edge.capacity, edge.duration);
        }
    }
    return g;
}

void Graph::maxWaitingTime() {
    map<int, int> slackNodes;

    int totalSlack, maxSlack = 0;

    vector<int> ES = earliestStart(false);
    vector<int> LF = latestFinish();

    for (int i = 1; i <= n; i++) {
        for (auto edge: nodes[i].adj) {
            totalSlack = LF[edge.dest] - ES[i] - edge.duration;
            if (totalSlack > 0 && edge.duration > 0) {
                if(slackNodes.find(edge.dest) == slackNodes.end()){
                    slackNodes.insert(make_pair(edge.dest, totalSlack));
                }
                else{
                    if(totalSlack > slackNodes[edge.dest])
                        slackNodes[edge.dest] = totalSlack;
                }
                if (totalSlack > maxSlack)
                    maxSlack = totalSlack;
            }
        }
    }
    cout << "\nNos com folga:\n";

    for (pair<int, int> slackNode: slackNodes) {
        cout << "no = " << slackNode.first << "  folga = " << slackNode.second << endl;
    }

    cout << "\nTempo maximo de espera: " << maxSlack << "\n\n";
}
