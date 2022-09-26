#include <iostream>
#include <fstream>
#include "src/Graph.h"

using namespace std;

/**
 * Reads a file and initializes the graph's values
 * @param g Given graph
 * @param filename Name of the file
 * @param size Number of the nodes of the graph
 * @return true if the file was read successfully or false otherwise
 */
bool readMap(Graph &g, const string &filename, int &size) {
    ifstream ifile(filename);
    bool read = false;
    int numNodes, numEdges;
    int src, dest, capacity, duration;
    if (ifile.is_open()) {
        read = true;
        ifile >> numNodes >> numEdges;
        size = numNodes;
        g.setSize(numNodes);
        bool first = true;
        while (!ifile.eof()) {
            if (!first) {
                g.addEdge(src, dest, capacity, duration);
            } else first = false;
            ifile >> src >> dest >> capacity >> duration;
        }
    }
    ifile.close();
    return read;
}

/**
 * Displays the menu
 * @param g Graph with the network
 * @param size Number of the nodes of the graph
 * @return 7 if the user want to use another graph or 0 if the user wants to exit
 */
int menu(Graph &g, int size) {
    int option;
    do {
        cout << "TRABALHO DE DA" << endl << endl;
        cout << "1) Cenario 1.1: Maximizar a dimensao do grupo.\n"
                "2) Cenario 1.2: Maximizar a dimensao do grupo e/ou minimizar o numero de transbordos.\n"
                "3) Cenario 2.1 e 2.2: Determinar um encaminhamento para um grupo, dada a sua dimensao, e com possibilidade de aumentar.\n"
                "4) Cenario 2.3: Determinar a dimensao maxima do grupo e um encaminhamento.\n"
                "5) Cenario 2.4: Determinar a duracao minima do caminho.\n"
                "6) Cenario 2.5: Tempo maximo de espera e locais de espera.\n"
                "7) Novo Mapa\n"
                "0) Sair\n"
                "Opcao:";
        cin >> option;
        int result;
        switch (option) {
            case 1:
                result = g.scenario1_1(1, size);
                if (result == -1)
                    cout << "Não existe um caminho da origem ao destino\n";
                break;
            case 2:
                result = g.scenario1_2(1, size);
                if (result == -1)
                    cout << "Não existe um caminho da origem ao destino\n";
                break;
            case 3: {
                int groupSize;
                do {
                    cout << "Tamanho do grupo:";
                    cin >> groupSize;
                } while (isalpha(groupSize));
                g.scenario2_1_2(1, size, groupSize);
                break;
            }
            case 4:
                g.scenario2_3(1, size);
                break;
            case 5:
                g.earliestStart(true);
                break;
            case 6:
                g.maxWaitingTime();
                break;
            case 7:
                break;
            case 0:
                return 0;
            default:
                cout << "Por favor escolha uma opçao valida!\n\n";
                break;
        }
    } while (option != 7);
    return 7;
}

int main() {
    int option;
    do {
        Graph g;
        string filename;
        bool doneReading;
        int size;
        do {
            cout << "Teste(0 to exit):";
            cin >> filename;
            if(filename == "0")
                return 0;
            doneReading = readMap(g, filename, size);

        } while (!doneReading);

        option = menu(g, size);
    } while (option != 0);
    return 0;
}



