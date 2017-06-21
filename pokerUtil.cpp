#include "pokerUtil.h"
#include <algorithm>
#include <random>
#include <iomanip>

void pokerUtil::SortCardList(std::vector<PokerCard>& CardList)
{
	std::sort(CardList.begin(), CardList.end(), [](PokerCard& a, PokerCard& b){ return a.getPokerCardvalue() < b.getPokerCardvalue(); });
}

bool pokerUtil::CheckSameValue(const PokerCard& card, int value)
{
	return card.getPokerCardvalue() == value;
}
bool pokerUtil::CheckSameKind(const PokerCard& card, PokerCard::Kind kind)
{
	
}

int count(const std::vector<PokerCard>& CardList, const PokerCard& card)
{
	return std::count(CardList.begin(), CardList.end(), card);
}

bool pokerUtil::CheckFlush(const std::vector<PokerCard>& CardList)
{
	PokerCard::Kind kind = CardList.at(0).getPokerCardkind();
	bool flags = true;

	std::for_each(CardList.begin() + 1, CardList.end(), [&](PokerCard temp){ if (temp.getPokerCardkind() != kind){ flags = false; }});

	return flags;
}

bool pokerUtil::CheckStraight(const std::vector<PokerCard>& CardList)
{
	auto value = CardList.at(0).getPokerCardvalue();

	for (int i = 1; i < CardList.size(); ++i)
	{
		if (CardList.at(i).getPokerCardvalue() - i != value)
		{
			return false;
		}
	}

	return true;
}

bool pokerUtil::CheckTwo(const std::vector<PokerCard>& CardLis)
{
	int keyvalue = CardLis.at(0).getPokerCardvalue();
	int count = 1;
	if (3 == CardLis.size())
	{
		for (int i = 1; i < CardLis.size(); ++i)
		{
			if (keyvalue == CardLis.at(i).getPokerCardvalue())
			{
				return true;
			}
		}
	}
	else if (5 == CardLis.size())
	{
		for (int i = 1; i < 3; ++i)
		{
			count = count()
		}
	}
}

bool pokerUtil::CheckDoubleTwo(const std::vector<PokerCard>& CardLis, int iNdex)
{

}

bool pokerUtil::CheckThree(const std::vector<PokerCard>& CardList)
{
	int keyvalue = CardList.at(0).getPokerCardvalue();

	if (3 == CardList.size())
	{
		if (keyvalue != CardList.at(1).getPokerCardvalue())
		{
			return false;
		}
	}
	else if (5 == CardList.size())
	{
		for (int i = 0; i < 3; ++i)
		{

		}
	}
}

bool pokerUtil::CheckFour(const std::vector<PokerCard>& CardList)
{
	if (CardList.size() < 5)
	{
		return false;
	}

	int keyvalue = CardList.at(0).getPokerCardvalue();

	if (keyvalue != CardList.at(1).getPokerCardvalue())
	{
		keyvalue = CardList.at(1).getPokerCardvalue();
	}

	for (int i = 2; i < CardList.size(); ++i)
	{
		if (keyvalue != CardList.at(i).getPokerCardvalue())
		{
			return false;
		}
	}

	return true;
}