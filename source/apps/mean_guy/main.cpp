#include <chrono>
#include <curses.h>
#include <mutex>
#include <stdio.h>
#include <sys/ioctl.h>
#include <thread>
#include <unistd.h>

#include "MeanGuy.h"

// a simple demo, if a walking guy moves close to the mean guy, the mean guy
// will yell bad words.

int op = ERR;
std::mutex ml;

int main() {
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  // PlayGround pg(50, 50);
  annie::Canvas pg(30, 30);
  auto meanGuy = std::make_shared<MeanGuy>(
      std::vector<std::string>{
        /*
        "  ///",
        " (0 0)",
        "   ~",
        "/ [|] \\",
        "   =",
        "  | |",
        " ~   ~"
        */
      },
      10,
      10,
      7,
      7,
      "fuck off!");
  auto walkingGuy = std::make_shared<annie::Object>(
    std::vector<std::string>{
      "  vwv ",
      " (0_0)"
      //"sdfdsfs"
      //"  m m"
    },
    0,
    0);
  pg.registerObj(walkingGuy);
  //pg.registerMeanGuy(meanGuy);

  initscr();

  std::thread drawer([&pg](){
    while (op != 'x') {
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
      ml.lock();
      pg.drawCanvas();
      ml.unlock();
    }
  });

  std::thread mover([&pg, &walkingGuy](){
    while (op != 'x') {
      nodelay(stdscr, TRUE);
      op = getch();
      ml.lock();
      switch (op) {
        case 'a':
          walkingGuy->setX((int)(walkingGuy->getX() - 1) % pg.getWidth());
          break;
        case 'd':
          walkingGuy->setX((int)(walkingGuy->getX() + 1) % pg.getWidth());
          break;
        case 'w':
          walkingGuy->setY((int)(walkingGuy->getY() + 1) % pg.getHeight());
          break;
        case 's':
          walkingGuy->setY((int)(walkingGuy->getY() - 1) % pg.getHeight());
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
