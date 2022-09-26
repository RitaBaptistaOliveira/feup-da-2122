#include "Problems.h"

#define MULTIPLIER 15 /** multiplier used to calculate if a pakcage is worth delivering*/

/**
 * Fills each van one by one according to the smaller variable at each moment (weight and volume) in a way that maximizes the profit
 * Time Complexity: O(n^2 logn)
 * @param vans vector with all the vans
 * @param packages vector with all the packages
 * @param totalCost sum of the cost of all the vans being used
 * @param reward sum of the reward of all the packages being delivered
 * @return a vector with all the vans used for the deliveries
 */
vector<DeliveryVan> maximizeProfit(const vector<DeliveryVan> &vans, const vector<DeliveryPackage> &packages, int &totalCost, int &reward) {
    vector<DeliveryVan> deliveryVans = vans, res;
    vector<DeliveryPackage> packagesByW = packages, packagesByV = packages;
    totalCost = 0;
    reward = 0;

    //Sorting
    sort(deliveryVans.begin(), deliveryVans.end(), sortVansByCost);
    sort(packagesByW.begin(), packagesByW.end(), sortPackagesByWeight);
    sort(packagesByV.begin(), packagesByV.end(), sortPackagesByVolume);

    //Fill each van one by one
    vector<pair<int, int>> auxVans; // vector with the weight and volume of each van, the values will decrease according to the packages
    setAuxVans(auxVans, deliveryVans);

    bool full;
    for (int vanNr = 0; vanNr < deliveryVans.size(); vanNr++) {
        if (packagesByV.empty() && packagesByW.empty())
            break;
        full = false;
        while (!full) {
            if (auxVans[vanNr].first == 0 || auxVans[vanNr].second == 0 || packagesByV.empty() || packagesByW.empty())
                break;
            else if (auxVans[vanNr].first < auxVans[vanNr].second) {
                full = placePackage(packagesByW, packagesByV, deliveryVans, res, auxVans, vanNr, reward, totalCost);
            } else if (auxVans[vanNr].first >= auxVans[vanNr].second) {
                full = placePackage(packagesByV, packagesByW, deliveryVans, res, auxVans, vanNr, reward, totalCost);
            }
        }
    }
    return res;
}

/**
 * Lambda function for sorting the packages by volume in ascending order
 * @param A first package to be compared
 * @param B second package to be compared
 * @return true if the the weight of van A and B are equal and the volume of A is smaller than the volume of B and if the weight of A is smaller than the weight of B or false otherwise
 */
bool sortPackagesByWeight(DeliveryPackage A, DeliveryPackage B) {
    if (A.getPackageWeight() == B.getPackageWeight())
        return A.getPackageVolume() < B.getPackageVolume();
    return A.getPackageWeight() < B.getPackageWeight();
}

/**
 * Lambda function for sorting the packages by volume in ascending order
 * @param A first package to be compared
 * @param B second package to be compared
 * @return true if the the volume of van A and B are equal and the weight of A is smaller than the weight of B and if the volume of A is smaller than the volume of B or false otherwise
 */
bool sortPackagesByVolume(DeliveryPackage A, DeliveryPackage B) {
    if (A.getPackageVolume() == B.getPackageVolume())
        return A.getPackageWeight() < B.getPackageWeight();
    return A.getPackageVolume() < B.getPackageVolume();
}

/**
 * Lambda function for sorting the vans by delivery cost in ascending order
 * @param A first van to be compared
 * @param B second van to be compared
 * @return true if the delivery cost of van A is smaller than van B or if the delivery cost of van A and B are equal and both the weight and volume of van A are bigger than van B or false otherwise
 */
bool sortVansByCost(DeliveryVan A, DeliveryVan B) {
    if (A.getDeliveryCost() == B.getDeliveryCost())
        return (A.getMaxWeight() > B.getMaxWeight() && A.getMaxVolume() > B.getMaxVolume());
    return A.getDeliveryCost() < B.getDeliveryCost();
}

