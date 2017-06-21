#ifndef TABLE_FRAME_SINK_HEAD_FILE
#define TABLE_FRAME_SINK_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgCustomRule.h"
#include "..\��Ϸ�ͻ���\GameLogic.h"

//////////////////////////////////////////////////////////////////////////

#define MAX_ROBOTCOUNT		1000

//////////////////////////////////////////////////////////////////////////
#define IDI_WRITE_SCORE       10			//������ϢID

#define IDT_WRITE_SCORE1      16           //����ʱ��
#define IDT_WRITE_SCORE2      5            //ȫ�������ƻ��ߵ�ˮʱ��

//��Ϸ������
class CTableFrameSink : public ITableFrameSink, public ITableUserAction
{
	//�������
protected:
	CGameLogic							m_GameLogic;										//��Ϸ�߼�
	ITableFrame							* m_pITableFrame;									//��ܽӿ�
	const tagGameServiceOption			* m_pGameServiceOption;								//���ò���
	tagCustomRule *						m_pGameCustomRule;									//�Զ�����

	//���Ա���
protected:
	static const WORD					m_wPlayerCount;										//��Ϸ����
	static const BYTE					m_GameStartMode;									//��ʼģʽ
	BYTE                                m_nAndroidCount;                                    //�������ӻ����˵�����

	int									m_nLeftAndroidchairID;								//�뿪������ID    
	BOOL								m_bNomalEnd;										//�Ƿ���������

	//��Ϸ����
protected:
	CMD_S_GameEnd						m_sGameEnd;											//��Ϸ��������
	BYTE								m_bUserCardData[GAME_PLAYER][HAND_CARD_COUNT];		//����˿�	7
	BYTE								m_bSegmentCard[GAME_PLAYER][3][5];					//�ֶ��˿�	7
	bool								m_bFinishSegment[GAME_PLAYER];						//��ɷֶ�
	BYTE								m_bShowCardCount;									//̯����Ŀ
	BYTE								m_bCompleteCompareCount ;							//��ɱȽ�
	BYTE								m_bOverTime[GAME_PLAYER];							//̯�Ƴ�ʱ
	bool								m_bUserLeft[GAME_PLAYER];							//���ǿ��
	bool                                m_bSpecialTypeTable[GAME_PLAYER];                   //�Ƿ���������	7
	int                                 m_nPlayerCount;                                     //ʵ���������
	TCHAR                               m_lpLeftszName[GAME_PLAYER][MAX_PATH];              //������ҵ�����
	int                                 m_nLeftChairID[GAME_PLAYER];                        //������ҵ����Ӻ�
	LONG                                m_lLeftScore[GAME_PLAYER];                          //������ҿ۵÷���
	bool                                m_bPlayer[GAME_PLAYER];                             //��Ҵ���
	bool                                m_bOnePlayer;                                       //�Ƿ�ֻʣһ�����
	bool                                m_bDragon[GAME_PLAYER];                             //�Ƿ�ˮ	7
	tagScoreInfo                        m_tagScoreInfo[GAME_PLAYER];                        //д��
	LONG                                m_lGameEndTax;                                      //��Ϸ������˰��
	bool                                m_bGameEnd;                                         //��Ϸ�Ƿ����
	LONG                                m_lLefUserScore[GAME_PLAYER];                       //ǿ����ҵķ���
	BYTE								cbResult[GAME_PLAYER][3];							//ÿһ���ĵ���
	BYTE								cbSpecialResult[GAME_PLAYER];						//�������͵ĵ���
	SCORE								m_lCellScore;										//��Ԫ�׷�

	//
private:
	int                                 m_bCompareResult[GAME_PLAYER][3];		//ÿһ���ȽϽ��
	int									m_bShootState[6][2];					//��ǹ(0Ӯ�����,1������)
	int									m_bThreeKillResult[GAME_PLAYER];		//ȫ�ݴ�Ӽ���
	int								    m_bToltalWinDaoShu[GAME_PLAYER];		//�ܹ�����
	int                                 m_bCompareDouble[GAME_PLAYER];			//��ǹ�ĵ���
	int                                 m_bSpecialCompareResult[GAME_PLAYER];	//�������ͱȽϽ�� 
	LONG								m_lGameScore[GAME_PLAYER];				//��Ϸ����
	BYTE								m_nXShoot;								//���Ҵ�ǹ

	//���Ʊ���
protected:
	TCHAR								m_szRoomName[32];						//���÷���
	TCHAR								m_szConfigFileName[MAX_PATH];			//�����ļ�
	TCHAR								m_szConfigFilePath[MAX_PATH];			//��������ļ�·��

	//�����˻���������Ϣ
	bool								m_bIsCheat;						//�Ƿ����ף����ƣ�
	LONG                                m_lRobotloseMax;				//����������������и��ʻ���
	LONG                                m_lRobotLoseMaxChange;			//����������������ٷְٻ���
	BYTE                                m_btRobotLoseChangePercent;		//��������֣����ưٷֱ�

	LONG                                m_lRealBankerRobotLoseMax;				//�и��ʻ��Ƶ���ʼ��ַ���
	LONG                                m_lRealBankerRobotLoseMaxChange;		//�ٷְٻ��Ƶ���ʼ��ַ���
	BYTE                                m_btRealBankerRobotLoseChangePercent;	//��ʼ��֣����ưٷֱ�

