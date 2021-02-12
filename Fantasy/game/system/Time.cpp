#include "Time.h"
#include <ctime>
#include <climits>

long Time::time = 0;
long Time::tickCount = 0;
float Time::deltaTime = 0;
float Time::timeScale = 1;
long lastTime = 0;

void Time::tick() {
    //������ʱ��
    long now = clock();
    long dTimeMs = now - lastTime;
    lastTime = now;

    if (dTimeMs < 0) {
        dTimeMs += LONG_MAX;//��ֹʱ������
    }
    time = now * 1000 / CLOCKS_PER_SEC;
    deltaTime = ((float) dTimeMs) / CLOCKS_PER_SEC;
    deltaTime *= timeScale;

    //֡������1
    tickCount++;
    if (tickCount == LONG_MAX)
        tickCount = 0;

}
