#include <string>
#include <iostream>
#include "Production.h"
#include "Grammar.h"

using namespace std;

/*
GRAMMAR RULES:
-NO SPACES ALLOWED UNLESS YOU WANT A TERMINAL SPACE
-SINGLE CHARACTER FOR NONTERMINAL
-'?' IS THE EPSILON/LAMBDA
-'|' IS A SEPARATE RULE
-"->" IS THE ARROW SYMBOL
*/

int main(int argc, char* argv[])
{
	Grammar G;
	G.add_production("S->E");
	G.add_production("E->TA");
	G.add_production("A->+TA|?");
	G.add_production("T->FB");
	G.add_production("B->*FB|?");
	G.add_production("F->(E)|i");
	
	G.generate_sets();
	G.print_sets();
	
	return 0;
}