#ifndef _POKERCARD_H_
#define _POKERCARD_H_

class PokerCard
{
public:
	enum Kind{
		HONGXIN   = 0x00,
		HEITIAO   = 0x10,
		FANGKUAI  = 0x20,
		MEIHUA    = 0x30
	};
	PokerCard();
	PokerCard(Kind kind, int value);
	~PokerCard();
	//---���� == ��ȵ�ʱ��ɫ�϶���ͬ �Ƚ���ֵ
	bool operator==(const PokerCard& obj) const;

public:
	Kind getPokerCardkind() const;
	int getPokerCardvalue() const;
private:
	Kind kind;
	int value;
};



#endif //_POKERCARD_H_