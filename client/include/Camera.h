#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <map>
#include "Model.h"
#include "sdl/SdlSurface.h"

class Camera {
private:
    SdlWindow &window;
    Model &model;
    std::map<PicType, SdlSurface*> &pictures;
    std::map<trackPartType, SdlSurface*> &trackPictures;
    double blockWidth;
    double blockHeight;

public:
    Camera(SdlWindow &window, Model &model, std::map<PicType, SdlSurface*> &pictures, std::map<trackPartType, SdlSurface*> &trackPictures);
    ~Camera();
    void showBackground();
    void showTrack(int xMyCar, int yMyCar);
    void showCars(int xMyCar, int yMyCar);
};

#endif
