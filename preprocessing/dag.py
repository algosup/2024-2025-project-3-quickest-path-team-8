import networkx as nx
import matplotlib.pyplot as plt
import pandas as pd

# Read edges from CSV
csv_file = '../quickest_path/data/USA-roads_sorted.csv'
edges_df = pd.read_csv(csv_file, names=['source', 'target', 'weight'])

def log_cycles(G):
    """
    Logs any cycles found in the directed graph.
    """
    try:
        cycles = list(nx.find_cycle(G, orientation='original'))
        if cycles:
            print("Cycles detected in the graph:")
            for cycle in cycles:
                cycle_nodes = " -> ".join(str(node) for node in cycle)
                print(f"Cycle found: {cycle_nodes}")
        else:
            print("No cycles detected. The graph is a DAG.")
    except nx.NetworkXNoCycle:
        print("No cycles detected. The graph is a DAG.")

def validate_dag(G):
    """
    Validates if the graph is a DAG.
    """
    if nx.is_directed_acyclic_graph(G):
        print("The graph is a valid DAG.")
    else:
        print("The graph contains cycles and is not a DAG.")



def check_connectivity(G):
    """
    Checks if the DAG is weakly connected without using library functions.
    If not, returns any separate components.
    """
    # Build an undirected adjacency list
    adjacency = {}
    for node in G.nodes():
        adjacency[node] = set()
    for source, target in G.edges():
        adjacency[source].add(target)
        adjacency[target].add(source)

    visited = set()
    components = []

    # BFS to identify connected components
    for node in G.nodes():
        if node not in visited:
            queue = [node]
            visited.add(node)
            component = {node}

            while queue:
                current = queue.pop(0)
                for neighbor in adjacency[current]:
                    if neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)
                        component.add(neighbor)

            components.append(component)

    if len(components) == 1:
        print("All nodes are connected in one main component.")
    else:
        print("The graph has multiple subgraphs:")
        for i, comp in enumerate(components, start=1):
            print(f"Subgraph {i}: {comp}")


# Ensure the CSV contains the correct columns
if 'source' in edges_df.columns and 'target' in edges_df.columns:
    # Create a directed graph
    G = nx.DiGraph()

    # Add edges from the CSV
    edges = list(zip(edges_df['source'], edges_df['target']))
    G.add_edges_from(edges)

    # Log and validate cycles
    # log_cycles(G)
    # validate_dag(G)
    check_connectivity(G)

else:
    print("CSV file must contain 'source' and 'target' columns.")


