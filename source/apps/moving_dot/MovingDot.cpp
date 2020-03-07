#include <chrono>
#include <curses.h>
#include <mutex>
#include <stdio.h>
#include <string>
#include <sys/ioctl.h>
#include <thread>
#include <unistd.h>

#include "Canvas.h"

// a simple demo that allows you to move a dot in the screen

int op = ERR;
std::mutex ml;

int main() {
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  annie::Canvas cvs(30, 30);
  auto dot = std::make_shared<annie::Object>(std::vector<std::string>{"o"}, 0, 0);
  cvs.registerObj(dot);

  initscr();

  std::thread drawer([&cvs](){
    while (op != 'x') {
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
      ml.lock();
      cvs.drawCanvas();
      ml.unlock();
    }
  });

  std::thread mover([&cvs, &dot](){
    while (op != 'x') {
      nodelay(stdscr, TRUE);
      op = getch();
      ml.lock();
      switch (op) {
        case 'a':
          dot->setX((int)(dot->getX() - 1) % cvs.getWidth());
          break;
        case 'd':
          dot->setX((int)(dot->getX() + 1) % cvs.getWidth());
          break;
        case 'w':
          dot->setY((int)(dot->getY() + 1) % cvs.getHeight());
          break;
        case 's':
          dot->setY((int)(dot->getY() - 1) % cvs.getHeight());
          break;
        default:
          break;
      }
      ml.unlock();
    }
  });

  drawer.join();
  mover.join();
  endwin();
  return 0;
}
