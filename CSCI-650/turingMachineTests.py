# CSCI 650 - Fall 2024
# Generate Tests for Turing Machines
# Author: Carter Tillquist

#Tests for this problem on INGInious are generated randomly following an approach similar, though not identical,
#to what is included here. Feel free to modify this code to help with testing on your local machine.

#Depending on your system, the following will generate a test, display the input in the terminal, and pass it to turingMachine.py
#python3 turingMachineTests.py | tee /dev/tty | python3 turingMachine.py

import numpy as np

#0^n1^n
def zerosOnes(n):
  A = ['E']
  transitions = '''A 0 B X R
A Y D Y R
A b D b R
B 0 B 0 R
B Y B Y R
B 1 C Y L
C Y C Y L
C 0 C 0 L
C X A X R
D Y D Y R
D b E b R'''
  delta = {(info[0], info[1]): info[2:] for info in [line.split(' ') for line in transitions.split('\n')]}
  w = ''.join(map(str, np.random.randint(2, size=n))) if np.random.ranf() > 0.6 else ('0'*n)+('1'*n)
  return delta, A, w

def palindrome(n):
  A = ['I']
  transitions = '''A 0 B X R
A 1 F X R
A b I b R
A X I X R
B 0 C 0 R
B 1 C 1 R
B b I b R
B X I X R
C 0 C 0 R
C 1 C 1 R
C b D b L
C X D X L
D 0 E X L
E 0 E 0 L
E 1 E 1 L
E X A X R
F 0 G 0 R
F 1 G 1 R
F b I b R
F X I X R
G 0 G 0 R
G 1 G 1 R
G b H b L
G X H X L
H 1 E X L'''
  delta = {(info[0], info[1]): info[2:] for info in [line.split(' ') for line in transitions.split('\n')]}
  s = ''.join(np.random.choice(['0', '1'], size=n, replace=True))
  w = s if np.random.ranf() > 0.6 else s+np.random.choice(['0','1',''])+s[::-1]
  return delta, A, w

def addition():
  A = ['G']
  transitions = '''A 0 A 0 R
A 1 A 1 R
A + B + R
B 0 B 0 R
B 1 B 1 R
B b C b L
C 0 C 1 L
C 1 D 0 L
C + F + R
D 0 D 0 L
D 1 D 1 L
D + E + L
E 0 A 1 R
E 1 E 0 L
E b A 1 R
F 1 F b R
F b G b R'''
  delta = {(info[0], info[1]): info[2:] for info in [line.split(' ') for line in transitions.split('\n')]}
  a = str(bin(np.random.randint(0, 100)))[2:]
  b = str(bin(np.random.randint(0, 100)))[2:]
  w = a+'+'+b
  return delta, A, w

