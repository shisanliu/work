#include "cardType.h"
#include "pokerUtil.h"

const AllBig::Type AllBig::getCardType() const
{
	return ThirteenFlush::Type::CT_ALL_BIG;
}

bool AllBig::CheckAllBig(std::vector<PokerCard>& CardList)
{
	for (std::vector<PokerCard>::iterator it = CardList.begin(); it < CardList.end(); ++it)
	{
		if (it->getPokerCardvalue() > 8)
		{
			return false;
		}
	}

	return true;
}