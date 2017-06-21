#include "Stdafx.h"
#include "AndroidUserItemSink.h"

//////////////////////////////////////////////////////////////////////////
#define IDI_READY                  100
#define IDI_SHOW_CARD              101

//���캯��
CAndroidUserItemSink::CAndroidUserItemSink()
{
	//AllocConsole();
	//freopen("CON","wt",stdout);
   ZeroMemory(m_bHandCardData,sizeof(m_bHandCardData));
   ZeroMemory(m_bSegmentCard,sizeof(m_bSegmentCard));
   ZeroMemory(m_bSpecialCardData,sizeof(m_bSpecialCardData));
   m_bHandCardCount=0;
   static LONG dwRandCount=0L;
   srand((unsigned)time(NULL)+dwRandCount++);

   m_nRobotPlayMaxCount=2+rand()%3;
   m_nRobotPlayCount=0; 

}

//��������
CAndroidUserItemSink::~CAndroidUserItemSink()
{
}

//�ӿڲ�ѯ
void * CAndroidUserItemSink::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IAndroidUserItemSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IAndroidUserItemSink,Guid,dwQueryVer);
	return NULL;
}

//��ʼ�ӿ�
bool CAndroidUserItemSink::Initialization(IUnknownEx * pIUnknownEx)
{
	//��ѯ�ӿ�
	m_pIAndroidUserItem=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,IAndroidUserItem);
	if (m_pIAndroidUserItem==NULL) return false;

	return true;
}

//���ýӿ�
bool CAndroidUserItemSink::RepositionSink()
{
	ZeroMemory(m_bHandCardData,sizeof(m_bHandCardData));
	ZeroMemory(m_bSegmentCard,sizeof(m_bSegmentCard));
	ZeroMemory(m_bSpecialCardData,sizeof(m_bSpecialCardData));
	m_bHandCardCount=0;
	return true;
}

//ʱ����Ϣ
bool CAndroidUserItemSink::OnEventTimer(UINT nTimerID)
{   
	switch(nTimerID)
	{
	case IDI_READY:
		{
			//����׼��
			m_pIAndroidUserItem->SendUserReady(NULL,0);
            m_pIAndroidUserItem->KillGameTimer(IDI_READY);
			return true;
		}
	case IDI_SHOW_CARD:
		{
            ShowCard();
            m_pIAndroidUserItem->KillGameTimer(IDI_SHOW_CARD);
			return true;
		}
	}
	return false;
}

//��Ϸ��Ϣ
bool CAndroidUserItemSink::OnEventGameMessage(WORD wSubCmdID, void * pData, WORD wDataSize)
{
	switch(wSubCmdID)
	{
	case SUB_S_SEND_CARD:
		{
			return OnSubSendCard(pData,wDataSize);
		}
	case SUB_S_GAME_END:
		{
			return OnSubGameEnd(pData,wDataSize);					
		}
	case SUB_S_SETSEGMENT:		//���÷ֶ�
		{
			return true ;
		}
	case SUB_S_SHOW_CARD:      //���̯��
		{
			return true;
		}
	case SUB_S_PLAYER_LEFT:     //���ǿ��
		{
			return true;
		}
	case SUB_S_SCORE_RESULT:     //��Ϸ����
		{
			return true;
		}
	case SUB_S_USEREXIT:         //����˳�
		{
			return true;
		}
	case SUB_S_AMDIN_COMMAND:
		{
			return true;
		}
	}
	return false;
}

//��Ϸ��Ϣ
bool CAndroidUserItemSink::OnEventFrameMessage(WORD wSubCmdID, void * pData, WORD wDataSize)
{
	return true;    
}

//������Ϣ
bool CAndroidUserItemSink::OnEventSceneMessage(BYTE cbGameStatus, bool bLookonOther, void * pData, WORD wDataSize)
{
	switch (cbGameStatus)
	{
	case GS_WK_FREE:			//����״̬
		{
			//��ʼʱ��
			UINT nElapse=rand()%(3)+2;
			if(rand()%100 > 90)
				nElapse=rand()%(15)+5;
			m_pIAndroidUserItem->SetGameTimer(IDI_READY,nElapse);  
			return true;
		}
	}

	return false;
}

