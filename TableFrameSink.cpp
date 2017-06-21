#include "StdAfx.h"
#include "TableFrameSink.h"

//////////////////////////////////////////////////////////////////////////

//��̬����
const WORD			CTableFrameSink::m_wPlayerCount=GAME_PLAYER;			//��Ϸ����
const BYTE			CTableFrameSink::m_GameStartMode=START_MODE_FULL_READY;	//��ʼģʽ
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

//���캯��
CTableFrameSink::CTableFrameSink()
{
	//AllocConsole();
	//freopen("CON","wt",stdout);
	srand((unsigned)time(NULL));
	//�������
	m_pITableFrame=NULL;
	m_pGameServiceOption=NULL;

	m_nLeftAndroidchairID=-1;
	m_bNomalEnd=false;

	//�ͻ��˿���
	m_bControl = false;
	m_bControlLossWin = false;
	m_dwControlID = INVALID_CHAIR;
	m_nControlCount = 0;
	//��Ϸ����
	memset(&m_sGameEnd,0,sizeof(m_sGameEnd));
	ZeroMemory(m_bCompareResult , sizeof(m_bCompareResult)) ;
	ZeroMemory(m_bShootState , sizeof(m_bShootState)) ;
	ZeroMemory(m_bThreeKillResult , sizeof(m_bThreeKillResult)) ;
	ZeroMemory(m_bToltalWinDaoShu , sizeof(m_bToltalWinDaoShu)) ;
	ZeroMemory(m_bCompareDouble , sizeof(m_bCompareDouble)) ;
	ZeroMemory(m_bSpecialCompareResult , sizeof(m_bSpecialCompareResult)) ;
	ZeroMemory(m_lGameScore , sizeof(m_lGameScore)) ;
	m_nXShoot = 0;

	ZeroMemory(m_bUserCardData , sizeof(m_bUserCardData)) ;
	ZeroMemory(m_bSegmentCard , sizeof(m_bSegmentCard)) ;
	ZeroMemory(m_bFinishSegment , sizeof(m_bFinishSegment)) ;
	ZeroMemory(m_bSpecialTypeTable,sizeof(m_bSpecialTypeTable));
	m_bShowCardCount=0 ; 
	m_bCompleteCompareCount=0 ;
	m_nPlayerCount=0;
	m_bOnePlayer=false;
	ZeroMemory(m_lpLeftszName,sizeof(m_lpLeftszName));
	ZeroMemory(m_nLeftChairID,sizeof(m_nLeftChairID));
	ZeroMemory(m_lLeftScore,sizeof(m_lLeftScore));
	ZeroMemory(m_bPlayer,sizeof(m_bPlayer));
	ZeroMemory(m_bDragon,sizeof(m_bDragon));
	ZeroMemory(m_tagScoreInfo,sizeof(m_tagScoreInfo));
	ZeroMemory(m_lLefUserScore,sizeof(m_lLefUserScore));
	m_lGameEndTax=0;
	m_bGameEnd=false;
	m_nAndroidCount=0;
	m_lCellScore=0;
	for(BYTE i=0; i<GAME_PLAYER; ++i)
	{
		m_bOverTime[i] = false ;
		m_bUserLeft[i] = false ;
	}
	//���ñ���
	m_bIsCheat = false;
	m_WinnerScore = 0;
	m_lRobotloseMax = 0;
	m_lRobotLoseMaxChange = 0;
	m_btRobotLoseChangePercent = 0;
	m_lRealBankerRobotLoseMax = 0;
	m_lRobotProbabilityTanking = 0;
	m_lRobotDefineTanking = 0;
	m_btRobotTankingPercent = 0;
	m_lRealBankerRobotLoseMaxChange = 0;
	m_btRealBankerRobotLoseChangePercent = 0;
	m_btUsuallyChangePercent = 0;
	m_btRobotWinScorePercent = 0;
	m_lRobotWinChiefScore = 0;
	m_lRobotResultScore = 0;

	m_IsCheatUser = FALSE;
	m_dwUserID = 0;
	m_dwUserLoseWinPercent = 0;
	m_bLoseWin = FALSE;
	m_lWinMaxGold = 0;
	m_lLoseMaxGold = 0;
	m_lAllUserGold = 0;
	m_lUserGold = 0;
	return;
}

//��������
CTableFrameSink::~CTableFrameSink(void)
{
}

//�ӿڲ�ѯ
VOID * CTableFrameSink::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITableFrameSink,Guid,dwQueryVer);
	QUERYINTERFACE(ITableUserAction,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITableFrameSink,Guid,dwQueryVer);
	return NULL;
}

//��ʼ��
bool CTableFrameSink::Initialization(IUnknownEx * pIUnknownEx)
{
	//��ѯ�ӿ�
	ASSERT(pIUnknownEx!=NULL);
	m_pITableFrame=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITableFrame);
	if (m_pITableFrame==NULL) return false;

	//��ȡ����
	m_pGameServiceOption=m_pITableFrame->GetGameServiceOption();
	ASSERT(m_pGameServiceOption!=NULL);

	m_pITableFrame->SetStartMode(START_MODE_FULL_READY);

	m_pGameCustomRule = (tagCustomRule *)m_pITableFrame->GetCustomRule();

	//��ȡ����
	TCHAR szPath[MAX_PATH]=TEXT("");
	GetCurrentDirectory(sizeof(szPath),szPath);
	_sntprintf_s(m_szConfigFileName, sizeof(m_szConfigFileName), TEXT("%s\\GameControl\\Thirteen.ini"), szPath);
	_sntprintf_s(m_szConfigFilePath, sizeof(m_szConfigFilePath), TEXT("%s\\GameControl\\User.ini"), szPath);

	ASSERT(m_pGameServiceOption!=NULL);
	_sntprintf_s(m_szRoomName, sizeof(m_szRoomName), TEXT("%d"), m_pGameServiceOption->wServerID);
	return true;
}

//��λ����
VOID CTableFrameSink::RepositionSink()
{
	//д������
	WriteGameINI();

	//��Ϸ����
	memset(&m_sGameEnd,0,sizeof(m_sGameEnd));
	ZeroMemory(m_bCompareResult , sizeof(m_bCompareResult)) ;
	ZeroMemory(m_bShootState , sizeof(m_bShootState)) ;
	ZeroMemory(m_bThreeKillResult , sizeof(m_bThreeKillResult)) ;
	ZeroMemory(m_bToltalWinDaoShu , sizeof(m_bToltalWinDaoShu)) ;
	ZeroMemory(m_bCompareDouble , sizeof(m_bCompareDouble)) ;
	ZeroMemory(m_bSpecialCompareResult , sizeof(m_bSpecialCompareResult)) ;
	ZeroMemory(m_lGameScore , sizeof(m_lGameScore)) ;
	m_nXShoot = 0;
	m_lUserGold = 0;
	m_WinnerScore = 0;

	ZeroMemory(m_bUserCardData , sizeof(m_bUserCardData));
	ZeroMemory(m_bSegmentCard , sizeof(m_bSegmentCard)) ;
	ZeroMemory(m_bFinishSegment , sizeof(m_bFinishSegment));
	ZeroMemory(m_bSpecialTypeTable,sizeof(m_bSpecialTypeTable));
	m_bShowCardCount=0 ; 
	m_bCompleteCompareCount=0 ;
	m_nPlayerCount=0;
	m_bOnePlayer=false;
	m_bGameEnd=false;
	ZeroMemory(m_lpLeftszName,sizeof(m_lpLeftszName));
	ZeroMemory(m_nLeftChairID,sizeof(m_nLeftChairID));
	ZeroMemory(m_lLeftScore,sizeof(m_lLeftScore));
	ZeroMemory(m_bPlayer,sizeof(m_bPlayer));
	ZeroMemory(m_bDragon,sizeof(m_bDragon));
	ZeroMemory(m_lLefUserScore,sizeof(m_lLefUserScore));
	for(BYTE i=0; i<GAME_PLAYER; ++i)
	{
		m_bOverTime[i] = false ;
		m_bUserLeft[i] = false ;
	}
	return;
}

//��������
SCORE CTableFrameSink::QueryConsumeQuota(IServerUserItem * pIServerUserItem)
{
	//Ч��״̬
	ASSERT((pIServerUserItem!=NULL)&&(pIServerUserItem->GetTableID()==m_pITableFrame->GetTableID()));
	if ((pIServerUserItem==NULL)||(pIServerUserItem->GetTableID()!=m_pITableFrame->GetTableID())) return 0;

	//�û��ж�
	switch (pIServerUserItem->GetUserStatus())
	{
	case US_SIT:		//����״̬
	case US_READY:		//׼��״̬
		{
			return pIServerUserItem->GetUserScore()-m_pGameServiceOption->lMinTableScore;
		}
	case US_PLAYING:	//��Ϸ״̬
	case US_OFFLINE:	//����״̬
		{
							return 0L;
		}
	case US_LOOKON:		//�Թ�״̬
		{
			return pIServerUserItem->GetUserScore();
		}
	}

	return 0L;
}

//���ٻ���
SCORE CTableFrameSink::QueryLessEnterScore(WORD wChairID, IServerUserItem * pIServerUserItem)
{
	return 0L;
}
//��ʼģʽ
BYTE  CTableFrameSink::GetGameStartMode()
{
	return m_GameStartMode;
}

//��Ϸ״̬
bool  CTableFrameSink::IsUserPlaying(WORD wChairID)
{
	return true;
}
//��Ϸ��ʼ
bool  CTableFrameSink::OnEventGameStart()
{
	//����״̬
	m_pITableFrame->SetGameStatus(GS_WK_PLAYING);
	IServerUserItem * pIServerUserItem=NULL;

	m_bControl = false;
	LONGLONG lMixScore=0;
	BYTE nCount=0;
	for (WORD i=0;i<GAME_PLAYER;i++)
	{
		//��ȡ�û�
		IServerUserItem * pIServerUserItem=m_pITableFrame->GetTableUserItem(i);
		if (pIServerUserItem==NULL) continue;
		nCount++;
		if(nCount==1)
			lMixScore=pIServerUserItem->GetUserScore();
		else
		{
			lMixScore=__min(lMixScore,pIServerUserItem->GetUserScore());
		}
	}
	m_lCellScore=__max(lMixScore/36L,m_pGameServiceOption->lCellScore);
	//��Ϸ����
	ZeroMemory(m_bUserCardData , sizeof(m_bUserCardData)) ;
	ZeroMemory(m_bSegmentCard , sizeof(m_bSegmentCard)) ;
	ZeroMemory(m_bFinishSegment , sizeof(m_bFinishSegment)) ;
	m_bShowCardCount=0 ; 
	m_bCompleteCompareCount=0 ;

	int Number=0;
	for(WORD i=0; i<GAME_PLAYER; i++)
	{
		pIServerUserItem = m_pITableFrame->GetTableUserItem(i);
		if(pIServerUserItem!=NULL)
		{
			m_bPlayer[i]=true;
			Number++;
		}
	}
	m_nPlayerCount=Number;
	for(BYTE i=0; i<GAME_PLAYER; ++i)
	{
		m_bOverTime[i] = false ;
		m_bUserLeft[i] = false ;
	}
	//����״̬
	m_pITableFrame->SetGameStatus(GS_WK_PLAYING);
	BYTE bCardData[52];
	m_GameLogic.RandCardList(bCardData , 52);
	for(int i=0;i<GAME_PLAYER;i++)
	{
		CopyMemory(m_bUserCardData[i] , bCardData+i*HAND_CARD_COUNT,HAND_CARD_COUNT);
	}
	//------���ƻ���------
	LoadGameINI();

	//�ͻ��˿��ƻ���
	if(m_nControlCount>0 && m_dwControlID!=INVALID_CHAIR)
	{
		ClientControl();
	}
	else
	{
		bool IsUser = false;
		if(m_IsCheatUser)
		{
			IsUser = UserControl();
		}
		if(!IsUser)
		{
			if(m_bIsCheat)
				ControlCheat();
		}
	}
	///////////////////////

	CMD_S_SendCard SendCard ;
	memset(&SendCard , 0 , sizeof(SendCard));

	SendCard.lCellScore = m_lCellScore;
	//�����˿�
	for(WORD i=0 ; i<GAME_PLAYER ; ++i)
	{
		CopyMemory(SendCard.bCardData , m_bUserCardData[i] , HAND_CARD_COUNT);
		CopyMemory(SendCard.bAllHandCardData,m_bUserCardData,sizeof(SendCard.bAllHandCardData));
		SendCard.wCurrentUser = i ;
		IServerUserItem *pIServerUserItem = m_pITableFrame->GetTableUserItem(i);
		if(pIServerUserItem)
		{
			m_pITableFrame->SendTableData(i,SUB_S_SEND_CARD,&SendCard,sizeof(SendCard));
			m_pITableFrame->SendLookonData(i,SUB_S_SEND_CARD,&SendCard,sizeof(SendCard));
		}
	}

	return true;
}

