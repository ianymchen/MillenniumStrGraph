import graph

g = graph.Graph()

node1 = g.AddNode("node1", "str1")
node2 = g.AddNode("node2", "str2")
node3 = g.AddNode("node3", "str3")

edge1 = g.AddEdge(node1, node2, 1)
edge2 = g.AddEdge(node2, node3, 2)
edge3 = g.AddEdge(node1, node3, 3)


def DFS(start_node, constant, path=None):
    stack = [(start_node, [start_node.s()])]  # start_node and its path's s()
    paths = []
    while stack:
        curr_node, path = stack.pop()
        for edge in curr_node.out_edges():
            next_node = edge.to()
            next_path = path + [next_node.s()]
            if next_node.out_edges():
                stack.append((next_node, next_path))
            else:
                paths.append("->".join(next_path))
    paths = [f"{path}=>{constant}" for path in paths]
    return paths


ret = DFS(node1, "Exit")

for i, path in enumerate(ret, 1):
    print(f"path{i}: {path}")

