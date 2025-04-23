#include <iostream>

#include "point3.h"
#include "vec3.h"
#include "color.h"
#include "constants.h"

int main() {

    const int image_width = constants::BYTE;
    const int image_height = constants::BYTE;

    std::cout << "P3" << std::endl;
    std::cout << image_width << ' ' << image_height << std::endl;
    std::cout << constants::BYTE - 1 << std::endl;

    for (int row = 0; row < image_height; row++) {
        std::clog << "\rScanlines remaining: " << image_height - row << " " << std::flush;
        for (int col = 0; col < image_width; col++) {
            double R = 1.0 * col / image_width;
            double G = 1.0 * row / image_height;
            double B = 0.0;

            std::cout << Color(R, G, B);

        }
    }
    std::clog << "\rDone                \n";

}
