# Bài Tập 4

Deadline: October 23, 2022
Type: 📌 Assignment

### Thông tin sinh viên

- Họ và tên: Cao Hoài Việt
- MSSV: 22850034

### 1. Viết vị từ `doublelist(L, R)` với `L` là một danh sách các số được cho, `R` là danh sách `L`với mỗi phần tử được gấp đôi lên.

```prolog
% Example
?- doublelist([-1, 0, 3], L).
L = [-2, 0, 6].
```

Bài làm

```prolog
doublelist([],[]).
doublelist([H|T], [X|Y]) :-
    X is H*2,
    doublelist(T,Y).
```

### 2. Viết vị từ `listran(L, R)` với `L` là một danh sách các số từ `0` đến `10`, `R` là danh sách các từ tiếng Anh tương ứng.

```prolog
% Example
?- listtran([0, 4, 5], L).
L = [zero, four, five].

?- listtran(L, [two, ten, two]).
L = [2, 10, 2].
```

Bài làm

```prolog
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
```

### 3. Viết vị từ `sumodd2to(N, S)` với `N` là một số nguyên dương được cho, `S` sẽ là tổng bình phương các số lẻ từ `1` đến `N` (nghĩa là, $S = 1^2 + 3^2 + 5^2 + ... +X^2$, $X$ là $N$ nếu $N$ lẻ và là $N– 1$ nếu $N$ chẵn).

```prolog
% Example
?- sumodd2to(5, S).
S = 35.

?- sumodd2to(6, S).
S = 35.
```

Bài làm

```prolog
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
```

### 4. Viết vị từ `removeNeg(L, R)` với `L` là một danh sách các số được cho, `R` là danh sách `L` sau khi xóa đi các số âm.

```prolog
% Example
?- removeNeg([-1, 0, 3, -10], L).
L = [0, 3].
```

Bài làm

```prolog
removeNeg([], []).
removeNeg([H|T], L) :-
    H < 0,
    removeNeg(T, L).
removeNeg([H|T], [H|L]) :-
    H >= 0,
    removeNeg(T, L).
```

### 5. Viết vị từ `minmax(L, X, Y)` tìm phần tử nhỏ nhất `X` và lớn nhất `Y` trong danh sách các số nguyên `L`.

```prolog
% Example
?- minmax([1, -10, 1, 0, 7, 7], X, Y).
X = -10, Y = 7.
```

Bài làm

```prolog
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
```
