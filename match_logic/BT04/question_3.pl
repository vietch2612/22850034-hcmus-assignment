is_odd(N) :-
    0 =\= N mod 2.

sum_on_list([], 0).
sum_on_list([H|T], S) :-
    sum_on_list(T, R),
    S is H * H + R.

get_num(N, L) :-
    (is_odd(N) -> L is N - 1; L is N - 2).

    create_list(1, [1]).
create_list(N, [N|T]) :-
    N > 1,
    get_num(N, L),
    create_list(L, T).

sumodd2to(0, 0).
sumodd2to(X, S) :-
    create_list(X, L),
    exclude(is_even, L, R),
    sum_on_list(R, S).

