#include "StdAfx.h"
#include "Resource.h"
#include "Tableframesink.h"
#include "GameServerManager.h"
#include "AndroidUserItemSink.h"

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameServiceManager::CGameServiceManager(void)
{
	//�ؼ�����
	//m_pDlgCustomRule=NULL;

	//�ں�����
	m_GameServiceAttrib.wKindID=KIND_ID;
	m_GameServiceAttrib.wChairCount=GAME_PLAYER;
	m_GameServiceAttrib.wSupporType=(GAME_GENRE_GOLD|GAME_GENRE_SCORE|GAME_GENRE_MATCH|GAME_GENRE_EDUCATE);

	//���ܱ�־
	m_GameServiceAttrib.cbDynamicJoin=TRUE;
	m_GameServiceAttrib.cbAndroidUser=TRUE;
	m_GameServiceAttrib.cbOffLineTrustee=FALSE;

	//��������
	m_GameServiceAttrib.dwServerVersion=VERSION_SERVER;
	m_GameServiceAttrib.dwClientVersion=VERSION_CLIENT;
	lstrcpyn(m_GameServiceAttrib.szGameName,GAME_NAME,CountArray(m_GameServiceAttrib.szGameName));
	lstrcpyn(m_GameServiceAttrib.szDataBaseName,TEXT("QPTreasureDB"),CountArray(m_GameServiceAttrib.szDataBaseName));
	lstrcpyn(m_GameServiceAttrib.szClientEXEName,TEXT("Thirteen.EXE"),CountArray(m_GameServiceAttrib.szClientEXEName));
	lstrcpyn(m_GameServiceAttrib.szServerDLLName,TEXT("ThirteenServer.DLL"),CountArray(m_GameServiceAttrib.szServerDLLName));

	return;
}

//��������
CGameServiceManager::~CGameServiceManager(void)
{
}

//�ӿڲ�ѯ
VOID * CGameServiceManager::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IGameServiceManager,Guid,dwQueryVer);
	QUERYINTERFACE(IGameServiceCustomRule,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IGameServiceManager,Guid,dwQueryVer);
	return NULL;
}

//������Ϸ��
VOID * CGameServiceManager::CreateTableFrameSink(REFGUID Guid, DWORD dwQueryVer)
{
	//��������
	CTableFrameSink * pTableFrameSink=NULL;
	try
	{
		pTableFrameSink=new CTableFrameSink();
		if (pTableFrameSink==NULL) throw TEXT("����ʧ��");
		void * pObject=pTableFrameSink->QueryInterface(Guid,dwQueryVer);
		if (pObject==NULL) throw TEXT("�ӿڲ�ѯʧ��");
		return pObject;
	}
	catch (...) {}

	//��������
	SafeDelete(pTableFrameSink);

	return NULL;
}

//��������
VOID * CGameServiceManager::CreateAndroidUserItemSink(REFGUID Guid, DWORD dwQueryVer)
{
	//��������//////////
	CAndroidUserItemSink * pAndroidUserItemSink=NULL;
	try
	{
		//��������
		pAndroidUserItemSink=new CAndroidUserItemSink();
		if (pAndroidUserItemSink==NULL) throw TEXT("����ʧ��");
		//��ѯ�ӿ�
		void * pObject=pAndroidUserItemSink->QueryInterface(Guid,dwQueryVer);
		if (pObject==NULL) throw TEXT("�ӿڲ�ѯʧ��");
		return pObject;
	}
	catch (...) {}

	//ɾ������
	SafeDelete(pAndroidUserItemSink);

	return NULL;
}

//��������
VOID * CGameServiceManager::CreateGameDataBaseEngineSink(REFGUID Guid, DWORD dwQueryVer)
{
	return NULL;
}
//��ȡ����
bool CGameServiceManager::GetServiceAttrib(tagGameServiceAttrib & GameServiceAttrib)
{
	GameServiceAttrib=m_GameServiceAttrib;
	return true;
}

//�����޸�
bool CGameServiceManager::RectifyParameter(tagGameServiceOption & GameServiceOption)
{
	//Ч�����
	ASSERT(&GameServiceOption!=NULL);
	if (&GameServiceOption==NULL) return false;

	//���ֵ���
	GameServiceOption.lCellScore=__max(1L,GameServiceOption.lCellScore);

	//��ҷ���
	if (GameServiceOption.wServerType&GAME_GENRE_GOLD)
	{
		GameServiceOption.lMinTableScore=__max(GameServiceOption.lCellScore*300L,GameServiceOption.lMinTableScore);
	}
	return true;
}

//��ȡ����
bool CGameServiceManager::SaveCustomRule(LPBYTE pcbCustomRule, WORD wCustonSize)
{
	//Ч��״̬
	ASSERT(m_pDlgCustomRule!=NULL);
	if (m_pDlgCustomRule==NULL) return false;

	//��������
	ASSERT(wCustonSize>=sizeof(tagCustomRule));
	tagCustomRule * pCustomRule=(tagCustomRule *)pcbCustomRule;

	//��ȡ����
	if (m_pDlgCustomRule->GetCustomRule(*pCustomRule)==false)
	{
		return false;
	}

	return true;
}

//Ĭ������
bool CGameServiceManager::DefaultCustomRule(LPBYTE pcbCustomRule, WORD wCustonSize)
{
	//��������
	ASSERT(wCustonSize>=sizeof(tagCustomRule));
	tagCustomRule * pCustomRule=(tagCustomRule *)pcbCustomRule;

	return true;
}

//��������
HWND CGameServiceManager::CreateCustomRule(CWnd * pParentWnd, CRect rcCreate, LPBYTE pcbCustomRule, WORD wCustonSize)
{
	//��������
	if (m_pDlgCustomRule==NULL)
	{
		m_pDlgCustomRule=new CDlgCustomRule;
	}

	//��������
	if (m_pDlgCustomRule->m_hWnd==NULL)
	{
		//������Դ
		AfxSetResourceHandle(GetModuleHandle(m_GameServiceAttrib.szServerDLLName));

		//��������
		m_pDlgCustomRule->Create(IDD_CUSTOM_RULE,pParentWnd);

		//��ԭ��Դ
		AfxSetResourceHandle(GetModuleHandle(NULL));
	}

	////���ñ���
	ASSERT(wCustonSize>=sizeof(tagCustomRule));
	m_pDlgCustomRule->SetCustomRule(*((tagCustomRule *)pcbCustomRule));

	//��ʾ����
	m_pDlgCustomRule->SetWindowPos(NULL,rcCreate.left,rcCreate.top,rcCreate.Width(),rcCreate.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);

	return m_pDlgCustomRule->GetSafeHwnd();
}

//////////////////////////////////////////////////////////////////////////////////

//����������
extern "C" __declspec(dllexport) VOID * CreateGameServiceManager(const GUID & Guid, DWORD dwInterfaceVer)
{
	static CGameServiceManager GameServiceManager;
	return GameServiceManager.QueryInterface(Guid,dwInterfaceVer);
}

//////////////////////////////////////////////////////////////////////////