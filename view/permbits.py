import matplotlib.pyplot as plt
import numpy as np
import matplotlib.ticker as ticker

# Define the permutation function P_64(i)
def P_64(i):
    return 4 * (i // 16) + 16 * ((3 * ((i % 16) // 4) + (i % 4)) % 4) + (i % 4)

# Generate the mappings
original_positions = np.arange(64)
new_positions = np.array([P_64(i) for i in original_positions])

# Convert positions to hexadecimal format for better readability
hex_positions = [f'{i:02x}' for i in range(64)]

# Create a prettier and more readable plot
plt.figure(figsize=(15, 10))
plt.scatter(original_positions, new_positions, c='blue', alpha=0.6, edgecolors='w', s=80)

# Set axis ticks to hexadecimal
plt.xticks(ticks=np.arange(64), labels=hex_positions, rotation=90, fontsize=10)
plt.yticks(ticks=np.arange(64), labels=hex_positions, fontsize=10)

plt.title('Bit Permutation Visualization for P_64(i)', fontsize=16)
plt.xlabel('Original Position (i) in Hexadecimal', fontsize=14)
plt.ylabel('New Position (P_64(i)) in Hexadecimal', fontsize=14)
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.tight_layout()
plt.show()

# Visualizing the effect of each term in the permutation function P_64(i)

# # Define the three terms of the function
# def term1(i):
#     return 4 * (i // 16)

# def term2(i):
#     return 16 * ((3 * ((i % 16) // 4) + (i % 4)) % 4)

# def term3(i):
#     return (i % 4)

# # Generate the values for each term
# values_term1 = np.array([term1(i) for i in original_positions])
# values_term2 = np.array([term2(i) for i in original_positions])
# values_term3 = np.array([term3(i) for i in original_positions])

# # Create the plot
# plt.figure(figsize=(15, 10))

# # Plot each term's contribution
# plt.scatter(original_positions, values_term1, alpha=0.6, edgecolors='none', s=80, label='Term 1: 4 * floor(i / 16)')
# plt.scatter(original_positions, values_term2, alpha=0.6, edgecolors='none', s=80, label='Term 2: 16 * ((3 * floor(i mod 16 / 4) + (i mod 4)) mod 4)')
# plt.scatter(original_positions, values_term3, alpha=0.6, edgecolors='none', s=80, label='Term 3: (i mod 4)')

# # Adding the total effect
# plt.scatter(original_positions, new_positions, alpha=0.6, edgecolors='none', s=80, label='Total: P_64(i)', color='black')

# plt.title('Individual Contribution of Each Term in P_64(i)', fontsize=16)
# plt.xlabel('Original Position (i)', fontsize=14)
# plt.ylabel('Value Contributed by Each Term', fontsize=14)
# plt.xticks(ticks=np.arange(64), labels=hex_positions, rotation=90, fontsize=10)
# plt.yticks(fontsize=10)
# plt.legend()
# plt.grid(True, which='both', linestyle='--', linewidth=0.5)
# plt.tight_layout()
# plt.show()