min([], []).
min([L], L).
min([H,K|T], R) :-
    H =< K,
    min([H|T], R).
min([H,K|T], R) :-
    H > K,
    min([K|T], R).

max([], []).
max([L], L).
max([H,K|T], R) :-
    H > K,
    max([H|T], R).
max([H,K|T], R) :-
    H =< K,
    max([K|T], R).

minmax([], [], []).
minmax(L, X, Y) :-
    min(L, X),
    max(L, Y).

