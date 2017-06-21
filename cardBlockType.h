#ifndef _CARDBLOCKTYPE_H_
#define _CARDBLOCKTYPE_H_
#include <vector>
#include "pokerCard.h"

class cardBlockType
{
public:
	enum BlockType {
		CT_INVALID                        =    0,
		CT_SINGLE                         =    1,
		CT_ONE_DOUBLE                     =    2,
		CT_FIVE_TWO_DOUBLE                =    3,
		CT_THREE                          =    4,
		CT_FIVE_MIXED_FLUSH_NO_A          =    5,
		CT_FIVE_MIXED_FLUSH_FIRST_A       =    6,
		CT_FIVE_MIXED_FLUSH_BACK_A        =    7,
		CT_FIVE_FLUSH                     =    8,
		CT_FIVE_THREE_DEOUBLE             =    9,
		CT_FIVE_FOUR_ONE                  =    10,
		CT_FIVE_STRAIGHT_FLUSH_NO_A       =    11,
		CT_FIVE_STRAIGHT_FLUSH_FIRST_A    =    12,
		CT_FIVE_STRAIGHT_FLUSH_BACK_A     =    13,
		CT_FIVE_MID_THREE_DEOUBLE         =    14
	};
public:
	cardBlockType();
	~cardBlockType();
public:
	BlockType getBlockType() const;
	void setBlockType(cardBlockType::BlockType type);

public:
	std::vector<cardBlockType>& checkBlockType(const std::vector<PokerCard>& CardList);
private:
	BlockType type;
};

#endif //_CARDBLOCKTYPE_H_
