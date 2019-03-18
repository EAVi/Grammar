#include"AugmentedProduction.h"
#include<iostream>
#include<queue>
#include<algorithm>
#include<tuple>

using namespace std;

bool Kernel::operator<(const Kernel& rhs) const
{
	return tie(production, rule, marker) < tie(rhs.production, rhs.rule, rhs.marker);
}

bool Kernel::operator==(const Kernel& rhs) const
{
	return (production == rhs.production 
		&& rule == rhs.rule 
		&& marker == rhs.marker);
}

bool operator==(Transition lhs, Transition rhs)
{
	return (lhs.X == rhs.X && lhs.index == rhs.index);
}

AugmentedProduction::AugmentedProduction()
	: m_productions(nullptr)
{}

AugmentedProduction::AugmentedProduction(const Production & p, const set<Production>* s, int rule, int marker)
	: m_productions(s)
{
	Kernel k;
	k.production = p;
	k.rule = rule;
	k.marker = marker;
	m_kernel.insert(k);
	m_productions = s;
}

AugmentedProduction::AugmentedProduction(std::set<Kernel> & k, const std::set<Production>* s)
{
	m_kernel = k;
	m_productions = s;
}

AugmentedProduction::~AugmentedProduction()
{}

void AugmentedProduction::closure()
{
	bool changed = true;
	queue<char> q;//queue of characters to check
	
	//start by pushing the marked character 
	//assumes all production rules are of nonzero length
	for( auto & kernel : m_kernel)
	{
		
		if(kernel.rule == Kernel::all_rules)
		{
			for(const string & s : kernel.production.m_rules)
				q.push(s[0]);
		}
		else if(kernel.marker < kernel.production.m_rules[kernel.rule].length())
		{
			q.push( 
				kernel.production.m_rules[kernel.rule][kernel.marker] );
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
		
		changed = true;
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
	set<char> alphabet = get_alphabet();
	for(auto X : alphabet)
	{
		set<Kernel> k;
		add_to_kernel(X, k);
		changed |= add_goto(augvec, X, k);
	}
	return changed;
}

set<char> AugmentedProduction::get_alphabet()
{
	set<char> alphabet;
	//find all characters marked by each kernel
	for(auto & kernel : m_kernel)
	{
		if(kernel.rule == Kernel::all_rules)
		{
			for(int i = 0, j = kernel.production.m_rules.size(); i < j; ++i)
			{
				if(kernel.production.m_rules[i].length() == 0)//prevent segfaults
					continue;
				alphabet.insert(kernel.production.m_rules[i][0]);
			}
		}
		else if(kernel.marker < kernel.production.m_rules[kernel.rule].length())
		{
			alphabet.insert(kernel.production.m_rules[kernel.rule][kernel.marker]);
		}
	}
	
	//find all characters marked by the closure productions
	for(auto & production : m_closure)
	{
		for(int i = 0, j = production.m_rules.size(); i < j ; ++i)
		{
			if(production.m_rules[i].length() == 0)
				continue;
			alphabet.insert(production.m_rules[i][0]);
		}
	}
	return alphabet;
}

void AugmentedProduction::add_to_kernel(char & X, set<Kernel>& kernelset)
{
	for(auto & kernel : m_kernel)
	{
		if(kernel.rule == Kernel::all_rules)
		{
			for(int i = 0, j = kernel.production.m_rules.size(); i < j; ++i)
			{
				if(kernel.production.m_rules[i].length() == 0)//prevent segfaults
					continue;
				else if (X == kernel.production.m_rules[i][0])
				{
					Kernel add;
					add.production = kernel.production;
					add.rule = i;
					add.marker = 1;
					kernelset.insert(add);
				}
				
			}
		}
		else if(kernel.marker < kernel.production.m_rules[kernel.rule].length()
			&& X == kernel.production.m_rules[kernel.rule][kernel.marker])
		{
			Kernel add;
			add.production = kernel.production;
			add.rule = kernel.rule;
			add.marker = kernel.marker + 1;
			kernelset.insert(add);
		}
		//else it's a reduce state, which doesn't have any goto
	}
	
	//goto on all of the closure productions
	for(auto & prod : m_closure)
	{
		//if(!prod.valid()) continue;
		for(int i = 0, j = prod.m_rules.size(); i < j; ++i)
		{
			if(X == prod.m_rules[i][0])
			{
				Kernel add;
				add.production = prod;
				add.rule = i;
				add.marker = 1;
				kernelset.insert(add);
			}
		}
	}
}

bool AugmentedProduction::add_goto(vector<AugmentedProduction*>& augvec, char& X, set<Kernel>& kernel)
{
	//if(rule >= p.m_rules.size()) return false;
	Transition t;
	AugmentedProduction* candidate = new AugmentedProduction(kernel, m_productions);
	int candidate_distance = check_exists(augvec, candidate);
	if(candidate_distance == -1)//candidate didn't exist in lookup
	{
		t.X = X;
		t.index = (int)augvec.size();
		m_goto.push_back(t);
		augvec.push_back(candidate);

		return true;
	}
	delete candidate;

	//try to add the transition
	t.X = X;
	t.index = candidate_distance;
	auto trans_it = find(m_goto.begin(), m_goto.end(), t);
	if(trans_it == m_goto.end())//t not found in m_goto
		m_goto.push_back(t);
	return false;
}

bool AugmentedProduction::operator==(const AugmentedProduction & rhs)const
{
	return (m_kernel == rhs.m_kernel);
}

set<Production>::iterator AugmentedProduction::find_production(char c)
{
	Production p(c);
	return m_productions->find(p);
}

void AugmentedProduction::print_productions(int id)
{
	cout << "kernel productions:" << endl;
	//print the kernels
	string temprule = "";
	for(auto & kernel : m_kernel)
	{
		temprule = "";
		cout << kernel.production.m_symbol << " -> ";
		for(int i = 0, j = kernel.production.m_rules.size(); i < j; ++i)
		{
			
			if(kernel.rule == Kernel::all_rules || i == kernel.rule)
			{
				temprule = kernel.production.m_rules[i];
				temprule.insert(kernel.marker,".");
				cout << temprule;
			}
			if(i == Kernel::all_rules && (i < j - 1))
				cout << " | ";
		}
		cout << endl;
	}
	
	if (m_closure.size() != 0)
		cout << "closure productions:" << endl;
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

string AugmentedProduction::get_action(char X, bool SLR)
{
	string action = "";
	bool is_terminal = (find_production(X) == m_productions->end());
	for(auto & transition : m_goto)
	{
		if(transition.X == X)
		{
			if (is_terminal) action += "s";
			action += to_string(transition.index);
			action += " ";
		}
	}
	if(is_terminal)//if nonterminal
		action += get_reduce(X,SLR);
	return action;
}

string AugmentedProduction::get_reduce(char X, bool SLR)
{
	string reduce = "";
	//check if any productions have a reduce condition
	for(auto & kernel : m_kernel)
	{
		//all rules means they're all at position 0, so we can skip that part
		if(kernel.rule != Kernel::all_rules
			&& kernel.marker == kernel.production.m_rules[kernel.rule].length()
			&& (!SLR || kernel.production.check_follow(X)))
		{
			int prod_id = kernel.production.m_id + kernel.rule;
			if(prod_id == 0 && X == '$')
				reduce += "accept ";
			else
			{
				reduce += "r";
				reduce += to_string(prod_id);
				reduce += " ";
			}
		}
	}
	//closure productions are at position 0, so no reductions there
	return reduce;
}