//�û�����
void CAndroidUserItemSink::OnEventUserEnter(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser)
{
	return;
}

//�û��뿪
void CAndroidUserItemSink::OnEventUserLeave(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser)
{
	return;
}

//�û�����
void CAndroidUserItemSink::OnEventUserScore(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser)
{
	return;
}

//�û�״̬
void CAndroidUserItemSink::OnEventUserStatus(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser)
{
	return;
}

//�û���λ
void CAndroidUserItemSink::OnEventUserSegment(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser)
{
	return;
}


//��Ϸ��ʼ
bool CAndroidUserItemSink::OnSubSendCard(void * pData, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_SendCard));
	if (wDataSize!=sizeof(CMD_S_SendCard)) return false;

    ZeroMemory(m_bHandCardData,sizeof(m_bHandCardData));
	//��������
	CMD_S_SendCard * pSendCard=(CMD_S_SendCard *)pData;
	CopyMemory(m_bHandCardData,pSendCard->bCardData,sizeof(m_bHandCardData));
	if(m_GameLogic.GetCardType(m_bHandCardData,13,m_GameLogic.btCardSpecialData)!=CT_INVALID)
	{
        m_pIAndroidUserItem->SetGameTimer(IDI_SHOW_CARD,(6+rand()%4));
	}
	else
	{ 
		int Number=rand()%3;
		if(Number==0)
		{
            m_pIAndroidUserItem->SetGameTimer(IDI_SHOW_CARD,(8+rand()%10));
		}
		else if(Number==1)
		{
            m_pIAndroidUserItem->SetGameTimer(IDI_SHOW_CARD,(8+rand()%20));
		}
		else if(Number==2)
		{
            m_pIAndroidUserItem->SetGameTimer(IDI_SHOW_CARD,(8+rand()%25));
		}
	}
	return true;
}


//��Ϸ����
bool CAndroidUserItemSink::OnSubGameEnd(void * pData, WORD wDataSize)
{
	ASSERT(wDataSize==sizeof(CMD_S_GameEnd));
	if (wDataSize!=sizeof(CMD_S_GameEnd)) return false;
	CMD_S_GameEnd * pGameEnd=(CMD_S_GameEnd *)pData;
	
	m_nRobotPlayCount += 1;

	//��ʼʱ��
	UINT nElapse=rand()%(3)+2;
	if(rand()%100 > 90)
		nElapse=rand()%(15)+5;
	m_pIAndroidUserItem->SetGameTimer(IDI_READY,pGameEnd->nTimer+nElapse); //����׼��ʱ��

	return true;
}

