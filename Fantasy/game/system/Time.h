#pragma once

//ʱ����Ϣ
class Time {
public:
    //��������ʱ��(ms)
    static long time;
    //ÿ֡ʱ������
    static float deltaTime;
    //ʱ���ٶ�����
    static float timeScale;

    static void tick();
};
