from greedy import GreedySearch
from ucs import UcsSearch
from a_star import AStarSearch
from graph_data import GraphData


class Graph(GreedySearch, UcsSearch, AStarSearch):
    pass


print('----------------')
print('Graph #1')
graph1 = Graph(GraphData.adjacency_list1, GraphData.heuristic1)
node_start = 'S'
node_end = 'G'
graph1.a_star_algorithm(node_start, node_end)
graph1.greedy_algorithm(node_start, node_end)
graph1.ucs_algorithm(node_start, node_end)
print('----------------')


print('Graph #2')
graph2 = Graph(GraphData.adjacency_list2, GraphData.heuristic2)
node_start = 's'
node_end = 'g'
graph2.a_star_algorithm(node_start, node_end)
graph2.greedy_algorithm(node_start, node_end)
graph2.ucs_algorithm(node_start, node_end)
print('----------------')

print('Graph #3 with h1')
graph3_1 = Graph(GraphData.adjacency_list3, GraphData.heuristic3_h1)
node_start = 'A'
node_end = 'G'
graph3_1.a_star_algorithm(node_start, node_end)
graph3_1.greedy_algorithm(node_start, node_end)
graph3_1.ucs_algorithm(node_start, node_end)
print('----------------')

print('Graph #3 with h2')
graph3_2 = Graph(GraphData.adjacency_list3, GraphData.heuristic3_h2)
node_start = 'A'
node_end = 'G'
graph3_2.a_star_algorithm(node_start, node_end)
graph3_2.greedy_algorithm(node_start, node_end)
graph3_2.ucs_algorithm(node_start, node_end)
print('----------------')

print('Graph #4')
graph4 = Graph(GraphData.adjacency_list4, GraphData.heuristic4)
node_start = 'Arad'
node_end = 'Bucharest'
graph4.a_star_algorithm(node_start, node_end)
graph4.greedy_algorithm(node_start, node_end)
graph4.ucs_algorithm(node_start, node_end)
print('----------------')
