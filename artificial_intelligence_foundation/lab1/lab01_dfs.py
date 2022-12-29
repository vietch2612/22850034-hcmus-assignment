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

# # Using recursive option
# def dfs_without_path(visited, graph, start, end):
#     visited.append(start)
#     print(start, end=" ")
#     if start == end:
#         return

#     for neighbour in graph[start]:
#         if neighbour not in visited:
#             dfs_without_path(visited, graph, neighbour, end)

def dfs_without_path(graph, start, end):
    visited = []
    stack = []
    stack.append(start)
    
    while (stack):
        s = stack.pop()

        print(s, end=" ")
        if s == end:
            return

        if s not in visited:
            visited.append(s)

        for neighbor in graph[s]:
            if neighbor not in visited:
                stack.append(neighbor)

# # Using recursive option
# def dfs(path, visited, graph, start, end):
#     visited.append(start)
#     path.append(start)

#     if start == end:
#         return path

#     for neighbour in graph[start]:
#         if neighbour not in visited:
#             dfs(path, visited, graph, neighbour, end)

#     path.pop()

def dfs(graph, start, end):
    # maintain a stack of paths
    visited = []
    stack = []
    # push the first path into the stack
    stack.append([start])
    while stack:
        # get the last path from the stack (Last in - First out)
        path = stack.pop()
        # get the last node from the path
        node = path[-1]
        # mark node as visited
        visited.append(node)
        # path found
        if node == end:
            return path
        # enumerate all adjacents, construct a new path and push it into the stack
        for neighbor in graph.get(node, []):
            if neighbor not in visited:
                new_path = list(path)
                new_path.append(neighbor)
                stack.append(new_path)


print(dfs_without_path(graph1, 's', 'g')) # Graph 1
print(dfs(graph1, 's', 'g'))  # Graph 1

print(dfs_without_path(graph2, 's', 'g'))  # Graph 2
print(dfs(graph2, 's', 'g'))  # Graph 2

print(dfs_without_path(graph3, 'A', 'G'))  # Graph 3
print(dfs(graph3, 'A', 'G'))  # Graph 3
