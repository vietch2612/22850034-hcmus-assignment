#!/usr/bin/env python3
from math import inf as infinity
from random import choice
import platform
import time
from os import system

"""
An implementation of alpha_beta_pruning AI Algorithm in Tic Tac Toe,
using Python.
This software is available under GPL license.
Author: Clederson Cruz
Year: 2017
License: GNU GENERAL PUBLIC LICENSE (GPL)
"""

HUMAN = -1
COMP = +1
NUM_TO_WIN = 3
BOARD_SIZE = 5
MAX_DEPTH = 9

board = []

# pre_input_board = [
#     ['X', 'O', 'O', 'X'],
#     [0, 0, 0, 'O'],
#     [0, 0, 0, 'X'],
#     [0, 0, 0, 'O']
# ]

# 4x4 Empty
pre_input_board = [
    [0, 0, 0, 0],
    [0, 0, 0, 0],
    [0, 0, 0, 0],
    [0, 0, 0, 0]
]

# 5x5 Empty (Not running yet)
# pre_input_board = [
#     [0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0],
#     [0, 0, 0, 0, 0]
# ]


def convert_board(board, h_choice, c_choice):
    rows = len(board)
    cols = len(board[0])

    for i in range(rows):
        for j in range(cols):
            if board[i][j] == h_choice:
                board[i][j] = HUMAN
            elif board[i][j] == c_choice:
                board[i][j] = COMP

    return board


def evaluate(state):
    """
    Function to heuristic evaluation of state.
    :param state: the state of the current board
    :return: +1 if the computer wins; -1 if the human wins; 0 draw
    """
    if wins(state, COMP):
        score = +1
    elif wins(state, HUMAN):
        score = -1
    else:
        score = 0

    return score


def wins(state, player, num_to_win=NUM_TO_WIN):
    """
    This function tests if a specific player wins on a board of any size.
    :param state: the state of the current board as a 2D list
    :param player: a human or a computer
    :param num_to_win: the number of consecutive marks needed to win
    :return: True if the player wins
    """
    rows = len(state)
    cols = len(state[0])

    # Check rows
    for i in range(rows):
        for j in range(cols - num_to_win + 1):
            if all(state[i][j+k] == player for k in range(num_to_win)):
                return True

    # Check columns
    for i in range(rows - num_to_win + 1):
        for j in range(cols):
            if all(state[i+k][j] == player for k in range(num_to_win)):
                return True

    # Check diagonals
    for i in range(rows - num_to_win + 1):
        for j in range(cols - num_to_win + 1):
            if all(state[i+k][j+k] == player for k in range(num_to_win)):
                return True

    for i in range(num_to_win-1, rows):
        for j in range(cols - num_to_win + 1):
            if all(state[i-k][j+k] == player for k in range(num_to_win)):
                return True

    return False


def game_over(state):
    """
    This function test if the human or computer wins
    :param state: the state of the current board
    :return: True if the human or computer wins
    """
    return wins(state, HUMAN) or wins(state, COMP)


def empty_cells(state):
    """
    Each empty cell will be added into cells' list
    :param state: the state of the current board
    :return: a list of empty cells
    """
    cells = []

    for x, row in enumerate(state):
        for y, cell in enumerate(row):
            if cell == 0:
                cells.append([x, y])

    return cells


def valid_move(x, y):
    """
    A move is valid if the chosen cell is empty
    :param x: X coordinate
    :param y: Y coordinate
    :return: True if the board[x][y] is empty
    """
    if [x, y] in empty_cells(board):
        return True
    else:
        return False


def set_move(x, y, player):
    """
    Set the move on board, if the coordinates are valid
    :param x: X coordinate
    :param y: Y coordinate
    :param player: the current player
    """
    if valid_move(x, y):
        board[x][y] = player
        return True
    else:
        return False


def alpha_beta_pruning(state, depth, player, alpha, beta):
    """
    AI function that choice the best move
    :param state: current state of the board
    :param depth: node index in the tree (0 <= depth <= BOARD_SIZE ** 2),
    but never nine in this case (see iaturn() function)
    :param player: an human or a computer
    :param alpha: the alpha value for alpha-beta pruning
    :param beta: the beta value for alpha-beta pruning
    :return: a list with [the best row, best col, best score]
    """
    if player == COMP:
        best = [-1, -1, -infinity]
    else:
        best = [-1, -1, +infinity]

    if depth == MAX_DEPTH:
        depth = MAX_DEPTH

    if depth == 0 or game_over(state):
        score = evaluate(state)
        return [-1, -1, score]

    for cell in empty_cells(state):
        x, y = cell[0], cell[1]
        state[x][y] = player
        score = alpha_beta_pruning(state, depth - 1, -player, alpha, beta)
        state[x][y] = 0
        score[0], score[1] = x, y

        if player == COMP:
            if score[2] > best[2]:
                best = score  # max value
            alpha = max(alpha, score[2])
            if beta <= alpha:
                break
        else:
            if score[2] < best[2]:
                best = score  # min value
            beta = min(beta, score[2])
            if beta <= alpha:
                break

    return best


