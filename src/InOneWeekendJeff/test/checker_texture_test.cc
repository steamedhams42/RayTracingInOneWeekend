#include "InOneWeekendJeff/textures/checker_texture.h"
#include "test_base.h"

#include <cassert>

class CheckerTextureTest : public TestBase {
 public:
  void RunTest() override {
    Color white(1, 1, 1);
    Color black(0, 0, 0);
    auto checker = CheckerTexture(1, white, black);
  }
};