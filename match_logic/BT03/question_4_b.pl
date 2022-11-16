% Facts
% Class name = Logic
programming(viet, java).
programming(an, java).
programming(tam, python).
class(an, logic).
class(viet, math).
class(tam, physic).

% Rules
highIncome(X) :-
    programming(X, java).

hasHighIncomeInClass(X) :-
    highIncome(Z), class(Z, X), !.

