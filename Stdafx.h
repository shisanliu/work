#pragma once




#include <afxwin.h>         // MFC ��������ͱ�׼���

#include <afxext.h>         // MFC ��չ



#ifndef _AFX_NO_OLE_SUPPORT

#include <afxole.h>         // MFC OLE ��

#include <afxodlgs.h>       // MFC OLE �Ի�����

#include <afxdisp.h>        // MFC �Զ�����

#endif // _AFX_NO_OLE_SUPPORT



#include <afxdtctl.h>		// MFC �� Internet Explorer 4 �����ؼ���֧��

#ifndef _AFX_NO_AFXCMN_SUPPORT

#include <afxcmn.h>			// MFC �� Windows �����ؼ���֧��

#endif // _AFX_NO_AFXCMN_SUPPORT


#include <SDKDDKVer.h>





//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef SDK_CONDITION

//////////////////////////////////////////////////////////////////////////////////
//��������

//ƽ̨����
#include "..\..\..\������\Include\GameServiceHead.h"


#ifndef _DEBUG
#ifndef _UNICODE
#pragma comment (lib,"../../../������/Lib/Ansi/KernelEngine.lib")
#else
#pragma comment (lib,"../../../������/Lib/Unicode/KernelEngine.lib")
#endif
#else
#ifndef _UNICODE
#pragma comment (lib,"../../../������/Lib/Ansi/KernelEngineD.lib")
#else
#pragma comment (lib,"../../../������/Lib/Unicode/KernelEngineD.lib")
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////

#else

//////////////////////////////////////////////////////////////////////////////////
//ϵͳ����

//ƽ̨����
#include "..\..\..\..\ϵͳģ��\���������\��Ϸ����\GameServiceHead.h"

#ifndef _DEBUG
#ifndef _UNICODE
#pragma comment (lib,"../../../../ϵͳģ��/���ӿ�/Ansi/KernelEngine.lib")
#else
#pragma comment (lib,"../../../../ϵͳģ��/���ӿ�/Unicode/KernelEngine.lib")
#endif
#else
#ifndef _UNICODE
#pragma comment (lib,"../../../../ϵͳģ��/���ӿ�/Ansi/KernelEngineD.lib")
#else
#pragma comment (lib,"../../../../ϵͳģ��/���ӿ�/Unicode/KernelEngineD.lib")
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////

#endif

#include "..\��Ϣ����\CMD_Thirteen.h"

//////////////////////////////////////////////////////////////////////////



