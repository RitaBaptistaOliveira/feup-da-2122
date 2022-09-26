#ifndef PROJ1_DELIVERYVAN_H
#define PROJ1_DELIVERYVAN_H

#include <iostream>

using namespace std;

class DeliveryVan {
private:
    int maxVolume;
    int maxWeight;
    int deliveryCost;
    int vanId;

public:
    DeliveryVan();
    DeliveryVan(int maxVolume, int maxWeight, int deliveryCost);

    int getMaxVolume() const;
    void setMaxVolume(int maxVolume);

    int getMaxWeight() const;
    void setMaxWeight(int maxWeight);

    int getDeliveryCost() const;
    void setDeliveryCost(int deliveryCost);

    int getVanId() const;
    void setVanId(int vanId);

    bool operator==(const DeliveryVan& deliveryVan) const;
};


#endif
