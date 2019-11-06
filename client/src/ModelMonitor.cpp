#include "../include/ModelMonitor.h"

ModelMonitor::ModelMonitor(Model &model) : model(model) {}

ModelMonitor::~ModelMonitor() {}

void ModelMonitor::setTrack(std::vector<TrackPartData> track) {
    std::lock_guard<std::mutex> lock(m);
    model.setTrack(track);
}

std::vector<TrackPartData>& ModelMonitor::getTrack() {
    std::lock_guard<std::mutex> lock(m);
    return model.getTrack();
}

void ModelMonitor::setMyColor(std::string str) {
    std::lock_guard<std::mutex> lock(m);
    model.setMyColor(str);
}

std::string ModelMonitor::getMyColor() const {
    //es constante, no usa mutex
    return model.getMyColor();
}

std::map<std::string, Car*>& ModelMonitor::getCars() {
    std::lock_guard<std::mutex> lock(m);
    return model.getCars();
}

void ModelMonitor::addCar(std::string str) {
    std::lock_guard<std::mutex> lock(m);
    model.addCar(str);
    model.updateCar(str);
}

void ModelMonitor::updateCar(std::string str) {
    std::lock_guard<std::mutex> lock(m);
    model.updateCar(str);
}