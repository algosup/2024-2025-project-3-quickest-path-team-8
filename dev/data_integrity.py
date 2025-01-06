import networkx as nx
import matplotlib.pyplot as plt
import pandas as pd

# Read edges from CSV
csv_file = 'dev/points_times.csv'
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
                print(" -> ".join(str(node) for node in cycle))
    except nx.NetworkXNoCycle:
        print("No cycles detected. The graph is a DAG.")

def visualize_graph(G):
    """
    Visualizes the graph using matplotlib.
    """
    plt.figure(figsize=(14, 10))
    pos = nx.spring_layout(G, k=0.8, scale=2)
    nx.draw(G, pos, with_labels=True, node_color='skyblue', node_size=2500, font_size=16, edge_color='gray')
    plt.title("Graph Visualization (Cycles Logged)")
    plt.show()

# Ensure the CSV contains the correct columns
if 'source' in edges_df.columns and 'target' in edges_df.columns:
    # Create a directed graph
    G = nx.DiGraph()

    # Add edges (ignore weights)
    edges = list(zip(edges_df['source'], edges_df['target']))
    G.add_edges_from(edges)

    # Log any detected cycles
    log_cycles(G)
    
    # Visualize the graph regardless of cycles
    visualize_graph(G)

else:
    print("CSV file must contain 'source' and 'target' columns.")