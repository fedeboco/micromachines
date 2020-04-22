# Micromachines

##### Features:
* Online multiplayer.
* Dedicated servers with multiple simultaneous races support.
* Match creation: number of players and track selection.
* Up to 6 players in each race.
* Simple IA.
* Track Editor and track save to file.
* Power-ups.
* Race cheating and corner-cutting control.
* Engine sound effects and background music.
* Car life.
* Integrated game video recording using ffmpeg.
* Race podium at race finish line.
* Lap and position HUD.
* Fullscreen mode.
* 60 FPS support.
* Car explosion animation and car engine vibration visual effect.
* Easily customizable sprites.

![]()<img src="https://github.com/fedeboco/micromachines/blob/master/screenshot.jpeg?raw=true">

##### Programming features:
* Threads.
* Polymorphism.
* Sockets.
* RAII.
* SDL and Box2D libraries.
* Event Loops.
* Custom protocol.
* ffmpeg mp4 w/ h264 video recording.

# Instalación y compilación
## Compilación
- Instalar CMake https://cmake.org/install/
- Crear la carpeta `/build`
```
mkdir build
cd build
```
- Ejecutar cmake pasándole el directorio donde se encuentra `CMakeLists.txt`
```
cmake ../
```
- Ejecutar `make`
```
make
make install
```

## Ejecución
Luego de compilar se deben haber creado 2 archivos para ejecutar:
- `micromachines-sv`
- `micromachines-cl`

### Servidor
Ej:
```
./micromachines-sv 3000
```

### Cliente
Ej:
```
./micromachines-cl localhost 3000
```

## Bibliotecas
### Lua
* Instalar:
```
sudo apt install lua5.3 liblua5.3-dev
```
* Cmake:
```
find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

```

### JSONCPP
* Instalar:
```
sudo apt-get install libjsoncpp-dev
```
* Cmake:
```
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
```

### SDL
* Instalar (server):
```
sudo apt-get install libsdl2-dev
```

* Instalar (client):
```
sudo apt-get install li
sudo apt-get install libavformat-dev
sudo apt-get install libavformat57
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-ttf-dev
sudo apt-get install libsdl2-mixer-dev
sudo apt-get install libswscale-dev
sudo apt install libdvdnav4 libdvdread4 gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly libdvd-pkg
sudo apt install ubuntu-restricted-extras
```

* Cmake:
```
target_link_libraries(main
        SDL2
        SDL2_image
        SDL2_mixer
        SDL2_ttf
        swscale)
```

### FFMPEG
* Instalar:
```
sudo apt install libavutil-dev libswresample-dev libavformat-dev libavcodec-dev
```

* Cmake:
```
target_link_libraries(main
        avutil
        avformat
        swscale
        avcodec)
```

### Box2D
* Instalar:
```
sudo apt-get install libbox2d-dev
```

* Cmake:
```
target_link_libraries(main -ldl -lBox2D)
```

## Config defaults
```
{
   "max velocity [%]": 100,
   "acceleration [%]" : 100,
   "grip [%]" : 50,
   "maneuverability [%]" : 50,
   "race time [mins]" : 10,
   "world refresh frequency [Hz]" : 60,
   "play music" : "false",
   "fullscreen" : "false",
   "draw distance [4 - 8]" : 4,
   "fps limit" : 60,
   "rec fps limit" : 30
}
```

***NOTA: Cualquier modificación de estos pasos hacer el cambio correspondiente en este Readme.***
