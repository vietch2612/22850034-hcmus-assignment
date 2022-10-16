is_even(N) :-
    0 =:= N mod 2.

sum_on_list([], 0).
sum_on_list([H|T], S) :-
    sum_on_list(T, R),
    S is H * H + R.

sumodd2to(0, 0).
sumodd2to(X, S) :-
    numlist(1, X, L),
    exclude(is_even, L, R),
    sum_on_list(R, S).

