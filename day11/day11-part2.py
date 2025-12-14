import sys

def numWaysToOut(graph, node, dest, cache):
    #print("At node:", node)
    if (node, dest) in cache:
        return cache[(node, dest)]
    if node == dest:
        return 1
    value = 0
    for neighbor in graph.get(node, []):
        value += numWaysToOut(graph, neighbor, dest, cache)
    cache[(node, dest)] = value
    return value
    
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
        
cache = {}
waysFromSvrToDac = numWaysToOut(graph, 'svr', 'dac', cache)
print("Number of ways from svr to dac:", waysFromSvrToDac)
waysFromSvrToFft = numWaysToOut(graph, 'svr', 'fft', cache)
print("Number of ways from svr to fft:", waysFromSvrToFft)
waysFromDacToFft = numWaysToOut(graph, 'dac', 'fft', cache)
print("Number of ways from dac to fft:", waysFromDacToFft)
waysFromFftToDac = numWaysToOut(graph, 'fft', 'dac', cache)
print("Number of ways from fft to dac:", waysFromFftToDac)
waysFromDacToOut = numWaysToOut(graph, 'dac', 'out', cache)
print("Number of ways from dac to out:", waysFromDacToOut)
waysFromFftToOut = numWaysToOut(graph, 'fft', 'out', cache)
print("Number of ways from fft to out:", waysFromFftToOut)

totalWays = (waysFromSvrToDac * waysFromDacToFft * waysFromFftToOut) + (waysFromSvrToFft * waysFromFftToDac * waysFromDacToOut)
print("Total number of ways from svr to out:", totalWays)