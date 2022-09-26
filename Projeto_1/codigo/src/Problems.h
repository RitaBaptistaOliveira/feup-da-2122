#ifndef PROJ1_PROBLEMS_H
#define PROJ1_PROBLEMS_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "DeliveryVan.h"
#include "DeliveryPackage.h"

using namespace std;

//Cenário 1

vector<DeliveryVan> deliveryVanMinimization(const vector<DeliveryVan>& vans, const vector<DeliveryPackage>& packages);

vector<DeliveryVan> distributePackages(vector<DeliveryVan>& vans, vector<DeliveryPackage>& packages);

void drawMinimizationOfVans(vector<DeliveryVan>deliveryVans, vector <DeliveryPackage> deliveryPackages);

//----------------------------------------------------------------------------------------------------------------------

vector<DeliveryVan> minimizeVans(const vector<DeliveryVan> &vans, const vector<DeliveryPackage> &packages);

bool place_Package(vector<DeliveryPackage> &searchPackages, vector<DeliveryPackage> &auxPackages,
                   vector<DeliveryVan> &deliveryVans, vector<DeliveryVan> &res,
                   vector<pair<int, int>> &auxVans, int vanNr);

void drawMinimizationOfVans_2nd(vector<DeliveryVan>deliveryVans, vector <DeliveryPackage> deliveryPackages);

//Cenário 2
vector<DeliveryVan> maximizeProfit(const vector<DeliveryVan> &vans, const vector<DeliveryPackage> &packages, int &totalCost, int &reward);

bool placePackage(vector<DeliveryPackage> &searchPackages, vector<DeliveryPackage> &auxPackages, vector<DeliveryVan> &deliveryVans, vector<DeliveryVan> &res,
                  vector<pair<int, int>> &auxVans, int vanNr, int &reward, int &totalCost);

void drawMaxProfit(const vector<DeliveryVan> &vans, const vector<DeliveryPackage> &packages);

void drawAuxVans(vector<pair<int,int>> auxVans);

//Cenário 3

vector<DeliveryPackage> expressOrder(vector<DeliveryPackage> packages);

void drawExpress (vector<DeliveryPackage> packages);

// funcoes auxiliares

void setAuxVans(vector<pair<int, int>> &auxVans, vector<DeliveryVan> &deliveryVans);

bool deliveryVanSort(const DeliveryVan &a, const DeliveryVan &b);

bool deliveryPackageSort(const DeliveryPackage &a, const DeliveryPackage &b);

bool sortPackagesByWeight(DeliveryPackage A, DeliveryPackage B);

bool sortPackagesByVolume(DeliveryPackage A, DeliveryPackage B);

bool sortVansByCost(DeliveryVan A, DeliveryVan B);

static bool sortByTime(DeliveryPackage A, DeliveryPackage B);

#endif //PROJ1_PROBLEMS_H
