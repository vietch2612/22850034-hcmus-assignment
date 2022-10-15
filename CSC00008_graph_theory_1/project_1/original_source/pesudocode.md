```
set UNVISITED = -1
n = numver of vertices in the graph
g = directed adjacency matrix
stack = empty stack
ids[n] = {-1, -1, ..., -1}
root[n] = {-1, -1, ..., -1}
on_stack[n] = {false, false, ..., false}
cps = empty vector contains the list of connected components
for (i = 0; i < n, i++)
if (ids[i] is UNVISITED)
dfs_find(v)
return root

function dfs_find(v)
stack.push(v)
ids[v] = root[v] = index++
on_stack[v] = true

for (i = 0; i < n, i++)
if g[u][i]
if ids[i] is UNVISITED
dfs_find(i)
root[v] = minimum(root[v], root[i])
else if on_strack[i] then
root[v] = minimum(root[v], ids[i])

if root[v] == ids[v]
cp = a new strongly connected component (cp)
while (stack.top() != v)
w = stack.pop()
on_stack[w] = false
cp.push[w]
w = stack.pop()
on_stack[w] = false
cp.push[w]
cps.push[cp]

print connected components CPS to console
```
