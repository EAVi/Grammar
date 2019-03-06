#include"AugmentedProduction.h"
#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

bool operator==(Transition lhs, Transition rhs)
{
	return (lhs.X == rhs.X && lhs.index == rhs.index);
}

AugmentedProduction::AugmentedProduction()
	: m_production(nullptr)
{}

AugmentedProduction::AugmentedProduction(const Production & p, const set<Production>* s, int rule, int marker)
	: m_productions(s)
{
	m_production = p;
	m_which_rule = rule;
	if(rule < 0) m_all_rules = true;
	else m_all_rules = false;
	m_marker = marker;
	//if(m_all_rules) marker = 0;
}

AugmentedProduction::~AugmentedProduction()
{}

void AugmentedProduction::closure()
{
	bool changed = true;
	queue<char> q;//queue of characters to check
	
	//start by pushing the marked character 
	//assumes all production rules are of nonzero length
	if(m_all_rules)
	{
		for(const string & s : m_production.m_rules)
			q.push(s[0]);
	}
	else if(m_marker < m_production.m_rules[m_which_rule].length())
	{
		q.push( 
			m_production.m_rules[m_which_rule][m_marker] );
	}
	else return;

	while(changed)
	{
		changed = false;
		while(!q.empty())
		{
			auto it = find_production(q.front());
			if (it != m_productions->end() && !closure_exists(it))
			{
				m_closure.push_back(*it);
				//add all starting elements to the queue for later checking
				for(auto val : it->get_rules())
					q.push(val[0]);
				
				changed = true;
			}
			q.pop();
		}
	}
}

bool AugmentedProduction::closure_exists(set<Production>::iterator it)
{
	return (find(m_closure.begin(), m_closure.end(), *it) != m_closure.end());
}

bool AugmentedProduction::goto_all(vector<AugmentedProduction*>& augvec)
{
	bool changed = false;
	//the top production first
	if(m_all_rules)
	{
		for(int i = 0, j = m_production.m_rules.size(); i < j; ++i)
		{
			if(m_production.m_rules[i].length() == 0)//prevent segfaults
				continue;
			changed |= add_goto(augvec, m_production, i, 1);//in this scenario m_marker is expected to be 0, so we use magic number 1
		}
	}
	else if(m_marker < m_production.m_rules[m_which_rule].length())
	{
		changed |= add_goto(augvec, m_production, m_which_rule, m_marker + 1);
	}
	//else it's a reduce state, which doesn't have any goto
	
	//goto on all of the closure productions
	for(auto & prod : m_closure)
	{
		if(!prod.valid()) continue;
		for(int i = 0, j = prod.m_rules.size(); i < j; ++i)
		{
			changed |= add_goto(augvec, prod, i, 1);
		}
	}
	return changed;
}

bool AugmentedProduction::add_goto(vector<AugmentedProduction*>& augvec, const Production& p, int rule, int marker)
{
	if(rule >= p.m_rules.size()) return false;
	AugmentedProduction* candidate = new AugmentedProduction(p, m_productions, rule, marker);
	int candidate_distance = check_exists(augvec, candidate);
	if(candidate_distance == -1)
	{
		Transition t;
		t.X = p.m_rules[rule][marker - 1];
		t.index = (int)augvec.size();
		m_goto.push_back(t);
		augvec.push_back(candidate);

		return true;
	}
	delete candidate;

	//try to add the transition
	Transition t;
	t.X = p.m_rules[rule][marker - 1];
	t.index = candidate_distance;
	auto trans_it = find(m_goto.begin(), m_goto.end(), t);
	if(trans_it == m_goto.end())//t not found in m_goto
		m_goto.push_back(t);
	return false;
}

bool AugmentedProduction::operator==(const AugmentedProduction & rhs)const
{
	return (m_production == rhs.m_production
		&& m_all_rules == rhs.m_all_rules 
		&& m_which_rule == rhs.m_which_rule
		&& m_marker == rhs.m_marker);
}

set<Production>::iterator AugmentedProduction::find_production(char c)
{
	Production p(c);
	return m_productions->find(p);
}

void AugmentedProduction::print_productions(int id)
{
	string temprule = "";
	//print the root production
	cout << m_production.m_symbol << " -> ";
	for(int i = 0, j = m_production.m_rules.size(); i < j; ++i)
	{
		
		if(m_all_rules || i == m_which_rule)
		{
			temprule = m_production.m_rules[i];
			temprule.insert(m_marker,".");
			cout << temprule;
		}
		if(m_all_rules && (i < j - 1))
			cout << " | ";
	}
	cout << endl;
	
	//print the closure productions
	for(int i = 0, j = m_closure.size(); i < j; ++i)
	{
		cout << m_closure[i].m_symbol << " -> ";
		for(int k = 0, l = m_closure[i].m_rules.size(); k < l; ++k)
		{
			temprule = m_closure[i].m_rules[k];
			temprule.insert(0,".");//all closure productions rules are marked at position 0
			cout << temprule;
			if(k < l - 1)
				cout << " | ";
		}
		cout << endl;
	}
	
	for(auto & val : m_goto)
	{
		cout << "GOTO( I" << id << ", " << val.X << " ) = I" << val.index << endl;
	}
	cout << endl;
}

int AugmentedProduction::check_exists(vector<AugmentedProduction*>& augvec, AugmentedProduction* candidate)
{
	for(int i = 0, j = augvec.size(); i < j; ++i)
	{
		if(*augvec[i] == *candidate)
			return i;
	}
	return -1;
}
