#include "cardType.h"
#include "pokerUtil.h"

const ThreeBoom::Type ThreeBoom::getCardType() const
{
	return ThirteenFlush::Type::CT_THREE_BOMB;
}

bool ThreeBoom::CheckThreeBoom(std::vector<PokerCard>& CardList)
{
	int countNum = 0;
	std::vector<PokerCard> temp = CardList;

	for (std::vector<PokerCard>::iterator it = temp.begin(); it < temp.end(); ++it)
	{
		PokerCard keyCard = *it;
		if (4 == pokerUtil::count(temp, keyCard))
		{
			temp.erase(find(temp.begin(), temp.end(), keyCard));
			countNum++;
		}
		else
		{
			temp.erase(find(temp.begin(), temp.end(), keyCard));
		}
	}

	if (4 == countNum)
	{
		return true;
	}
	else
	{
		return false;
	}
}