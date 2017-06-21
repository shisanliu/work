#include "cardType.h"
#include "pokerUtil.h"

const Thirteen::Type ThirteenFlush::getCardType() const
{
	return ThirteenFlush::Type::CT_THIRTEEN;
}

bool Thirteen::CheckThirteen(std::vector<PokerCard>& CardList)
{
	if (pokerUtil::CheckFlush(CardList))
	{
		return true;
	}


	return false;
}