#include "Stdafx.h"
#include "Resource.h"
#include "DlgCustomRule.h"

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgCustomRule, CDialog)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CDlgCustomRule::CDlgCustomRule() : CDialog(IDD_CUSTOM_RULE)
{
	//设置变量
	ZeroMemory(&m_CustomRule,sizeof(m_CustomRule));

	return;
}

//析构函数
CDlgCustomRule::~CDlgCustomRule()
{
}

//配置函数
BOOL CDlgCustomRule::OnInitDialog()
{
	__super::OnInitDialog();

	//设置控件
	((CEdit *)GetDlgItem(IDC_ROBOT_LOSE_START_CHANG))->LimitText(10);
	((CEdit *)GetDlgItem(IDC_ROBOT_LOSE_MAX_CHANGE))->LimitText(10);
	((CEdit *)GetDlgItem(IDC_ROBOT_LOSE_START_CHANGE_PRECENT))->LimitText(2);
	((CEdit *)GetDlgItem(IDC_ROBOT_WIN_START_TANK))->LimitText(10);
	((CEdit *)GetDlgItem(IDC_ROBOT_WIN_RANK))->LimitText(10);
	((CEdit *)GetDlgItem(IDC_ROBOT_WIN_START_TANK_PRECENT))->LimitText(2);

	//更新参数
	FillDataToControl();

	return FALSE;
}

//确定函数
VOID CDlgCustomRule::OnOK() 
{ 
	//投递消息
	GetParent()->PostMessage(WM_COMMAND,MAKELONG(IDOK,0),0);

	return;
}

//取消消息
VOID CDlgCustomRule::OnCancel() 
{ 
	//投递消息
	GetParent()->PostMessage(WM_COMMAND,MAKELONG(IDCANCEL,0),0);

	return;
}

//更新控件
bool CDlgCustomRule::FillDataToControl()
{
	SetDlgItemInt(IDC_ROBOT_LOSE_START_CHANG, m_CustomRule.realBankerRobotLoseMax);
	SetDlgItemInt(IDC_ROBOT_LOSE_MAX_CHANGE, m_CustomRule.realBankerRobotLoseMaxChange);
	SetDlgItemInt(IDC_ROBOT_LOSE_START_CHANGE_PRECENT, m_CustomRule.realBankerRobotLoseChangePercent);


	SetDlgItemInt(IDC_ROBOT_WIN_START_TANK, m_CustomRule.robotProbabilityTanking);
	SetDlgItemInt(IDC_ROBOT_WIN_RANK, m_CustomRule.robotDefineTanking);
	SetDlgItemInt(IDC_ROBOT_WIN_START_TANK_PRECENT, m_CustomRule.robotTankingPercent);
	((CButton *)GetDlgItem(IDC_IS_CHEAT))->SetCheck((m_CustomRule.isCheat == TRUE) ? BST_CHECKED : BST_UNCHECKED);

	return true;
}

//更新数据
bool CDlgCustomRule::FillControlToData()
{
	m_CustomRule.realBankerRobotLoseMax = (LONG)GetDlgItemInt(IDC_ROBOT_LOSE_START_CHANG);
	m_CustomRule.realBankerRobotLoseMaxChange = (LONG)GetDlgItemInt(IDC_ROBOT_LOSE_MAX_CHANGE);
	m_CustomRule.realBankerRobotLoseChangePercent = (BYTE)GetDlgItemInt(IDC_ROBOT_LOSE_START_CHANGE_PRECENT);

	m_CustomRule.robotProbabilityTanking = (LONG)GetDlgItemInt(IDC_TIME_HEAD_OUT_CARD);
	m_CustomRule.robotDefineTanking = (LONG)GetDlgItemInt(IDC_MAX_SCORE_TIMES);
	m_CustomRule.robotTankingPercent = (BYTE)GetDlgItemInt(IDC_FLEE_SCORE_TIMES);

	m_CustomRule.isCheat = (((CButton *)GetDlgItem(IDC_IS_CHEAT))->GetCheck() == BST_CHECKED);

	return true;
}

//读取配置
bool CDlgCustomRule::GetCustomRule(tagCustomRule & CustomRule)
{
	//读取参数
	if (FillControlToData()==true)
	{
		CustomRule=m_CustomRule;
		return true;
	}

	return false;
}

//设置配置
bool CDlgCustomRule::SetCustomRule(tagCustomRule & CustomRule)
{
	//设置变量
	m_CustomRule=CustomRule;

	//更新参数
	if (m_hWnd!=NULL) FillDataToControl();

	return true;
}

//////////////////////////////////////////////////////////////////////////////////
