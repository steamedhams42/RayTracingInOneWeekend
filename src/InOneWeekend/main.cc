#include <iostream>

#include "color.h"
#include "constants.h"
#include "point3.h"
#include "vec3.h"

int main() {

    std::cout << "P3" << std::endl;
    std::cout << constants::IMAGE_WIDTH << ' ' << constants::IMAGE_HEIGHT << std::endl;
    std::cout << constants::BYTE - 1 << std::endl;

    for (int row = 0; row < constants::IMAGE_HEIGHT; row++) {
        std::clog << "\rScanlines remaining: " << constants::IMAGE_HEIGHT - row << " " << std::flush;
        for (int col = 0; col < constants::IMAGE_WIDTH; col++) {
            double R = 1.0 * col / constants::IMAGE_WIDTH;
            double G = 1.0 * row / constants::IMAGE_HEIGHT;
            double B = 0.0;

            std::cout << Color(R, G, B);

        }
    }
    std::clog << "\rDone                \n";

}
