#include "Time.h"
#include <ctime>
#include <climits>

long Time::time = 0;
double Time::deltaTime = 0;
double Time::timeScale = 1;
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
}
