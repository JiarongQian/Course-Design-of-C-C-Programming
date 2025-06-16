#ifndef FILE_INCLUDE_H
#define FILE_INCLUDE_H

//用于集中包含项目中所需的各种标准库和第三方库

//标准C++库
#include<iostream>  //提供C++的输入输出流功能
#include<string>    //提供字符串处理功能
#include<vector>     //提供动态数组容器
#include<fstream>  //提供文件输入输出功能
#include <sstream>  //提供字符串流功能
#include <algorithm> //提供常用算法

//标准C库
#include<stdio.h>   //提供C风格的输入输出功能
#include<ctime>  //提供时间处理功能
#include<stdlib.h> //提供通用工具函数

//Windows特定库
#include <windows.h> //提供Windows API功能 这里用来播放音乐
#include<mmsystem.h> //提供多媒体系统功能
#pragma comment(lib,"WINMM.LIB") //编译器指令，用于指定链接器需要链接的库文件

//图形和控制台库
#include<graphics.h> //EasyX图形库，这里用于图形绘制和图片背景加载
#include<conio.h>  //提供控制台输入输出功能

#endif // !FILE_INCLUDE_H

