#ifndef __PICTURELOADER_H__
#define __PICTURELOADER_H__

#include <map>
#include "sdl/SdlSurface.h"
#include "PicType.h"
#include "../../common/include/TrackPartData.h"
#include "../../common/include/Track.h"

class PictureLoader {
private:
    std::map<PicType, SdlSurface*> &pictures;
    std::map<trackPartType, SdlSurface*> &trackPictures;

public:
    PictureLoader(std::map<PicType, SdlSurface*> &pictures, std::map<trackPartType, SdlSurface*> &trackPictures);
    ~PictureLoader();
};

#endif
