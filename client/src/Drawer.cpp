#include <SDL2/SDL_events.h>
#include <iostream>
#include "../include/Drawer.h"
#include "../include/sdl/SdlAnimation.h"
#include <unistd.h>

#define WIDTH 900
#define HEIGHT 600
#define MICROSECS_WAIT 16000 //seria que en un segundo se dibujen aprox 60 veces
#define MUSICPATH "../common/sounds/beat.wav"
#define FULLSCREENBUTTON "../common/images/fullscreen.png"

Drawer::Drawer(ModelMonitor &modelMonitor) :
    window(WIDTH, HEIGHT),
    loader(window, pictures, trackPictures),
    camera(window, pictures, trackPictures),
    modelMonitor(modelMonitor), music(MUSICPATH) {
    createFullScreenButton();
}

Drawer::~Drawer() {}

void Drawer::run() {
    music.play();
    running = true;
    while (running) {
        auto start = std::chrono::system_clock::now();
        try {
            draw();
        } catch (std::exception &e) {
            running = false;
        }
        auto end = std::chrono::system_clock::now();
        int microsecsPassed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        usleep(MICROSECS_WAIT - microsecsPassed);
    }
    music.stop();
}

void Drawer::stop() {
    running = false;
}

void Drawer::resize(int width, int height) {
    window.resize(width, height);
}

void Drawer::createFullScreenButton() {
    int size = (window.getWidth() + window.getHeight()) / 37;
    SDL_Rect area = {0, 0, size, size};
    fullScreenButton = Button(window.getRenderer(), area, FULLSCREENBUTTON);
}

void Drawer::updateFullScreenButton(const SDL_Event *event) {
    fullScreenButton.updateEvent(event);
    if (fullScreenButton.isClicked()) {
        window.changeFullScreen();
    }
}

void Drawer::showFullScreenButton() {
    int size = (window.getWidth() + window.getHeight()) / 37;
    fullScreenButton.updateSize(size, size);
    fullScreenButton.draw(window.getRenderer());
}

void Drawer::draw() {
    window.fill();
    camera.updateBlockSize();
    camera.showBackground();
    int x = modelMonitor.getCars()[modelMonitor.getMyColor()]->getX();
    int y = modelMonitor.getCars()[modelMonitor.getMyColor()]->getY();
    camera.showTrack(x, y, modelMonitor.getTrack());
    camera.showCars(x, y, modelMonitor.getCars());

    showFullScreenButton();
    window.render();
}

void Drawer::showAnimation(SdlWindow &window) {
    //Muestro una animacion de prueba
    int framesInX = 5;
    int framesInY = 2;
    //Divido el ancho de la imagen por la cantidad de frames a lo ancho
    int widthFrame = 960 / framesInX;
    //Divido el largo de la imagen por la cantidad de frames a lo largo
    int heightFrame = 384 / framesInY;

    SdlTexture texture("images/explosion.png", window);
    SdlAnimation anim(texture, framesInX, framesInY, widthFrame, heightFrame);
    SDL_Rect sdlDest = {(window.getWidth() - widthFrame) / 2, (window.getHeight() - heightFrame) / 2, widthFrame, heightFrame};
    anim.render(sdlDest, window);
}
