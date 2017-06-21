#include "cardType.h"
#include "pokerUtil.h"

const ThirteenFlush::Type ThirteenFlush::getCardType() const
{
	return ThirteenFlush::Type::CT_THIRTEEN_FLUSH;
}

bool ThirteenFlush::CheckThirteenFlush(std::vector<PokerCard>& CardList)
{
	if (pokerUtil::CheckFlush(CardList) && pokerUtil::CheckStraight(CardList))
	{
		return true;
	}
	

	return false;
}