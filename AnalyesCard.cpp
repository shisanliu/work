#include "analyCard.h"
#include "pokerUtil.h"
#include <vector>
#include <algorithm>


void analyCard::AnalyseCard(const std::vector<PokerCard>& CardList,
	std::vector<PokerCard>& ResultList)
{
	std::for_each(CardList.begin(), CardList.end(), 
		[&](PokerCard a){ ResultList.push_back(a); });

	pokerUtil::SortCardList(ResultList);
}


