translate(0, zero).
translate(1, one).
translate(2, two).
translate(3, three).
translate(4, four).
translate(5, five).
translate(6, six).
translate(7, seven).
translate(8, eight).
translate(9, nine).

listtran([], []).
listtran([H|T], [X|Y]) :-
    translate(H, X),
    listtran(T, Y).
