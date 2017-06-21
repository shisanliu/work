#include "pokerCard.h"

PokerCard::PokerCard()
{

}
PokerCard::PokerCard(Kind kind, int value)
{
	kind = HONGXIN;
	value = 0;
}
PokerCard::~PokerCard()
{
}
PokerCard::Kind PokerCard::getPokerCardkind() const
{
	return this->kind;
}
int PokerCard::getPokerCardvalue() const
{
	return this->value;
}

bool PokerCard::operator==(const PokerCard& obj) const
{
	return this->value == obj.value;
}

bool PokerCard::operator<(const PokerCard& obj) const
{
	if (this->value > obj.value)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PokerCard::operator>(const PokerCard& obj) const
{
	if (this->value < obj.value)
	{
		return true;
	}
	else
	{
		return false;
	}
}