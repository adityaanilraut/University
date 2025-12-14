#CSCI 650 - Fall 2024
#An Implementation of a Simple Turing Machine Skeleton
#Author: Carter Tillquist

from collections import Counter
from itertools import product

#Given a transition function delta and a set of accepting states A, determine whether or not w is recognized by the associated Turing machine.
#Recall that we are making several assumptions here including that state A is the start state.
#Return True if w is recognized and False otherwise in addition to the final configuration of the Turing machine tape.
def simulateTM(delta, A, w):
  tape = list(w) if w else ['b']
  head = 0
  state = 'A' # Assumption: A is always the start state

  step = 0
  max_steps = 2000000 # Safety limit for standard tests

  while step < max_steps:
    
    # Track if we expanded the tape specifically in this step
    just_expanded = False 

    if head < 0:
      tape.insert(0, 'b')
      head = 0 
    elif head >= len(tape):
      tape.append('b')
      just_expanded = True # Mark that we added a trailing 'b'
    
    symbol = tape[head]
    
    if (state, symbol) not in delta:
      # FIX: If we appended a 'b' just to read this symbol, 
      # but effectively halted immediately, remove that extra 'b'.
      if just_expanded:
          tape.pop()
      break

    new_state, write_symbol, direction = delta[(state, symbol)]
    tape[head] = write_symbol
    state = new_state
    
    if direction == 'R':
      head += 1
    elif direction == 'L':
      head -= 1
      
    step += 1

  accepted = state in A

  config = "".join(tape)
  # If tape is all blanks, reduce to one blank
  if all(c == 'b' for c in config):
      config = 'b'

  return accepted, config

##########################
### MAIN FOR INGINIOUS ###
##########################
def main(M):
  M = M.strip().split('\n')
  w = M[-1].strip()
  A = M[-2].strip().split(' ')
  delta = {}
  for line in M[1:-2]:
    line = line.strip().split(' ')
    delta[(line[0], line[1])] = line[2:]
  accepted, config = simulateTM(delta, A, w)
  return config+'\n'+str(accepted)

if __name__=='__main__':
  n = input("Enter the number of transitions: ")
  M = n+'\n'
  print("Enter one transition per line with the initial state, symbol being read on the tape, destination state, symbol written to the tape, and tape head direction (L or R) separated by spaces:")
  delta = {}
  for _ in range(int(n)):
    M += input()+'\n'
  M += input("Enter accepting states separated by spaces: ")+'\n'
  M += input("Enter a string to check: ")
  result = main(M)
  print(result)