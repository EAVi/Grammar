#ifndef PRODUCTION_H
#define PRODUCTION_H

#include<set>
#include<vector>
#include<string>

const char epsilon = '?'; //the empty character variable

class AugmentedProduction;

class Production
{
public:
	Production();
	Production(char c);
	Production(std::string rule);
	void read_rule(std::string rule);//read the entire production rule. 
	bool operator<(const Production & rhs)const;
	bool operator==(const Production & rhs)const;
	void print();
	char get_symbol();
	const std::vector<std::string> & get_rules() const;
	const std::set<char> & get_first() const;
	const std::set<char> & get_follow() const;
	
	//add characters to the first and follow sets
	void add_first(char c)const;
	void add_first(const std::set<char>& s)const;
	bool add_follow(char c)const;//returns whether the set changed
	bool add_follow(const std::set<char> s)const;//returns whether the set changed
	
protected:
	char m_symbol;
	std::vector<std::string> m_rules;//rules of production
	mutable std::set<char> m_first;//mutable because std::set is strict with constness
	mutable std::set<char> m_follow;
	friend Production;
	friend AugmentedProduction;
};

#endif