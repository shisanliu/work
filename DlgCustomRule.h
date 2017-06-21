#ifndef GAME_DLG_CUSTOM_RULE_HEAD_FILE
#define GAME_DLG_CUSTOM_RULE_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////////////

//配置结构
struct tagCustomRule
{
	BYTE								isCheat;						//是否作弊（换牌）

	LONG                                realBankerRobotLoseMax;				//有概率换牌的起始输分分数
	LONG                                realBankerRobotLoseMaxChange;		//百分百换牌的起始输分分数
	BYTE                                realBankerRobotLoseChangePercent;	//起始输分，换牌百分比

	LONG                                robotProbabilityTanking;		//赢的金额数，机器人有概率放水
	LONG                                robotDefineTanking;			//赢的金额数，机器人百分百放水
	BYTE                                robotTankingPercent;		//机器人放水的百分比
};

//////////////////////////////////////////////////////////////////////////////////

//配置窗口
class CDlgCustomRule : public CDialog
{
	//配置变量
protected:
	tagCustomRule					m_CustomRule;						//配置结构

	//函数定义
public:
	//构造函数
	CDlgCustomRule();
	//析构函数
	virtual ~CDlgCustomRule();

	//重载函数
protected:
	//配置函数
	virtual BOOL OnInitDialog();
	//确定函数
	virtual VOID OnOK();
	//取消消息
	virtual VOID OnCancel();

	//功能函数
public:
	//更新控件
	bool FillDataToControl();
	//更新数据
	bool FillControlToData();

	//配置函数
public:
	//读取配置
	bool GetCustomRule(tagCustomRule & CustomRule);
	//设置配置
	bool SetCustomRule(tagCustomRule & CustomRule);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif