#include "../../include/model/micromachines.h"
#include "../../../common/include/lock.h"
#include "../../../common/include/socket_error.h"
#include <Box2D/Box2D.h>

#define DEGTORAD 0.0174532925199432957f

Micromachines::Micromachines() {
    tracks.readTracks();
    world = new b2World(b2Vec2(0, 0));
    world->SetDestructionListener(&destruction_listener);
}

void Micromachines::update() {
    Lock l(m);
    for (size_t i = 0; i < players.size(); i++) {
        players[i]->updateCar();
    }
}

void Micromachines::addPlayer(ClientTh *client) {
    Lock l(m);
    players.push_back(client);
}

void Micromachines::removePlayer(ClientTh *client) {
    Lock l(m);
    removePlayerFromVector(client);
}

void Micromachines::removePlayerFromVector(ClientTh *player) {
    size_t index_to_remove = -1;

    for (size_t i = 0; i < players.size(); i++) {
        if (players[i] == player) {
            index_to_remove = i;
            break;
        }
    }
    if (index_to_remove != -1) {
        players.erase(players.begin() + index_to_remove);
    }
}

void Micromachines::updatePlayersState() {
    Lock l(m);
    for (size_t i = 0; i < players.size(); i++) {
        players[i]->processNextAction();
    }
}

void Micromachines::cleanPlayers() {
    Lock l(m);
    players.clear();
}

void Micromachines::sendNewStateToPlayers() {
    Lock l(m);
    for (size_t i = 0; i < players.size(); i++) {
        try {
            players[i]->sendAllCarsToPlayer(players);
        } catch(const SocketError &e) {
            removePlayerFromVector(players[i]);
        }
    }
}

std::string Micromachines::trackSerialized() {
    return tracks.getTrack("test28").serialize();
}
