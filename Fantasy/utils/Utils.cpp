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
#include <glfm.h>
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

#ifdef __ANDROID__
static int _fc_android_read(void *cookie, char *buf, int size) {
    return AAsset_read((AAsset *)cookie, buf, (size_t)size);
}

static int _fc_android_write(void *cookie, const char *buf, int size) {
    (void)cookie;
    (void)buf;
    (void)size;
    errno = EACCES;
    return -1;
}

static fpos_t _fc_android_seek(void *cookie, fpos_t offset, int whence) {
    return AAsset_seek((AAsset *)cookie, offset, whence);
}

static int _fc_android_close(void *cookie) {
    AAsset_close((AAsset *)cookie);
    return 0;
}

static FILE *_fc_android_fopen(const char *filename, const char *mode) {
    ANativeActivity *activity = glfmAndroidGetActivity();
    AAssetManager *assetManager = NULL;
    AAsset *asset = NULL;
    if (activity) {
        assetManager = activity->assetManager;
    }
    if (assetManager && mode && mode[0] == 'r') {
        asset = AAssetManager_open(assetManager, filename, AASSET_MODE_UNKNOWN);
    }
    if (asset) {
        return funopen(asset, _fc_android_read, _fc_android_write, _fc_android_seek,
                       _fc_android_close);
    } else {
        return fopen(filename, mode);
    }
}
#endif



string read_file(string path)
{
	LOG_I("File", "load " + path);
	string str;
	ifstream cv(path);
	char ch;
	if (cv.is_open())
	{
		while (!cv.eof())
		{
			cv.get(ch);
			str += ch;
		}
		cv.close();
		return str;

	}
	LOG_E("File","load " + path + " field");
	return "";
}

string load_asset(string path){
    LOG_I("File", "load asset " + path);
	FILE *file;
#ifdef __ANDROID__
	file = _fc_android_fopen(path.c_str(), "rb");
#else
	file =fopen(("assets/"+path).c_str(), "rb");
#endif
	if (file) {
		fseek(file, 0, SEEK_END);
		long length = ftell(file);
		fseek(file, 0, SEEK_SET);

		char *fstr = new char[length+1];
		fread(fstr, length, 1, file);
		fstr[length] = 0;
		fclose(file);
		string ret(fstr);
		delete[] fstr;
		return ret;
	}
	LOG_E("File","load " + path + " field");
    return "";
}