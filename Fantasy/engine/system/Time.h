#pragma once

//ʱ����Ϣ
class Time {
public:
    //֡����
    static long tickCount;
    //��������ʱ��(s)
    static float time;
    //ÿ֡ʱ������(s)
    static float deltaTime;
    //ʱ���ٶ�����
    static float timeScale;

    static void tick();
};