//------------------------------------yueya-------------------------------------------------
/*
conclude  ����ʱ���� 
���������ɢ �ص���Ϸ������
����������� �ص���Ϸ��������
����쳣���� �������� �ٴ����ӵ�ʱ�� ��Ϣ����
*/
//------------------------------------------------------------------------------------------
bool CTableFrameSink::ConcludeGame(BYTE cbGameStatus)
{
	switch (cbGameStatus)
	{
	case GS_WK_FREE:
		WORD                wChiarID                      =              NULL;
		IServerUserItem *	pIServerUserItem              =		         nullptr;
		BYTE		        bGameStatus                   =              GS_WK_FREE;
		bool                bSendSecret                   =              true;
	
		for (int i = 0; i < GAME_PLAYER; ++i)
		{
			pIServerUserItem = m_pITableFrame->GetTableUserItem(i);
			
			OnEventSendGameScene(i, pIServerUserItem, bGameStatus, bSendSecret);
		}
		return true;
	}
}

//��Ϸ����
bool  CTableFrameSink::OnEventGameConclude(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	switch (cbReason)
	{
	case GER_DISMISS:		//��Ϸ��ɢ
		{
			//Ч�����
			ASSERT(pIServerUserItem!=NULL);
			ASSERT(wChairID<m_wPlayerCount);

			if(m_bGameEnd==false)
			{
				//��������
				CMD_S_GameEnd GameEnd;

				memset(&GameEnd,0,sizeof(GameEnd));
				GameEnd.bLeft=true;
				GameEnd.bEndMode = GER_DISMISS ;

				//������Ϣ
				m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
				m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));

				//������Ϸ
				m_pITableFrame->ConcludeGame(GS_WK_FREE);

			}
			return true;
		}
	case GER_NORMAL:		//�������
		{
			m_bGameEnd=true;
			//MessageBox(NULL,"jieshu1",NULL,NULL);
			//��������
			CMD_S_GameEnd GameEnd;
			memset(&GameEnd,0,sizeof(GameEnd));

			GameEnd.bEndMode = GER_NORMAL;

			//�˿�����
			CopyMemory(GameEnd.cbCardData, m_bUserCardData, sizeof(GameEnd.cbCardData));

			//��ʱ״̬
			CopyMemory(GameEnd.bOverTime, m_bOverTime, sizeof(GameEnd.bOverTime));

			//����״̬
			CopyMemory(GameEnd.bUserLeft, m_bUserLeft, sizeof(GameEnd.bUserLeft));
			CopyMemory(GameEnd.LeftszName,m_lpLeftszName,sizeof(GameEnd.LeftszName));
			CopyMemory(m_lGameScore,m_lLeftScore,sizeof(m_lGameScore));
			for(int i=0;i<GAME_PLAYER;i++)
			{
				GameEnd.bToltalWinDaoShu[i]=m_lGameScore[i]/m_lCellScore;
			}
			ComputeChout();
			//������
			ComputeResult();

			//У����Ӯ�����᲻�����
			/*LONG llWinScore=0;
			LONG llLoseScore=0;
			for(int i=0;i<GAME_PLAYER;i++)
			{
				if(m_lGameScore[i]>0)
				{
					llWinScore+=m_lGameScore[i];
				}
				else
				{
					llLoseScore+=m_lGameScore[i];
				}
			}
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				printf("\n�������%d\n",m_lGameScore[i]);	
			}*/

			for(int i=0;i<GAME_PLAYER;i++)
			{
				LONG lTmpTax;
				if(m_lGameScore[i]>0)
				{
					lTmpTax   = (LONG)(m_lGameScore[i]*m_pGameServiceOption->wRevenueRatio/100);
					GameEnd.lGameEveryTax[i]+=lTmpTax;
					GameEnd.lGameTax	  += lTmpTax;
					m_lGameScore[i] -= lTmpTax;
				}
			}
			int nSpecialCard=0;
			int nDragon=0;
			for(int i=0;i<GAME_PLAYER;i++)
			{
				if(m_bSpecialTypeTable[i]&&m_bPlayer[i])
				{
					nSpecialCard++;
				}
				if(m_bDragon[i]&&m_bPlayer[i])
				{
					nDragon++;
				}
			}
			if((m_nPlayerCount==nSpecialCard+nDragon) || (m_nPlayerCount<=nSpecialCard+1))
			{
				GameEnd.bAllSpecialCard=true;
			}
			else
			{
				GameEnd.bAllSpecialCard=false;
			}
			if(m_bOnePlayer)
			{
				GameEnd.bLeft=true;
			}
			
			m_lGameEndTax=GameEnd.lGameTax;

			GameEnd.m_nXShoot = m_nXShoot;
			CopyMemory(GameEnd.cbCompareResult,m_bCompareResult , sizeof(GameEnd.cbCompareResult)) ;
			CopyMemory(GameEnd.ShootState,m_bShootState , sizeof(GameEnd.ShootState)) ;
			CopyMemory(GameEnd.cbThreeKillResult,m_bThreeKillResult , sizeof(GameEnd.cbThreeKillResult)) ;
			CopyMemory(GameEnd.bToltalWinDaoShu,m_bToltalWinDaoShu , sizeof(GameEnd.bToltalWinDaoShu)) ;
			CopyMemory(GameEnd.cbCompareDouble,m_bCompareDouble , sizeof(GameEnd.cbCompareDouble)) ;
			CopyMemory(GameEnd.cbSpecialCompareResult,m_bSpecialCompareResult , sizeof(GameEnd.cbSpecialCompareResult)) ;
			CopyMemory(GameEnd.bSpecialCard,m_bSpecialTypeTable , sizeof(GameEnd.bSpecialCard)) ;
			CopyMemory(GameEnd.lGameScore,m_lGameScore , sizeof(GameEnd.lGameScore)) ;

			bool IsFourbagger=false;
			//�޸Ļ���
			ZeroMemory(m_tagScoreInfo,sizeof(m_tagScoreInfo));
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				if(m_bThreeKillResult[i]>0)
					IsFourbagger=true;
				if( m_bPlayer[i] == TRUE )
				{	
					m_tagScoreInfo[i].lScore=GameEnd.lGameScore[i];
					m_tagScoreInfo[i].lRevenue=0;
					m_tagScoreInfo[i].cbType=SCORE_TYPE_DRAW;
					if(GameEnd.lGameScore[i]>0)
						m_tagScoreInfo[i].cbType=SCORE_TYPE_WIN;
					else
						m_tagScoreInfo[i].cbType=SCORE_TYPE_LOSE;
				}
			}
			m_lUserGold = 0;
			if(m_IsCheatUser)
			{
				for (WORD wChairID = 0; wChairID < GAME_PLAYER; wChairID++)
				{
					IServerUserItem * pIServerUserItem = m_pITableFrame->GetTableUserItem(wChairID);
					if (pIServerUserItem != NULL)
					{
						if(pIServerUserItem->GetGameID() == m_dwUserID)
						{
							if(m_bPlayer[wChairID])
							{
								m_lUserGold = GameEnd.lGameScore[wChairID];
								m_lAllUserGold += m_lUserGold;
							}
							break;
						}
					}
				}
			}
			//������Ϸ
			if(m_bOnePlayer==false)
			{
				if(GameEnd.bAllSpecialCard)
				{
					GameEnd.nTimer=IDT_WRITE_SCORE2;
					m_pITableFrame->SetGameTimer(IDI_WRITE_SCORE, GameEnd.nTimer*1000,1,NULL);
				}
				else
				{
					BYTE nCount=0;
					if(IsFourbagger)
						nCount=3;
					if(nSpecialCard>0)
						nCount+=3;
					GameEnd.nTimer=IDT_WRITE_SCORE1+m_nXShoot*3+nCount;
					m_pITableFrame->SetGameTimer(IDI_WRITE_SCORE, GameEnd.nTimer*1000,1,NULL);
				}
				//������Ϣ
				m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
				m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
			}
			else
			{
				GameEnd.nTimer=0;
				//������Ϣ
				m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
				m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
				for(int i=0;i<GAME_PLAYER;i++)
				{
					if(m_bPlayer[i]&&m_bUserLeft[i] ==false)
					{
						m_pITableFrame->WriteUserScore(i,m_tagScoreInfo[i]);
					}
				}
				m_pITableFrame->ConcludeGame(GS_WK_FREE);
			}
			m_sGameEnd=GameEnd;

			//����
			if(m_bControl)
			{
				for (WORD i = 0; i < GAME_PLAYER; i++)
				{
					IServerUserItem * pIUserItem = m_pITableFrame->GetTableUserItem(i);
					if (pIUserItem != NULL && !pIUserItem->IsAndroidUser() && GameEnd.lGameScore[i] != 0)
					{
						TCHAR szPath[MAX_PATH]=TEXT("");
						if (GetCurrentDirectory(sizeof(szPath), szPath))
						{
							CTime tm;
							tm = CTime::GetCurrentTime();
							TCHAR szFileName[MAX_PATH];
							TCHAR szBunko[MAX_PATH]=TEXT("");
							CString str1,str2;
							str1.Format(TEXT("%s\t���[%s]�����Ƶĳɼ�\t"),tm.Format("%X"),pIUserItem->GetNickName());
							_sntprintf_s(szFileName, sizeof(szFileName), TEXT("%s\\GameLog\\ControlRecord\\%s.log"), szPath, tm.Format("%Y-%m-%d"));
							_sntprintf_s(szBunko, sizeof(szBunko), TEXT("%d"), GameEnd.lGameScore[i]);
							WritePrivateProfileString(m_szRoomName,str1,szBunko,szFileName);
						}
					}
				}
			}
			return true;
		}
	case GER_USER_LEAVE:		//�û�ǿ��
		{
			//MessageBox(NULL,"qiangtui",NULL,NULL);
			if(m_bGameEnd==false)
			{
				//����ǿ��
				m_bUserLeft[wChairID] = true ;
				m_bOverTime[wChairID] = true ;
				//��������
				BYTE cbPlayerCount=0 ;
				for(WORD wUser=0; wUser<GAME_PLAYER; ++wUser)
				{
					//IServerUserItem *pServerUserItem = m_pITableFrame->GetTableUserItem(wUser) ;
					if(m_bPlayer[wUser]&&m_bUserLeft[wUser] ==false) ++cbPlayerCount ;
				}

				//m_bPlayer[wChairID] = false;
				lstrcpyn(m_lpLeftszName[wChairID],m_pITableFrame->GetTableUserItem(wChairID)->GetNickName(),CountArray(m_pITableFrame->GetTableUserItem(wChairID)->GetNickName()));
				//m_lpLeftszName[wChairID]=m_pITableFrame->GetTableUserItem(wChairID)->GetUserData()->szAgname; 
				
				CMD_S_PlayerLeft  PlayerLeft;
				PlayerLeft.nPlayerLetfChairID=wChairID;
				m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_PLAYER_LEFT,&PlayerLeft,sizeof(PlayerLeft));
				m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_PLAYER_LEFT,&PlayerLeft,sizeof(PlayerLeft));

				if(m_bFinishSegment[wChairID])
				{
					m_bShowCardCount--;
				}
				if(cbPlayerCount==1)
				{
					m_bOnePlayer=true;
				}
				int LossShui=0;
				int iShuiShu[GAME_PLAYER]={0};
				for(int i=0;i<GAME_PLAYER;i++)
				{
					if(!m_bFinishSegment[i] && wChairID!=i)
						ShowCard(i);
				}
				ComputeChout();
				for(int i=0;i<GAME_PLAYER;i++)
				{
					if(	m_bUserLeft[i] !=true && m_bPlayer[i])
					{
						if(m_bSpecialTypeTable[i])
							iShuiShu[i]=cbSpecialResult[i];
						else
						{
							for(int j=0;j<3;j++)
							{
								iShuiShu[i]+=cbResult[i][j];
							}
						}
						LossShui-=iShuiShu[i];
					}
				}
				//printf("�������%d\n",cbPlayerCount);
				tagScoreInfo  ScoreInfo;
				ZeroMemory(&ScoreInfo,sizeof(ScoreInfo));
				ScoreInfo.lScore=LossShui*m_lCellScore;
				ScoreInfo.lRevenue=0;
				ScoreInfo.cbType=SCORE_TYPE_LOSE;
				if((m_pITableFrame->GetTableUserItem(wChairID)->GetUserScore()+ScoreInfo.lScore)<0)
				{
					ScoreInfo.lScore=-(m_pITableFrame->GetTableUserItem(wChairID)->GetUserScore());
					for(int i=0;i<GAME_PLAYER;i++)
					{
						if(	m_bUserLeft[i] !=true && m_bPlayer[i])
						{
							m_lLeftScore[i]+=iShuiShu[i]*ScoreInfo.lScore/(-LossShui);
							printf("���%d,��%d��\n",i,m_lLeftScore[i]);
						}
					}
				}
				else
				{
					for(int i=0;i<GAME_PLAYER;i++)
					{
						if(	m_bUserLeft[i] !=true && m_bPlayer[i])
						{
							m_lLeftScore[i]+=iShuiShu[i]*m_lCellScore;
							printf("���%d,��%d��\n",i,m_lLeftScore[i]);
						}
					}
				}
				//printf("���%d���˶���ˮ%d\n",wChairID,ScoreInfo.lScore);
				m_pITableFrame->WriteUserScore(wChairID,ScoreInfo);
				m_lLeftScore[wChairID]=ScoreInfo.lScore;
				CMD_S_GameEnd GameEnd;
				memset(&GameEnd,0,sizeof(GameEnd));

				GameEnd.bLeft=true;
				GameEnd.bEndMode=GER_USER_LEAVE ;
				//�˿�����
				CopyMemory(GameEnd.cbCardData, m_bUserCardData, sizeof(GameEnd.cbCardData));
				//��ʱ״̬
				CopyMemory(GameEnd.bOverTime, m_bOverTime, sizeof(GameEnd.bOverTime));
				//����״̬
				CopyMemory(GameEnd.bUserLeft, m_bUserLeft, sizeof(GameEnd.bUserLeft));
				CopyMemory(GameEnd.LeftszName,m_lpLeftszName,sizeof(GameEnd.LeftszName));
				CopyMemory(m_lGameScore,m_lLeftScore,sizeof(m_lGameScore));
				ComputeResult();
				for(int i=0;i<GAME_PLAYER;i++)
				{
					if(	m_bUserLeft[i] !=true && m_bPlayer[i])
					{
						if(m_bSpecialTypeTable[i])
						{
							m_bSpecialCompareResult[i]+=cbSpecialResult[i];
							m_bSpecialCompareResult[wChairID]-=cbSpecialResult[i];
							m_bToltalWinDaoShu[wChairID]-=cbSpecialResult[i];
						}
						else
						{
							for(int j=0;j<3;j++)
							{
								m_bCompareResult[i][j]+=cbResult[i][j];
								m_bCompareResult[wChairID][j]-=cbResult[i][j];
								m_bToltalWinDaoShu[wChairID]-=cbResult[i][j];
								m_bToltalWinDaoShu[i]+=cbResult[i][j];
							}
						}
					}
				}
				CopyMemory(GameEnd.cbCompareResult,m_bCompareResult , sizeof(GameEnd.cbCompareResult)) ;
				CopyMemory(GameEnd.bToltalWinDaoShu,m_bToltalWinDaoShu , sizeof(GameEnd.bToltalWinDaoShu)) ;
				CopyMemory(GameEnd.cbCompareDouble,m_bCompareDouble , sizeof(GameEnd.cbCompareDouble)) ;
				CopyMemory(GameEnd.cbSpecialCompareResult,m_bSpecialCompareResult , sizeof(GameEnd.cbSpecialCompareResult)) ;
				CopyMemory(GameEnd.lGameScore,m_lGameScore , sizeof(GameEnd.lGameScore)) ;
				//�������
				//m_lGameScore[wChairID] =-m_pGameServiceOption->lCellScore*m_pGameServiceOption->uFree/100;
				//����˰��
				m_lUserGold = 0;
				if(m_IsCheatUser)
				{
					for (WORD wChairID = 0; wChairID < GAME_PLAYER; wChairID++)
					{
						IServerUserItem * pIServerUserItem = m_pITableFrame->GetTableUserItem(wChairID);
						if (pIServerUserItem != NULL)
						{
							if(pIServerUserItem->GetGameID() == m_dwUserID)
							{
								if(m_bPlayer[wChairID])
								{
									m_lUserGold = GameEnd.lGameScore[wChairID];
									m_lAllUserGold += m_lUserGold;
								}
								break;
							}
						}
					}
				}
				//������Ϣ
				GameEnd.nTimer=0;
				m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
				m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));

				//����
				if(m_bControl)
				{
					for (WORD i = 0; i < GAME_PLAYER; i++)
					{
						IServerUserItem * pIUserItem = m_pITableFrame->GetTableUserItem(i);
						if (pIUserItem != NULL && !pIUserItem->IsAndroidUser() && GameEnd.lGameScore[i] != 0)
						{
							TCHAR szPath[MAX_PATH]=TEXT("");
							if (GetCurrentDirectory(sizeof(szPath), szPath))
							{
								CTime tm;
								tm = CTime::GetCurrentTime();
								TCHAR szFileName[MAX_PATH];
								TCHAR szBunko[MAX_PATH]=TEXT("");
								CString str1,str2;
								str1.Format(TEXT("%s\t���[%s]�����Ƶĳɼ�\t"),tm.Format("%X"),pIUserItem->GetNickName());
								_sntprintf_s(szFileName, sizeof(szFileName), TEXT("%s\\GameLog\\ControlRecord\\%s.log"), szPath, tm.Format("%Y-%m-%d"));
								_sntprintf_s(szBunko, sizeof(szBunko), TEXT("%d"), GameEnd.lGameScore[i]);
								WritePrivateProfileString(m_szRoomName,str1,szBunko,szFileName);
							}
						}
					}
				}

				//������Ϸ
				m_pITableFrame->ConcludeGame(GS_WK_FREE);

				return true ;
			}
		}
	}

	//ASSERT(FALSE);
	return false;
}

