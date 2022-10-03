bigger_than(katarina, olga).
bigger_than(olga, natasha).
bigger_than(natasha, irina).

in(X, Y) :-
    bigger_than(X, Y).

in(X, Y) :-
    bigger_than(X, Z),
    in(Z, Y).