def binToDec():
  A = ['Z']
  transitions = '''B b B b R
C b E b L
D b B b R
E 1 F 0 L
E 0 E 1 L
E b H b R
F b G b L
G 0 D 1 R
G 1 D 2 R
G 2 D 3 R
G 3 D 4 R
G 4 D 5 R
G 5 D 6 R
G 6 D 7 R
G 7 D 8 R
G 8 D 9 R
G 9 G 0 L
G b D 1 R
H b I b L
I b I b L
J b Z b R
B 3 C 3 R
B 9 C 9 R
B 5 C 5 R
B 1 C 1 R
B 4 C 4 R
B 6 C 6 R
B 2 C 2 R
B 8 C 8 R
B 7 C 7 R
B 0 C 0 R
C 3 C 3 R
C 9 C 9 R
C 5 C 5 R
C 1 C 1 R
C 4 C 4 R
C 6 C 6 R
C 2 C 2 R
C 8 C 8 R
C 7 C 7 R
C 0 C 0 R
D 3 D 3 R
D 9 D 9 R
D 5 D 5 R
D 1 D 1 R
D 4 D 4 R
D 6 D 6 R
D 2 D 2 R
D 8 D 8 R
D 7 D 7 R
D 0 D 0 R
F 3 F 3 L
F 9 F 9 L
F 5 F 5 L
F 1 F 1 L
F 4 F 4 L
F 6 F 6 L
F 2 F 2 L
F 8 F 8 L
F 7 F 7 L
F 0 F 0 L
H 3 H b R
H 9 H b R
H 5 H b R
H 1 H b R
H 4 H b R
H 6 H b R
H 2 H b R
H 8 H b R
H 7 H b R
H 0 H b R
I 3 J 3 L
I 9 J 9 L
I 5 J 5 L
I 1 J 1 L
I 4 J 4 L
I 6 J 6 L
I 2 J 2 L
I 8 J 8 L
I 7 J 7 L
I 0 J 0 L
J 3 J 3 L
J 9 J 9 L
J 5 J 5 L
J 1 J 1 L
J 4 J 4 L
J 6 J 6 L
J 2 J 2 L
J 8 J 8 L
J 7 J 7 L
J 0 J 0 L
A 3 L 3 R
A 9 M 9 R
A 5 N 5 R
A 1 O 1 R
A 4 P 4 R
A 6 Q 6 R
A 2 R 2 R
A 8 S 8 R
A 7 T 7 R
A 0 U 0 R
L 3 B 3 L
L 9 B 9 L
L 5 B 5 L
L 1 B 1 L
L 4 B 4 L
L 6 B 6 L
L 2 B 2 L
L 8 B 8 L
L 7 B 7 L
L 0 B 0 L
M 3 B 3 L
M 9 B 9 L
M 5 B 5 L
M 1 B 1 L
M 4 B 4 L
M 6 B 6 L
M 2 B 2 L
M 8 B 8 L
M 7 B 7 L
M 0 B 0 L
N 3 B 3 L
N 9 B 9 L
N 5 B 5 L
N 1 B 1 L
N 4 B 4 L
N 6 B 6 L
N 2 B 2 L
N 8 B 8 L
N 7 B 7 L
N 0 B 0 L
O 3 B 3 L
O 9 B 9 L
O 5 B 5 L
O 1 B 1 L
O 4 B 4 L
O 6 B 6 L
O 2 B 2 L
O 8 B 8 L
O 7 B 7 L
O 0 B 0 L
O b Z b R
P 3 B 3 L
P 9 B 9 L
P 5 B 5 L
P 1 B 1 L
P 4 B 4 L
P 6 B 6 L
P 2 B 2 L
P 8 B 8 L
P 7 B 7 L
P 0 B 0 L
Q 3 B 3 L
Q 9 B 9 L
Q 5 B 5 L
Q 1 B 1 L
Q 4 B 4 L
Q 6 B 6 L
Q 2 B 2 L
Q 8 B 8 L
Q 7 B 7 L
Q 0 B 0 L
R 3 B 3 L
R 9 B 9 L
R 5 B 5 L
R 1 B 1 L
R 4 B 4 L
R 6 B 6 L
R 2 B 2 L
R 8 B 8 L
R 7 B 7 L
R 0 B 0 L
S 3 B 3 L
S 9 B 9 L
S 5 B 5 L
S 1 B 1 L
S 4 B 4 L
S 6 B 6 L
S 2 B 2 L
S 8 B 8 L
S 7 B 7 L
S 0 B 0 L
T 3 B 3 L
T 9 B 9 L
T 5 B 5 L
T 1 B 1 L
T 4 B 4 L
T 6 B 6 L
T 2 B 2 L
T 8 B 8 L
T 7 B 7 L
T 0 B 0 L
U 3 B 3 L
U 9 B 9 L
U 5 B 5 L
U 1 B 1 L
U 4 B 4 L
U 6 B 6 L
U 2 B 2 L
U 8 B 8 L
U 7 B 7 L
U 0 B 0 L
U b Z b R'''
  delta = {(info[0], info[1]): info[2:] for info in [line.split(' ') for line in transitions.split('\n')]}
  w = str(bin(np.random.randint(0, 10000)))[2:]
  return delta, A, w

def randExpression(literals=['0','1'], ops1=['~'], ops2=['|','&'], d=0):
  probs = [0.2+d*0.1, 0.3, 0.5]
  probs = [x/sum(probs) for x in probs]
  p = np.random.choice(['l','o','t'], p=probs)
  if p=='l': return str(np.random.choice(literals))
  elif p=='o': return randExpression(d=d+1)+'~'
  else: return randExpression(d=d+1)+randExpression(d=d+1)+np.random.choice(ops2)

