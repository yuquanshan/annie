#include <cassert>
#include "MeanGuy.h"

void MeanGuy::fillCanvas(std::vector<std::string>& canvas) const {
  if (captionOn_) {
    caption_.fillCanvas(canvas);
  }
  annie::Object::fillCanvas(canvas);
}

void PlayGround::drawCanvas() const {
  assert(objects_.size() == 2);
  // mean guy should be the first object
  int dx = (int)objects_[0]->getX() - objects_[1]->getX();
  int dy = (int)objects_[0]->getY() - objects_[1]->getY();
  if (dx >= 0 || dy >= 0) {
    if (dx * dx + dy * dy >= 145) {
      dynamic_cast<MeanGuy*>(objects_[0].get())->captionOff();
    } else {
      dynamic_cast<MeanGuy*>(objects_[0].get())->captionOn();
    }
  } else {
    if (dx * dx + dy * dy >= 145) {
      dynamic_cast<MeanGuy*>(objects_[0].get())->captionOff();
    } else {
      dynamic_cast<MeanGuy*>(objects_[0].get())->captionOn();
    }
  }
  annie::Canvas::drawCanvas();
}
