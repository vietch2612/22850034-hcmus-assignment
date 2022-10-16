removeNeg([], []).
removeNeg([H|T], L) :-
    H < 0,
    removeNeg(T, L).
removeNeg([H|T], [H|L]) :-
    H >= 0,
    removeNeg(T, L).
