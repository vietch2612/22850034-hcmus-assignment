
class GraphData:
    adjacency_list1 = {
        'A': [('C', 2), ('D', 3)],
        'B': [('D', 2), ('E', 4)],
        'C': [('G', 4)],
        'D': [('G', 4)],
        'E': [],
        'F': [('G', 6)],
        'G': [],
        'S': [('A', 2), ('B', 1), ('F', 3)]
    }

    heuristic1 = {
        'A': 4,
        'B': 5,
        'C': 2,
        'D': 2,
        'E': 8,
        'F': 4,
        'G': 0,
        'S': 6
    }

    adjacency_list2 = {
        'a': [('b', 1), ('c', 1)],
        'b': [('a', 1), ('d', 1)],
        'c': [('a', 1), ('k', 1)],
        'd': [('b', 1), ('e', 1), ('m', 1)],
        'e': [('d', 1), ('n', 1)],
        'f': [('p', 1), ('s', 1)],
        'g': [('m', 1), ('t', 1)],
        'h': [('k', 1), ('s', 1)],
        'k': [('c', 1), ('h', 1)],
        'm': [('d', 1), ('g', 1), ('n', 1)],
        'n': [('e', 1), ('m', 1)],
        'p': [('f', 1), ('q', 1)],
        'q': [('p', 1), ('r', 1)],
        'r': [('q', 1), ('t', 1)],
        't': [('g', 1), ('r', 1)],
        's': [('h', 1), ('f', 1)]
    }

    heuristic2 = {
        'a': 4,
        'b': 3,
        'c': 3,
        'd': 2,
        'e': 3,
        'f': 5,
        'g': 0,
        'h': 3,
        'k': 2,
        'm': 1,
        'n': 2,
        'p': 4,
        'q': 3,
        'r': 2,
        't': 1,
        's': 4,
    }

    adjacency_list3 = {
        'A': [('B', 1), ('C', 4)],
        'B': [('A', 1), ('C', 1), ('D', 5)],
        'C': [('A', 4), ('B', 1), ('D', 3)],
        'D': [('B', 5), ('C', 3), ('E', 8), ('F', 3), ('G', 9)],
        'E': [('D', 8), ('G', 2)],
        'F': [('D', 3), ('G', 5)],
        'G': [('D', 9), ('E', 2), ('F', 5)]
    }

    heuristic3_h1 = {
        'A': 9.5,
        'B': 9,
        'C': 8,
        'D': 7,
        'E': 1.5,
        'F': 4,
        'G': 0,
    }

    heuristic3_h2 = {
        'A': 10,
        'B': 12,
        'C': 10,
        'D': 8,
        'E': 1,
        'F': 4.5,
        'G': 0,
    }

    adjacency_list4 = {
        'Arad': [
            ('Zerind', 75),
            ('Sibiu', 140),
            ('Timisoara', 118)],
        'Bucharest': [
            ('Fagaras', 211),
            ('Pitesti', 101),
            ('Giurgiu', 90),
            ('Urzieeni', 85)],
        'Craiova': [
            ('Dobreta', 120),
            ('Rimnicu Vilcea', 146),
            ('Pitesti', 138)],
        'Dobreta': [
            ('Mehadia', 75),
            ('Craiova', 120)],
        'Eforie': [
            ('Hirsova', 86)],
        'Fagaras': [
            ('Sibiu', 99),
            ('Bucharest', 211)],
        'Giurgiu': [
            ('Bucharest', 90)],
        'Hirsova': [
            ('Urzieeni', 98),
            ('Eforie', 86)],
        'Lasi': [
            ('Neamt', 87),
            ('Vaslui', 92)],
        'Lugoj': [
            ('Timisoara', 111),
            ('Mehadia', 70)],
        'Mehadia': [
            ('Lugoj', 70),
            ('Dobreta', 75)],
        'Neamt': [
            ('Lasi', 87)],
        'Oradea': [
            ('Zerind', 71),
            ('Sibiu', 151)],
        'Pitesti': [
            ('Craiova', 138),
            ('Rimnicu Vilcea', 97),
            ('Bucharest', 101)],
        'Rimnicu Vilcea': [
            ('Sibiu', 80),
            ('Pitesti', 97),
            ('Craiova', 146)],
        'Sibiu': [
            ('Oradea', 151),
            ('Arad', 140),
            ('Fagaras', 99),
            ('Rimnicu Vilcea', 80)],
        'Timisoara': [
            ('Arad', 118),
            ('Lugoj', 111)],
        'Urzieeni': [
            ('Vaslui', 142),
            ('Bucharest', 85),
            ('Hirsova', 98)],
        'Vaslui': [
            ('Lasi', 92),
            ('Urzieeni', 142)],
        'Zerind': [
            ('Oradea', 71),
            ('Arad', 75)]
    }

    heuristic4 = {
        'Arad': 366,
        'Bucharest': 0,
        'Craiova': 160,
        'Dobreta': 242,
        'Eforie': 161,
        'Fagaras': 178,
        'Giurgiu': 77,
        'Hirsova': 151,
        'Lasi': 266,
        'Lugoj': 244,
        'Mehadia': 241,
        'Neamt': 234,
        'Oradea': 380,
        'Pitesti': 98,
        'Rimnicu Vilcea': 193,
        'Sibiu': 253,
        'Timisoara': 329,
        'Urzieeni': 80,
        'Vaslui': 199,
        'Zerind': 374
    }