//���ͳ���
bool  CTableFrameSink::OnEventSendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE bGameStatus, bool bSendSecret)
{
	switch (bGameStatus)
	{
	case GS_WK_FREE:		//����״̬
		{
			//��������
			CMD_S_StatusFree StatusFree;
			memset(&StatusFree,0,sizeof(StatusFree));

			//printf("%d",pIServerUserItem->GetUserID());
			if(pIServerUserItem->IsAndroidUser())
			{
				pIServerUserItem->SetAndroidUser(true);
			}
			//���ͳ���
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusFree,sizeof(StatusFree));
		}
	case GS_WK_PLAYING:		//��Ϸ״̬
		{
			//��������
			CMD_S_StatusPlay StatusPlay;
			memset(&StatusPlay,0,sizeof(StatusPlay));

			StatusPlay.wCurrentUser = wChiarID;
			StatusPlay.wUserToltalChip=pIServerUserItem->GetUserScore();
			StatusPlay.lCellScore=m_lCellScore;

			CopyMemory(StatusPlay.bHandCardData , m_bUserCardData[wChiarID] , HAND_CARD_COUNT) ;
			CopyMemory(StatusPlay.bSegmentCard , m_bSegmentCard , sizeof(m_bSegmentCard)) ;
			CopyMemory(StatusPlay.bFinishSegment , m_bFinishSegment , sizeof(m_bFinishSegment)) ;
			CopyMemory(StatusPlay.bOverTime, m_bOverTime, sizeof(StatusPlay.bOverTime)) ;

			CopyMemory(StatusPlay.bSpecialTypeTable1, m_bSpecialTypeTable, sizeof(StatusPlay.bSpecialTypeTable1)) ;
			CopyMemory(StatusPlay.bDragon1, m_bDragon, sizeof(StatusPlay.bDragon1)) ;
			CopyMemory(StatusPlay.bAllHandCardData,m_bUserCardData,sizeof(StatusPlay.bAllHandCardData));
			StatusPlay.sGameEnd=m_sGameEnd;

			//���ñ���

			//���ͳ���
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusPlay,sizeof(StatusPlay));
		}
	}

	return false;
}

//��ʱ���¼�
bool CTableFrameSink::OnTimerMessage(DWORD wTimerID, WPARAM wBindParam)
{
	switch(wTimerID)
	{
	case IDI_WRITE_SCORE:
		{
			printf("***************************************************9\n");
			//MessageBox(NULL,"shijian",NULL,NULL);
			for(int i=0;i<GAME_PLAYER;i++)
			{
				if(m_bPlayer[i]&&m_bUserLeft[i] ==false)
				{

					m_pITableFrame->WriteUserScore(i,m_tagScoreInfo[i]);

				}
			}
			m_pITableFrame->KillGameTimer(IDI_WRITE_SCORE);
			CMD_S_ScoreResult ScoreResult;
			ScoreResult.bScoreResult=true;
			m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_SCORE_RESULT,&ScoreResult,sizeof(ScoreResult));
			m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_SCORE_RESULT,&ScoreResult,sizeof(ScoreResult)); 
			m_pITableFrame->ConcludeGame(GS_WK_FREE);
			return true;
		}
	}
	return false;
}

//��Ϸ��Ϣ����
bool CTableFrameSink::OnGameMessage(WORD wSubCmdID, VOID * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{

	switch (wSubCmdID)
	{
	case SUB_C_SEGCARD:				//���÷ֶ�
		{	
			//�û�Ч��
			tagUserInfo * pUserData=pIServerUserItem->GetUserInfo();
			if (pUserData->cbUserStatus!=US_PLAYING) return true;

			return OnSetSegment(pIServerUserItem->GetChairID() , pDataBuffer, wDataSize) ;
		}
	case SUB_C_SHOWCARD:			//���̯��
		{
			//�û�Ч��
			tagUserInfo * pUserData=pIServerUserItem->GetUserInfo();
			if (pUserData->cbUserStatus!=US_PLAYING) return true;

			return OnShowCard(pIServerUserItem->GetChairID() , pDataBuffer, wDataSize) ;
		}
	case SUB_C_OVERTIME:			//��ҳ�ʱ
		{
			//�û�Ч��
			tagUserInfo * pUserData=pIServerUserItem->GetUserInfo();
			if (pUserData->cbUserStatus!=US_PLAYING) return true;

			//���ñ���
			m_bOverTime[pIServerUserItem->GetChairID()] = true;
			m_bShowCardCount++ ;

			//��������
			int nPlayerCount=0 ; 
			for(WORD i=0 ; i<GAME_PLAYER ; ++i)
			{
				IServerUserItem *pIServerUserItem = m_pITableFrame->GetTableUserItem(i);
				if(pIServerUserItem) ++nPlayerCount ;
			}

			//�����ж�
			if(nPlayerCount==m_bShowCardCount)
			{
				OnEventGameConclude(INVALID_CHAIR, NULL, 0) ;
			}

			return true ;
		}
	case SUB_C_USEREXIT:
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_C_UserExit));
			if (wDataSize!=sizeof(CMD_C_UserExit)) return false;
			//�û�Ч��
			tagUserInfo * pUserData=pIServerUserItem->GetUserInfo();
			if (pUserData->cbUserStatus!=US_PLAYING) return true;
			
			CMD_C_UserExit *pUserExit=(CMD_C_UserExit*)pDataBuffer;
			WORD wUserID=pUserExit->wUserID;
			WORD wChairID=pUserExit->wChairID;
			WORD wTableID=pUserExit->wTableID;
			bool bEnterExit=pUserExit->bEnterExit;
			
			return OnUserExit(wChairID,wTableID,wUserID);
		}	
	case SUB_C_AMDIN_COMMAND:
		{
			ASSERT(wDataSize == sizeof(CMD_C_ControlData));
			if(wDataSize!=sizeof(CMD_C_ControlData)) return false;
			//��������
			CMD_C_ControlData * pControlData=(CMD_C_ControlData *)pDataBuffer;
			CString strUserName = pControlData->chUserName;
			m_bControlLossWin = pControlData->bWinloss;
			m_nControlCount = pControlData->cbCount;
			m_dwControlID = INVALID_CHAIR;
			if(m_nControlCount>0)
			{
				for (WORD nID = 0; nID<GAME_PLAYER; nID++)
				{
					IServerUserItem *pServerBankerUser = m_pITableFrame->GetTableUserItem(nID);
					if(pServerBankerUser != NULL)
					{
						CString str = pServerBankerUser->GetNickName();
						if(strUserName.Compare(str)==0)
						{
							m_dwControlID = pServerBankerUser->GetChairID();
						}
					}
				}
			}
			return true;
		}
	}

	return false;
}

