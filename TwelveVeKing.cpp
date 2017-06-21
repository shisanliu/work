#include "cardType.h"
#include "pokerUtil.h"

const TwelveVeKing::Type TwelveVeKing::getCardType() const
{
	return TwelveVeKing::Type::CT_TWELVE_KING;
}
bool TwelveVeKing::CheckTwelveVeKing(std::vector<PokerCard>& CardList)
{
	for (std::vector<PokerCard>::iterator it = CardList.begin(); it < CardList.end(); ++it)
	{
		if (it->getPokerCardvalue() < 11)
		{
			return false;
		}
	}

	return true;
}