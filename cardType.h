#ifndef _CARDTYPE_H_
#define _CARDTYPE_H_

#include <algorithm>
#include <random>
#include <iomanip>
#include "pokerCard.h"

class cardType
{
public:
	enum Type {
		CT_THIRTEEN_FLUSH         =     26,
		CT_THIRTEEN               =     25,
		CT_TWELVE_KING            =     24,
		CT_THREE_STRAIGHTFLUSH    =     23,  
		CT_THREE_BOMB             =     22,
		CT_ALL_BIG                =     21,
		CT_ALL_SMALL              =     20,
		CT_SAME_COLOR             =     19,
		CT_FOUR_THREESAME         =     18,
		CT_FIVEPAIR_THREE         =     17,
		CT_SIXPAIR                =     16,
		CT_THREE_FLUSH            =     15,
		CT_THREE_STRAIGHT         =     14,
		
		LX_ONEPARE                =     13,
		LX_TWOPARE                =     14,
		LX_THREESAME              =     15,
		LX_STRAIGHT               =     16,
		LX_FLUSH                  =     17,
		LX_GOURD                  =     18,
		LX_FOURSAME               =     19,
		LX_STRAIGHTFLUSH          =     20
	};

public:
	virtual const Type getCardType() const = 0;

};


class ThirteenFlush : public cardType
{
public:
	virtual const Type getCardType() const;
	bool CheckThirteenFlush(std::vector<PokerCard>& CardList);
};

class Thirteen : public cardType
{
public:
	virtual const Type getCardType() const;
	bool CheckThirteen(std::vector<PokerCard>& CardList);
};

class TwelveVeKing : public cardType
{
public:
	virtual const Type getCardType() const;
	bool CheckTwelveVeKing(std::vector<PokerCard>& CardList);
};

class ThreeStraightFlush : public cardType
{
public:
	virtual const Type getCardType() const;
	bool CheckThreeStraightFlush(std::vector<PokerCard>& CardList);

};

class ThreeBoom : public cardType
{
public:
	virtual const Type getCardType() const;
	bool CheckThreeBoom(std::vector<PokerCard>& CardList);

};

class AllBig : public cardType
{
public:
	virtual const Type getCardType() const;
	bool CheckAllBig(std::vector<PokerCard>& CardList);
};

class AllSmall : public cardType
{
public:
	virtual const Type getCardType() const;
	bool CheckAllSmall(std::vector<PokerCard>& CardList);
};

class AllSameColor : public cardType
{
public:
	virtual const Type getCardType() const;
	bool CheckAllSmameColor(std::vector<PokerCard>& CardList);
};

class FourThreeSame : public cardType
{
public:
	virtual const Type getCardType() const;
	bool CheckAllSmameColor(std::vector<PokerCard>& CardList);
};

class FivePairThree : public cardType
{


};

class SixPair : public cardType
{


};

class ThreeFlush : public cardType
{

};

class ThreeStraight : public cardType
{


};

class OnePare : public cardType
{


};

class TwoPare : public cardType
{


};

class ThreeSame : public cardType
{

};

class Stright : public cardType
{


};

class Flush : public cardType
{


};

class Gourd : public cardType
{


};
class FourSame : public cardType
{


};

class StraightFlush : public cardType
{

};
#endif //_CARDTYPE_H_