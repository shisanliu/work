#include "cardBlockType.h"
#include "pokerCard.h"
#include "pokerUtil.h"
#include <vector>

cardBlockType::cardBlockType() :
provCard(PokerCard::HONGXIN, 0)
{
}

cardBlockType::~cardBlockType()
{

}

cardBlockType::BlockType cardBlockType::getBlockType()const
{
	return this->type;
}

void cardBlockType::setBlockType(cardBlockType::BlockType type)
{
	this->type = type;
}

std::vector<cardBlockType>& cardBlockType::checkBlockType(const std::vector<PokerCard>& CardList)
{
	std::vector<cardBlockType> typeList;
	size_t i = CardList.size();

	if (3 == i)
	{
		if ()
	}
	else if (5 == i)
	{


	}
}