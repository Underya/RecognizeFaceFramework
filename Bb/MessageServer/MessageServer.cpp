// MessageServer.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "MessageServer.h"


// This is an example of an exported variable
MESSAGESERVER_API int nMessageServer=0;

// This is an example of an exported function.
MESSAGESERVER_API int fnMessageServer(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CMessageServer::CMessageServer()
{
    return;
}
