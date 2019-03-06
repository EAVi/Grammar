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
GOTO( I0, ( ) = I4
GOTO( I0, i ) = I5

LR(0) sets for item I1
S -> E.

LR(0) sets for item I2
E -> T.A
A -> .+TA | .?
GOTO( I2, A ) = I6
GOTO( I2, + ) = I9
GOTO( I2, ? ) = I10

LR(0) sets for item I3
T -> F.B
B -> .*FB | .?
GOTO( I3, B ) = I7
GOTO( I3, * ) = I11
GOTO( I3, ? ) = I12

LR(0) sets for item I4
F -> (.E)
E -> .TA
T -> .FB
F -> .(E) | .i
GOTO( I4, E ) = I8
GOTO( I4, T ) = I2
GOTO( I4, F ) = I3
GOTO( I4, ( ) = I4
GOTO( I4, i ) = I5

LR(0) sets for item I5
F -> i.

LR(0) sets for item I6
E -> TA.

LR(0) sets for item I7
T -> FB.

LR(0) sets for item I8
F -> (E.)
GOTO( I8, ) ) = I13

LR(0) sets for item I9
A -> +.TA
T -> .FB
F -> .(E) | .i
GOTO( I9, T ) = I14
GOTO( I9, F ) = I3
GOTO( I9, ( ) = I4
GOTO( I9, i ) = I5

LR(0) sets for item I10
A -> ?.

LR(0) sets for item I11
B -> *.FB
F -> .(E) | .i
GOTO( I11, F ) = I15
GOTO( I11, ( ) = I4
GOTO( I11, i ) = I5

LR(0) sets for item I12
B -> ?.

LR(0) sets for item I13
F -> (E).

LR(0) sets for item I14
A -> +T.A
A -> .+TA | .?
GOTO( I14, A ) = I16
GOTO( I14, + ) = I9
GOTO( I14, ? ) = I10

LR(0) sets for item I15
B -> *F.B
B -> .*FB | .?
GOTO( I15, B ) = I17
GOTO( I15, * ) = I11
GOTO( I15, ? ) = I12

LR(0) sets for item I16
A -> +TA.

LR(0) sets for item I17
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
GOTO( I1, a ) = I4

LR(0) sets for item I2
S -> cA.d
GOTO( I2, d ) = I5

LR(0) sets for item I3
A -> a.b
GOTO( I3, b ) = I6

LR(0) sets for item I4
A -> a.

LR(0) sets for item I5
S -> cAd.

LR(0) sets for item I6
A -> ab.

```

# Complexity

Constructing the FIRST set is of O(m\*n<sup>2</sup>), where m is the number of rules per production, and n is the number of productions.

Constructing the FOLLOW set is of O(l\*m\*n<sup>2</sup>), where m is the number of rules per production, n is the number of productions, and l is the length of each production rule.
  
There are probably better approaches to constructing the sets, but the algorithm works.
