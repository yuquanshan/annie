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
  unsigned int playGroundWidth = 60;
  unsigned int playGroundHeight = 30;
  PlayGround pg(playGroundWidth, playGroundHeight);
  auto meanGuy = std::make_shared<MeanGuy>(
    std::vector<std::string>{
      "  ///",
      " (0 0)",
      "   ~",
      "/ [|] \\",
      "   =",
      "  | |",
      " ~   ~"
    },
    15,
    15,
    7,
    7,
    "fuck off!"
  );
  auto walkingGuy = std::make_shared<annie::Object>(
    std::vector<std::string>{
      "  vwv ",
      " (o_o)",
      "   ~",
      "/ [|] \\",
      "   =",
      "  | |",
      " ~   ~"
    },
    0,
    0
  );
  auto cloud = std::make_shared<annie::Object>(
    std::vector<std::string>{
      "     @@@@              @@@@            @@@@     @@@@@@@",
      "@@@@@@      @@@@@@   @@@    @@@@@@  @@@     @@@@     @@@@@@@@@@",
      "        @@@@@             @@@@@       @@@@             @@@@@"
    },
    0,
    playGroundHeight - 5
  );
  pg.registerObj(walkingGuy);
  pg.registerObj(cloud);
  pg.registerMeanGuy(meanGuy);

  unsigned int cloudTimer = 0;

  initscr();
  std::thread drawer([&pg, &cloud, &cloudTimer](){
    while (op != 'x') {
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
      cloudTimer = (cloudTimer + 1) % 25;
      if (cloudTimer == 0) {
        cloud->setX((int)(cloud->getX() + 1) % pg.getWidth());
      }
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
