# CSCI 650 - Fall 2024
# Generate Random Tests for the CYK Algorithm
# Author: Carter Tillquist

#Tests for this problem on INGInious are generated randomly following an approach similar, though not identical,
#to what is included here. Feel free to modify this code to help with testing on your local machine.

#Depending on your system, the following will generate a test, display the input in the terminal, and pass it to CYK.py
#python3 cykTests.py | tee /dev/tty | python3 CYK.py

import numpy as np
import string

def nongeneratingSymbols(G):
  V, T, P, S = G
  invP = {}
  for head,bodies in P.items():
    for body in bodies:
      invP[body] = invP.get(body, set()) | {head}
  generating = {t for t in T}
  work = list(T)
  while len(work) > 0:
    newSyms = {sym for body in invP.get(work[0], []) for sym in body} - generating
    generating |= newSyms
    work = work[1:] + [s for s in newSyms if s in V]
  return V - generating

def unreachableSymbols(G):
  V, T, P, S = G
  reachable = {'S'}
  work = ['S']
  while len(work) > 0:
    newSyms = {sym for body in P[work[0]] for sym in body} - reachable
    reachable |= newSyms
    work = work[1:] + [s for s in newSyms if s in V]
  return (V | T) - reachable

def genWord(P, thresh=100):
  w = 'S'
  loc = 0
  while loc >= 0:
    body = np.random.choice(list(P[w[loc]])) if len(w) < thresh else np.random.choice([t for t in P[w[loc]] if len(t)==1])
    w = w[:loc] + body + w[loc+1:]
    loc = [i for i in range(len(w)) if w[i].isupper()]
    loc = loc[0] if len(loc) > 0 else -1
  return str(w)

if __name__=='__main__':
  opt = np.random.randint(0, 5)

  V, T, P, S, w = set(), set(), {}, 'S', ''
  minV, maxV, minT, maxT, minVBodies, maxVBodies, minTBodies, maxTBodies = 0, 0, 0, 0, 0, 0, 0, 0
  pNoVBodies, pNoTBodies = 0.05, 0.05
  match opt:
    case 0:
      minV = 1
      maxV = 3
      minT = 1
      maxT = 3
      minVBodies = 1
      maxVBodies = 3
      minTBodies = 1
      maxTBodies = 3
    case 1: 
      minV = 3
      maxV = 10
      minT = 1
      maxT = 6
      minVBodies = 1
      maxVBodies = 10
      minTBodies = 1
      maxTBodies = 6
    case 2:
      minV = 3
      maxV = 8
      minT = 3
      maxT = 15
      minVBodies = 1
      maxVBodies = 10
      minTBodies = 1
      maxTBodies = 6
    case 3:
      minV = 5
      maxV = 15
      minT = 2
      maxT = 5
      minVBodies = 5
      maxVBodies = 10
      minTBodies = 1
      maxTBodies = 3
    case 4:
      minV = 1
      maxV = 15
      minT = 1
      maxT = 15
      minVBodies = 1
      maxVBodies = 15
      minTBodies = 1
      maxTBodies = 15

  V = {str(s) for s in np.random.choice(list(string.ascii_uppercase[:18]), size=np.random.randint(minV, maxV+1), replace=False)}
  V |= {'S'}
  T = {str(s) for s in np.random.choice(list(string.ascii_lowercase), size=np.random.randint(minT, maxT+1), replace=False)}
  for v in V:
    P[v] = set()
    if np.random.uniform(0, 1) > pNoVBodies: P[v] |= {''.join(np.random.choice(list(V - {'S'}), size=2, replace=True)) for _ in range(np.random.randint(minVBodies, maxVBodies+1))}
    if np.random.uniform(0, 1) > pNoTBodies: P[v] |= {str(s) for s in np.random.choice(list(T), size=np.random.randint(minTBodies, maxTBodies+1))}

  for v in nongeneratingSymbols((V,T,P,S)):
    P[v] |= {np.random.choice(list(T))}

  for v in unreachableSymbols((V,T,P,S)):
    reachable = V - unreachableSymbols((V,T,P,S))
    if v in T: P[np.random.choice(list(reachable))] |= {v}
    else: P[np.random.choice(list(reachable))] |= {(v+np.random.choice(list(V)))[::np.random.choice([-1,1])]}

  l = np.random.randint(3, 10)
  x = np.random.uniform(0, 1)
  w = genWord(P) if x > 0.3 else ''.join(np.random.choice(list(T), size=l, replace=True))
  print(len(P)) #num lines
  print('S -> '+' | '.join(list(P['S'])))
  for v in P:
    if v != 'S': print(v+' -> '+' | '.join(list(P[v]))) #productions
  print(w) 

