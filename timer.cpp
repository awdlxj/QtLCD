#include "timer.h"
#include <windows.h>
#include <iostream>

using namespace std;

double timer::gettimerfreq()//���ʱ������Ƶ�ʣ�����ִ������һ��
{
	LARGE_INTEGER litmp;
	QueryPerformanceFrequency(&litmp);
	timerfreq = (double)litmp.QuadPart;//   ��ü�������ʱ��Ƶ��
	return timerfreq;
}

bool timer::starttimer() //��ʼ��ʱ���ɹ�����1��ʧ�ܷ���0��ʧ��ԭ������ִ��һ��gettimerfreq��
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
double timer::getthroughtime()//ȡ����ʱ����ʱ�䣬��λ��s���ɹ�����˫����ʱ�䣬ʧ�ܷ���һ��������ʧ��ԭ������ִ��һ��gettimerfreq��δ��ʼ��ʱ
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
		QPart = litmp.QuadPart;//�����ֵֹ
		dfMinus = (double)(QPart - this->startcycle);
		dfTim = dfMinus / timerfreq;//   �����Ӧ��ʱ��ֵ����λΪ��
		return dfTim;
	}
}
double timer::endtimer()//ȡ����ʱ����ʱ�䲢������ʱ����λ��s���ɹ�����˫����ʱ�䣬ʧ�ܷ���һ��������ʧ��ԭ������ִ��һ��gettimerfreq��δ��ʼ��ʱ
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
		QPart = litmp.QuadPart;//�����ֵֹ
		dfMinus = (double)(QPart - this->startcycle);
		dfTim = dfMinus / timerfreq;//   �����Ӧ��ʱ��ֵ����λΪ��
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

bool cls() //��̷�ʽʵ�������Ļ����ֹ��Ļ��˸
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };    /* here's where we'll home the cursor */
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
	DWORD dwConSize;                 /* number of character cells in the current buffer */

	//CONSOLE_CURSOR_INFO CursorInfo;
	//GetConsoleCursorInfo(hConsole, &CursorInfo);//��ȡ����̨�����Ϣ
	//CursorInfo.bVisible = false; //���ؿ���̨���
	//SetConsoleCursorInfo(hConsole, &CursorInfo);//���ÿ���̨���״̬

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