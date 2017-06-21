#include "cardType.h"
#include "pokerUtil.h"

const ThreeStraightFlush::Type ThreeStraightFlush::getCardType() const
{
	return ThirteenFlush::Type::CT_THREE_STRAIGHTFLUSH;
}

bool ThreeStraightFlush::CheckThreeStraightFlush(std::vector<PokerCard>& CardList)
{
	std::vector<PokerCard>::iterator it;
	std::vector<PokerCard> temp;

	//1
	for (it = CardList.begin(); it < CardList.begin() + 2;  ++it)
	{
		temp.push_back(*it);
	}

	if (pokerUtil::CheckStraight(temp) && pokerUtil::CheckFlush(temp))
	{
		temp.clear();
		for (it = CardList.begin() + 3; it < CardList.begin() + 8; ++it)
		{
			temp.push_back(*it);
		}
	}
	else
	{
		return false;
	}

	//2
	if (pokerUtil::CheckStraight(temp) && pokerUtil::CheckFlush(temp))
	{
		temp.clear();
		for (it = CardList.begin() + 8; it < CardList.begin() + 13; ++it)
		{
			temp.push_back(*it);
		}
	}
	else
	{
		return false;
	}

	//3
	if (pokerUtil::CheckStraight(temp) && pokerUtil::CheckFlush(temp))
	{
		return true;
	}
	else
	{
		return false;
	}
}