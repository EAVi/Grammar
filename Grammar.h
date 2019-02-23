#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <set>
#include <vector>
#include <string>
#include "Production.h"
#include "AugmentedProduction.h"

class Grammar
{
public:
	Grammar();
	Grammar(std::string filename);//constructor calling a file to read
	void read_file(std::string filename);//read productions from file
	void add_production(std::string s);//add a production to the grammar
	void generate_sets();
	void print_sets();//print the first and follow sets
	std::set<Production>::iterator find_production(char c);//find production of specified 
private:
	//terminals and nonterminals cannot have anything in common
	std::set<Production> m_production;
	std::vector<AugmentedProduction> m_lr_closures;//list of lr sets
	char m_initial_symbol;//initial production index
	void m_generate_lr();//generate the LR(0) sets
	void m_generate_first();//calls the recursive algorithm
	void m_generate_follow();//calls the recursive algorithm
	std::set<char> m_first(Production p);//recursive function
	std::set<char> m_first(char production, std::set<char> & visited);//recursive function
	bool m_follow();
};

#endif