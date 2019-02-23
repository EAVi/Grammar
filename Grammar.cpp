#include "Grammar.h"
#include <iostream>

using namespace std;

Grammar::Grammar()
{
	m_production = set<Production>();
	m_initial_symbol = '\0';
}

Grammar::Grammar(std::string filename)
{
	m_production = set<Production>();
	m_initial_symbol = '\0';
	read_file(filename);
}

void Grammar::read_file(std::string filename)
{
	
}

void Grammar::add_production(std::string s)
{
	Production p(s);
	m_production.insert(p);
	
	//the first element added to the array will become the starting symbol
	if(m_production.size() == 1)
		m_initial_symbol = p.get_symbol();
}

void Grammar::generate_sets()
{
	m_generate_first();
	m_generate_follow();
	m_generate_lr();
}

void Grammar::print_sets()
{
	for(auto val : m_production)
	{
		val.print();//change me later
	}
	for(int i = 0, j = m_lr_closures.size(); i < j; ++i)
	{
		cout << "LR(0) sets for item I" << i << endl;
		m_lr_closures[i].print_productions(i);
	}
}

set<Production>::iterator Grammar::find_production(char c)
{
	Production p(c);
	return m_production.find(p);
}

void Grammar::m_generate_first()
{
	for(auto& prod : m_production)
	{
		prod.add_first(m_first(prod));
	}
}


void Grammar::m_generate_follow()
{
	//keep calling the follow until m_follow returns false
	//until the iteration changes nothing
	while(m_follow()){}
}

set<char> Grammar::m_first(Production p)
{
	set<char> result;
	set<char> visited;
	visited.insert(p.get_symbol());
	vector<string> rules = p.get_rules();
	for(auto val : rules)	
	{
		set<char> first = m_first(val[0], visited);
		result.insert(first.begin(), first.end());
	}
	return result;
}

set<char> Grammar::m_first(char symbol, set<char> & visited)
{
	set<char> result;
	set<Production>::iterator it = find_production(symbol);
	if(it == m_production.end())//if is terminal (nonterminal not found)
	{
		result.insert(symbol);
		return result;
	}
	if(visited.count(symbol) == 1)//only return epsilon for the root production
		return result;
	visited.insert(symbol);
	vector<string> rules = it->get_rules();
	for(auto val : rules)
	{
		set<char> first = m_first(val[0], visited);
		result.insert(first.begin(), first.end());
	}
	return result;
}

bool Grammar::m_follow()
{
	bool changed = false;
	set<Production>::iterator it;
	it = find_production(m_initial_symbol);
	changed = it->add_follow('$');
	for(auto& prod : m_production)
	{
		vector<string> rule = prod.get_rules();
		for(const string& str : rule)
		{
			for(int i = 0, j = str.length(); i < j; ++i)
			{
				auto current_production = find_production(str[i]);
				if(current_production == m_production.end())//terminal
					continue;
				if(i < (j - 1))
				{
					auto next_production = find_production(str[i+1]);
					if(next_production == m_production.end())//terminal
						changed |= current_production->add_follow(str[i+1]);
					else//nonterminal
					{
						auto next_first = next_production->get_first();
						changed |= current_production->add_follow(next_first);
						
						//next_first contains epsilon
						if(next_first.count(epsilon) == 1)
							changed |= current_production->add_follow(
								prod.get_follow());
					}
						
				}
				else//last nonterminal of production rule
				{
					changed |= current_production->add_follow(prod.get_follow());
				}
			}
		}
	}
	
	return changed;
}

void Grammar::m_generate_lr()
{
	Production start = *find_production(m_initial_symbol);
	AugmentedProduction I(start, m_production);
	I.closure();
	m_lr_closures.push_back(I);
	bool changed = true;
	while(changed)
	{
		changed = false;
		for(int i = 0, j = m_lr_closures.size(); i < j; ++i)
		{
			//cout << "for'in" << endl;
			changed |= m_lr_closures[i].goto_all(m_lr_closures);
			m_lr_closures[i].closure();
		}
	}
}