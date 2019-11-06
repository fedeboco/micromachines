#ifndef __CAR_H__
#define __CAR_H__

#include <string>

class Car {
private:
    int x;
    int y;
    int degrees;
    int health;
    std::string color;

public:
    Car(std::string color);
    ~Car();
    int getX() const;
    int getY() const;
    int getDegrees() const;
    int getHealth() const;
    std::string getMyColor() const;
    void update(int x, int y, int degrees, int health);
};

#endif