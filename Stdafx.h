#pragma once




#include <afxwin.h>         // MFC 核心组件和标准组件

#include <afxext.h>         // MFC 扩展



#ifndef _AFX_NO_OLE_SUPPORT

#include <afxole.h>         // MFC OLE 类

#include <afxodlgs.h>       // MFC OLE 对话框类

#include <afxdisp.h>        // MFC 自动化类

#endif // _AFX_NO_OLE_SUPPORT



#include <afxdtctl.h>		// MFC 对 Internet Explorer 4 公共控件的支持

#ifndef _AFX_NO_AFXCMN_SUPPORT

#include <afxcmn.h>			// MFC 对 Windows 公共控件的支持

#endif // _AFX_NO_AFXCMN_SUPPORT


#include <SDKDDKVer.h>





//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef SDK_CONDITION

//////////////////////////////////////////////////////////////////////////////////
//开发环境

//平台环境
#include "..\..\..\开发库\Include\GameServiceHead.h"


#ifndef _DEBUG
#ifndef _UNICODE
#pragma comment (lib,"../../../开发库/Lib/Ansi/KernelEngine.lib")
#else
#pragma comment (lib,"../../../开发库/Lib/Unicode/KernelEngine.lib")
#endif
#else
#ifndef _UNICODE
#pragma comment (lib,"../../../开发库/Lib/Ansi/KernelEngineD.lib")
#else
#pragma comment (lib,"../../../开发库/Lib/Unicode/KernelEngineD.lib")
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////

#else

//////////////////////////////////////////////////////////////////////////////////
//系统环境

//平台环境
#include "..\..\..\..\系统模块\服务器组件\游戏服务\GameServiceHead.h"

#ifndef _DEBUG
#ifndef _UNICODE
#pragma comment (lib,"../../../../系统模块/链接库/Ansi/KernelEngine.lib")
#else
#pragma comment (lib,"../../../../系统模块/链接库/Unicode/KernelEngine.lib")
#endif
#else
#ifndef _UNICODE
#pragma comment (lib,"../../../../系统模块/链接库/Ansi/KernelEngineD.lib")
#else
#pragma comment (lib,"../../../../系统模块/链接库/Unicode/KernelEngineD.lib")
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////

#endif

#include "..\消息定义\CMD_Thirteen.h"

//////////////////////////////////////////////////////////////////////////



