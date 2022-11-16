sumlist([],0).
sumlist([H|T], Sum) :-
    sumlist(T, R),
    Sum is H * H + R.
