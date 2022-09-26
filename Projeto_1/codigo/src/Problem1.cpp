#include "Problems.h"

/**
 * Lambda function for sorting the vans by maximum volume and weight in decreasing order
 * @param A first van to be compared
 * @param B second van to be compared
 * @return true if the first van's volume and weight are larger than the second one's and false otherwise
 */
bool deliveryVanSort(const DeliveryVan &a, const DeliveryVan &b) {
    return (a.getMaxVolume() > b.getMaxVolume()) && (a.getMaxWeight() > b.getMaxWeight());
}

/**
 * Lambda function for sorting the packages by volume and weight in increasing order
 * @param A first package to be compared
 * @param B second package to be compared
 * @return true if the first package's volume and weight are smaller than the second one's and false otherwise
 */
bool deliveryPackageSort(const DeliveryPackage &a, const DeliveryPackage &b) {
    return (a.getPackageVolume() < b.getPackageVolume()) && (a.getPackageWeight() < b.getPackageWeight());
}

/**
 * Function where we sort the given vectors and call the function to distribute the packages
 * Time complexity : O(n * log n)
 * @param vans vector with all the vans
 * @param packages vector with all the packages
 * @return the vector of vans used to distribute the pachages
 */
vector<DeliveryVan> deliveryVanMinimization(const vector<DeliveryVan> &vans, const vector<DeliveryPackage> &packages) {
    vector<DeliveryVan> deliveryVans = vans;
    vector<DeliveryPackage> deliveryPackages = packages;
    sort(deliveryVans.begin(), deliveryVans.end(), deliveryVanSort); // sorting the vans (decrease)
    sort(deliveryPackages.begin(), deliveryPackages.end(), deliveryPackageSort);
    return distributePackages(deliveryVans, deliveryPackages);
}

/**
 * Places the packages in the vans trying to reach the smallest amount of vans used
 * Time complexity : O(P * V) -> P is the number of packages and V is the number of vans
 * @param vans vector with all the vans
 * @param deliveryPackages vector with all the packages
 * @return a vector with the vans needed
 */
vector<DeliveryVan> distributePackages(vector<DeliveryVan> &vans, vector<DeliveryPackage> &deliveryPackages) {
    vector<DeliveryPackage> packages = deliveryPackages;
    vector<pair<int, int>> auxVans; // vector with the weight and volume of each van, the values will decrease according to the packages
    vector<DeliveryVan> res;
    auxVans.reserve(vans.size());
    for (auto van: vans) {
        auxVans.emplace_back(van.getMaxWeight(), van.getMaxVolume());
    }
    for (auto package: packages) {
        for (size_t i = 0; i < auxVans.size(); i++) {
            if (auxVans[i].first >= package.getPackageWeight() && auxVans[i].second >=
                                                                  package.getPackageVolume()) {// if the package can fit inside the van then we decrease the respective values by the weight and volume of the package
                if (find(res.begin(), res.end(), vans[i]) == res.end()) {
                    res.insert(res.begin(),
                               vans[i]); // if the DeliveryVan is not found then we add it to the res vector
                }
                auxVans[i].first -= package.getPackageWeight();
                auxVans[i].second -= package.getPackageVolume();
                break;
            }
        }
    }

    return res;
}

/**
 * Function to show the results obtained on the deliveryVanMinimization function (1st solution)
 * @param deliveryVans vector with all the vans
 * @param deliveryPackages vector with all the packages
 */
void drawMinimizationOfVans(vector<DeliveryVan> deliveryVans, vector<DeliveryPackage> deliveryPackages) {
    vector<DeliveryVan> deliveryVanMinimized = deliveryVanMinimization(deliveryVans, deliveryPackages);

    cout << "-----------------------------PROBLEM 1-----------------------------\n";
    cout << "                  MINIMIZATION OF VANS - 1st option:                \n" << endl;

    cout << "Numero de carrinhas necessarias 1: " << deliveryVanMinimized.size() << endl << endl;
}

//=======================================================================================================================================

/**
 * Fills each van one by one according to the smaller variable at each moment (weight and volume) in a way that minimizes the amount of vans needed
 * Time Complexity: O(n^2 * logn)
 * @param vans vector with all the vans
 * @param packages vector with all the packages
 * @return a vector with the vans needed
 */
vector<DeliveryVan> minimizeVans(const vector<DeliveryVan> &vans, const vector<DeliveryPackage> &packages) {
    vector<DeliveryVan> deliveryVans = vans, res;
    vector<DeliveryPackage> packagesByW = packages, packagesByV = packages;

    //Sorting
    sort(deliveryVans.begin(), deliveryVans.end(), deliveryVanSort);
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
                full = place_Package(packagesByW, packagesByV, deliveryVans, res, auxVans, vanNr);
            } else if (auxVans[vanNr].first >= auxVans[vanNr].second) {
                full = place_Package(packagesByV, packagesByW, deliveryVans, res, auxVans, vanNr);
            }
        }
    }
    return res;
}

/**
 * Tries to place the best package from the vector searchPackages into the van number vanNr
 * Time Complexity: O(n^2)
 * @param searchPackages vector with the packages sorted by the most favorable variable (weight or volume)
 * @param auxPackages vector with the same packages as searchPackages, but sorted by the least favorable variable (weight or volume)
 * @param deliveryVans vector with all the vans
 * @param res vector with the vans that have currently packages assigned to them
 * @param auxVans vector with a pair of two integers, in which the first is the weight and the second is the volume of a van
 * @param vanNr number of the van in which we are trying to assign a package
 * @return true if it is able to place a package or false otherwise
 */
bool place_Package(vector<DeliveryPackage> &searchPackages, vector<DeliveryPackage> &auxPackages,
                  vector<DeliveryVan> &deliveryVans, vector<DeliveryVan> &res,
                  vector<pair<int, int>> &auxVans, int vanNr) {
    bool full = true;
    auto it = searchPackages.begin();
    while (it != searchPackages.end()) {
        if (it->getPackageWeight() <= auxVans[vanNr].first && it->getPackageVolume() <= auxVans[vanNr].second) {
            if (find(res.begin(), res.end(), deliveryVans[vanNr]) == res.end()) {
                res.emplace_back(deliveryVans[vanNr]); // if the van is not found then we add it to the res vector
            }
            auxVans[vanNr].first -= it->getPackageWeight();
            auxVans[vanNr].second -= it->getPackageVolume();
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
 * Function to show the results obtained on the deliveryVanMinimization function (2nd solution)
 * @param deliveryVans vector with all the vans
 * @param deliveryPackages vector with all the packages
 */
void drawMinimizationOfVans_2nd(vector<DeliveryVan> deliveryVans, vector<DeliveryPackage> deliveryPackages) {

    cout << "--------------------------------------------------------------------\n";
    cout << "                  MINIMIZATION OF VANS - 2nd option:                \n" << endl;

    vector<DeliveryVan> minVans = minimizeVans(deliveryVans, deliveryPackages);

    cout << "Numero de carrinhas necessarias: " << minVans.size() << "\n";

}