void CAndroidUserItemSink::GetSpecialCard( BYTE CardData[],BYTE CardCount )
{

	BYTE btSpecialCard[13];
	ZeroMemory(btSpecialCard,sizeof(btSpecialCard));
	tagAnalyseData AnalyseData ;
	m_GameLogic.AnalyseCard(CardData , CardCount , AnalyseData) ;
	if(m_GameLogic.GetCardType(CardData,CardCount,btSpecialCard)==CT_THIRTEEN_FLUSH||
		m_GameLogic.GetCardType(CardData,CardCount,btSpecialCard)==CT_THIRTEEN||
		m_GameLogic.GetCardType(CardData,CardCount,btSpecialCard)==CT_TWELVE_KING||
		m_GameLogic.GetCardType(CardData,CardCount,btSpecialCard)==CT_THREE_STRAIGHTFLUSH||
		m_GameLogic.GetCardType(CardData,CardCount,btSpecialCard)==CT_THREE_BOMB||
		m_GameLogic.GetCardType(CardData,CardCount,btSpecialCard)==CT_ALL_BIG||
		m_GameLogic.GetCardType(CardData,CardCount,btSpecialCard)==CT_ALL_SMALL||
		m_GameLogic.GetCardType(CardData,CardCount,btSpecialCard)==CT_SAME_COLOR||
		m_GameLogic.GetCardType(CardData,CardCount,btSpecialCard)==CT_FOUR_THREESAME)
	{
		CopyMemory(m_bSpecialCardData,CardData,sizeof(m_bSpecialCardData));
		return;
	}
	if(m_GameLogic.GetCardType(CardData,CardCount,btSpecialCard)==CT_THREE_FLUSH)
	{
		CopyMemory(m_bSpecialCardData,btSpecialCard,sizeof(btSpecialCard));
		return;
	}
	if(m_GameLogic.GetCardType(CardData,CardCount,btSpecialCard)==CT_THREE_STRAIGHT)
	{
		CopyMemory(m_bSpecialCardData,btSpecialCard,sizeof(btSpecialCard));
		return;
	}
	if(m_GameLogic.GetCardType(CardData,CardCount,btSpecialCard)==CT_FIVEPAIR_THREE)
	{
		BYTE SaveData[5];
		ZeroMemory(SaveData,sizeof(SaveData));
		SaveData[0]=CardData[AnalyseData.bThreeFirst[0]];
		SaveData[1]=CardData[AnalyseData.bThreeFirst[0]+1];
		SaveData[2]=CardData[AnalyseData.bThreeFirst[0]+2];
		m_GameLogic.RemoveCard(SaveData,3,CardData,CardCount);
		CardCount-=3;
		m_GameLogic.SortCardList(CardData,CardCount);
		for(int i=0;i<CardCount;i++)
		{
			m_bSpecialCardData[i]=CardData[i];
		}
		m_bSpecialCardData[10]=SaveData[0];
		m_bSpecialCardData[11]=SaveData[1];
		m_bSpecialCardData[12]=SaveData[2];

		return;
	}
	if(m_GameLogic.GetCardType(CardData,CardCount,btSpecialCard)==CT_SIXPAIR)
	{
		BYTE SaveData[5];
		ZeroMemory(SaveData,sizeof(SaveData));
		SaveData[0]=CardData[AnalyseData.bOneFirst[0]];
		m_GameLogic.RemoveCard(SaveData,1,CardData,CardCount);
		CardCount-=1;
		m_GameLogic.SortCardList(CardData,CardCount);
		for(int i=0;i<CardCount;i++)
		{
			m_bSpecialCardData[i]=CardData[i];
		}
		m_bSpecialCardData[12]=SaveData[0];
		return;
	}
}

