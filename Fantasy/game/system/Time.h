#pragma once

//ʱ����Ϣ
class Time {
public:
    //��������ʱ��(ms)
    static long time;
    //ÿ֡ʱ������
    static double deltaTime;
    //ʱ���ٶ�����
    static double timeScale;
    static void tick();
};
