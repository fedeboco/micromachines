#ifndef __MICROMACHINES_H__
#define __MICROMACHINES_H__

#include "cars/car.h"
#include "tracks/track.h"
#include "../client_th.h"
#include <vector>

class Micromachines {
    private:
    Track track;
    std::vector<ClientTh*> clients;

    public:
    void update();
    void addClient(ClientTh *client);
    
    size_t removeCar(Car *car);
};

#endif