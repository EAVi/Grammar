# Grammar Rules
1. Single character terminals and nonterminals
1. **->** symbol 'produces'
1. **|** splits separate rules of a production
1. **?** is an epsilon/lambda character
1. Do not use whitespace

# Example Grammar 1
```
S->E
E->TA
A->+TA|?
T->FB
B->*FB|?
F->(E)|i
```
# Example Grammar 2
```
S->cAd
A->ab|a
```

### Tested Output
```
Grammar Test 1 (fig 4.28)
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

LR(0) sets for item I0
S -> .E
E -> .TA
T -> .FB
F -> .(E) | .i
GOTO( I0, E ) = I1
GOTO( I0, T ) = I2
GOTO( I0, F ) = I3
GOTO( I0, ( ) = I5
GOTO( I0, i ) = I5

LR(0) sets for item I1
S -> E.

LR(0) sets for item I2
E -> T.A
A -> .+TA | .?
GOTO( I2, A ) = I4
GOTO( I2, + ) = I6
GOTO( I2, ? ) = I6

LR(0) sets for item I3
T -> F.B
B -> .*FB | .?
GOTO( I3, B ) = I7
GOTO( I3, * ) = I8
GOTO( I3, ? ) = I8

LR(0) sets for item I4
E -> TA.

LR(0) sets for item I5
F -> (.E)
E -> .TA
T -> .FB
F -> .(E) | .i
GOTO( I5, E ) = I9
GOTO( I5, T ) = I2
GOTO( I5, F ) = I3
GOTO( I5, ( ) = I5
GOTO( I5, i ) = I5

LR(0) sets for item I6
A -> +.TA
T -> .FB
F -> .(E) | .i
GOTO( I6, T ) = I10
GOTO( I6, F ) = I3
GOTO( I6, ( ) = I5
GOTO( I6, i ) = I5

LR(0) sets for item I7
T -> FB.

LR(0) sets for item I8
B -> *.FB
F -> .(E) | .i
GOTO( I8, F ) = I11
GOTO( I8, ( ) = I5
GOTO( I8, i ) = I5

LR(0) sets for item I9
F -> (E.)
GOTO( I9, ) ) = I12

LR(0) sets for item I10
A -> +T.A
A -> .+TA | .?
GOTO( I10, A ) = I13
GOTO( I10, + ) = I6
GOTO( I10, ? ) = I6

LR(0) sets for item I11
B -> *F.B
B -> .*FB | .?
GOTO( I11, B ) = I14
GOTO( I11, * ) = I8
GOTO( I11, ? ) = I8

LR(0) sets for item I12
F -> (E).

LR(0) sets for item I13
A -> +TA.

LR(0) sets for item I14
B -> *FB.

------------------------------
Grammar Test 2 (ex 4.29)
A -> ab | a
FIRST(A) = { a }
FOLLOW(A) = { d }

S -> cAd
FIRST(S) = { c }
FOLLOW(S) = { $ }

LR(0) sets for item I0
S -> .cAd
GOTO( I0, c ) = I1

LR(0) sets for item I1
S -> c.Ad
A -> .ab | .a
GOTO( I1, A ) = I2
GOTO( I1, a ) = I3

LR(0) sets for item I2
S -> cA.d
GOTO( I2, d ) = I4

LR(0) sets for item I3
A -> a.b
GOTO( I3, b ) = I5

LR(0) sets for item I4
S -> cAd.

LR(0) sets for item I5
A -> ab.
```

# Complexity

Constructing the FIRST set is of O(m\*n<sup>2</sup>), where m is the number of rules per production, and n is the number of productions.

Constructing the FOLLOW set is of O(l\*m\*n<sup>2</sup>), where m is the number of rules per production, n is the number of productions, and l is the length of each production rule.
  
There are probably better approaches to constructing the sets, but the algorithm works.
