#pragma once

#include "Canvas.h"

class MeanGuy: public annie::Object {
 public:
  // rx and ry mean caption's relative x and y to MeanGuy
  MeanGuy(std::vector<std::string>&& content, unsigned int x, unsigned int y, unsigned int rx, unsigned int ry, std::string cap): Object(std::move(content), x, y), caption_(std::vector<std::string>{cap}, x + rx, y + ry) {};
  inline void toggleCaption() {
    captionOn_ = !captionOn_;
  }
  virtual void fillCanvas(std::vector<std::string>& canvas) const override;

 private:
  bool captionOn_ = false;
  annie::Object caption_;
};

class PlayGround: public annie::Canvas {
 public:
  PlayGround(int w, int h): annie::Canvas(w, h) {}
  void registerMeanGuy(std::shared_ptr<MeanGuy> meanGuy) {
    objects_.insert(objects_.begin(), meanGuy);
  }
  void drawCanvas() const override;

 private:
  std::shared_ptr<MeanGuy> meanGuy_;
};
