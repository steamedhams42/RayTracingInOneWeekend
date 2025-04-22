#include <iostream>

const int BYTE = 1 << 8;

int main() {

    const int image_width = BYTE;
    const int image_height = BYTE;

    std::cout << "P3" << std::endl;
    std::cout << image_width << ' ' << image_height << std::endl;
    std::cout << BYTE - 1 << std::endl;

    for (int row = 0; row < image_height; row++) {
        std::clog << "\rScanlines remaining: " << image_height - row << " " << std::flush;
        for (int col = 0; col < image_width; col++) {
            double R = 1.0 * col / image_width;
            double G = 1.0 * row / image_height;
            double B = 0.0;

            int iR = int(R * BYTE);
            int iG = int(G * BYTE);
            int iB = int(B * BYTE);

            std::cout << iR << ' ' << iG << ' ' << iB << std::endl;
        }
    }
    std::clog << "\rDone                \n";

}
