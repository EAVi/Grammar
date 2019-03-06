#ifndef AUGMENTEDPRODUCTION_H
#define AUGMENTEDPRODUCTION_H

#include<set>
#include<vector>
#include<string>
#include"Production.h"

struct Transition
{
	char X;
	int index;
};

bool operator==(Transition lhs, Transition rhs);

//production with added "marker" which keeps track of the position in the production
class AugmentedProduction
{
public:
	/*
	An augmented production zones in on specific symbols on one or more grammar rules in a production
	* p is the production in question
	* s is the set of productions from the grammar
	* rule is the specific grammar rule
	* marker is the position of some imaginary dot/period
	*/
	AugmentedProduction();
	AugmentedProduction(const Production & p, const std::set<Production>* s, int rule = -1, int marker = 0);
	~AugmentedProduction();
	void closure();//generate the closure set
	bool closure_exists(std::set<Production>::iterator it);
	bool goto_all(std::vector<AugmentedProduction*>& augvec);
	bool add_goto(std::vector<AugmentedProduction*>& augvec, const Production& p, int rule = -1, int marker = 0);//add closure if it doesnt exist already
	bool operator==(const AugmentedProduction & rhs)const;
	std::set<Production>::iterator find_production(char c);//find production given character
	void print_productions(int id);//print the goto and closure sets
	int check_exists(std::vector<AugmentedProduction*>& augvec, AugmentedProduction* candidate);//returns index of existing candidate
private:
	bool m_all_rules;
	int m_which_rule;//the specific rule on the production
	Production m_production;
	int m_marker;//position where the "period" is
	const std::set<Production>* m_productions;//a reference to all productions in the grammar
	mutable std::vector<Production> m_closure;//closure of the augmented production
	mutable std::vector<Transition> m_goto;//goto of the augmented production
};

#endif
