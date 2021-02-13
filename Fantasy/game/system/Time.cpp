#include "Time.h"
#include <ctime>
#include <climits>


long Time::tickCount = 0;
float Time::time = 0;
float Time::deltaTime = 0;
float Time::timeScale = 1;
long lastTime = 0;

void Time::tick() {
    //计算间隔时间
    long now = clock();
    long dTimeMs = now - lastTime;
    lastTime = now;

    if (dTimeMs < 0) {
        dTimeMs += LONG_MAX;//防止时间重置
    }
    time = (float)(now) / CLOCKS_PER_SEC;
    deltaTime = ((float) dTimeMs) / CLOCKS_PER_SEC;
    deltaTime *= timeScale;

    //帧计数加1
    tickCount++;
    if (tickCount == LONG_MAX)
        tickCount = 0;

}
