#pragma once

//时间信息
class Time {
public:
    //程序运行时间(ms)
    static long time;
    //每帧时间增量
    static double deltaTime;
    //时间速度缩放
    static double timeScale;
    static void tick();
};
