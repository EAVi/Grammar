#include "Production.h"
#include <iostream>

using namespace std;

Production::Production()
{
	m_symbol = 0;
	m_rules = vector<string>();
	m_first = set<char>();
	m_follow = set<char>();
}

Production::Production(char c)
{
	m_symbol = c;
}

Production::Production(std::string rule)
{
	m_symbol = 0;
	m_rules = vector<string>();
	m_first = set<char>();
	m_follow = set<char>();

	read_rule(rule);
}

void Production::read_rule(std::string rule)
{
	const string rightarrow = "->";//the rightarrow delimiter
	const string nextproduction = "|";//the symbol representing a different production
	
	//in the future, I may allow a nonterminal to be a string
	size_t tok_min = 0;
	size_t tok_max = rule.find(rightarrow);
	string token = rule.substr(tok_min, tok_max);
	
	//the nonterminal is a single character
	m_symbol = token[0];
	tok_max += rightarrow.length() - nextproduction.length();
	
	size_t tok_len;
	while(tok_max != string::npos)
	{
		tok_min = tok_max + nextproduction.length();
		tok_max = rule.find(nextproduction, tok_min);
		tok_len = (tok_max == string::npos) ? string::npos : tok_max - tok_min;
		token = rule.substr(tok_min, tok_len);
		m_rules.push_back(token);
	}
}

bool Production::operator<(const Production & rhs) const
{
	return this->m_symbol < rhs.m_symbol;
}

void Production::print()
{
	cout << m_symbol << " -> ";
	for(int i = 0, j = m_rules.size(); i < j; ++i)
	{
		cout << m_rules[i];
		if (i != (j-1))
			cout << " | ";
	}
	cout << endl;
	
	cout << "FIRST(" << m_symbol << ") = { ";
	for(set<char>::iterator it = m_first.begin(); it != m_first.end(); it = next(it))
	{
		cout << *it;
		if(next(it) != m_first.end())
			cout << ", ";
	}
	cout << " }" << endl;
	
	cout << "FOLLOW(" << m_symbol << ") = { ";
	for(set<char>::iterator it = m_follow.begin(); it != m_follow.end(); it = next(it))
	{
		cout << *it;
		if(next(it) != m_follow.end())
			cout << ", ";
	}
	cout << " }" << endl << endl;
}

char Production::get_symbol()
{
	return m_symbol;
}

const vector<string> & Production::get_rules() const
{
	return m_rules;
}

const set<char> & Production::get_first() const
{
	return m_first;
}

const set<char> & Production::get_follow() const
{
	return m_follow;
}

void Production::add_first(char c) const
{
	m_first.insert(c);
}

void Production::add_first(const set<char>& s) const
{
	m_first.insert(s.begin(), s.end());
}

bool Production::add_follow(char c) const
{
	bool found = (m_follow.find(c) != m_follow.end());
	if (found)
		return false;
	else 
	{
		m_follow.insert(c);
		return true;
	}
}

bool Production::add_follow(const std::set<char> s) const
{
	bool changed = false;
	set<char>::iterator it;
	for(const char& c : s)
	{
		if(c == epsilon) continue;//epsilon doesn't belong in a follow set
		it = m_follow.find(c);
		if(it == m_follow.end())
		{
			changed = true;
			m_follow.insert(c);
		}
	}
	return changed;
}