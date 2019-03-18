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
	//This grammar is from Figure 4.2 of the 2nd Edition(Purple) of the Dragon Book
	//I added the start nonterminal manually out of personal preference
	/*
	*/
	Grammar G;
	G.add_production("S->E");
	G.add_production("E->TA");
	G.add_production("A->+TA|?");
	G.add_production("T->FB");
	G.add_production("B->*FB|?");
	G.add_production("F->(E)|i");
	
	cout << "Grammar Test 1 (fig 4.28)" << endl;
	G.generate_sets();
	G.print_sets();
	cout << "------------------------------" << endl;
	//Note that since I'm using an ordered set, the printed result will come out 
	//in alphabetical order rather than the order the nonterminal productions were given
	
	//This grammar is from Figure 4.29 of the Dragon Book
	Grammar G2;
	G2.add_production("S->cAd");
	G2.add_production("A->ab|a");
	
	cout << "Grammar Test 2 (ex 4.29)" << endl;
	G2.generate_sets();
	G2.print_sets();


	cout << "------------------------------" << endl;
	//This grammar is from Figure 4.1 of the Dragon Book
	Grammar G3;
	G3.add_production("S->E");
	G3.add_production("E->E+T|T");
	G3.add_production("T->T*F|F");
	G3.add_production("F->(E)|i");
	
	cout << "Grammar Test 3 (fig 4.1)" << endl;
	G3.generate_sets();
	G3.print_sets();
	
	cout << "------------------------------" << endl;
	Grammar G4;
	G4.add_production("S->E");
	G4.add_production("A->B|C");
	G4.add_production("B->D0|EB|BED");
	G4.add_production("C->F1|GC|CGF");
	G4.add_production("D->D0|?");
	G4.add_production("E->EE|0E1|1E0");
	G4.add_production("F->F1|?");
	G4.add_production("G->GG|0G1|1G0");
	cout << "Grammar Test 4 (num 0s != num 1s)" << endl;
	G4.generate_sets();
	G4.print_LR_table();

	cout << "------------------------------" << endl;
	Grammar G5;
	G5.add_production("S->P");
	G5.add_production("P->1P1|0P0|1|0|?");
	cout << "Grammar Test 4 (Palindrome of 0s and 1s)" << endl;
	G5.generate_sets();
	G5.print_LR_table();
	
	return 0;
}
