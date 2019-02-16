# Grammar Rules
1. Single character terminals and nonterminals
1. **->** symbol 'produces'
1. **|** splits separate rules of a production
1. **?** is an epsilon/lambda character
1. Do not use whitespace

# Example Grammar
```
S->E
E->TA
A->+TA|?
T->FB
B->*FB|?
F->(E)|i
```
### Tested Output
```
A -> +TA | ?
FIRST(A) = { +, ? }
FOLLOW(A) = { $, ) }

B -> *FB | ?
FIRST(B) = { *, ? }
FOLLOW(B) = { $, ), + }

E -> TA
FIRST(E) = { (, i }
FOLLOW(E) = { $, ) }

F -> (E) | i
FIRST(F) = { (, i }
FOLLOW(F) = { $, ), *, + }

S -> E
FIRST(S) = { (, i }
FOLLOW(S) = { $ }

T -> FB
FIRST(T) = { (, i }
FOLLOW(T) = { $, ), + }
```

#Complexity

Constructing the FIRST set is of O(m\*n<sup>2</sup>), where m is the number of rules per production, and n is the number of productions.

Constructing the FOLLOW set is of O(l\*m\*n<sup>2</sup>), where m is the number of rules per production, n is the number of productions, and l is the length of each production rule.
  
There are probably better approaches to constructing the sets, but the algorithm works.
