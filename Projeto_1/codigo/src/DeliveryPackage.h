#ifndef PROJ1_DELIVERYPACKAGE_H
#define PROJ1_DELIVERYPACKAGE_H

#include <iostream>

using namespace std;

class DeliveryPackage {
private:
    int id;
    int packageWeight;
    int packageVolume;
    int value;
    int deliveryTime;

public:
    DeliveryPackage();
    DeliveryPackage(int packageWeight, int packageVolume, int value, int deliveryTime, int id);

    int getPackageWeight() const;
    void setPackageWeight(const int packageWeight);

    int getPackageVolume() const;
    void setPackageVolume(const int packageVolume);

    int getValue() const;
    void setValue(const int value);

    int getDeliveryTime() const;
    void setDeliveryTime(const int deliveryTime);

    int getId() const;
    void setId(const int id);
};


#endif