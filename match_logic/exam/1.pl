element_at([H|_], I, X) :-
    I = 0,
    X is H.
element_at([_|T], I, X) :-
    I > 0,
    I1 is I - 1,
    element_at(T, I1, X).
