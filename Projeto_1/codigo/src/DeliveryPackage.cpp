#include "DeliveryPackage.h"

DeliveryPackage::DeliveryPackage() {

}

DeliveryPackage::DeliveryPackage(int packageWeight, int packageVolume, int value,
                                 int deliveryTime, int id) {
    this->packageWeight = packageWeight;
    this->packageVolume = packageVolume;
    this->value = value;
    this->deliveryTime = deliveryTime;
    this->id = id;
}

int DeliveryPackage::getPackageWeight() const {
    return this->packageWeight;
}

void DeliveryPackage::setPackageWeight(const int packageWeight) {
    this->packageWeight = packageWeight;
}

int DeliveryPackage::getPackageVolume() const {
    return this->packageVolume;
}

void DeliveryPackage::setPackageVolume(const int packageVolume) {
    this->packageVolume = packageVolume;
}

int DeliveryPackage::getValue() const {
    return this->value;
}

void DeliveryPackage::setValue(const int value) {
    this->value = value;
}

int DeliveryPackage::getDeliveryTime() const {
    return this->deliveryTime;
}

void DeliveryPackage::setDeliveryTime(const int deliveryTime) {
    this->deliveryTime = deliveryTime;
}

int DeliveryPackage::getId() const {
    return this->id;
}

void DeliveryPackage::setId(const int id) {
    this->id = id;
}