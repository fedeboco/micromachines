#include <SDL2/SDL_events.h>
#include <iostream>
#include "../include/Drawer.h"
#include "../include/sdl/SdlAnimation.h"
#include "../include/PicType.h"
#include "../include/Model.h"

#define WIDTH 900
#define HEIGHT 600

Drawer::Drawer(Socket &socket) : socket(socket), window(WIDTH, HEIGHT),
    loader(pictures, trackPictures), camera(window, model, pictures, trackPictures) {
    //std::string welcome =  receive(); // Recibe mensaje de bienvenida
    std::string car = receive(); // Recibe auto
    std::string trackStr = receive(); // Recibe pista
    std::cout << car;
    std::cout << trackStr;

    Track track = Track(trackStr);
    model.setTrackPartData(track.getTrackPartData());
}

Drawer::~Drawer() {}

void Drawer::run() {
    this->running = true;
    draw();
    while (running) {
        try {
            std::string text = receive();
            //printf("recibo: %s\n\n", text.c_str());
            //ACTUALIZAR MODELO
            //draw();
        } catch (std::exception &e) {
            printf("murio el socket en el drawer\n");
            running = false;
        }
    }
}

void Drawer::stop() {

}

int Drawer::draw() {
    try {
        window.fill();
        camera.showBackground();
        camera.showTrack(150, 100);
        camera.showCars(150, 100);
        window.render();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

std::string Drawer::receive() {
    std::vector<char> response;
    char c;
    this->socket.Receive(&c, 1);
    while (c != '\n') {
        response.push_back(c);
        this->socket.Receive(&c, 1);
    }
    std::string str_resp(response.begin(), response.end());
    return str_resp + "\n";
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
