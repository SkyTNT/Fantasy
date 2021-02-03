#include "Utils.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>

string i2s(int i)
{
	stringstream sout;
	string s;
	sout << i;
	sout >> s;
	return s;
}

string f2s(float fl)
{
	stringstream sout;
	string s;
	sout << fl;
	sout >> s;
	return s;
}

string d2s(double d)
{
	stringstream sout;
	string s;
	sout << d;
	sout >> s;
	return s;
}

int s2i(string s)
{
	stringstream sout;
	int i;
	sout << s;
	sout >> i;
	return i;
}

string gettime()
{
	time_t rawtime;
	struct tm *ptminfo;
	time(&rawtime);
	ptminfo = localtime(&rawtime);
	stringstream ss;
	ss << "[" << ptminfo->tm_year + 1900 << ":" << ptminfo->tm_mon + 1 << ":" << ptminfo->tm_mday << ":" << ptminfo->tm_hour << ":" << ptminfo->tm_min << ":" << ptminfo->tm_sec << "]";
	string result;
	ss >> result;
	return result;
}

#ifdef __ANDROID__
#include <android/log.h>
#define LOG_BASE(l,t,s) __android_log_write(l, t.c_str(), s.c_str());
#define I ANDROID_LOG_INFO
#define W ANDROID_LOG_WARN
#define E ANDROID_LOG_ERROR
#else
#define LOG_BASE(l,t,s) cout << "["#l"]" << gettime() <<"[" << tag << "]:\t" << s << "\n";
#endif

void LOG_I(string str)
{
	LOG_I("common", str);
}

void LOG_W(string str)
{
	LOG_W("common", str);
}

void LOG_E(string str)
{
	LOG_W("common", str);
}

void LOG_I(string tag, string str)
{
	LOG_BASE(I, tag, str);
}

void LOG_W(string tag, string str)
{
	LOG_BASE(W, tag, str);
}

void LOG_E(string tag, string str)
{
	LOG_BASE(E, tag, str);
}
