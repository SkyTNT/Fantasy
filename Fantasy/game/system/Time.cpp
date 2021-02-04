#include "Time.h"
#include <ctime>
#include <climits>

long Time::time = 0;
double Time::deltaTime = 0;
double Time::timeScale = 1;

void Time::update() {
    //计算间隔时间
    long now = clock();
    long dTimeMs = now - time;
    time = now;
    if (dTimeMs < 0) {
        dTimeMs += LONG_MAX;//防止时间重置
    }
    deltaTime = ((float) dTimeMs) / CLOCKS_PER_SEC;
    deltaTime *= timeScale;
}
