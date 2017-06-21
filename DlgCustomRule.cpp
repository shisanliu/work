#include "Stdafx.h"
#include "Resource.h"
#include "DlgCustomRule.h"

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgCustomRule, CDialog)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgCustomRule::CDlgCustomRule() : CDialog(IDD_CUSTOM_RULE)
{
	//���ñ���
	ZeroMemory(&m_CustomRule,sizeof(m_CustomRule));

	return;
}

//��������
CDlgCustomRule::~CDlgCustomRule()
{
}

//���ú���
BOOL CDlgCustomRule::OnInitDialog()
{
	__super::OnInitDialog();

	//���ÿؼ�
	((CEdit *)GetDlgItem(IDC_ROBOT_LOSE_START_CHANG))->LimitText(10);
	((CEdit *)GetDlgItem(IDC_ROBOT_LOSE_MAX_CHANGE))->LimitText(10);
	((CEdit *)GetDlgItem(IDC_ROBOT_LOSE_START_CHANGE_PRECENT))->LimitText(2);
	((CEdit *)GetDlgItem(IDC_ROBOT_WIN_START_TANK))->LimitText(10);
	((CEdit *)GetDlgItem(IDC_ROBOT_WIN_RANK))->LimitText(10);
	((CEdit *)GetDlgItem(IDC_ROBOT_WIN_START_TANK_PRECENT))->LimitText(2);

	//���²���
	FillDataToControl();

	return FALSE;
}

//ȷ������
VOID CDlgCustomRule::OnOK() 
{ 
	//Ͷ����Ϣ
	GetParent()->PostMessage(WM_COMMAND,MAKELONG(IDOK,0),0);

	return;
}

//ȡ����Ϣ
VOID CDlgCustomRule::OnCancel() 
{ 
	//Ͷ����Ϣ
	GetParent()->PostMessage(WM_COMMAND,MAKELONG(IDCANCEL,0),0);

	return;
}

//���¿ؼ�
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

//��������
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

//��ȡ����
bool CDlgCustomRule::GetCustomRule(tagCustomRule & CustomRule)
{
	//��ȡ����
	if (FillControlToData()==true)
	{
		CustomRule=m_CustomRule;
		return true;
	}

	return false;
}

//��������
bool CDlgCustomRule::SetCustomRule(tagCustomRule & CustomRule)
{
	//���ñ���
	m_CustomRule=CustomRule;

	//���²���
	if (m_hWnd!=NULL) FillDataToControl();

	return true;
}

//////////////////////////////////////////////////////////////////////////////////
