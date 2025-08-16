#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<iomanip>
#include<fstream>
#include<sstream>                            
#include<set>
using namespace std;
void transfFileName(string& tmpNickname);
bool checkStartElem(string tempstr);
string longToStr(long long l);
long long strToLong(string str);             //stringתlong long
bool checkTailElem(string tempstr);
string intStr(int temp);
const string save_url = "D:\\newArea\\Dcollect\\needData\\";
// 原来是可以修改的
