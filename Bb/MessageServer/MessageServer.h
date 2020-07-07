// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the MESSAGESERVER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// MESSAGESERVER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MESSAGESERVER_EXPORTS
#define MESSAGESERVER_API __declspec(dllexport)
#else
#define MESSAGESERVER_API __declspec(dllimport)
#endif

// This class is exported from the dll
class MESSAGESERVER_API CMessageServer {
public:
	CMessageServer(void);
	// TODO: add your methods here.
};

extern MESSAGESERVER_API int nMessageServer;

MESSAGESERVER_API int fnMessageServer(void);
