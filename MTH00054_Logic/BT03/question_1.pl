% a. Butch is a killer.
killer(butch).

% b. Mia and Marcellus are married.
married(mia, marcellus).

% c. Zed is dead.
dead(zed).

% d. Marcellus kills everyone who gives Mia a footmassage.
kill(marcellus, X):-
    footmassage(X, mia).

% e. Mia loves everyone who is a good dancer.
love(mia, X):-
    good_dancer(X).

% f. Fules eats anything that is nutritious or tasty
eat(jules, X):-
    nutritious(X);
    tasty(X).
