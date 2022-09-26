#include "Graph.h"
#include "exercises.h"
#include <vector>
#include <string>

using namespace std;

int exA(){
    vector<string> input;
    string s;
    Graph<char> graph;
    while(getline(cin,s)){
        if(s == "#")
            break;
        input.push_back(s);
    }
    getline(cin, s); //s is the starting node

    for(int i = 0; i < input.size() - 1; i++){
        string s1 = input[i], s2 = input[i+1], temp1;
        int charNum, size = min(s1.size(),s2.size());
        for(int j = 0; j < size; j++){
            if(s1[j] != s2[j]){
                charNum = j;
                break;
            }
        }
        if (charNum + 1 == size) continue;
        graph.addVertex(s1[charNum]);
        graph.addVertex(s2[charNum]);
        graph.addEdge(s1[charNum],s2[charNum],1);
    }
}