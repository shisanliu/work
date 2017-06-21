#ifndef ANDROID_USER_ITEM_SINK_HEAD_FILE
#define ANDROID_USER_ITEM_SINK_HEAD_FILE
#pragma once

#include "Stdafx.h"
#include "TableFrameSink.h"

//////////////////////////////////////////////////////////////////////////

//��������
class CAndroidUserItemSink : public IAndroidUserItemSink
{
	//�˿˱���
protected:
    BYTE                            m_bHandCardData[HAND_CARD_COUNT];   //���������е���
	BYTE                            m_bHandCardCount;                   //�Ƶ�����
	BYTE                            m_bSegmentCard[3][5];               //�ֶ��˿�
	BYTE                            m_bSpecialCardData[HAND_CARD_COUNT];//�����Ƶ�����
	int                             m_nRobotPlayCount;                  //��������ľ���
	int                             m_nRobotPlayMaxCount;                //�����������ľ���
	//�ؼ�����
protected:
	CGameLogic						m_GameLogic;						//��Ϸ�߼�
	IAndroidUserItem *				m_pIAndroidUserItem;				//�û��ӿ�
	//��������
public:
	//���캯��
	CAndroidUserItemSink();
	//��������
	virtual ~CAndroidUserItemSink();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID Release() { }
	//�Ƿ���Ч
	virtual bool IsValid() { return AfxIsValidAddress(this,sizeof(CAndroidUserItemSink))?true:false; }
	//�ӿڲ�ѯ
	virtual void * QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//���ƽӿ�
public:
	//��ʼ�ӿ�
	virtual bool Initialization(IUnknownEx * pIUnknownEx);
	//���ýӿ�
	virtual bool RepositionSink();

	//��Ϸ�¼�
public:
	//ʱ����Ϣ
	virtual bool OnEventTimer(UINT nTimerID);
	//��Ϸ��Ϣ
	virtual bool OnEventGameMessage(WORD wSubCmdID, void * pData, WORD wDataSize);
	//��Ϸ��Ϣ
	virtual bool OnEventFrameMessage(WORD wSubCmdID, void * pData, WORD wDataSize);
	//������Ϣ
	virtual bool OnEventSceneMessage(BYTE cbGameStatus, bool bLookonOther, void * pData, WORD wDataSize);

	//�û��¼�
public:
	//�û�����
	virtual void  OnEventUserEnter(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser);
	//�û��뿪
	virtual void  OnEventUserLeave(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser);
	//�û�����
	virtual void  OnEventUserScore(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser);
	//�û�״̬
	virtual void  OnEventUserStatus(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser);
	//�û���λ
	virtual void  OnEventUserSegment(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser);

protected:
	//���÷ֶ�
	//bool OnSubSetSegment(const void * pBuffer , WORD wDataSize);
	//���̯��
	//bool OnSubShowCard(const void * pBuffer , WORD wDataSize) ;
	//��Ϸ��ʼ
	bool OnSubSendCard(void * pData, WORD wDataSize);
	//��Ϸ����
	bool OnSubGameEnd(void * pData, WORD wDataSize);
	void GetSpecialCard(BYTE CardData[],BYTE CardCount);
	void ShowCard();
};

//////////////////////////////////////////////////////////////////////////

#endif