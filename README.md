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

# Grammar for unequal number of 0s and 1s
```
S->A
A->B|C
B->D0|EB|BED
C->F1|GC|CGF
D->D0|?
E->EE|0E1|1E0
F->F1|?
G->GG|0G1|1G0
```

# Grammar for Palindrome

```
S->P
P->1P1|0P0|1|0|?
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
kernel productions:
S -> .cAd
GOTO( I0, c ) = I1

LR(0) sets for item I1
kernel productions:
S -> c.Ad
closure productions:
A -> .ab | .a
GOTO( I1, A ) = I2
GOTO( I1, a ) = I3

LR(0) sets for item I2
kernel productions:
S -> cA.d
GOTO( I2, d ) = I4

LR(0) sets for item I3
kernel productions:
A -> a.b
A -> a.
GOTO( I3, b ) = I5

LR(0) sets for item I4
kernel productions:
S -> cAd.

LR(0) sets for item I5
kernel productions:
A -> ab.

------------------------------
Grammar Test 3 (fig 4.1)
E -> E+T | T
FIRST(E) = { (, i }
FOLLOW(E) = { $, ), + }

F -> (E) | i
FIRST(F) = { (, i }
FOLLOW(F) = { $, ), *, + }

S -> E
FIRST(S) = { (, i }
FOLLOW(S) = { $ }

T -> T*F | F
FIRST(T) = { (, i }
FOLLOW(T) = { $, ), *, + }

LR(0) sets for item I0
kernel productions:
S -> .E
closure productions:
E -> .E+T | .T
T -> .T*F | .F
F -> .(E) | .i
GOTO( I0, ( ) = I1
GOTO( I0, E ) = I2
GOTO( I0, F ) = I3
GOTO( I0, T ) = I4
GOTO( I0, i ) = I5

LR(0) sets for item I1
kernel productions:
F -> (.E)
closure productions:
E -> .E+T | .T
T -> .T*F | .F
F -> .(E) | .i
GOTO( I1, ( ) = I1
GOTO( I1, E ) = I6
GOTO( I1, F ) = I3
GOTO( I1, T ) = I4
GOTO( I1, i ) = I5

LR(0) sets for item I2
kernel productions:
E -> E.+T
S -> E.
GOTO( I2, + ) = I7

LR(0) sets for item I3
kernel productions:
T -> F.

LR(0) sets for item I4
kernel productions:
E -> T.
T -> T.*F
GOTO( I4, * ) = I8

LR(0) sets for item I5
kernel productions:
F -> i.

LR(0) sets for item I6
kernel productions:
E -> E.+T
F -> (E.)
GOTO( I6, ) ) = I9
GOTO( I6, + ) = I7

LR(0) sets for item I7
kernel productions:
E -> E+.T
closure productions:
T -> .T*F | .F
F -> .(E) | .i
GOTO( I7, ( ) = I1
GOTO( I7, F ) = I3
GOTO( I7, T ) = I10
GOTO( I7, i ) = I5

LR(0) sets for item I8
kernel productions:
T -> T*.F
closure productions:
F -> .(E) | .i
GOTO( I8, ( ) = I1
GOTO( I8, F ) = I11
GOTO( I8, i ) = I5

LR(0) sets for item I9
kernel productions:
F -> (E).

LR(0) sets for item I10
kernel productions:
E -> E+T.
T -> T.*F
GOTO( I10, * ) = I8

LR(0) sets for item I11
kernel productions:
T -> T*F.


```

### LR(0) table for num0 != num1