//�����Ϣ����
bool CTableFrameSink::OnFrameMessage(WORD wSubCmdID, VOID * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	return false;
}

//�����¼�
bool CTableFrameSink::OnDataBaseMessage(WORD wRequestID, VOID * pData, WORD wDataSize)
{
	return false;
}
//�����¼�
bool CTableFrameSink::OnUserScroeNotify(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	return true;
}

//���÷ֶ�
bool CTableFrameSink::OnSetSegment(const WORD wChairID , const void * pDataBuffer, WORD wDataSize) 
{
	//������֤
	ASSERT(INVALID_CHAIR!=wChairID) ;
	if(INVALID_CHAIR==wChairID) return false;

	ASSERT(sizeof(CMD_C_SegCard)==wDataSize);
	if(sizeof(CMD_C_SegCard)!=wDataSize) return false;

	CMD_C_SegCard *pSetSeg = (CMD_C_SegCard*) pDataBuffer;

	//��������
	CMD_S_SetSegment SetSegment;
	memset(&SetSegment , 0 , sizeof(SetSegment));

	SetSegment.SegmentType = pSetSeg->SegmentType;
	SetSegment.wCurrentUser=wChairID;

	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_SETSEGMENT,&SetSegment,sizeof(SetSegment));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_SETSEGMENT,&SetSegment,sizeof(SetSegment)); 
	return true ;
}
//�˳��¼�
bool CTableFrameSink::OnUserExit(WORD wChairID,WORD wTableID,WORD wUserID)
{
	IServerUserItem * pIServerUserItem=NULL;
	pIServerUserItem=m_pITableFrame->GetTableUserItem(wChairID);
	if (pIServerUserItem!=NULL)
	{
		pIServerUserItem->SetUserStatus(US_NULL,wTableID,wChairID);
		printf("=====�˳��û�����Ϊ%d,IDΪ:%d\n",wChairID,wUserID);

	}
	
	m_pITableFrame->ConcludeGame(GS_WK_FREE);
	return true;
}
//���̯��
bool CTableFrameSink::OnShowCard(const WORD wChairID , const void * pDataBuffer, WORD wDataSize)
{

	//������֤ 
	ASSERT(INVALID_CHAIR!=wChairID) ;
	if(INVALID_CHAIR==wChairID) return false ;

	ASSERT(sizeof(CMD_C_ShowCard)==wDataSize) ;
	if(sizeof(CMD_C_ShowCard)!=wDataSize) return false ;

	CMD_C_ShowCard *pSetSeg = (CMD_C_ShowCard*) pDataBuffer ;

	//��������
	m_bFinishSegment[wChairID] = true ;
	CopyMemory(m_bSegmentCard[wChairID][0] , pSetSeg->bFrontCard , 3) ;
	CopyMemory(m_bSegmentCard[wChairID][1] , pSetSeg->bMidCard , 5) ;
	CopyMemory(m_bSegmentCard[wChairID][2] , pSetSeg->bBackCard , 5) ;

	//��������
	CMD_S_ShowCard  ShowCard ;
	memset(&ShowCard , 0 , sizeof(ShowCard)) ;

	//��������
	WORD wPlayerCount=0 ; 
	for(WORD wID=0 ; wID<GAME_PLAYER ; ++wID)
	{
		IServerUserItem *pIServerUserItem = m_pITableFrame->GetTableUserItem(wID);
		if(pIServerUserItem && !m_bOverTime[wID] && m_bPlayer[wID]) ++wPlayerCount ;
	}

	m_bShowCardCount++ ;

	ShowCard.bDragon = m_GameLogic.isDragon(m_bSegmentCard[wChairID][0], m_bSegmentCard[wChairID][1], m_bSegmentCard[wChairID][2]);
	ShowCard.wShowUser=wChairID;
	m_bDragon[wChairID]=ShowCard.bDragon;
	pSetSeg->bSpecialType = m_GameLogic.isSpecialType(m_bSegmentCard[wChairID][0], m_bSegmentCard[wChairID][1], m_bSegmentCard[wChairID][2]);
	m_bSpecialTypeTable[wChairID]=pSetSeg->bSpecialType;
	if(pSetSeg->bSpecialType)
	{
		ShowCard.bSpecialType=true;
		CopyMemory(ShowCard.btSpecialData, m_bSegmentCard[wChairID][0], 3);
		CopyMemory(ShowCard.btSpecialData+3, m_bSegmentCard[wChairID][1], 5);
		CopyMemory(ShowCard.btSpecialData + 8, m_bSegmentCard[wChairID][2], 5);
	}
	if(m_bShowCardCount!=wPlayerCount)
		ShowCard.bCanSeeShowCard = false ;
	else
		ShowCard.bCanSeeShowCard = true ;
	ShowCard.wCurrentUser =wChairID;
	CopyMemory(ShowCard.bFrontCard , m_bSegmentCard[wChairID][0] , 3);
	CopyMemory(ShowCard.bMidCard ,   m_bSegmentCard[wChairID][1] , 5);
	CopyMemory(ShowCard.bBackCard ,  m_bSegmentCard[wChairID][2] , 5);
	for(WORD i=0 ; i<GAME_PLAYER ; ++i)
	{
		IServerUserItem *pIServerUserItem = m_pITableFrame->GetTableUserItem(i);
		if(pIServerUserItem)
		{
			m_pITableFrame->SendTableData(i,SUB_S_SHOW_CARD,&ShowCard,sizeof(ShowCard));
			m_pITableFrame->SendLookonData(i,SUB_S_SHOW_CARD,&ShowCard,sizeof(ShowCard));
		}
	}

	int nPlayerCount=0 ; 
	for(WORD i=0 ; i<GAME_PLAYER ; ++i)
	{
		IServerUserItem *pIServerUserItem = m_pITableFrame->GetTableUserItem(i);
		if(pIServerUserItem && m_bPlayer[i]) ++nPlayerCount ;
	}

	if(nPlayerCount==m_bShowCardCount)
	{
		OnEventGameConclude(INVALID_CHAIR, NULL, 0) ;
	}

	return true ;
}

//�û�����
bool CTableFrameSink::OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	return true;
}

bool  CTableFrameSink::OnActionUserStandUp( WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser )
{
	CMD_S_UserExit UserExit;
	ZeroMemory(&UserExit,sizeof(UserExit));
	UserExit.nLeftChairID=wChairID;
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_USEREXIT,&UserExit,sizeof(UserExit));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_USEREXIT,&UserExit,sizeof(UserExit)); 
	return true;
}

bool CTableFrameSink::BinarySearch(const DWORD array[], int wCount, DWORD wUserID) 
{
	int begin,center,end;
	begin=0;  //�ײ� 
	end=wCount-1; //β�� 
	while(begin<=end && begin>=0)
	{
		center=(begin+end+1)/2;

		if(array[center]==wUserID)    
		{
			return true;				 
		}
		else
			if(array[center]<wUserID)
				begin=center+1;   //��ǰ�� 
			else
				end=center-1;    //�Ⱥ��� 
	}
	return false;
}

