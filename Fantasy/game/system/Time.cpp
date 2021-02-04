#include "Time.h"
#include <ctime>
#include <climits>

long Time::time = 0;
double Time::deltaTime = 0;
double Time::timeScale = 1;

void Time::update() {
    //������ʱ��
    long now = clock();
    long dTimeMs = now - time;
    time = now;
    if (dTimeMs < 0) {
        dTimeMs += LONG_MAX;//��ֹʱ������
    }
    deltaTime = ((float) dTimeMs) / CLOCKS_PER_SEC;
    deltaTime *= timeScale;
}
