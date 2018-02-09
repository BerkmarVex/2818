#ifndef DUALZONE_H
#define DUALZONE_H
#include <main.h>

#ifdef __cplusplus

extern "C" {
#endif

 static int dualzone(int speed, int range, double multiplier, double multiplier2){
    if (speed < range){
      speed = speed * multiplier;
    }
    if (speed >=range){
      speed = speed * multiplier2;
    }
    return speed;
  }

#ifdef __cplusplus

}
#endif

#endif