	LONG                                m_lRobotProbabilityTanking;		//Ӯ�Ľ�������������и��ʷ�ˮ
	LONG                                m_lRobotDefineTanking;			//Ӯ�Ľ�����������˰ٷְٷ�ˮ
	BYTE                                m_btRobotTankingPercent;		//�����˷�ˮ�İٷֱ�

	BYTE                                m_btUsuallyChangePercent;		//ͨ������£����ưٷֱ�
	BYTE                                m_btRobotWinScorePercent ;		//�۳�������Ӯ�ķ����İٷֱ�
	LONG								m_lRobotWinChiefScore;			//�۳��Ļ�����Ӯ�ķ����ܺ�
	LONG                                m_lRobotResultScore;			//���л�������Ӯ���ܷ�
	LONG                                m_WinnerScore;					//���ֻ�������Ӯ�������

	BOOL								m_IsCheatUser;					//�Ƿ�������
	DWORD								m_dwUserID;						//������Ӯ�����ID
	DWORD								m_dwUserLoseWinPercent;			//�������������Ӯ�İٷֱȸ���
	BOOL								m_bLoseWin;						//���������Ӯ�����䣨1��ʾӮ 0��ʾ�䣩
	LONG								m_lWinMaxGold;					//�������Ӯ�Ľ���������
	LONG								m_lLoseMaxGold;					//���������Ľ����������
	LONG								m_lAllUserGold;					//������ҵ���Ӯ���
	LONG								m_lUserGold;					//�����û��ɼ�

	//�ͻ��˿���
protected:
	bool							m_bControl;								//�Ƿ����
	bool							m_bControlLossWin;						//������Ӯ
	DWORD							m_dwControlID;							//���Ƶ����ID
	int								m_nControlCount;						//���ƴ���

	//��������
public:
	//���캯��
	CTableFrameSink();
	//��������
	virtual ~CTableFrameSink();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID Release() { delete this; }
	//�Ƿ���Ч
	virtual bool  IsValid() { return AfxIsValidAddress(this,sizeof(CTableFrameSink))?true:false; }
	//�ӿڲ�ѯ
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//����ӿ�
public:
	//��ʼ��
	virtual bool Initialization(IUnknownEx * pIUnknownEx);
	//��λ����
	virtual VOID RepositionSink();

	//��ѯ�ӿ�
public:
	//��ѯ�޶�
	virtual SCORE QueryConsumeQuota(IServerUserItem * pIServerUserItem);
	//���ٻ���
	virtual SCORE QueryLessEnterScore(WORD wChairID, IServerUserItem * pIServerUserItem);
	//��ѯ�����
	virtual bool QueryBuckleServiceCharge(WORD wChairID){return true;}
	//���û���
	virtual void SetGameBaseScore(LONG lBaseScore){};

	//��Ϣ�ӿ�
public:
	//��ʼģʽ
	virtual BYTE GetGameStartMode();
	//��Ϸ״̬
	virtual bool IsUserPlaying(WORD wChairID);

	//��Ϣ����
protected:

	//�˳��¼�
	bool OnUserExit(WORD wChairID,WORD wTableID,WORD wUserID);
	//���÷ֶ�
	bool OnSetSegment(const WORD wChairID , const void * pDataBuffer, WORD wDataSize) ;
	//���̯��
	bool OnShowCard(const WORD wChairID , const void * pDataBuffer, WORD wDataSize) ;
    bool BinarySearch(const DWORD array[], int wCount, DWORD wUserID); 

	//��Ϸ�¼�
public:
	//��Ϸ��ʼ
	virtual bool OnEventGameStart();
	//��Ϸ����
	virtual bool OnEventGameConclude(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason);
	//���ͳ���
	virtual bool OnEventSendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE bGameStatus, bool bSendSecret);

	//�¼��ӿ�
public:
	//��ʱ���¼�
	virtual bool OnTimerMessage(DWORD wTimerID, WPARAM wBindParam);
	//��Ϸ��Ϣ����
	virtual bool OnGameMessage(WORD wSubCmdID, VOID * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);
	//�����Ϣ����
	virtual bool OnFrameMessage(WORD wSubCmdID, VOID * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);
	//�����¼�
	virtual bool OnDataBaseMessage(WORD wRequestID, VOID * pData, WORD wDataSize);
	//�����¼�
	virtual bool OnUserScroeNotify(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason);

	//////////////////////////////////////////////////////////////////////////

	//�û��¼�
public:
	//�û�����
	virtual bool OnActionUserOffLine(WORD wChairID, IServerUserItem * pIServerUserItem) { return true; }
	//�û�����
	virtual bool OnActionUserConnect(WORD wChairID, IServerUserItem * pIServerUserItem) { return true; }
	//�û�����
	virtual bool OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	//�û�����
	virtual bool OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser);
	//�û�ͬ��
	virtual bool OnActionUserOnReady(WORD wChairID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize) { return true; }


	void SetPrivateInfo(BYTE bGameTypeIdex, DWORD bGameRuleIdex) {}

	//���ܺ���
private:
	//���ð���
	void ShowCard(BYTE ShowPos);
	//������
	void ComputeResult();
	//����ÿһ���ĵ���
	void ComputeChout();
	//���������ļ�
	void LoadGameINI();
	//д������
	void WriteGameINI();
	//��������
	void ControlCheat();
	//��ҿ���
	bool UserControl();
	//�ͻ��˿���
	bool ClientControl();

//------------------------yueya Game service head ------------------------
public:
	//������Ϸ
	virtual bool ConcludeGame(BYTE cbGameStatus);

};

//////////////////////////////////////////////////////////////////////////

#endif