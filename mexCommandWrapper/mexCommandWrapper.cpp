// mexCommandWrapper.cpp : Defines the exported functions for the DLL application.
//
// Author: Shanqing Cai (shanqing.cai@gmail.com)
// Created 02/24/2013

/* #include <stdlib.h> */
#include <windows.h>
#include <process.h>

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

/* Usage of mex function: mex(cmdLine) */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] ) {
	char *cmdLine;			
	funcCallInfo *fCallInfo = NULL;
	/* mwSize inArgDims[2]; */

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

	
}