/**
 * Fills a vector with pairs of two integers with the weight and volume of each van
 * Time Complexity: O(n)
 * @param auxVans vector of pairs of two integers with the weight and volume, respectively, of the vans
 * @param deliveryVans vector with all the vans
 */
void setAuxVans(vector<pair<int, int>> &auxVans, vector<DeliveryVan> &deliveryVans) {
    auxVans.reserve(deliveryVans.size());
    for (const auto van: deliveryVans) {
        auxVans.emplace_back(van.getMaxWeight(), van.getMaxVolume());
    }
}

/**
 * Tries to place the best from searchPackages into the van number vanNr
 * Time Complexity: O(n^2)
 * @param searchPackages vector with the packages sorted by the most favorable variable (weight or volume)
 * @param auxPackages vector with the same packages as searchPackages, but sorted by the least favorable variable (weight or volume)
 * @param deliveryVans vector with all the vans
 * @param res vector with the vans that have currently packages assigned to them
 * @param auxVans vector with a pair of two integers, in which the first is the weight and the second is the volume of a van
 * @param vanNr number of the van in which we are trying to assign a package
 * @param reward sum of the total reward of packages already assigned
 * @param cost sum of the total cost from the vans being used
 * @return true if it is able to place a package or false otherwise
 */
bool placePackage(vector<DeliveryPackage> &searchPackages, vector<DeliveryPackage> &auxPackages,
                  vector<DeliveryVan> &deliveryVans, vector<DeliveryVan> &res,
                  vector<pair<int, int>> &auxVans, int vanNr, int &reward, int &cost) {
    bool full = true;
    auto it = searchPackages.begin();
    while (it != searchPackages.end()) {
        if (it->getValue() < (it->getPackageVolume()+it->getPackageWeight())*MULTIPLIER) {
            it = searchPackages.erase(it);
            continue;
        }
        if (it->getPackageWeight() <= auxVans[vanNr].first && it->getPackageVolume() <= auxVans[vanNr].second) {
            if (find(res.begin(), res.end(), deliveryVans[vanNr]) == res.end()) {
                res.emplace_back(deliveryVans[vanNr]); // if the van is not found then we add it to the res vector
                cost += deliveryVans[vanNr].getDeliveryCost();
            }
            auxVans[vanNr].first -= it->getPackageWeight();
            auxVans[vanNr].second -= it->getPackageVolume();
            reward += it->getValue();
            full = false;
            auxPackages.erase(find_if(auxPackages.begin(),auxPackages.end(), [&it](const DeliveryPackage& P)
            { return P.getId() == it->getId(); }));
            searchPackages.erase(it);
            break;
        } else it++;
    }
    return full;
}

/**
 * Calculates the profit and displays the profit
 * Time Complexity: O()
 * @param vans vector with the all vans
 * @param packages vector with all the packages
 */
void drawMaxProfit(const vector<DeliveryVan> &vans, const vector<DeliveryPackage> &packages) {
    cout << "-----------------------------PROBLEM 2-----------------------------\n";
    cout << "                            MAX PROFIT\n\n";

    int totalCost = 0, reward = 0;

    vector<DeliveryVan> maxProfit = maximizeProfit(vans, packages, totalCost, reward);

    cout << "Numero de carrinhas necessarias: " << maxProfit.size() << "\n";
    cout << "Custo total = " << totalCost << "\n";
    cout << "Recompensa = " << reward << "\n";
    cout << "Lucro = " << reward - totalCost << "\n\n";
}

/**
 * Displays the remaining weight and volume of each van. Usually used after filling the vans
 * Time Complexity: O(n)
 * @param auxVans vector with the current weight and volume of the vans
 */
void drawAuxVans(vector<pair<int, int>> auxVans) {
    for (int i = 0; i < auxVans.size(); i++) {
        cout << "Estafeta " << i + 1 << ":\n";
        cout << "Peso restante: " << auxVans[i].first << "u.m.\n";
        cout << "Volume restante: " << auxVans[i].second << "u.v.\n\n";
    }
}
