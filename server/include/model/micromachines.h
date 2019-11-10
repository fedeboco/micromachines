#ifndef __MICROMACHINES_H__
#define __MICROMACHINES_H__

#include "cars/car.h"
#include "../client_th.h"
#include "../../../common/include/TrackList.h"
#include <vector>
#include <mutex>

class Micromachines {
    private:
    TrackList tracks;
    Track track;
    std::mutex m;
    std::vector<ClientTh*> players;

    void removePlayerFromVector(ClientTh *player);

    public:
    Micromachines();
    void update();
    void addPlayer(ClientTh *client);
    void updatePlayersState();
    void removePlayer(ClientTh *client);
    void cleanPlayers();
    void sendNewStateToPlayers();
    std::string trackSerialized();
    Point getStartingPoint(int position);
    uint16_t getStartingCarRot(int position);
};

#endif