| LR(0) item | 0 | 1 | ? | $ | A | B | C | D | E | F | G | S |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | s1  | s2  | s3  |  | 4  | 5  | 6  | 7  | 8  | 9  | 10  |  |
| 1 | s1  | s2  |  |  |  |  |  |  | 11  |  | 12  |  |
| 2 | s1  | s2  |  |  |  |  |  |  | 13  |  | 14  |  |
| 3 | r10 r15  | r10 r15  | r10 r15  | r10 r15  |  |  |  |  |  |  |  |  |
| 4 | r0  | r0  | r0  | accept  |  |  |  |  |  |  |  |  |
| 5 | r1  | r1  | r1  | r1  |  |  |  |  | 15  |  |  |  |
| 6 | r2  | r2  | r2  | r2  |  |  |  |  |  |  | 16  |  |
| 7 | s17  |  |  |  |  |  |  |  |  |  |  |  |
| 8 | s18  | s19  | s20  |  |  | 21  |  | 7  | 22  |  |  |  |
| 9 |  | s23  |  |  |  |  |  |  |  |  |  |  |
| 10 | s24  | s25  | s26  |  |  |  | 27  |  |  | 9  | 28  |  |
| 11 | s18  | s29  |  |  |  |  |  |  | 30  |  |  |  |
| 12 | s24  | s31  |  |  |  |  |  |  |  |  | 32  |  |
| 13 | s33  | s19  |  |  |  |  |  |  | 30  |  |  |  |
| 14 | s34  | s25  |  |  |  |  |  |  |  |  | 32  |  |
| 15 |  |  | s20  |  |  |  |  | 35  |  |  |  |  |
| 16 |  |  | s26  |  |  |  |  |  |  | 36  |  |  |
| 17 | r3 r9  | r3 r9  | r3 r9  | r3 r9  |  |  |  |  |  |  |  |  |
| 18 | s18  | s19  |  |  |  |  |  |  | 11  |  |  |  |
| 19 | s18  | s19  |  |  |  |  |  |  | 13  |  |  |  |
| 20 | r10  | r10  | r10  | r10  |  |  |  |  |  |  |  |  |
| 21 | r4  | r4  | r4  | r4  |  |  |  |  | 15  |  |  |  |
| 22 | s18 r11  | s19 r11  | s20 r11  | r11  |  | 21  |  | 7  | 22  |  |  |  |
| 23 | r6 r14  | r6 r14  | r6 r14  | r6 r14  |  |  |  |  |  |  |  |  |
| 24 | s24  | s25  |  |  |  |  |  |  |  |  | 12  |  |
| 25 | s24  | s25  |  |  |  |  |  |  |  |  | 14  |  |
| 26 | r15  | r15  | r15  | r15  |  |  |  |  |  |  |  |  |
| 27 | r7  | r7  | r7  | r7  |  |  |  |  |  |  | 16  |  |
| 28 | s24 r16  | s25 r16  | s26 r16  | r16  |  |  | 27  |  |  | 9  | 28  |  |
| 29 | r12  | r12  | r12  | r12  |  |  |  |  | 37  |  |  |  |
| 30 | s18 r11  | s19 r11  | r11  | r11  |  |  |  |  | 30  |  |  |  |
| 31 | r17  | r17  | r17  | r17  |  |  |  |  |  |  | 38  |  |
| 32 | s24 r16  | s25 r16  | r16  | r16  |  |  |  |  |  |  | 32  |  |
| 33 | s18 r13  | s19 r13  | r13  | r13  |  |  |  |  | 11  |  |  |  |
| 34 | s24 r18  | s25 r18  | r18  | r18  |  |  |  |  |  |  | 12  |  |
| 35 | s39 r5  | r5  | r5  | r5  |  |  |  |  |  |  |  |  |
| 36 | r8  | s40 r8  | r8  | r8  |  |  |  |  |  |  |  |  |
| 37 | s41  |  |  |  |  |  |  |  |  |  |  |  |
| 38 | s42  |  |  |  |  |  |  |  |  |  |  |  |
| 39 | r9  | r9  | r9  | r9  |  |  |  |  |  |  |  |  |
| 40 | r14  | r14  | r14  | r14  |  |  |  |  |  |  |  |  |
| 41 | r13  | r13  | r13  | r13  |  |  |  |  |  |  |  |  |
| 42 | r18  | r18  | r18  | r18  |  |  |  |  |  |  |  |  |

### LR(0) table for palindrome

| LR(0) item | 0 | 1 | ? | $ | P | S |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | s1  | s2  | s3  |  | 4  |  |
| 1 | s1 r4  | s2 r4  | s3 r4  | r4  | 5  |  |
| 2 | s1 r3  | s2 r3  | s3 r3  | r3  | 6  |  |
| 3 | r5  | r5  | r5  | r5  |  |  |
| 4 | r0  | r0  | r0  | accept  |  |  |
| 5 | s7  |  |  |  |  |  |
| 6 |  | s8  |  |  |  |  |
| 7 | r2  | r2  | r2  | r2  |  |  |
| 8 | r1  | r1  | r1  | r1  |  |  |

# Complexity

Constructing the FIRST set is of O(m\*n<sup>2</sup>), where m is the number of rules per production, and n is the number of productions.

Constructing the FOLLOW set is of O(l\*m\*n<sup>2</sup>), where m is the number of rules per production, n is the number of productions, and l is the length of each production rule.
  
There are probably better approaches to constructing the sets, but the algorithm works.
