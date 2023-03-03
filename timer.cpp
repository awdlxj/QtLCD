#include "timer.h"
#include <windows.h>
#include <iostream>

using namespace std;

double timer::gettimerfreq()//获得时钟周期频率，必须执行至少一次
{
	LARGE_INTEGER litmp;
	QueryPerformanceFrequency(&litmp);
	timerfreq = (double)litmp.QuadPart;//   获得计数器的时钟频率
	return timerfreq;
}

bool timer::starttimer() //开始计时，成功返回1，失败返回0。失败原因：至少执行一次gettimerfreq。
{

	if (timerfreq < 0)
	{
		return 0;
	}
	else
	{
		LARGE_INTEGER  litmp;
		QueryPerformanceCounter(&litmp);
		this->startcycle = litmp.QuadPart;
		return 1;
	}
}
double timer::getthroughtime()//取出计时经历时间，单位：s，成功返回双精度时间，失败返回一个负数。失败原因：至少执行一次gettimerfreq或并未开始计时
{
	if (timerfreq < 0)
	{
		return -1.0;
	}
	else if (this->startcycle < 0)
	{
		return -1.0;
	}
	else
	{
		LARGE_INTEGER   litmp;
		long long   QPart;
		double   dfMinus, dfTim;
		QueryPerformanceCounter(&litmp);
		QPart = litmp.QuadPart;//获得中止值
		dfMinus = (double)(QPart - this->startcycle);
		dfTim = dfMinus / timerfreq;//   计算对应的时间值，单位为秒
		return dfTim;
	}
}
double timer::endtimer()//取出计时经历时间并结束计时，单位：s，成功返回双精度时间，失败返回一个负数。失败原因：至少执行一次gettimerfreq或并未开始计时
{
	if (timerfreq < 0)
	{
		return -1.0;
	}
	else if (this->startcycle < 0)
	{
		return -1.0;
	}
	else
	{
		LARGE_INTEGER   litmp;
		long long   QPart;
		double   dfMinus, dfTim;
		QueryPerformanceCounter(&litmp);
		QPart = litmp.QuadPart;//获得中止值
		dfMinus = (double)(QPart - this->startcycle);
		dfTim = dfMinus / timerfreq;//   计算对应的时间值，单位为秒
		this->startcycle = -99999;
		return dfTim;
	}
}
timer::timer()
{
	timerfreq = -99999;
	this->gettimerfreq();
	this->startcycle = -99999;
}

bool cls() //编程方式实现清除屏幕，防止屏幕闪烁
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };    /* here's where we'll home the cursor */
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
	DWORD dwConSize;                 /* number of character cells in the current buffer */

	//CONSOLE_CURSOR_INFO CursorInfo;
	//GetConsoleCursorInfo(hConsole, &CursorInfo);//获取控制台光标信息
	//CursorInfo.bVisible = false; //隐藏控制台光标
	//SetConsoleCursorInfo(hConsole, &CursorInfo);//设置控制台光标状态

	/* get the number of character cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return false;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	/* fill the entire screen with blanks */
	if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten))
		return false;

	/* get the current text attribute */
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return false;

	/* now set the buffer's attributes accordingly */
	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten))
		return false;

	/* put the cursor at (0, 0) */
	if (!SetConsoleCursorPosition(hConsole, coordScreen))
		return false;
}