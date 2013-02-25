// mexCommandWrapper.cpp : Defines the exported functions for the DLL application.
//
// Author: Shanqing Cai (shanqing.cai@gmail.com)
// Created 02/24/2013

/* #include <stdlib.h> */
#include <windows.h>
#include <process.h>
#include <String.h>

#include "stdafx.h"
#include "mex.h"

using namespace std;

//#define DEBUG

const char mexProgName[] = "mexCommandWrapper";

typedef struct funcCallInfo_t {
	char *cmdLine;
} funcCallInfo;

void cmdCall_wrap(void *finfo) {
#ifdef DEBUG
	printf("cmdLine = %s\n", ((funcCallInfo *)finfo)->cmdLine);
#endif
	system(((funcCallInfo *)finfo)->cmdLine);

	if (finfo)
		free((funcCallInfo *)finfo);
}

//static void ForceForegroundWindow(HWND hWnd) 
///* This function is adapted from "SHShadow's" post at : */
///* http://www.codeproject.com/Tips/76427/How-to-bring-window-to-top-with-SetForegroundWindo */
//{
//	HWND hWndFg = GetForegroundWindow();
//    unsigned int foreThread = GetWindowThreadProcessId(hWndFg, NULL);
//    unsigned int appThread = GetCurrentThreadId();
//	LPWSTR fgWinTitle;
//	BOOL attachOkay;
//
//	printf("ForceForegroundWindow: GetForegroundWindow() = %d\n", GetForegroundWindow());
//	printf("ForceForegroundWindow: input window title length = %d\n", GetWindowText(hWnd, fgWinTitle, 256));
//
//	//DEBUG
//	printf("foreThread = %d\n", foreThread);
//	printf("appThread = %d\n", appThread);
//	printf("hWnd = %d\n", hWnd);
//
//    if (foreThread != appThread)
//    {
//        //attachOkay = AttachThreadInput(foreThread, appThread, true);
//		if (attachOkay)
//			printf("Attaching succeeded.\n");
//		else
//			printf("Attaching failed.\n");
//
//        //BringWindowToTop(hWnd);        		
//		//SetActiveWindow(hWnd);
//		//SwitchToThisWindow(hWnd, true);
//		//SwitchToThisWindow(hWnd, false);
//		//BringWindowToTop(hWnd);
//		//SetActiveWindow(hWnd);
//        //ShowWindow(hWnd, SW_SHOW);
//
//		//ShowWindow(hWnd, SW_SHOWNORMAL);
//		//ShowWindow(hWnd, SW_SHOWMAXIMIZED);
//		SetForegroundWindow(hWnd);
//        AttachThreadInput(foreThread, appThread, false);
//    }
//    else
//    {
//        BringWindowToTop(hWnd);
//        ShowWindow(hWnd, SW_SHOW);
//    }
//}



/* Usage of mex function: mex(cmdLine) */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] ) {
	char *cmdLine;
	funcCallInfo *fCallInfo = NULL;
	HWND hwnd, t_hwnd;
	/* mwSize inArgDims[2]; */	
	LPWSTR fgWinTitle;
	unsigned int mexThreadId = GetCurrentThreadId();

	/* Find the handle to the main matlab window */
	hwnd = GetForegroundWindow();
	t_hwnd = GetWindow(hwnd, GW_HWNDFIRST);

	//do {
	//	//printf("t_hwnd = %d\n", t_hwnd);
	//	GetWindowText(t_hwnd, fgWinTitle, 512);
	//} while (t_hwnd = GetWindow(t_hwnd, GW_HWNDNEXT));
	/* ~Find the handle to the main matlab window */

	if (nrhs < 1) {
		mexErrMsgTxt("Incorrect input argument format");
	}

#ifdef DEBUG
	mexPrintf("%s: nrhs = %d\n", mexProgName, nrhs);
#endif

	/* Get the input function name */
	cmdLine = mxArrayToString(prhs[0]);
#ifdef DEBUG
	mexPrintf("%s: cmdLine = \'%s\'\n", mexProgName, cmdLine);
#endif

	fCallInfo = (funcCallInfo *) calloc(1, sizeof(funcCallInfo));
	fCallInfo->cmdLine = cmdLine;

	/* cmdCall_wrap(fCallInfo); */
	_beginthread(cmdCall_wrap, 0, (void *)fCallInfo);

	//printf("hwnd = %d\n", hwnd);
	//printf("mexThreadId = %d\n", mexThreadId);
	Sleep(80);
	//ForceForegroundWindow(hwnd);
	SetForegroundWindow(hwnd);
}
