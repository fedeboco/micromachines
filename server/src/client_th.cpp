#include "../include/client_th.h"
#include "../include/blocking_queue.h"
#include "../include/model/cars/blue_car.h"
#include "../include/model/cars/states/car_state.h"
#include "../../common/include/socket.h"
#include "../../common/include/socket_error.h"
#include "iostream"
#include "vector"
#include "string"

ClientTh::ClientTh(Socket *peer): keep_talking(true), is_running(true),
    peer(peer) {
    car = new BlueCar();
    std::string welcome_msg = "Bienvenido!\n";
    send(welcome_msg);
}

void ClientTh::run() {
    while (keep_talking) {
        try {
            char action;
            receive(&action);
            actions.push(action);
        } catch(const SocketError &e) {
            keep_talking = false;
            std::cout << e.what() << "\n";
        }
    }

    is_running = false;
}

char ClientTh::popAction() {
    return actions.pop();
}

void ClientTh::updateCarState(CarState *state_received) {
    car->setState(state_received);
}

void ClientTh::updateCar() {
    car->update();
}

void ClientTh::receive(char *action) {
    peer->Receive(action, 1);
}

void ClientTh::send(std::string &response) {
    const char *resp = response.c_str();
    peer->Send(resp, response.length());
}

void ClientTh::stop() {
    keep_talking = false;
    peer->Release();
}

bool ClientTh::isDead() {
    return !is_running;
}

ClientTh::~ClientTh() {
    delete car;
}
