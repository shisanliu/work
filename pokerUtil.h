#ifndef _POKERUTIL_H_
#define _POKERUTIL_H_

#include <vector>
#include "pokerCard.h"

class pokerUtil
{
public:
	static void SortCardList(std::vector<PokerCard>& CardList);
	static bool CheckSameValue(const PokerCard& card, int value);
	static bool CheckSameKind(const PokerCard& card, PokerCard::Kind kind);
	static bool CheckFlush(const std::vector<PokerCard>& CardList);
	static bool CheckTwo(const std::vector<PokerCard>& CardLis);
	static bool CheckDoubleTwo(const std::vector<PokerCard>& CardLis);
	static bool CheckThree(const std::vector<PokerCard>& CardList);
	static bool CheckFour(const std::vector<PokerCard>& CardList);
	static int count(const std::vector<PokerCard>& CardList, const PokerCard& card);
	static bool CheckStraight(const std::vector<PokerCard>& CardList);
	static bool CheckSpcial(const std::vector<PokerCard>& CardList);
	static void AnalyesCard(const std::vector<PokerCard>& CardList, std::vector<PokerCard>& ResultCard);
};

#endif // _POKERUTIL_H_