void CAndroidUserItemSink::ShowCard()
{
   if(m_GameLogic.GetCardType(m_bHandCardData,HAND_CARD_COUNT,m_GameLogic.btCardSpecialData)!=CT_INVALID)
   {
       m_GameLogic.SortCardList(m_bHandCardData,HAND_CARD_COUNT);
       GetSpecialCard(m_bHandCardData,HAND_CARD_COUNT);

	   CMD_C_ShowCard AllSegmentCard;
	   memset(&AllSegmentCard , 0 , sizeof(AllSegmentCard)) ;
	   for(int i=0;i<3;i++)
	   {
		   m_bSegmentCard[0][i]=m_bSpecialCardData[10+i];
	   }

	   for(int i=0;i<5;i++)
	   {
		   m_bSegmentCard[1][i]=m_bSpecialCardData[5+i];
	   }

	   for(int i=0;i<5;i++)
	   {
		   m_bSegmentCard[2][i]=m_bSpecialCardData[i];
	   }
       m_GameLogic.SortCardList(m_bSegmentCard[0],3);
	   m_GameLogic.SortCardList(m_bSegmentCard[1],5);
	   m_GameLogic.SortCardList(m_bSegmentCard[2],5);
	   CopyMemory(AllSegmentCard.bFrontCard,m_bSegmentCard[0],sizeof(AllSegmentCard.bFrontCard));
       CopyMemory(AllSegmentCard.bMidCard,m_bSegmentCard[1],sizeof(AllSegmentCard.bMidCard));
       CopyMemory(AllSegmentCard.bBackCard,m_bSegmentCard[2],sizeof(AllSegmentCard.bBackCard));
       
	   AllSegmentCard.bSpecialType=true;
	   CopyMemory(AllSegmentCard.btSpecialData,m_bSpecialCardData,sizeof(AllSegmentCard.btSpecialData));
	   m_pIAndroidUserItem->SendSocketData(SUB_C_SHOWCARD,&AllSegmentCard,sizeof(AllSegmentCard));
   }
   else
   {
	  m_GameLogic.SortCardList(m_bHandCardData,HAND_CARD_COUNT);
	  /*for(int i=0;i<13;i++)
	  {
          printf("m_bHandCardData[i]=%d ",m_bHandCardData[i]);
	  }*/
	  
	  m_bHandCardCount=HAND_CARD_COUNT;
      tagAnalyseType tagCardType;                            //���ͼ����
	  ZeroMemory(&tagCardType,sizeof(tagCardType));
      tagCardType=m_GameLogic.GetType(m_bHandCardData,m_bHandCardCount);
	  m_GameLogic.TheBestCard(tagCardType,m_bHandCardData,m_bHandCardCount,m_bSegmentCard[0],m_bSegmentCard[1],m_bSegmentCard[2]);
      
	  CMD_C_ShowCard AllSegmentCard ;
	  memset(&AllSegmentCard , 0 , sizeof(AllSegmentCard)) ;
	  CopyMemory(AllSegmentCard.bFrontCard,m_bSegmentCard[0],sizeof(AllSegmentCard.bFrontCard));
	  CopyMemory(AllSegmentCard.bMidCard,m_bSegmentCard[1],sizeof(AllSegmentCard.bMidCard));
	  CopyMemory(AllSegmentCard.bBackCard,m_bSegmentCard[2],sizeof(AllSegmentCard.bBackCard));
	  //�����ж�
	  bool bDragon = false ;
	  if((true==m_GameLogic.CompareCard(AllSegmentCard.bFrontCard , AllSegmentCard.bMidCard , 3 , 5 , false)) &&
		  (true==m_GameLogic.CompareCard(AllSegmentCard.bMidCard, AllSegmentCard.bBackCard , 5 , 5 , false)))
		  bDragon = false ;
	  else
		  bDragon = true ;
      AllSegmentCard.bDragon=bDragon;
	  if(AllSegmentCard.bDragon)
	  {
          memset(&AllSegmentCard , 0 , sizeof(AllSegmentCard)) ;
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
				  bCardData[bFrontCard] = m_bHandCardData[bCardDataIndex[bCardIndex]] ;
				  bCardDataIndex[bCardIndex] = bCardDataIndex[13-bFrontCard-1] ;
			  }

			  m_GameLogic.SortCardList(bCardData , 3 , enDescend) ;
			  bFrontCardType = m_GameLogic.GetCardType(bCardData , 3,m_GameLogic.btCardSpecialData) ;

			  //�ж��˿�
			  for(BYTE bMidCard=0 ; bMidCard<5 ; ++bMidCard)
			  {
				  bCardIndex = rand()%(10-bMidCard) ;
				  bAllSegmentCardIndex[bSegCount][1][bMidCard] = bCardDataIndex[bCardIndex] ;
				  bCardData[bMidCard] = m_bHandCardData[bCardDataIndex[bCardIndex]] ;
				  bCardDataIndex[bCardIndex] = bCardDataIndex[10-bMidCard-1] ;
			  }

			  m_GameLogic.SortCardList(bCardData , 5 , enDescend) ;
			  bMidCardType = m_GameLogic.GetCardType(bCardData , 5,m_GameLogic.btCardSpecialData) ;

			  //����˿�
			  for(BYTE bBackCard=0 ; bBackCard<5 ; ++bBackCard)
			  {
				  bAllSegmentCardIndex[bSegCount][2][bBackCard] = bCardDataIndex[bBackCard] ;
				  bCardData[bBackCard] = m_bHandCardData[bCardDataIndex[bBackCard]] ;
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
                  AllSegmentCard.bFrontCard[i]=m_bHandCardData[bAllSegmentCardIndex[bIndex][0][i]];
			  }
              //�����жأ����
              for(int i=0;i<5;i++)
			  {
                  AllSegmentCard.bMidCard[i]=m_bHandCardData[bAllSegmentCardIndex[bIndex][1][i]];
                  AllSegmentCard.bBackCard[i]=m_bHandCardData[bAllSegmentCardIndex[bIndex][2][i]];
			  }
		  }
	  }
	  m_GameLogic.SortCardList(AllSegmentCard.bFrontCard,3);
	  m_GameLogic.SortCardList(AllSegmentCard.bMidCard,5);
	  m_GameLogic.SortCardList(AllSegmentCard.bBackCard,5);
	  m_pIAndroidUserItem->SendSocketData(SUB_C_SHOWCARD,&AllSegmentCard,sizeof(AllSegmentCard));
   }
}