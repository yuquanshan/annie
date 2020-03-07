#pragma once

#include <curses.h>
#include <memory>
#include <string>
#include <vector>

namespace annie {

class Object {
 public:
  Object(std::vector<std::string>&& content, unsigned int x, unsigned int y): content_(std::move(content)), x_(x), y_(y) {};
  Object(std::vector<std::string>& content, unsigned int x, unsigned int y): content_(content), x_(x), y_(y) {};
  inline void setX(unsigned int x) { x_ = x; };
  inline void setY(unsigned int y) { y_ = y; };
  inline unsigned int getX() const { return x_; };
  inline unsigned int getY() const { return y_; };
  virtual void fillCanvas(std::vector<std::string>& canvas) const;
  inline std::vector<std::string>& getContent() {
    return content_;
  }

 private:
  std::vector<std::string> content_;
  unsigned int x_;
  unsigned int y_;
};

class Canvas {
 public:
  Canvas(int w, int h): width_(w), height_(h) {};
  virtual void drawCanvas() const;
  inline unsigned int getWidth() {
    return width_;
  }
  inline unsigned int getHeight() {
    return height_;
  }
  inline void registerObj(std::shared_ptr<Object> obj) {
    objects_.push_back(obj);
  }

 protected:
  std::vector<std::shared_ptr<Object>> objects_;

 private:
  const unsigned int width_;
  const unsigned int height_;
};

} // annie
