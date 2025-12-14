import sys

def numWaysToOut(graph, node):
    if node == 'out':
        return 1
    for neighbor in graph.get(node, []):
        return sum(numWaysToOut(graph, neighbor) for neighbor in graph.get(node, []))

graph = {}
for line in sys.stdin:
    tokens = [x for x in line.split()]
    source = tokens[0][0:-1]
    destinations = tokens[1:]
    for i in range(len(destinations)):
        if source not in graph:
            graph[source] = [destinations[i]]
        else:
            graph[source].append(destinations[i])
    
print(numWaysToOut(graph, 'you'))
 
        