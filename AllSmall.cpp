#include "cardType.h"
#include "pokerUtil.h"

const AllSmall::Type AllSmall::getCardType() const
{
	return ThirteenFlush::Type::CT_ALL_SMALL;
}

bool AllSmall::CheckAllSmall(std::vector<PokerCard>& CardList)
{
	for (std::vector<PokerCard>::iterator it = CardList.begin(); it < CardList.end(); ++it)
	{
		if (it->getPokerCardvalue() < 8)
		{
			return false;
		}
	}

	return true;
}