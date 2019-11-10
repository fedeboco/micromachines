#ifndef __YELLOW_CAR_H__
#define __YELLOW_CAR_H__

#include "car.h"

class YellowCar: public Car {
    public:
    YellowCar(const Point &startingPoint, uint16_t rot);
    ~YellowCar();
};

#endif
