#pragma once
#include <string>
#include <iostream>

std::string getLocalTime();

#ifdef __ANDROID__
#include <android/log.h>
#define LOG_BASE(l,t,s) __android_log_write(l, t.c_str(), s.c_str());
#define I ANDROID_LOG_INFO
#define W ANDROID_LOG_WARN
#define E ANDROID_LOG_ERROR
#else
#define LOG_BASE(l,t,s) std::cout << "["#l"]" << getLocalTime() <<"[" << t << "]"<<"[" << __FILE__ << "]:\t" << s << "\n";
#endif

#define LOG_I(t,s) LOG_BASE(I,t,s)
#define LOG_W(t,s) LOG_BASE(W,t,s)
#define LOG_E(t,s) LOG_BASE(E,t,s)

std::string i2s(int i);
std::string f2s(float fl);
std::string d2s(double d);

int s2i(std::string s);


