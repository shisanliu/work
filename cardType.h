#ifndef _CARDTYPE_H_
#define _CARDTYPE_H_

class cardType
{
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

	virtual Type getCardType() const;
	virtual int getCardShui() const;
	virtual void setCardType(Type type);
private:
	int shui;
};



class FiveMidThreeDeouble : public cardType
{


};

class ThirteenFlush : public cardType
{


};

class Thirteen : public cardType
{


};

class TwelveVeKing : public cardType
{


};

class ThreeStraightFlush : public cardType
{


};

class ThreeBoom : public cardType
{


};

class AllBig : public cardType
{


};

class AllSmall : public cardType
{


};

class AllSmallColor : public cardType
{


};

class FourThreeSame : public cardType
{

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