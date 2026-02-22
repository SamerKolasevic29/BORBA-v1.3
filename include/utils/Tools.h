#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <string>
#include <random>
#include "../models/Fighter.h"  //for Fighter definition

namespace Tools {

    // CSV Operations
    bool loadCSV(std::vector<Fighter>& fighters, const std::string& fileName);
    bool writeCSV(const Fighter& f, const std::string& fileName);

    // Random Generator
    int randomInt(int min, int max);

   

     #ifdef _WIN32
    void playMusic(const std::string& fileName);
    void stopMusic();
    void enableAnsi();
    #endif

}
#endif