#include <algorithm>
#include <iostream>
#include "Canvas.h"

namespace annie {
  void Object::fillCanvas(std::vector<std::string>& canvas) const {
    unsigned int h = canvas.size();
    for (unsigned int row = getY(); row < std::min(getY() + (unsigned int)content_.size(), h); ++row) {
      unsigned int w = canvas[canvas.size() - 1 - row].size();
      for (unsigned int col = getX(); col < std::min(getX() + (unsigned int)content_[content_.size() - 1 - (row - getY())].size(), w); ++col) {
        canvas[canvas.size() - 1 - row][col] = content_[content_.size() - 1 - (row - getY())][col - getX()];
      }
    }
  }

  void Canvas::drawCanvas() const {
    std::string blank(width_, ' ');
    blank.append("\n");
    std::vector<std::string> canvas;
    for (unsigned int i = 0; i < height_; ++i) {
      canvas.push_back(blank);
    }
    for (auto& obj : objects_) {
      obj->fillCanvas(canvas);
    }
    clear();
    for (const auto& line : canvas) {
      printw(line.c_str());
    }
    refresh();
  }
} // annie
