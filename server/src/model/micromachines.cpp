#include "../../include/model/micromachines.h"
#include "../../../common/include/lock.h"
#include "../../../common/include/socket_error.h"
#include <Box2D/Box2D.h>

#define DEGTORAD 0.0174532925199432957f

Micromachines::Micromachines() {
    tracks.readTracks();
    track = tracks.getTrack("classic");
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

int Micromachines::getPlayersNumber() {
    return players.size();
}

void Micromachines::setPlayerGameState(ClientTh *player, GameState state) {
    Lock l(m);
    player->setState(state);
}

void Micromachines::setAllPlayersGameStates(GameState state) {
    Lock l(m);
    for (size_t i = 0; i < players.size(); i++) {
        players[i]->setState(state);
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

void Micromachines::changeCarState(char *new_command) {
    for (size_t i = 0; i < players.size(); i++)
        for (int j = 0; j < 10; ++j)
            players[i]->receiveActionPlugin(new_command);
}

void Micromachines::sendNewStateToPlayers() {
    Lock l(m);
    for (size_t i = 0; i < players.size(); i++) {
        try {
            players[i]->sendAllCarsToPlayer(players);
        } catch (const SocketError &e) {
            removePlayerFromVector(players[i]);
        }
    }
}

std::string Micromachines::trackSerialized() {
    return tracks.getTrack("classic").serialize();
}

std::string Micromachines::allTrackNames() {
    std::vector<std::string> names = tracks.getTrackNames();
    std::string namesConcatenated;
    for (int i = 0; i < names.size(); i++) {
        namesConcatenated += names[i] + ',';
    }
    namesConcatenated.erase(namesConcatenated.length()-1); //borro la ultima coma
    namesConcatenated.append("\n");
    return namesConcatenated;
}

Point Micromachines::getStartingPoint(int position) {
    return track.getCarStartingPos(position);
}

uint16_t Micromachines::getStartingCarRot(int position) {
    return track.getCarStartingRotation(position);
}

TrackList& Micromachines::getTracks() {
    return tracks;
}

bool Micromachines::somePlayersInMainMenu() {
    for (int i = 0; i < players.size(); i++) {
        if (players[i]->getState() == mainMenu) {
            return true;
        }
    }
    return false;
}
