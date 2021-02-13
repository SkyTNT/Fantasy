#pragma once

//时间信息
class Time {
public:
    //帧计数
    static long tickCount;
    //程序运行时间(s)
    static float time;
    //每帧时间增量(s)
    static float deltaTime;
    //时间速度缩放
    static float timeScale;

    static void tick();
};