def revPolishBool():
  A = ['halt']
  transitions = '''A b A b R
B x B x R
B 0 D x L
B 1 G x L
B & J x L
B | P x L
B ~ V x L
B b C b L
C x C b L
C b halt b L
D x D x L
D b E b L
E b F 0 R
F b A b R
G x G x L
G b H b L
H b I 1 R
I b A b R
J x J x L
J b K b L
K b L b R
L 0 M b R
L 1 N b R
M 0 O 0 R
M 1 O 0 R
N 0 O 0 R
N 1 O 1 R
O b A b R
P x P x L
P b Q b L
Q b R b R
R 0 S b R
R 1 T b R
S 0 U 0 R
S 1 U 1 R
T 0 U 1 R
T 1 U 1 R
U b A b R
V x V x L
V b W b L
W b X b R
X 0 Y 1 R
X 1 Y 0 R
Y b A b R
E 1 E 1 L
E ! E ! L
E ~ E ~ L
E x E x L
E | E | L
E & E & L
E 0 E 0 L
F 1 F 1 R
F ! F ! R
F ~ F ~ R
F x F x R
F | F | R
F & F & R
F 0 F 0 R
H 1 H 1 L
H ! H ! L
H ~ H ~ L
H x H x L
H | H | L
H & H & L
H 0 H 0 L
I 1 I 1 R
I ! I ! R
I ~ I ~ R
I x I x R
I | I | R
I & I & R
I 0 I 0 R
K 1 K 1 L
K ! K ! L
K ~ K ~ L
K x K x L
K | K | L
K & K & L
K 0 K 0 L
L b q0q ! R
O 1 O 1 R
O ! O ! R
O ~ O ~ R
O x O x R
O | O | R
O & O & R
O 0 O 0 R
Q 1 Q 1 L
Q ! Q ! L
Q ~ Q ~ L
Q x Q x L
Q | Q | L
Q & Q & L
Q 0 Q 0 L
R b q1q ! R
S b q2q ! R
T b q3q ! R
U 1 U 1 R
U ! U ! R
U ~ U ~ R
U x U x R
U | U | R
U & U & R
U 0 U 0 R
W 1 W 1 L
W ! W ! L
W ~ W ~ L
W x W x L
W | W | L
W & W & L
W 0 W 0 L
X b q4q ! R
Y 1 Y 1 R
Y ! Y ! R
Y ~ Y ~ R
Y x Y x R
Y | Y | R
Y & Y & R
Y 0 Y 0 R
A 1 q5q 1 R
A ! q6q ! R
A ~ q7q ~ R
A x q8q x R
A | q9q | R
A & q10q & R
A 0 q11q 0 R
q0q 1 halt 1 L
q0q ! halt ! L
q0q ~ halt ~ L
q0q x halt x L
q0q | halt | L
q0q & halt & L
q0q 0 halt 0 L
N ! q12q ! R
N ~ q13q ! R
N x q14q ! R
N | q15q ! R
N & q16q ! R
q1q 1 halt 1 L
q1q ! halt ! L
q1q ~ halt ~ L
q1q x halt x L
q1q | halt | L
q1q & halt & L
q1q 0 halt 0 L
q2q 1 halt 1 L
q2q ! halt ! L
q2q ~ halt ~ L
q2q x halt x L
q2q | halt | L
q2q & halt & L
q2q 0 halt 0 L
q3q 1 halt 1 L
q3q ! halt ! L
q3q ~ halt ~ L
q3q x halt x L
q3q | halt | L
q3q & halt & L
q3q 0 halt 0 L
q4q 1 halt 1 L
q4q ! halt ! L
q4q ~ halt ~ L
q4q x halt x L
q4q | halt | L
q4q & halt & L
q4q 0 halt 0 L
q5q 1 B 1 L
q5q ! B ! L
q5q ~ B ~ L
q5q x B x L
q5q | B | L
q5q & B & L
q5q 0 B 0 L
q5q b halt b L
q6q 1 B 1 L
q6q ! B ! L
q6q ~ B ~ L
q6q x B x L
q6q | B | L
q6q & B & L
q6q 0 B 0 L
q7q 1 B 1 L
q7q ! B ! L
q7q ~ B ~ L
q7q x B x L
q7q | B | L
q7q & B & L
q7q 0 B 0 L
q8q 1 B 1 L
q8q ! B ! L
q8q ~ B ~ L
q8q x B x L
q8q | B | L
q8q & B & L
q8q 0 B 0 L
q9q 1 B 1 L
q9q ! B ! L
q9q ~ B ~ L
q9q x B x L
q9q | B | L
q9q & B & L
q9q 0 B 0 L
q10q 1 B 1 L
q10q ! B ! L
q10q ~ B ~ L
q10q x B x L
q10q | B | L
q10q & B & L
q10q 0 B 0 L
q11q 1 B 1 L
q11q ! B ! L
q11q ~ B ~ L
q11q x B x L
q11q | B | L
q11q & B & L
q11q 0 B 0 L
q11q b halt b L
q12q 1 halt 1 L
q12q ! halt ! L
q12q ~ halt ~ L
q12q x halt x L
q12q | halt | L
q12q & halt & L
q12q 0 halt 0 L
q13q 1 halt 1 L
q13q ! halt ! L
q13q ~ halt ~ L
q13q x halt x L
q13q | halt | L
q13q & halt & L
q13q 0 halt 0 L
q14q 1 halt 1 L
q14q ! halt ! L
q14q ~ halt ~ L
q14q x halt x L
q14q | halt | L
q14q & halt & L
q14q 0 halt 0 L
q15q 1 halt 1 L
q15q ! halt ! L
q15q ~ halt ~ L
q15q x halt x L
q15q | halt | L
q15q & halt & L
q15q 0 halt 0 L
q16q 1 halt 1 L
q16q ! halt ! L
q16q ~ halt ~ L
q16q x halt x L
q16q | halt | L
q16q & halt & L
q16q 0 halt 0 L'''
  delta = {(info[0], info[1]): info[2:] for info in [line.split(' ') for line in transitions.split('\n')]}
  w = randExpression()
  return delta, A, w

if __name__=='__main__':
  opt = np.random.randint(0, 5)

  delta, A, w = {}, [], ''
  if opt==0:
    delta, A, w = zerosOnes(np.random.randint(2, 15))
  elif opt==1:
    delta, A, w = palindrome(np.random.randint(4, 31))
  elif opt==2:
    delta, A, w = addition()
  elif opt==3:
    delta, A, w = binToDec()
  elif opt==4:
    delta, A, w = revPolishBool()

  print(len(delta))
  for k in delta: print(' '.join(map(str, k))+' '+' '.join(map(str, delta[k])))
  print(' '.join(A))
  print(w)

