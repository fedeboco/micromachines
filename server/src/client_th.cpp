#include "../include/client_th.h"
#include "../include/model/cars/blue_car.h"
#include "../../common/include/socket_error.h"
#include "../../common/include/lock.h"
#include "iostream"
#include "vector"
#include "string"

ClientTh::ClientTh(Socket *peer, Car* car): keep_talking(true), is_running(true),
    peer(peer), car(car) {
    sendWelcomeMsg();
    sendCarData();
}

void ClientTh::sendWelcomeMsg() {
    std::string welcome_msg = "Bienvenido!\n";
    send(welcome_msg);
}

void ClientTh::sendCarData() {
    std::string car_msg = car->serialize();
    send(car_msg);
}

void ClientTh::sendAllCarsToPlayer(std::vector<ClientTh*> players) {
    for (size_t i = 0; i < players.size(); i++) {
        std::string s = players[i]->car->serialize();
        send(s);
    }
}

void ClientTh::sendTrackData(std::string track_serialized) {
    send(track_serialized);
}

void ClientTh::run() {
    while (keep_talking) {
        char action;
        receive(&action);
        Lock l(m);
        actions.push(action);
    }
    is_running = false;
}

void ClientTh::processNextAction() {
    Lock l(m);
    while (!actions.empty()) {
        char a = actions.front();
        actions.pop();
        car->updateState(a);
    }
}

void ClientTh::updateCar() {
    car->update();
}

void ClientTh::receive(char *action) {
    try {
        peer->Receive(action, 1);
    } catch(const SocketError &e) {
        keep_talking = false;
        std::cout << e.what() << "\n";
    }
}

void ClientTh::send(std::string &response) {
    try {
        const char *resp = response.c_str();
        peer->Send(resp, response.length());
    } catch(const SocketError &e) {
        keep_talking = false;
        std::cout << e.what() << "\n";
        throw e;
    }
}

void ClientTh::stop() {
    keep_talking = false;
    peer->Release();
}

bool ClientTh::isDead() {
    return !is_running;
}

ClientTh::~ClientTh() {
    //delete car;
    //Por ahora hago el delete de todos los autos en acceptor_th
}
