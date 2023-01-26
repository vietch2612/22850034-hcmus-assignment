class GraphBase:

    def __init__(self, adjacency_list, heuristic):
        self.adjacency_list = adjacency_list
        self.h = heuristic

    def get_neighbors(self, v):
        return self.adjacency_list[v]