void CTableFrameSink::ComputeChout()
{
	ZeroMemory(cbResult , sizeof(cbResult)) ;
	ZeroMemory(cbSpecialResult , sizeof(cbSpecialResult)) ;//�������
	for(WORD wUser=0; wUser<GAME_PLAYER; ++wUser)
	{
		//����ж�;
		if(!m_bPlayer[wUser]||m_bUserLeft[wUser]) continue ;

		/////////////////////////////////////////////////////////////
		//�Ʊȵ���
		if(m_bSpecialTypeTable[wUser]==false)
		{
			//���ͬ��˳
			if(!cbResult[wUser][2]&&(CT_FIVE_STRAIGHT_FLUSH_FIRST_A==m_GameLogic.GetCardType(m_bSegmentCard[wUser][2],5,m_GameLogic.btCardSpecialData)||
				CT_FIVE_STRAIGHT_FLUSH_NO_A==m_GameLogic.GetCardType(m_bSegmentCard[wUser][2],5,m_GameLogic.btCardSpecialData)
				||CT_FIVE_STRAIGHT_FLUSH_BACK_A==m_GameLogic.GetCardType(m_bSegmentCard[wUser][2],5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][2] = 5;
			}
			//�ж�ͬ��˳
			if(!cbResult[wUser][1]&&(CT_FIVE_STRAIGHT_FLUSH_FIRST_A==m_GameLogic.GetCardType(m_bSegmentCard[wUser][1],5,m_GameLogic.btCardSpecialData)||
				CT_FIVE_STRAIGHT_FLUSH_NO_A==m_GameLogic.GetCardType(m_bSegmentCard[wUser][1],5,m_GameLogic.btCardSpecialData)
				||CT_FIVE_STRAIGHT_FLUSH_BACK_A==m_GameLogic.GetCardType(m_bSegmentCard[wUser][1],5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][1] = 10;
			}
			//���ը��
			if(!cbResult[wUser][2]&&(CT_FIVE_FOUR_ONE==m_GameLogic.GetCardType(m_bSegmentCard[wUser][2],5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][2] = 4;
			}
			//�ж�ը��
			if(!cbResult[wUser][1]&&(CT_FIVE_FOUR_ONE==m_GameLogic.GetCardType(m_bSegmentCard[wUser][1],5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][1] = 8;
			}
			//��غ�«
			if(!cbResult[wUser][2]&&(CT_FIVE_THREE_DEOUBLE==m_GameLogic.GetCardType(m_bSegmentCard[wUser][2],5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][2] = 1;
			}
			//�жغ�«
			if(!cbResult[wUser][1]&&(CT_FIVE_THREE_DEOUBLE==m_GameLogic.GetCardType(m_bSegmentCard[wUser][1],5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][1] = 2;
			}

			//���ͬ��
			if(!cbResult[wUser][2] && CT_FIVE_FLUSH==m_GameLogic.GetCardType(m_bSegmentCard[wUser][2], 5,m_GameLogic.btCardSpecialData))
			{
				cbResult[wUser][2] = 1 ;
			}
			//�ж�ͬ��
			if(!cbResult[wUser][1]&& CT_FIVE_FLUSH==m_GameLogic.GetCardType(m_bSegmentCard[wUser][1], 5,m_GameLogic.btCardSpecialData))
			{
				cbResult[wUser][1] = 1 ;
			}
			//���˳��
			if(!cbResult[wUser][2] && (CT_FIVE_MIXED_FLUSH_NO_A==m_GameLogic.GetCardType(m_bSegmentCard[wUser][2], 5,m_GameLogic.btCardSpecialData)||
				CT_FIVE_MIXED_FLUSH_FIRST_A==m_GameLogic.GetCardType(m_bSegmentCard[wUser][2], 5,m_GameLogic.btCardSpecialData)||
				CT_FIVE_MIXED_FLUSH_BACK_A==m_GameLogic.GetCardType(m_bSegmentCard[wUser][2], 5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][2] = 1 ;
			}
			//�ж�˳��
			if(!cbResult[wUser][1]&&(CT_FIVE_MIXED_FLUSH_NO_A==m_GameLogic.GetCardType(m_bSegmentCard[wUser][1], 5,m_GameLogic.btCardSpecialData)||
				CT_FIVE_MIXED_FLUSH_FIRST_A==m_GameLogic.GetCardType(m_bSegmentCard[wUser][1], 5,m_GameLogic.btCardSpecialData)||
				CT_FIVE_MIXED_FLUSH_BACK_A==m_GameLogic.GetCardType(m_bSegmentCard[wUser][1], 5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][1] = 1 ;
			}
			//�������
			if(!cbResult[wUser][2]&&(CT_THREE==m_GameLogic.GetCardType(m_bSegmentCard[wUser][2],5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][2] = 1;
			}
			//�ж�����
			if(!cbResult[wUser][1]&&(CT_THREE==m_GameLogic.GetCardType(m_bSegmentCard[wUser][1],5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][1] = 1;
			}
			//ǰ������
			if(!cbResult[wUser][0]&&(CT_THREE==m_GameLogic.GetCardType(m_bSegmentCard[wUser][0],3,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][0] = 3;
			}
			//�������
			if(!cbResult[wUser][2]&&(CT_FIVE_TWO_DOUBLE==m_GameLogic.GetCardType(m_bSegmentCard[wUser][2],5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][2] = 1;
			}
			//�ж�����
			if(!cbResult[wUser][1]&&(CT_FIVE_TWO_DOUBLE==m_GameLogic.GetCardType(m_bSegmentCard[wUser][1],5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][1] = 1;
			}
			//���һ��
			if(!cbResult[wUser][2]&&(CT_ONE_DOUBLE==m_GameLogic.GetCardType(m_bSegmentCard[wUser][2],5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][2] = 1;
			}
			//�ж�һ��
			if(!cbResult[wUser][1]&&(CT_ONE_DOUBLE==m_GameLogic.GetCardType(m_bSegmentCard[wUser][1],5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][1] = 1;
			}
			//ǰ��һ��
			if(!cbResult[wUser][0]&&(CT_ONE_DOUBLE==m_GameLogic.GetCardType(m_bSegmentCard[wUser][0],3,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][0] = 1;
			}
			//���ɢ��
			if(!cbResult[wUser][2]&&(CT_SINGLE==m_GameLogic.GetCardType(m_bSegmentCard[wUser][2],5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][2] = 1;
			}
			//�ж�ɢ��
			if(!cbResult[wUser][1]&&(CT_SINGLE==m_GameLogic.GetCardType(m_bSegmentCard[wUser][1],5,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][1] = 1;
			}
			//ǰ��ɢ��
			if(!cbResult[wUser][0]&&(CT_SINGLE==m_GameLogic.GetCardType(m_bSegmentCard[wUser][0],3,m_GameLogic.btCardSpecialData)))
			{
				cbResult[wUser][0] = 1;
			}
		}
		else
		{
			if(!cbSpecialResult[wUser]&&CT_THIRTEEN_FLUSH==m_GameLogic.GetCardType(m_bUserCardData[wUser],13,m_GameLogic.btCardSpecialData))
			{
				cbSpecialResult[wUser]=108;
			}
			if(!cbSpecialResult[wUser]&&CT_THIRTEEN==m_GameLogic.GetCardType(m_bUserCardData[wUser],13,m_GameLogic.btCardSpecialData))
			{
				cbSpecialResult[wUser]=36;
			}
			if(!cbSpecialResult[wUser]&&CT_TWELVE_KING==m_GameLogic.GetCardType(m_bUserCardData[wUser],13,m_GameLogic.btCardSpecialData))
			{
				cbSpecialResult[wUser]=24;
			}
			if(!cbSpecialResult[wUser]&&CT_THREE_STRAIGHTFLUSH==m_GameLogic.GetCardType(m_bUserCardData[wUser],13,m_GameLogic.btCardSpecialData))
			{
				cbSpecialResult[wUser]=20;
			}
			if(!cbSpecialResult[wUser]&&CT_THREE_BOMB==m_GameLogic.GetCardType(m_bUserCardData[wUser],13,m_GameLogic.btCardSpecialData))
			{
				cbSpecialResult[wUser]=20;
			}
			if(!cbSpecialResult[wUser]&&CT_ALL_BIG==m_GameLogic.GetCardType(m_bUserCardData[wUser],13,m_GameLogic.btCardSpecialData))
			{
				cbSpecialResult[wUser]=10;
			}
			if(!cbSpecialResult[wUser]&&CT_ALL_SMALL==m_GameLogic.GetCardType(m_bUserCardData[wUser],13,m_GameLogic.btCardSpecialData))
			{
				cbSpecialResult[wUser]=10;
			}
			if(!cbSpecialResult[wUser]&&CT_SAME_COLOR==m_GameLogic.GetCardType(m_bUserCardData[wUser],13,m_GameLogic.btCardSpecialData))
			{
				cbSpecialResult[wUser]=10;
			}
			if(!cbSpecialResult[wUser]&&CT_FOUR_THREESAME==m_GameLogic.GetCardType(m_bUserCardData[wUser],13,m_GameLogic.btCardSpecialData))
			{
				cbSpecialResult[wUser]=6;
			}
			if(!cbSpecialResult[wUser]&&CT_FIVEPAIR_THREE==m_GameLogic.GetCardType(m_bUserCardData[wUser],13,m_GameLogic.btCardSpecialData))
			{
				cbSpecialResult[wUser]=5;
			}
			if(!cbSpecialResult[wUser]&&CT_SIXPAIR==m_GameLogic.GetCardType(m_bUserCardData[wUser],13,m_GameLogic.btCardSpecialData))
			{
				cbSpecialResult[wUser]=4;
			}
			if(!cbSpecialResult[wUser]&&CT_THREE_STRAIGHT==m_GameLogic.GetCardType(m_bUserCardData[wUser],13,m_GameLogic.btCardSpecialData))
			{
				cbSpecialResult[wUser]=4;
			}
			if(!cbSpecialResult[wUser]&&CT_THREE_FLUSH==m_GameLogic.GetCardType(m_bUserCardData[wUser],13,m_GameLogic.btCardSpecialData))
			{
				cbSpecialResult[wUser]=3;
			}
		}         
	}
}

void CTableFrameSink::ComputeResult()
{
	//��Ϸ����
	ZeroMemory(m_bCompareResult , sizeof(m_bCompareResult)) ;
	ZeroMemory(m_bShootState , sizeof(m_bShootState)) ;
	ZeroMemory(m_bThreeKillResult , sizeof(m_bThreeKillResult)) ;
	ZeroMemory(m_bToltalWinDaoShu , sizeof(m_bToltalWinDaoShu)) ;
	ZeroMemory(m_bCompareDouble , sizeof(m_bCompareDouble)) ;
	ZeroMemory(m_bSpecialCompareResult , sizeof(m_bSpecialCompareResult)) ;
	ZeroMemory(m_lGameScore , sizeof(m_lGameScore)) ;
	m_nXShoot = 0;
	int WinNum[4]={0,0,0,0};
	int WinShuiShu[4]={0,0,0,0};
	for(int i=0;i<6;i++)
	{
		m_bShootState[i][0]=-1;
		m_bShootState[i][1]=-1;
		if(i<4)
		{
			m_bThreeKillResult[i]=0;
		}
	}

	for(WORD wUser=0; wUser<GAME_PLAYER; ++wUser)
	{
		LONG lWinDaoShu=0 ;
		//����ж�
		if(!m_bPlayer[wUser]||m_bUserLeft[wUser]) continue ;

		BYTE const cbConstUserFrontDaoShu= cbResult[wUser][0];
		BYTE const cbConstUserMidDaoShu= cbResult[wUser][1];
		BYTE const cbConstUserBackDaoShu= cbResult[wUser][2];
		BYTE const cbSpecialUserDaoShu=cbSpecialResult[wUser];
		//��Ӯ����

		for(WORD wCmpUser=0; wCmpUser<GAME_PLAYER; ++wCmpUser)
		{
			int nIndex=0;

			//����ж�
			if(!m_bPlayer[wCmpUser]||m_bUserLeft[wCmpUser]) continue ;

			if(wUser != wCmpUser)
			{
				BYTE const cbConstCmpUserFrontDaoShu= cbResult[wCmpUser][0];
				BYTE const cbConstCmpUserMidDaoShu= cbResult[wCmpUser][1];
				BYTE const cbConstCmpUserBackDaoShu= cbResult[wCmpUser][2];
				BYTE const cbSpecialCmpUserDaoShu= cbSpecialResult[wCmpUser];

				if(m_bDragon[wUser]&&m_bDragon[wCmpUser]==false)     ///<һ�ҵ�ˮһ�Ҳ���ˮ
				{
					if(m_bSpecialTypeTable[wCmpUser]==false)			///<��������������
					{

						lWinDaoShu-=cbConstCmpUserFrontDaoShu;
						m_bCompareResult[wUser][0]-=cbConstCmpUserFrontDaoShu;

						lWinDaoShu-=cbConstCmpUserMidDaoShu;
						m_bCompareResult[wUser][1]-=cbConstCmpUserMidDaoShu;

						lWinDaoShu-=cbConstCmpUserBackDaoShu;
						m_bCompareResult[wUser][2]-=cbConstCmpUserBackDaoShu;

					}
					else
					{
						lWinDaoShu-=cbSpecialCmpUserDaoShu;
						m_bSpecialCompareResult[wUser]-=cbSpecialCmpUserDaoShu;
					}
				}
				else if(m_bDragon[wUser]==false&&m_bDragon[wCmpUser])   ///<һ�Ҳ���ˮ��һ�ҵ�ˮ
				{
					if(m_bSpecialTypeTable[wUser]==false)				///<��������������
					{
						lWinDaoShu+=cbConstUserFrontDaoShu;
						m_bCompareResult[wUser][0]+=cbConstUserFrontDaoShu;

						lWinDaoShu+=cbConstUserMidDaoShu;
						m_bCompareResult[wUser][1]+=cbConstUserMidDaoShu;

						lWinDaoShu+=cbConstUserBackDaoShu;
						m_bCompareResult[wUser][2]+=cbConstUserBackDaoShu;

						WinNum[wUser]++;
					}
					else
					{
						lWinDaoShu+=cbSpecialUserDaoShu;
						m_bSpecialCompareResult[wUser]+=cbSpecialUserDaoShu;
					}
				}
				else if(m_bDragon[wUser]==false&&m_bDragon[wCmpUser]==false)
				{

					if(m_bSpecialTypeTable[wUser]==false&&m_bSpecialTypeTable[wCmpUser]==false)
					{

						if(m_GameLogic.CompareCard(m_bSegmentCard[wCmpUser][0], m_bSegmentCard[wUser][0], 3, 3, true)) 
						{
							lWinDaoShu+=cbConstUserFrontDaoShu;
							m_bCompareResult[wUser][0]+=cbConstUserFrontDaoShu;
						}
						else
						{
							lWinDaoShu-=cbConstCmpUserFrontDaoShu;
							m_bCompareResult[wUser][0]-=cbConstCmpUserFrontDaoShu;
						}

						if(m_GameLogic.CompareCard(m_bSegmentCard[wCmpUser][1], m_bSegmentCard[wUser][1], 5, 5, true))
						{
							lWinDaoShu+=cbConstUserMidDaoShu;
							m_bCompareResult[wUser][1]+=cbConstUserMidDaoShu;
						}
						else 
						{
							lWinDaoShu-=cbConstCmpUserMidDaoShu;
							m_bCompareResult[wUser][1]-=cbConstCmpUserMidDaoShu;
						}
						if(m_GameLogic.CompareCard(m_bSegmentCard[wCmpUser][2], m_bSegmentCard[wUser][2], 5, 5, true))
						{
							lWinDaoShu+=cbConstUserBackDaoShu;
							m_bCompareResult[wUser][2]+=cbConstUserBackDaoShu;
						}
						else 
						{
							lWinDaoShu-=cbConstCmpUserBackDaoShu;
							m_bCompareResult[wUser][2]-=cbConstCmpUserBackDaoShu;
						}

						if(m_GameLogic.CompareCard(m_bSegmentCard[wCmpUser][0], m_bSegmentCard[wUser][0], 3, 3, true)&&
							m_GameLogic.CompareCard(m_bSegmentCard[wCmpUser][1], m_bSegmentCard[wUser][1], 5, 5, true)&&
							m_GameLogic.CompareCard(m_bSegmentCard[wCmpUser][2], m_bSegmentCard[wUser][2], 5, 5, true)) 
						{
							lWinDaoShu+=3;
							m_bCompareDouble[wUser]+=3;

							m_bShootState[m_nXShoot][0] = wUser;		///<Ӯ��
							m_bShootState[m_nXShoot][1] = wCmpUser;	///<���
							m_nXShoot++;
							WinNum[wUser]++;
						}

						else if(!m_GameLogic.CompareCard(m_bSegmentCard[wCmpUser][0], m_bSegmentCard[wUser][0], 3, 3, true)&&
							!m_GameLogic.CompareCard(m_bSegmentCard[wCmpUser][1], m_bSegmentCard[wUser][1], 5, 5, true)&&
							!m_GameLogic.CompareCard(m_bSegmentCard[wCmpUser][2], m_bSegmentCard[wUser][2], 5, 5, true)) 
						{
							lWinDaoShu-=3;
							m_bCompareDouble[wUser]-=3;
						}
					}
					else if(m_bSpecialTypeTable[wUser]==true&&m_bSpecialTypeTable[wCmpUser]==false)
					{
						lWinDaoShu+=cbSpecialUserDaoShu;
						m_bSpecialCompareResult[wUser]+=cbSpecialUserDaoShu;
					}
					else if(m_bSpecialTypeTable[wUser]==true&&m_bSpecialTypeTable[wCmpUser]==true)
					{
						if(m_GameLogic.GetCardType(m_bUserCardData[wUser],13,m_GameLogic.btCardSpecialData)>m_GameLogic.GetCardType(m_bUserCardData[wCmpUser],13,m_GameLogic.btCardSpecialData))
						{
							lWinDaoShu+=cbSpecialUserDaoShu;
							m_bSpecialCompareResult[wUser]+=cbSpecialUserDaoShu;
						}
						else if(m_GameLogic.GetCardType(m_bUserCardData[wUser],13,m_GameLogic.btCardSpecialData)<m_GameLogic.GetCardType(m_bUserCardData[wCmpUser],13,m_GameLogic.btCardSpecialData))
						{
							lWinDaoShu-=cbSpecialCmpUserDaoShu;
							m_bSpecialCompareResult[wUser]-=cbSpecialCmpUserDaoShu;
						}
					}
					else if(m_bSpecialTypeTable[wUser]==false&&m_bSpecialTypeTable[wCmpUser]==true)
					{
						lWinDaoShu-=cbSpecialCmpUserDaoShu;
						m_bSpecialCompareResult[wUser]-=cbSpecialCmpUserDaoShu;
					}
				}
			}
		}
		m_lGameScore[wUser] += lWinDaoShu*m_lCellScore;
		m_bToltalWinDaoShu[wUser] += lWinDaoShu;
		printf("����%d\n",m_lGameScore[wUser]);
	}
	///<�����ж��Ƿ�ȫ�ݴ��ڼӼ���
	for(int i=0;i<GAME_PLAYER;i++)
	{
		if(WinNum[i]==3)
		{
			for(int j=0;j<GAME_PLAYER;j++)
			{
				printf("���%d����ȫ�ݴ�\n",i);
				if(i==j)
				{
					printf("����%d\n",m_lGameScore[i]);
					m_lGameScore[j] += 36*m_lCellScore;
					m_bToltalWinDaoShu[j] += 36;
					m_bThreeKillResult[j] = 36;
				}
				else
				{
					m_lGameScore[j] -= 12*m_lCellScore;
					m_bToltalWinDaoShu[j] -= 12 ;
					m_bThreeKillResult[j] = -12;
				}
			}
			break;
		}
	}

	if(m_pGameServiceOption->wServerType==GAME_GENRE_GOLD)
	{
		LONG lMoreScore=0;
		LONG lTrueScore=0;
		bool bdo=false;
		IServerUserItem * pIServerUserItem=NULL;
		//�������ķ��������Լ��ķ�����ֻ���Լ��ķ���
		bool bMoreScore[GAME_PLAYER];
		ZeroMemory(bMoreScore,sizeof(bMoreScore));
		do 
		{
			lMoreScore=0;
			lTrueScore=0;
			bdo=false;
			for(int i=0;i<GAME_PLAYER;i++)
			{
				if(m_bPlayer[i]&&m_bUserLeft[i]==false)
				{
					if(m_lGameScore[i]<0)
					{
						LONG lUserScore=0;
						pIServerUserItem=m_pITableFrame->GetTableUserItem(i);
						if(pIServerUserItem)
							lUserScore=pIServerUserItem->GetUserScore();
						LONG lTemp=lUserScore+m_lGameScore[i];
						if(lTemp<0)                         
						{
							bMoreScore[i]=true;
							bdo=true;
							lTrueScore=-lUserScore;
							lMoreScore=m_lGameScore[i];
							m_lGameScore[i]=-lUserScore;
							break;
						}
					}

				}
			}
			if(bdo)
			{
				int nLeaveCount=0;
				//�ж������
				for(int i=0;i<GAME_PLAYER;i++)
				{
					if(m_bPlayer[i]&&bMoreScore[i]==false)
					{
						nLeaveCount++;
					}
				}
				//�����˰�����ֳ�������ķ�������ֳ������Լ��ķ����ı�������
				int LeaveNum=0;
				for(int i=0;i<GAME_PLAYER;i++)
				{
					if(m_bPlayer[i]&&bMoreScore[i]==false)
					{
						LeaveNum+=m_lGameScore[i]*lTrueScore%lMoreScore;
						m_lGameScore[i]=m_lGameScore[i]*lTrueScore/lMoreScore;
					}
				}
				if(LeaveNum!=0)
				{
					LONG lTemp=LeaveNum%nLeaveCount;
					LONG lEveryTemp=LeaveNum/nLeaveCount;
					int nCount=0;
					int nrand=rand()%nLeaveCount+1;
					for(int i=0;i<GAME_PLAYER;i++)
					{
						if(m_bPlayer[i]&&bMoreScore[i]==false)
						{
							nCount++;
							if(nrand==nCount)
							{
								m_lGameScore[i]+=lEveryTemp;
								m_lGameScore[i]+=lTemp;
							}
							else
							{
								m_lGameScore[i]+=lEveryTemp;
							}
						}
					}
				}
			}

		} while (bdo);

		//Ӯ����Ӯ�ķ��������Լ��ķ���ֻӮ�Լ��ķ���
		ZeroMemory(bMoreScore,sizeof(bMoreScore));
		do 
		{
			lMoreScore=0;
			lTrueScore=0;
			bdo=false;
			for(int i=0;i<GAME_PLAYER;i++)
			{
				if(m_bPlayer[i]&&m_bUserLeft[i]==false)
				{
					if(m_lGameScore[i]>0)
					{
						LONG lUserScore=0;
						pIServerUserItem=m_pITableFrame->GetTableUserItem(i);
						if(pIServerUserItem)
							lUserScore=pIServerUserItem->GetUserScore();
						LONG lTemp=m_lGameScore[i]-lUserScore;
						if(lTemp>0)                         
						{
							bMoreScore[i]=true;
							bdo=true;
							lTrueScore=lUserScore;
							lMoreScore=m_lGameScore[i];
							m_lGameScore[i]=lUserScore;
							break;
						}
					}

				}
			}

			if(bdo)
			{
				int nLeaveCount=0;
				//�ж������ 
				for(int i=0;i<GAME_PLAYER;i++)
				{
					if(m_bPlayer[i]&&bMoreScore[i]==false)
					{
						nLeaveCount++;
					}
				}
				//�����˰���Ӯ�ֳ�����Ӯ�ķ�����Ӯ�ֳ������Լ��ķ����ı�������
				int LeaveNum=0;
				for(int i=0;i<GAME_PLAYER;i++)
				{
					if(m_bPlayer[i]&&bMoreScore[i]==false)
					{
						LeaveNum+=m_lGameScore[i]*lTrueScore%lMoreScore;
						m_lGameScore[i]=m_lGameScore[i]*lTrueScore/lMoreScore;
					}
				}
				if(LeaveNum!=0)
				{
					LONG lTemp=LeaveNum%nLeaveCount;
					LONG lEveryTemp=LeaveNum/nLeaveCount;
					int nCount=0;
					int nrand=rand()%nLeaveCount+1;
					for(int i=0;i<GAME_PLAYER;i++)
					{
						if(m_bPlayer[i]&&bMoreScore[i]==false)
						{
							nCount++;
							if(nrand==nCount)
							{
								m_lGameScore[i]+=lEveryTemp;
								m_lGameScore[i]+=lTemp;
							}
							else
							{
								m_lGameScore[i]+=lEveryTemp;
							}
						}
					}
				}
			}

		} while (bdo);
	}
	m_WinnerScore = 0;
	bool bUser = false;
	for(int i=0;i<GAME_PLAYER;i++)
	{
		IServerUserItem* pIServerUserItem=m_pITableFrame->GetTableUserItem(i);
		if(pIServerUserItem!=NULL && !pIServerUserItem->IsAndroidUser() && m_bPlayer[i])
		{
			bUser = true;
			break;
		}
	}
	if(bUser)
	{
		for(int j=0;j<GAME_PLAYER;j++)
		{
			IServerUserItem* pIServerUserItem=m_pITableFrame->GetTableUserItem(j);
			if(pIServerUserItem!=NULL && pIServerUserItem->IsAndroidUser() && m_bPlayer[j])
			{
				m_WinnerScore+=m_lGameScore[j];
			}
		}
	}
	printf("\n �þֻ�������Ӯ = %d",m_WinnerScore);
	for (BYTE i=0; i<GAME_PLAYER; i++)
	{
		printf("\n ���%d�÷� = %d",i,m_lGameScore[i]);
	}
	/*for (BYTE j=0; j<GAME_PLAYER; j++)
	{
		for (BYTE n=0; n<3; n++)
		{
			for (BYTE m=0; m<5; m++)
			{
				printf("\n m_bSegmentCard[%d][%d][%d] = %d",j,n,m,m_bSegmentCard[j][n][m]);
			}
		}
	}*/
}

void CTableFrameSink::ShowCard(BYTE ShowPos)
{
	if(!m_bPlayer[ShowPos]) return;

	BYTE j=ShowPos;
	BYTE m_bSpecialCardData[HAND_CARD_COUNT];//�����Ƶ�����

	if(m_GameLogic.GetCardType(m_bUserCardData[j],HAND_CARD_COUNT,m_GameLogic.btCardSpecialData)!=CT_INVALID)
	{
		m_GameLogic.SortCardList(m_bUserCardData[j],HAND_CARD_COUNT);

		BYTE m_bHandCardCount=HAND_CARD_COUNT;
		BYTE btSpecialCard[13];
		ZeroMemory(btSpecialCard,sizeof(btSpecialCard));
		tagAnalyseData AnalyseData ;
		m_GameLogic.AnalyseCard(m_bUserCardData[j] , m_bHandCardCount , AnalyseData) ;
		if(m_GameLogic.GetCardType(m_bUserCardData[j],m_bHandCardCount,btSpecialCard)==CT_THIRTEEN_FLUSH||
			m_GameLogic.GetCardType(m_bUserCardData[j],m_bHandCardCount,btSpecialCard)==CT_THIRTEEN||
			m_GameLogic.GetCardType(m_bUserCardData[j],m_bHandCardCount,btSpecialCard)==CT_TWELVE_KING||
			m_GameLogic.GetCardType(m_bUserCardData[j],m_bHandCardCount,btSpecialCard)==CT_THREE_STRAIGHTFLUSH||
			m_GameLogic.GetCardType(m_bUserCardData[j],m_bHandCardCount,btSpecialCard)==CT_THREE_BOMB||
			m_GameLogic.GetCardType(m_bUserCardData[j],m_bHandCardCount,btSpecialCard)==CT_ALL_BIG||
			m_GameLogic.GetCardType(m_bUserCardData[j],m_bHandCardCount,btSpecialCard)==CT_ALL_SMALL||
			m_GameLogic.GetCardType(m_bUserCardData[j],m_bHandCardCount,btSpecialCard)==CT_SAME_COLOR||
			m_GameLogic.GetCardType(m_bUserCardData[j],m_bHandCardCount,btSpecialCard)==CT_FOUR_THREESAME)
		{
			CopyMemory(m_bSpecialCardData,m_bUserCardData[j],sizeof(m_bSpecialCardData));
		}
		else if(m_GameLogic.GetCardType(m_bUserCardData[j],m_bHandCardCount,btSpecialCard)==CT_THREE_FLUSH)
		{
			CopyMemory(m_bSpecialCardData,btSpecialCard,sizeof(btSpecialCard));
		}
		else if(m_GameLogic.GetCardType(m_bUserCardData[j],m_bHandCardCount,btSpecialCard)==CT_THREE_STRAIGHT)
		{
			CopyMemory(m_bSpecialCardData,btSpecialCard,sizeof(btSpecialCard));
		}
		else if(m_GameLogic.GetCardType(m_bUserCardData[j],m_bHandCardCount,btSpecialCard)==CT_FIVEPAIR_THREE)
		{
			BYTE SaveData[5];
			ZeroMemory(SaveData,sizeof(SaveData));
			SaveData[0]=m_bUserCardData[j][AnalyseData.bThreeFirst[0]];
			SaveData[1]=m_bUserCardData[j][AnalyseData.bThreeFirst[0]+1];
			SaveData[2]=m_bUserCardData[j][AnalyseData.bThreeFirst[0]+2];
			m_GameLogic.RemoveCard(SaveData,3,m_bUserCardData[j],m_bHandCardCount);
			m_bHandCardCount-=3;
			m_GameLogic.SortCardList(m_bUserCardData[j],HAND_CARD_COUNT);
			for(int i=0;i<m_bHandCardCount;i++)
			{
				m_bSpecialCardData[i]=m_bUserCardData[j][i];
			}
			m_bSpecialCardData[10]=SaveData[0];
			m_bSpecialCardData[11]=SaveData[1];
			m_bSpecialCardData[12]=SaveData[2];
		}
		else if(m_GameLogic.GetCardType(m_bUserCardData[j],m_bHandCardCount,btSpecialCard)==CT_SIXPAIR)
		{
			BYTE SaveData[5];
			ZeroMemory(SaveData,sizeof(SaveData));
			SaveData[0]=m_bUserCardData[j][AnalyseData.bOneFirst[0]];
			m_GameLogic.RemoveCard(SaveData,1,m_bUserCardData[j],m_bHandCardCount);
			m_bHandCardCount-=1;
			m_GameLogic.SortCardList(m_bUserCardData[j],m_bHandCardCount);
			for(int i=0;i<m_bHandCardCount;i++)
			{
				m_bSpecialCardData[i]=m_bUserCardData[j][i];
			}
			m_bSpecialCardData[12]=SaveData[0];
		}

		for(int i=0;i<3;i++)
		{
			m_bSegmentCard[j][0][i]=m_bSpecialCardData[10+i];
		}

		for(int i=0;i<5;i++)
		{
			m_bSegmentCard[j][1][i]=m_bSpecialCardData[5+i];
		}

		for(int i=0;i<5;i++)
		{
			m_bSegmentCard[j][2][i]=m_bSpecialCardData[i];
		}
		m_bSpecialTypeTable[j]=true;
		m_GameLogic.SortCardList(m_bSegmentCard[j][0],3);
		m_GameLogic.SortCardList(m_bSegmentCard[j][1],5);
		m_GameLogic.SortCardList(m_bSegmentCard[j][2],5);
	}
	else
	{
		m_GameLogic.SortCardList(m_bUserCardData[j],HAND_CARD_COUNT);
		/*for(int i=0;i<13;i++)
		{
			printf("m_bUserCardData[j][i]=%d ",m_bUserCardData[j][i]);
		}*/

		BYTE m_bHandCardCount=HAND_CARD_COUNT;
		tagAnalyseType tagCardType;                            //���ͼ����
		ZeroMemory(&tagCardType,sizeof(tagCardType));
		tagCardType=m_GameLogic.GetType(m_bUserCardData[j],m_bHandCardCount);
		m_GameLogic.TheBestCard(tagCardType,m_bUserCardData[j],m_bHandCardCount,m_bSegmentCard[j][0],m_bSegmentCard[j][1],m_bSegmentCard[j][2]);

		//�����ж�
		bool bDragon = false ;
		if((true==m_GameLogic.CompareCard(m_bSegmentCard[j][0] , m_bSegmentCard[j][1], 3 , 5 , false)) &&
			(true==m_GameLogic.CompareCard(m_bSegmentCard[j][1], m_bSegmentCard[j][2] , 5 , 5 , false)))
			bDragon = false ;
		else
			bDragon = true ;
		if(bDragon)
		{
			//�ָ��˿�
			BYTE bCardCount=HAND_CARD_COUNT;

			const BYTE SEARCHE_COUNT = 10 ;
			ASSERT(bCardCount==13) ;
			if(bCardCount!=13) return ;
			BYTE bAllSegmentCardIndex[SEARCHE_COUNT][3][5] ;			//�ֶ��˿�

			BYTE bSegmentScore[SEARCHE_COUNT] ;							//�ֶ�Ȩ��
			BYTE bCardDataIndex[13] = {0,1,2,3,4,5,6,7,8,9,10,11,12} ;	//�˿��±�
			BYTE bFrontCardType ,										//ǰ������
				bMidCardType,											//�ж�����
				bBackCardType;											//�������
			BYTE bCardData[5] ;
			ZeroMemory(bAllSegmentCardIndex , sizeof(bAllSegmentCardIndex)) ;
			ZeroMemory(bSegmentScore , sizeof(bSegmentScore)) ;

			srand((unsigned)time( NULL ));

			int  bSegCount=0 ;
			LONG bSearchCount = 0 ;
			bool bStop = false ;
			while(false==bStop)
			{
				++bSearchCount ;
				BYTE bCardIndex=0 ;										//�˿��±�
				//ǰ���˿�


				for(BYTE bFrontCard=0 ; bFrontCard<3 ; ++bFrontCard)
			{
				bCardIndex = rand()%(13-bFrontCard) ;
				bAllSegmentCardIndex[bSegCount][0][bFrontCard] = bCardDataIndex[bCardIndex] ;
				bCardData[bFrontCard] = m_bUserCardData[j][bCardDataIndex[bCardIndex]] ;
				bCardDataIndex[bCardIndex] = bCardDataIndex[13-bFrontCard-1] ;
			}

			m_GameLogic.SortCardList(bCardData , 3 , enDescend) ;
			bFrontCardType = m_GameLogic.GetCardType(bCardData , 3,m_GameLogic.btCardSpecialData) ;

			//�ж��˿�
			for(BYTE bMidCard=0 ; bMidCard<5 ; ++bMidCard)
			{
				bCardIndex = rand()%(10-bMidCard) ;
				bAllSegmentCardIndex[bSegCount][1][bMidCard] = bCardDataIndex[bCardIndex] ;
				bCardData[bMidCard] = m_bUserCardData[j][bCardDataIndex[bCardIndex]] ;
				bCardDataIndex[bCardIndex] = bCardDataIndex[10-bMidCard-1] ;
			}

			m_GameLogic.SortCardList(bCardData , 5 , enDescend) ;
			bMidCardType = m_GameLogic.GetCardType(bCardData , 5,m_GameLogic.btCardSpecialData) ;

			//����˿�
			for(BYTE bBackCard=0 ; bBackCard<5 ; ++bBackCard)
			{
				bAllSegmentCardIndex[bSegCount][2][bBackCard] = bCardDataIndex[bBackCard] ;
				bCardData[bBackCard] = m_bUserCardData[j][bCardDataIndex[bBackCard]] ;
			}
			m_GameLogic.SortCardList(bCardData , 5 , enDescend) ;


			bBackCardType = m_GameLogic.GetCardType(bCardData , 5,m_GameLogic.btCardSpecialData) ;


			if(bBackCardType>bMidCardType && bMidCardType>bFrontCardType) 
			{
				bSegmentScore[bSegCount] = bFrontCardType+bMidCardType+bBackCardType ;
				bSegCount++;				
			}

			//�ָ�����
			for(BYTE i=0 ; i<13 ; ++i)
				bCardDataIndex[i] = i ;

			//ֹͣ����
			if(bSegCount>=SEARCHE_COUNT || bSearchCount>=10000) bStop = true ;
			//�ѵ�һ��
			if(true==bStop && 0==bSegCount) bStop = false ; 

			//��������
			if(bSearchCount>=100000)
			{
				BYTE bIndex=0 ; 
				for(BYTE i=0 ; i<3 ; ++i)
					for(BYTE j=0 ; j<5 ; ++j)
						bAllSegmentCardIndex[0][i][j]=bIndex++ ;
				bStop = true ;
				break ;
			}
			}

			//���Ȩ��
			BYTE bMaxScore=bSegmentScore[0] ;
			BYTE bIndex=0 ;
			for(BYTE i=0 ; i<bSegCount ; ++i)
			{
				if(bMaxScore<bSegmentScore[i])
			{
				bIndex=i ;
				bMaxScore=bSegmentScore[i] ;
			}
			//����ǰ��
			for(int i=0;i<3;i++)
			{
				m_bSegmentCard[j][0][i]=m_bUserCardData[j][bAllSegmentCardIndex[bIndex][0][i]];
			}
			//�����жأ����
			for(int i=0;i<5;i++)
			{
				m_bSegmentCard[j][1][i]=m_bUserCardData[j][bAllSegmentCardIndex[bIndex][1][i]];
				m_bSegmentCard[j][2][i]=m_bUserCardData[j][bAllSegmentCardIndex[bIndex][2][i]];
			}
			}
		}
		m_bSpecialTypeTable[j]=false;
		m_GameLogic.SortCardList(m_bSegmentCard[j][0],3);
		m_GameLogic.SortCardList(m_bSegmentCard[j][1],5);
		m_GameLogic.SortCardList(m_bSegmentCard[j][2],5);
	}
}
void CTableFrameSink::LoadGameINI()
{
	//�Ƿ����׻���
	m_bIsCheat = (bool)this->m_pGameCustomRule->isCheat; // GetPrivateProfileInt(m_szRoomName, TEXT("Ischeat"), 0, m_szConfigFileName) > 0;
	
	//�и��ʻ��Ƶ���ʼ��ַ���
	m_lRealBankerRobotLoseMax = this->m_pGameCustomRule->realBankerRobotLoseMax; // GetPrivateProfileInt(m_szRoomName, TEXT("RealBankerRobotLoseMax"), 10000000, m_szConfigFileName);
	//�ٷְٻ��ƣ������������ʼ����
	m_lRealBankerRobotLoseMaxChange = this->m_pGameCustomRule->realBankerRobotLoseMaxChange; // GetPrivateProfileInt(m_szRoomName, TEXT("RealBankerRobotLoseMaxChange"), 30000000, m_szConfigFileName);
	//���ưٷֱ�
	m_btRealBankerRobotLoseChangePercent = this->m_pGameCustomRule->realBankerRobotLoseChangePercent; // GetPrivateProfileInt(m_szRoomName, TEXT("RealBankerRobotLoseChangePercent"), 30, m_szConfigFileName);

	//Ӯ�Ľ�������������и��ʷ�ˮ
	m_lRobotProbabilityTanking = this->m_pGameCustomRule->robotProbabilityTanking; // GetPrivateProfileInt(m_szRoomName, TEXT("RobotProbabilityTanking "), 80000000, m_szConfigFileName);
	//Ӯ�Ľ�����������˰ٷְٷ�ˮ
	m_lRobotDefineTanking = this->m_pGameCustomRule->robotDefineTanking; // GetPrivateProfileInt(m_szRoomName, TEXT("RobotDefineTanking "), 100000000, m_szConfigFileName);
	//�����˷�ˮ�İٷֱ�
	m_btRobotTankingPercent = this->m_pGameCustomRule->robotTankingPercent; // GetPrivateProfileInt(m_szRoomName, TEXT("RobotTankingPercent "), 20, m_szConfigFileName);
}

void CTableFrameSink::WriteGameINI()
{
	//д������
	TCHAR szPath[MAX_PATH]=TEXT("");
	TCHAR szFileName[MAX_PATH];

	//�������ۼƵ���Ӯ����
	m_lRobotResultScore = GetPrivateProfileInt(m_szRoomName,TEXT("RobotResultScore"),0,m_szConfigFileName);
	//�۳��Ļ�����Ӯ�ķ����ܺ�
	m_lRobotWinChiefScore = GetPrivateProfileInt(m_szRoomName,TEXT("RobotWinChiefScore"),0,m_szConfigFileName);
	//�������ۼƵ���Ӯ����
	if (GetCurrentDirectory(sizeof(szPath), szPath))
	{
		TCHAR szRobotResultScore[MAX_PATH]=TEXT("");
		//��ҿ���
		if(m_IsCheatUser && m_lUserGold!=0)
		{
			_sntprintf_s(szRobotResultScore, sizeof(szRobotResultScore), TEXT("%d"), m_lAllUserGold);
			WritePrivateProfileString(TEXT("1"),TEXT("UserGold"),szRobotResultScore,m_szConfigFilePath);
		}
		if(((m_bLoseWin && m_lAllUserGold>m_lWinMaxGold) || (!m_bLoseWin && m_lAllUserGold<m_lLoseMaxGold)) && m_IsCheatUser)
			WritePrivateProfileString(TEXT("1"),TEXT("IsCheatUser"),TEXT("0"),m_szConfigFilePath);

		//�����˿���
		if(m_WinnerScore != 0)
		{
			m_lRobotResultScore+=m_WinnerScore;
			if(m_lRobotResultScore>=m_lRobotDefineTanking)
			{
				long lMoney = m_lRobotResultScore*( m_btRobotWinScorePercent*0.01);
				m_lRobotWinChiefScore += lMoney;
				m_lRobotResultScore -= lMoney;
				//�۳��Ļ�����Ӯ�ķ����ܺ�
				_sntprintf_s(szRobotResultScore, sizeof(szRobotResultScore), TEXT("%d"), m_lRobotWinChiefScore);
				WritePrivateProfileString(m_szRoomName,TEXT("RobotWinChiefScore"),szRobotResultScore,m_szConfigFileName);
			}
			//�������ۼƵ���Ӯ����
			_sntprintf_s(szRobotResultScore, sizeof(szRobotResultScore), TEXT("%d"), m_lRobotResultScore);
			WritePrivateProfileString(m_szRoomName,TEXT("RobotResultScore"),szRobotResultScore,m_szConfigFileName);
		}

		static bool bControl = true;
		TCHAR szBunko[MAX_PATH]=TEXT("");
		CString str;
		CTime tm;
		tm = CTime::GetCurrentTime();
		if(tm.GetHour() == 11)
		{
			bControl = true;
		}
		if(tm.GetHour() == 12)
		{
			if(bControl)
			{
				bControl = false;
				_sntprintf_s(szFileName, sizeof(szFileName), TEXT("%s\\GameLog\\Thirteen.log"), szPath);
				str = tm.Format("%Y-%m-%d %X");
				str+= "\tʤ��";
				_sntprintf_s(szBunko, sizeof(szBunko), TEXT("%d"), m_lRobotResultScore + m_lRobotWinChiefScore);
				WritePrivateProfileString(m_szRoomName,str,szBunko,szFileName);
				//bControl = false;
				m_lRobotWinChiefScore = 0;
				m_lRobotResultScore = 0;
				//�۳��Ļ�����Ӯ�ķ����ܺ�
				_sntprintf_s(szRobotResultScore, sizeof(szRobotResultScore), TEXT("%d"), m_lRobotWinChiefScore);
				WritePrivateProfileString(m_szRoomName,TEXT("RobotWinChiefScore"),szRobotResultScore,m_szConfigFileName);
				//�������ۼƵ���Ӯ����
				_sntprintf_s(szRobotResultScore, sizeof(szRobotResultScore), TEXT("%d"), m_lRobotResultScore);
				WritePrivateProfileString(m_szRoomName,TEXT("RobotResultScore"),szRobotResultScore,m_szConfigFileName);
			}
		}
	}
}
void CTableFrameSink::ControlCheat()
{
	//��֤���
	bool IsAndroid = false;
	bool IsPlayer = false;
	for(BYTE j=0; j<m_wPlayerCount; j++)
	{
		IServerUserItem *pServerBankerUser = m_pITableFrame->GetTableUserItem(j);
		if(pServerBankerUser!=NULL && m_bPlayer[j])
		{
			if(pServerBankerUser->IsAndroidUser())
				IsAndroid = true;
			else
				IsPlayer = true;
		}
	}
	if(IsAndroid && IsPlayer)
	{
		for (BYTE i=0; i<m_wPlayerCount; i++)
		{
			ShowCard(i);
		}
		ComputeChout();
		//������Ӯ
		ComputeResult();

		//��ˮ
		if((m_lRobotResultScore>=m_lRobotDefineTanking) ||
			(m_lRobotResultScore>=m_lRobotProbabilityTanking && rand()%100 < m_btRobotTankingPercent))
		{
			if(m_WinnerScore>0)
			{
				WORD nWinUser=0,nLoseUser=0,nCount=0;
				LONG lMaxScore=0;
				for (BYTE i=0; i<m_wPlayerCount; i++)
				{
					IServerUserItem *pServerUser = m_pITableFrame->GetTableUserItem(i);
					if(pServerUser!=NULL && m_bPlayer[i])
					{
						if(pServerUser->IsAndroidUser() && m_lGameScore[i]>0)
						{
							if(nCount==0)
							{
								lMaxScore=m_lGameScore[i];
								nWinUser=i;
							}
							else
							{
								if(lMaxScore<m_lGameScore[i])
								{
									lMaxScore=m_lGameScore[i];
									nWinUser=i;
								}
							}
							nCount++;
						}
						if(!pServerUser->IsAndroidUser() && m_lGameScore[i]<0)
						{
							nLoseUser=i;
						}
					}
				}
				/*for (BYTE i=0; i<13; i++)
				{
					printf("\n Ӯ m_bUserCardData[%d][%d] = %d",nWinUser,i,m_bUserCardData[nWinUser][i]);
				}
				for (BYTE i=0; i<13; i++)
				{
					printf("\n �� m_bUserCardData[%d][%d] = %d",nLoseUser,i,m_bUserCardData[nLoseUser][i]);
				}*/
				//��������
				BYTE bTempCardData[13] = {};
				memcpy(bTempCardData,	m_bUserCardData[nWinUser],	sizeof(bTempCardData));
				memcpy(m_bUserCardData[nWinUser],	m_bUserCardData[nLoseUser],	sizeof(bTempCardData));
				memcpy(m_bUserCardData[nLoseUser],	bTempCardData,	sizeof(bTempCardData));
				printf("\n Ӯ��%d���䣺%d",nWinUser,nLoseUser);
				printf("\n �����˷�ˮ�ɹ�����");
			}
		}//Ӯ
		else if((m_lRobotResultScore<=m_lRobotLoseMaxChange) || (m_lRobotResultScore<=m_lRobotloseMax && rand()%100 < m_btRobotLoseChangePercent) ||
			(rand()%100 < m_btUsuallyChangePercent) || (m_WinnerScore<=(-m_lRealBankerRobotLoseMaxChange)) || 
			(m_WinnerScore<=(-m_lRealBankerRobotLoseMax) && rand()%100 < m_btRealBankerRobotLoseChangePercent))
		{
			if(m_WinnerScore<0)
			{
				WORD nWinUser=0,nLoseUser=0,nCount=0;
				LONG lMaxScore=0;
				for (BYTE i=0; i<m_wPlayerCount; i++)
				{
					IServerUserItem *pServerUser = m_pITableFrame->GetTableUserItem(i);
					if(pServerUser!=NULL && m_bPlayer[i])
					{
						if(!pServerUser->IsAndroidUser() && m_lGameScore[i]>0)
						{
							if(nCount==0)
							{
								lMaxScore=m_lGameScore[i];
								nWinUser=i;
							}
							else
							{
								if(lMaxScore<m_lGameScore[i])
								{
									lMaxScore=m_lGameScore[i];
									nWinUser=i;
								}
							}
							nCount++;
						}
						if(pServerUser->IsAndroidUser() && m_lGameScore[i]<0)
						{
							nLoseUser=i;
						}
					}
				}
				//��������
				BYTE bTempCardData[13] = {};
				memcpy(bTempCardData,	m_bUserCardData[nWinUser],	sizeof(bTempCardData));
				memcpy(m_bUserCardData[nWinUser],	m_bUserCardData[nLoseUser],	sizeof(bTempCardData));
				memcpy(m_bUserCardData[nLoseUser],	bTempCardData,	sizeof(bTempCardData));
				printf("\n Ӯ��%d���䣺%d",nWinUser,nLoseUser);
				printf("\n �����˻��Ƴɹ�����");
			}
		}
	}
}

bool CTableFrameSink::UserControl()
{
	WORD wUserChairIndex = INVALID_CHAIR;
	for (WORD wChairID = 0; wChairID < GAME_PLAYER; wChairID++)
	{
		IServerUserItem * pIServerUserItem = m_pITableFrame->GetTableUserItem(wChairID);
		if (pIServerUserItem != NULL)
		{
			if(pIServerUserItem->GetGameID() == m_dwUserID)
			{
				wUserChairIndex = wChairID;
				break;
			}
		}
	}
	if(wUserChairIndex != INVALID_CHAIR && m_bPlayer[wUserChairIndex])
	{
		for (BYTE i=0; i<m_wPlayerCount; i++)
		{
			ShowCard(i);
		}
		ComputeChout();
		//������Ӯ
		ComputeResult();
		m_lUserGold = m_lGameScore[wUserChairIndex];
		//�жϻ���
		if(m_bLoseWin)
		{
			if((((DWORD)(rand()%100) < m_dwUserLoseWinPercent) && (m_lUserGold < 0)) /*|| ((m_lUserScore+m_lAllUserGold) > (m_lWinMaxGold+m_lWinMaxGold/10))*/)
			{
				for (BYTE j=0; j<m_wPlayerCount; j++)
				{
					if(m_bPlayer[j] && m_lGameScore[j]>0)
					{
						//��������
						BYTE bTempCardData[13] = {};
						memcpy(bTempCardData,	m_bUserCardData[wUserChairIndex],	sizeof(bTempCardData));
						memcpy(m_bUserCardData[wUserChairIndex],	m_bUserCardData[j],	sizeof(bTempCardData));
						memcpy(m_bUserCardData[j],	bTempCardData,	sizeof(bTempCardData));
					}
				}
			}
		}
		else
		{
			if ((((DWORD)(rand() % 100) < m_dwUserLoseWinPercent) && (m_lUserGold >0)) /*|| ((m_lUserScore+m_lAllUserGold) < (m_lLoseMaxGold+m_lLoseMaxGold/10))*/)
			{
				for (BYTE j=0; j<m_wPlayerCount; j++)
				{
					if(m_bPlayer[j] && m_lGameScore[j]<0)
					{
						//��������
						BYTE bTempCardData[13] = {};
						memcpy(bTempCardData,	m_bUserCardData[wUserChairIndex],	sizeof(bTempCardData));
						memcpy(m_bUserCardData[wUserChairIndex],	m_bUserCardData[j],	sizeof(bTempCardData));
						memcpy(m_bUserCardData[j],	bTempCardData,	sizeof(bTempCardData));
					}
				}
			}
		}
		return true;
	}
	return false;
}

bool CTableFrameSink::ClientControl()
{

	if(m_bPlayer[m_dwControlID])
	{
		for (BYTE i=0; i<m_wPlayerCount; i++)
		{
			ShowCard(i);
		}
		ComputeChout();
		//������Ӯ
		ComputeResult();
		m_lUserGold = m_lGameScore[m_dwControlID];
		//�жϻ���
		if(m_bControlLossWin)
		{
			if( m_lUserGold<0)
			{
				for (BYTE j=0; j<m_wPlayerCount; j++)
				{
					if(m_lGameScore[j]>0)
					{
						//��������
						BYTE bTempCardData[13] = {};
						memcpy(bTempCardData,	m_bUserCardData[m_dwControlID],	sizeof(bTempCardData));
						memcpy(m_bUserCardData[m_dwControlID],	m_bUserCardData[j],	sizeof(bTempCardData));
						memcpy(m_bUserCardData[j],	bTempCardData,	sizeof(bTempCardData));
					}
				}
			}
		}
		else
		{
			if(m_lUserGold>0)
			{
				for (BYTE j=0; j<m_wPlayerCount; j++)
				{
					if(m_lGameScore[j]<0)
					{
						//��������
						BYTE bTempCardData[13] = {};
						memcpy(bTempCardData,	m_bUserCardData[m_dwControlID],	sizeof(bTempCardData));
						memcpy(m_bUserCardData[m_dwControlID],	m_bUserCardData[j],	sizeof(bTempCardData));
						memcpy(m_bUserCardData[j],	bTempCardData,	sizeof(bTempCardData));
					}
				}
			}
		}
		m_nControlCount--;
		m_bControl = true;

		CMD_C_ControlData ControlData;
		ZeroMemory(&ControlData,sizeof(ControlData));
		ControlData.cbCount = m_nControlCount;
		ControlData.bWinloss = m_bControlLossWin;
		ControlData.dwChairID = m_dwControlID;
		m_pITableFrame->SendTableData(INVALID_CHAIR, SUB_S_AMDIN_COMMAND, &ControlData, sizeof(ControlData));
		m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_AMDIN_COMMAND,&ControlData,sizeof(ControlData));
	}
	return true;
}


//////////////////////////////////////////////////////////////////////////
