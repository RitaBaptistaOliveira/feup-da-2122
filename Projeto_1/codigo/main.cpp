#include <iostream>
#include <vector>
#include <fstream>
#include "src\DeliveryVan.h"
#include "src\DeliveryPackage.h"
#include "src\Problems.h"

using namespace std;

/**
 * Reads the file with the delivery vans and puts them all in a vector
 * @param filename name of the file containing the information of the delivery vans
 * @return a vector with all the delivery vans
 */
vector<DeliveryVan> readVans(string filename){
    int Id = 0;
    vector<DeliveryVan> res = {};
    ifstream ifile(filename);
    DeliveryVan c;
    string aux;
    int volMax, pesoMax, custo;
    if(ifile.is_open()){
        ifile >> aux >> aux >> aux;
        while(!ifile.eof()){
            ifile >> volMax >> pesoMax >> custo;
            c.setMaxVolume(volMax);
            c.setMaxWeight(pesoMax);
            c.setDeliveryCost(custo);
            c.setVanId(Id);
            res.push_back(c);
            Id ++;
        }
    }
    else {
        return res;
    }
    ifile.close();
    return res;
}
/**
 * Reads the file with the delivery packages and puts them all in a vector
 * @param filename name of the file containing the information of the delivery packages
 * @return a vector with all the delivery packages
 */
vector<DeliveryPackage> readDeliveryPackage(string filename){
    vector<DeliveryPackage> res = {};
    ifstream ifile(filename);
    DeliveryPackage d;
    string aux;
    int cnt = 1;
    int volume, peso, recompensa, duracao;
    if(ifile.is_open()){
        ifile >> aux >> aux >> aux >> aux;
        while(!ifile.eof()){
            ifile >> volume >> peso >> recompensa >> duracao;
            //cout << "Value = " << recompensa << endl;
            d.setPackageVolume(volume);
            d.setPackageWeight(peso);
            d.setValue(recompensa);
            d.setDeliveryTime(duracao);
            d.setId(cnt);
            res.push_back(d);
            cnt++;
        }
    }
    else {
        return res;
    }
    ifile.close();
    return res;
}


int main() {
    vector<DeliveryVan> vans = readVans("carrinhas.txt");
    vector<DeliveryPackage> packages = readDeliveryPackage("encomendas.txt");

    while(true) {
        cout << "TRABALHO DE DA" << endl << endl;
        cout << "1) Problema 1" << endl << "2) Problema 2" << endl << "3) Problema 3" << endl << "0) Sair" <<endl << "Opcao:" << endl;
        int option;
        cin >> option;
        switch (option) {
            case 1:
                drawMinimizationOfVans(vans, packages);
                drawMinimizationOfVans_2nd(vans, packages);
                break;
            case 2:
                drawMaxProfit(vans,packages);
                break;
            case 3:
                drawExpress(packages);
                break;
            case 0:
                return 0;
            default:
                cout << "Por favor escolha uma opção valida" << endl << endl;
                break;
        }
    }
}
