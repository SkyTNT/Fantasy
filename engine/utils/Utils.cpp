#include "Utils.h"

#include <fstream>
#include <sstream>
#include <ctime>

std::string i2s(int i) {
    std::stringstream sout;
    std::string s;
    sout << i;
    sout >> s;
    return s;
}

std::string f2s(float fl) {
    std::stringstream sout;
    std::string s;
    sout << fl;
    sout >> s;
    return s;
}

std::string d2s(double d) {
    std::stringstream sout;
    std::string s;
    sout << d;
    sout >> s;
    return s;
}

int s2i(std::string s) {
    std::stringstream sout;
    int i;
    sout << s;
    sout >> i;
    return i;
}

std::string getLocalTime() {
    time_t rawtime;
    struct tm *ptminfo;
    time(&rawtime);
    ptminfo = localtime(&rawtime);
    std::stringstream ss;
    ss << "[" << ptminfo->tm_year + 1900 << ":" << ptminfo->tm_mon + 1 << ":" << ptminfo->tm_mday << ":"
       << ptminfo->tm_hour << ":" << ptminfo->tm_min << ":" << ptminfo->tm_sec << "]";
    std::string result;
    ss >> result;
    return result;
}

#ifdef __ANDROID__
void LOG_BASE(android_LogPriority logPriority,const std::string &tag,const std::string &text){
    __android_log_write(logPriority, tag.c_str(), text.c_str());
}
#endif