import pandas as pd
import os

def sort_and_compare_csv(file_path):
    try:
        # Read the original CSV
        df = pd.read_csv(file_path)
        original_count = len(df)
        
        # Sort by the first and second columns
        sorted_df = df.sort_values(by=[df.columns[0], df.columns[1]])
        
        # Generate output filename
        directory, filename = os.path.split(file_path)
        name, ext = os.path.splitext(filename)
        output_path = os.path.join(directory, f"{name}_sorted{ext}")
        
        # Save the sorted CSV
        sorted_df.to_csv(output_path, index=False)
        
        # Compare row counts
        sorted_count = len(sorted_df)
        
        print(f"File sorted and saved as: {output_path}")
        print(f"Original row count: {original_count}")
        print(f"Sorted row count: {sorted_count}")
        
        # Check for discrepancies
        if original_count == sorted_count:
            print("No values are missing. Row counts match.")
        else:
            print("Warning: Mismatch detected. Rows may be missing!")
            print(f"Difference: {original_count - sorted_count}")
        
    except Exception as e:
        print(f"Error processing file: {str(e)}")

# Example usage
csv_file = 'USA-roads.csv'  # Replace with your file path
sort_and_compare_csv(csv_file)