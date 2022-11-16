is_negative(X) :-
    X < 0.

removeNeg(L, R) :-
    exclude(is_negative, L, R).

minmax(X,Y,Z) :- min_list(X, Y), max_list(X, Z).