def clean():
    """
    Clears the console
    """
    os_name = platform.system().lower()
    if 'windows' in os_name:
        system('cls')
    else:
        system('clear')


def render(state, c_choice, h_choice):
    """
    Print the board on console
    :param state: current state of the board
    """

    chars = {
        -1: h_choice,
        +1: c_choice,
        0: ' '
    }
    str_line = '---------------'

    print('\n' + str_line)
    for row in state:
        for cell in row:
            symbol = chars[cell]
            print(f'| {symbol} |', end='')
        print('\n' + str_line)


def ai_turn(c_choice, h_choice, board_size=BOARD_SIZE):
    """
    It calls the alpha_beta_pruning function if the depth < (board_size ** 2),
    else it chooses a random coordinate.
    :param c_choice: computer's choice X or O
    :param h_choice: human's choice X or O
    :param board_size: size of the board (default 3 for standard tic-tac-toe)
    :return:
    """
    print("AI Turn")
    depth = len(empty_cells(board))
    if depth == 0 or game_over(board):
        return

    clean()
    print(f'Computer turn [{c_choice}]')
    render(board, c_choice, h_choice)

    if depth == (board_size ** 2):
        x = choice(range(board_size))
        y = choice(range(board_size))
    else:
        alpha = -infinity
        beta = +infinity
        move = alpha_beta_pruning(board, depth, COMP, alpha, beta)
        x, y = move[0], move[1]

    set_move(x, y, COMP)


def human_turn(c_choice, h_choice):
    """
    The Human plays choosing a valid move.
    :param c_choice: computer's choice X or O
    :param h_choice: human's choice X or O
    :return:
    """
    depth = len(empty_cells(board))
    if depth == 0 or game_over(board):
        return

    clean()
    print(f'Human turn [{h_choice}]')
    render(board, c_choice, h_choice)

    moved = False
    while not moved:
        try:
            input_str = input(
                "Please input your move with the index. e.g: 0,2 to move to row 0 and column 2: ")
            x, y = map(int, input_str.split(','))
            moved = set_move(x, y, HUMAN)

            if not moved:
                print('Bad move')

        except (EOFError, KeyboardInterrupt):
            print('Bye')
            exit()
        except (KeyError, ValueError):
            print('Bad choice')


def main():
    """
    Main function that calls all functions
    """
    clean()
    h_choice = ''  # X or O
    c_choice = ''  # X or O
    first = ''  # if human is the first

    # Human chooses X or O to play
    while h_choice != 'O' and h_choice != 'X':
        try:
            print('')
            h_choice = input('Choose X or O\nChosen: ').upper()
        except (EOFError, KeyboardInterrupt):
            print('Bye')
            exit()
        except (KeyError, ValueError):
            print('Bad choice')

    # Setting computer's choice
    if h_choice == 'X':
        c_choice = 'O'
    else:
        c_choice = 'X'

    global board
    board = convert_board(pre_input_board, h_choice, c_choice)

    # Human may starts first
    clean()
    while first != 'Y' and first != 'N':
        try:
            first = input('First to start? [y/n]: ').upper()
        except (EOFError, KeyboardInterrupt):
            print('Bye')
            exit()
        except (KeyError, ValueError):
            print('Bad choice')

    # Main loop of this game
    while len(empty_cells(board)) > 0 and not game_over(board):
        if first == 'N':
            ai_turn(c_choice, h_choice)
            first = ''

        human_turn(c_choice, h_choice)
        ai_turn(c_choice, h_choice)

    # Game over message
    if wins(board, HUMAN):
        clean()
        print(f'Human turn [{h_choice}]')
        render(board, c_choice, h_choice)
        print('YOU WIN!')
    elif wins(board, COMP):
        clean()
        print(f'Computer turn [{c_choice}]')
        render(board, c_choice, h_choice)
        print('YOU LOSE!')
    else:
        clean()
        render(board, c_choice, h_choice)
        print('DRAW!')

    exit()


if __name__ == '__main__':
    main()
