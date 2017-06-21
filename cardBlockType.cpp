#include "cardBlockType.h"
#include "pokerCard.h"
#include <vector>

cardBlockType::cardBlockType()
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
	if (3 == CardList.size())
	{
	}
	else if (5 == CardList.size())
	{}
}