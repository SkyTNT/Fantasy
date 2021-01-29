#pragma once

#include<string>

using namespace std;


string i2s(int i);
string f2s(float fl);
string d2s(double d);

int s2i(string s);

void LOG_I(string str);
void LOG_W(string str);
void LOG_E(string str);
void LOG_I(string tag, string str);
void LOG_W(string tag, string str);
void LOG_E(string tag, string str);

string read_file(string path);
