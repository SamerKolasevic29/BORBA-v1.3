#include "../include/utils/Tools.h"
#include <fstream>
#include <sstream>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#endif

namespace Tools { 

    bool loadCSV(std::vector<Fighter>& fighters, const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            return false; // UI will hande errors
        }
    
         std::string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> parts;

            // Split line by comma
            while(getline(ss, segment, ',')) {
                parts.push_back(segment);
            }

            // Expecting 5 columns: Name, HP, LA, SA, Crit
            if(parts.size() >= 5) {
                try {
                    std::string name = parts[0];
                    int hp = std::stoi(parts[1]);
                    int la = std::stoi(parts[2]);
                    int sa = std::stoi(parts[3]);
                    int crit = std::stoi(parts[4]);

                    Fighter f(name, hp, la, sa, static_cast<uint8_t>(crit));
                    fighters.push_back(f);
                } catch (...) {
                    // Ignore bad row
                    continue; 
                }
            }
        }

        file.close();
        return true;
    }

    bool writeCSV(const Fighter& f, const std::string& fileName) {
        std::ofstream file(fileName, std::ios::app); // Append mode
        if (!file.is_open()) {
            return false;
        }

        file << f.Name() << ","
             << f.Health() << ","
             << f.LightAttack() << ","
             << f.SpecialAttack() << ","
             << static_cast<int>(f.Critical()) << "\n";

        file.close();
        return true;
    }

    int randomInt(int min, int max) {
        static std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }


    #ifdef _WIN32
    void playMusic(const std::string& fileName) {
        PlaySound(fileName.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    }

     void stopMusic() {
        PlaySound(NULL, 0, 0);
    }
    #endif


}