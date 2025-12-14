# CSCI 650 - Fall 2024
# The CYK Algorithm Skeleton
# Author: Carter Tillquist

from itertools import product

# Run the CYK algorithm to determine whether or not w is in the language associated with the grammar G
# Return True if it is and False otherwise. In addition, return the table filled in during the course of the CYK algorithm.
def cyk(G, w):
  V, T, P, S = G
  n = len(w)
  
  # Handle empty string edge case if necessary (though CYK usually requires n >= 1)
  if n == 0:
    # If empty string is in language (S -> epsilon), return True. 
    # But standard CYK implies length > 0. We'll return False/Empty table.
    return False, []

  # Initialize Table (n x n)
  # M[i][j] stores the set of variables that derive the substring starting at j with length i+1.
  # Note: The indices can be organized variously. Here we use: M[length-1][start_index]
  M = [[set() for _ in range(n)] for _ in range(n)]

  # 1. Base Case: Substrings of length 1
  for i in range(n):
    symbol = w[i]
    # Check all productions for A -> symbol
    for head, bodies in P.items():
      if symbol in bodies:
        M[0][i].add(head)

  # 2. Recursive Step: Substrings of length 2 to n
  for length in range(2, n + 1):
    for i in range(n - length + 1):
      j = i + length - 1
      # Partition the substring w[i...j] at k
      # Left part: length (k - i + 1), starts at i
      # Right part: length (j - k), starts at k + 1
      for k in range(i, j):
        left_len_idx = (k - i + 1) - 1
        right_len_idx = (j - (k + 1) + 1) - 1
        
        B_set = M[left_len_idx][i]
        C_set = M[right_len_idx][k+1]
        
        # Look for A -> BC
        if B_set and C_set:
          for head, bodies in P.items():
            for body in bodies:
              if len(body) == 2: # Ensure it's a binary production (CNF)
                B = body[0]
                C = body[1]
                if B in B_set and C in C_set:
                  M[length-1][i].add(head)

  # 3. Check if Start symbol S is in the cell for the whole string M[n-1][0]
  isElem = S in M[n-1][0]
  
  # Format table elements as sorted strings for cleaner output if desired, 
  # but the main function maps str() which handles sets.
  # We simply return the matrix of sets.
  return isElem, M

##########################
### MAIN FOR INGINIOUS ###
##########################
def main(V, T, P, S, w):
  isElem, M = cyk((V, T, P, S), w)
  mat = ''
  for row in M: mat += ' | '.join(map(str, row))+'\n'
  return mat+str(isElem)

if __name__=='__main__':
  n = int(input("Enter a number of lines to read: "))
  V, T, P, S = set(), set(), {}, ''
  for i in range(n):
    line = input().strip()
    V |= set([c for c in line if c.isupper()])
    T |= set([c for c in line if not c.isupper() and c not in '->| '])
    line = line.split('->')
    head = line[0].strip()
    bodies = set([b.strip() for b in line[1].split('|')])
    if i == 0: S = head
    P[head] = P.get(head, set()) | bodies
  w = input("Enter a string to test: ")
  result = main(V, T, P, S, w)
  print(result)