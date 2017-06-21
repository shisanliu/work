#include "pokerUtil.h"
#include <algorithm>
#include <random>
#include <iomanip>

//---------------------------------------------------------------------
/*
后期 加注释
优化代码
循环部分 判定部分 全要优化
for 改for_each
*/

void pokerUtil::SortCardList(std::vector<PokerCard>& CardList)
{
	std::sort(CardList.begin(), CardList.end(), [](PokerCard& a, PokerCard& b){ return a.getPokerCardvalue() < b.getPokerCardvalue(); });
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
	std::vector<PokerCard> temp = CardList;
	int value = temp.at(0).getPokerCardvalue();

	for (std::vector<PokerCard>::iterator it = temp.begin() + 1; it < temp.end(); ++it)
	{
		if (it->getPokerCardvalue() != (value + 1))
		{
			return false;
		}
		value = it->getPokerCardvalue();
	}

	return true;
}

bool pokerUtil::CheckTwo(const std::vector<PokerCard>& CardList)
{
	int countNum = 0;
	std::vector<PokerCard> temp = CardList;
	int size = temp.size();

	if (3 == CardList.size())
	{
		for (int i = 0; i < CardList.size(); ++i)
		{
			if (2 == count(CardList, CardList.at(i)))
			{
				return true;
			}
		}
	}
	else if (5 == CardList.size())
	{
		for (std::vector<PokerCard>::iterator it = temp.begin(); it < temp.end(); ++it)
		{
			if (2 == count(CardList, *it))
			{
				countNum++;
				temp.erase(it);
			}
		}
	}

	if (1 == countNum)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool pokerUtil::CheckDoubleTwo(const std::vector<PokerCard>& CardList)
{
	if (CardList.size() < 5)
	{
		return false;
	}

	std::vector<PokerCard> temp = CardList;
	int countNum = 0;

	//后面再改 用for_each
	//错误------------------------vector越界
	//for (int i = 0; i < CardLis.size(); ++i)
	//{
	//	if (2 == count(temp, temp.at(i)))
	//	{
	//		countNum++;
	//		temp.push_back(temp.at(i));
	//	}
	//}
	
	for (std::vector<PokerCard>::iterator it = temp.begin(); it < temp.end(); ++it)
	{
		if (2 == count(CardList, *it))
		{
			countNum++;
			temp.erase(it);
		}
	}
	if (2 == countNum)
	{
		return true;
	}
	else
	{
		return false;
	}
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
			if (3 == count(CardList, CardList.at(i)))
			{
				return true;
			}
		}

		return false;
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