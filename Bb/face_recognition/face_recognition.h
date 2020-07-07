// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the FACERECOGNITION_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// FACERECOGNITION_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#pragma once

#ifdef FACERECOGNITION_EXPORTS
#define FACERECOGNITION_API __declspec(dllexport)
#else
#define FACERECOGNITION_API __declspec(dllimport)
#endif

#include "face.h"

// This class is exported from the dll
class FACERECOGNITION_API Cfacerecognition {
public:
	Cfacerecognition(void);
	// TODO: add your methods here.

};

extern FACERECOGNITION_API int nfacerecognition;

FACERECOGNITION_API int fnfacerecognition(void);
