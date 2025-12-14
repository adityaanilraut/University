import pandas as pd
from itertools import product

def analyze_bb2():
    # Options for a transition: (NewState, Write, Move)
    # States: A, B. Symbols: 0, 1. Moves: L, R.
    moves = list(product(['A', 'B'], ['0', '1'], ['L', 'R']))
    # Add 'None' to represent HALT (undefined transition)
    options = moves + [None]
    
    # Inputs: (A,0), (A,1), (B,0), (B,1)
    inputs = [('A','0'), ('A','1'), ('B','0'), ('B','1')]
    
    # Storage for step counts
    results = []

    # Iterate over all 6561 combinations
    for p in product(options, repeat=4):
        delta = {}
        for i, transition in enumerate(p):
            if transition is not None:
                delta[inputs[i]] = transition
        
        # Simulate Machine
        tape = ['0'] # Initially 0s
        head = 0
        state = 'A'
        step = 0
        
        while step < 100:
            if head < 0:
                tape.insert(0, '0')
                head = 0
            elif head >= len(tape):
                tape.append('0')
            
            sym = tape[head]
            if (state, sym) not in delta:
                break # Halt
            
            new_state, write_sym, direction = delta[(state, sym)]
            tape[head] = write_sym
            state = new_state
            head += 1 if direction == 'R' else -1
            step += 1
        
        results.append(step)

    # Generate Table Data
    # We want counts for steps 0, 1, 2, 3, 4, 5, 6, and 100+
    counts = {k: 0 for k in [0, 1, 2, 3, 4, 5, 6, 100]}
    total_machines = len(results)
    
    for r in results:
        if r in counts:
            counts[r] += 1
        elif r >= 100:
            counts[100] += 1
            
    # Print Table
    print(f"{'Steps':<10} || {' | '.join([f'{k:<4}' for k in counts.keys()])}")
    print("-" * 60)
    print(f"{'Number':<10} || {' | '.join([f'{counts[k]:<4}' for k in counts.keys()])}")
    print(f"{'Fraction':<10} || {' | '.join([f'{counts[k]/total_machines:<8.6f}' for k in counts.keys()])}")

if __name__ == "__main__":
    analyze_bb2()