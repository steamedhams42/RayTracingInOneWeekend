#ifndef RTW_STB_IMAGE_H
#define RTW_STB_IMAGE_H
//==============================================================================================
// To the extent possible under law, the author(s) have dedicated all copyright
// and related and neighboring rights to this software to the public domain
// worldwide. This software is distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public
// Domain Dedication along with this software. If not, see
// <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

// Disable strict warnings for this header from the Microsoft Visual C++
// compiler.
#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#include <string>

class rtw_image {
 public:
  rtw_image() {}

  rtw_image(const char* image_filename);

  ~rtw_image();

  bool load(const std::string& filename);

  int width() const { return (fdata == nullptr) ? 0 : image_width; }
  int height() const { return (fdata == nullptr) ? 0 : image_height; }

  const unsigned char* pixel_data(int x, int y) const;

 private:
  const int bytes_per_pixel = 3;
  float* fdata = nullptr;          // Linear floating point pixel data
  unsigned char* bdata = nullptr;  // Linear 8-bit pixel data
  int image_width = 0;             // Loaded image width
  int image_height = 0;            // Loaded image height
  int bytes_per_scanline = 0;

  static int clamp(int x, int low, int high);

  static unsigned char float_to_byte(float value);

  void convert_to_bytes();
};

// Restore MSVC compiler warnings
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
