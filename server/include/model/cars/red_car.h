#ifndef __RED_CAR_H__
#define __RED_CAR_H__

#include "car.h"

class RedCar : public Car {
public:
    RedCar(b2World *world);
    ~RedCar();
};

#endif
