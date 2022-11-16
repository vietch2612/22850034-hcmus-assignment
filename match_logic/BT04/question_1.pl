doublelist([],[]).
doublelist([H|T], [X|Y]) :-
    X is H*2,
    doublelist(T,Y).
