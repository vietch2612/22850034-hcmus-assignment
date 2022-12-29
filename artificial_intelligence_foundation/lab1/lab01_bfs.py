# Graph 1
graph1 = {
    'a': [],
    'b': ['a'],
    'c': ['a'],
    'd': ['b', 'c', 'e'],
    'e': ['h', 'r'],
    'f': ['c', 'g'],
    'g': [],
    'h': ['p', 'q'],
    'p': ['q'],
    'q': [],
    'r': ['f'],
    's': ['d', 'e', 'p']
}

# Graph 2
graph2 = {
    'a': ['b', 'c'],
    'b': ['a', 'd'],
    'c': ['a', 'k'],
    'd': ['b', 'e', 'm'],
    'e': ['d', 'n'],
    'f': ['p', 's'],
    'g': ['m', 't'],
    'h': ['k', 's'],
    'k': ['c', 'h'],
    'm': ['d', 'g', 'n'],
    'n': ['e', 'm'],
    'p': ['f', 'q'],
    'q': ['p', 'r'],
    'r': ['q', 't'],
    't': ['g', 'r'],
    's': ['h', 'f']
}

# Graph 3
graph3 = {
    'A': ['B', 'C'],
    'B': ['A', 'C', 'D'],
    'C': ['A', 'B', 'D'],
    'D': ['B', 'C', 'E', 'F', 'G'],
    'E': ['D', 'G'],
    'F': ['D', 'G'],
    'G': ['D', 'E', 'F']
}


def bfs_without_path(graph, start, end):
    visited = []  # List to keep track of visited nodes.
    queue = []
    visited.append(start)
    queue.append(start)
    while queue:
        s = queue.pop(0)

        print(s, end=" ")
        if s == end:
            return

        for neighbour in graph[s]:
            if neighbour not in visited:
                visited.append(neighbour)
                queue.append(neighbour)


def bfs(graph, start, end):
    # maintain a queue of paths
    visited = []
    queue = []
    # push the first path into the queue
    queue.append([start])
    while queue:
        # get the first path from the queue
        path = queue.pop(0)
        # get the last node from the path
        node = path[-1]
        # mark node as visited
        visited.append(node)
        # path found
        if node == end:
            return path
        # enumerate all adjacent nodes, construct a new path and push it into the queue
        for neighbour in graph.get(node, []):
            if neighbour not in visited:
                new_path = list(path)
                new_path.append(neighbour)
                queue.append(new_path)


print(bfs_without_path(graph1, 's', 'g'))  # Graph 1
print(bfs(graph1, 's', 'g'))  # Graph 1

print(bfs_without_path(graph2, 's', 'g'))  # Graph 2
print(bfs(graph2, 's', 'g'))  # Graph 2

print(bfs_without_path(graph3, 'A', 'G'))  # Graph 3
print(bfs(graph3, 'A', 'G'))  # Graph 3
