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


//a kernel item in an augmented production
struct Kernel
{
	Production production;//pointer to a production
	int rule;//which rule
	int marker;//position of the period
	static const int all_rules = -1;
	bool operator<(const Kernel & rhs) const;
	bool operator==(const Kernel & rhs) const;
};

bool operator==(Transition lhs, Transition rhs);

//production with added "marker" which keeps track of the position in the production
class AugmentedProduction
{
public:
	/*
	An augmented production is made up of a set of kernels and its closures
	*/
	AugmentedProduction();
	AugmentedProduction(const Production & p, const std::set<Production>* s, int rule = Kernel::all_rules, int marker = 0);//construct using a single rule 
	AugmentedProduction(std::set<Kernel> & k, const std::set<Production>* s);//construct using a complete kernel
	~AugmentedProduction();
	void closure();//generate the closure set
	bool closure_exists(std::set<Production>::iterator it);
	bool goto_all(std::vector<AugmentedProduction*>& augvec);
	std::set<char> get_alphabet();//get an alphabet of the current item
	void add_to_kernel(char & X, std::set<Kernel>& kernelset);//helper which constructs a kernel, given a specified character
	bool add_goto(std::vector<AugmentedProduction*>& augvec, char & X, std::set<Kernel>& kernelset);//add closure if it doesnt exist already
	bool operator==(const AugmentedProduction & rhs)const;
	std::set<Production>::iterator find_production(char c);//find production given character
	void print_productions(int id);//print the goto and closure sets
	int check_exists(std::vector<AugmentedProduction*>& augvec, AugmentedProduction* candidate);//returns index of existing candidate
	
	//LR0 table construction helpers
	std::string get_action(char X);
	std::string get_reduce(char X);
private:
	std::set<Kernel> m_kernel;
	const std::set<Production>* m_productions;//a reference to all productions in the grammar
	mutable std::vector<Production> m_closure;//closure of the augmented production
	mutable std::vector<Transition> m_goto;//goto of the augmented production
};

#endif
