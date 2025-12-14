#!/usr/bin/env python3
"""
Comprehensive test suite for turingMachine.py
Tests all machine types based on the failure examples
"""

import turingMachine
import turingMachineTests
import numpy as np

def test_zerosOnes():
    """Test zerosOnes machine"""
    print("=" * 60)
    print("Testing zerosOnes")
    print("=" * 60)
    
    for n in [3, 5, 7]:
        delta, A, w = turingMachineTests.zerosOnes(n)
        # Force valid input
        w = '0'*n + '1'*n
        
        accepted, config = turingMachine.simulateTM(delta, A, w)
        print(f"Input: {w} (n={n})")
        print(f"Accepted: {accepted}")
        print(f"Config: '{config}'")
        print(f"Ends with 'b': {config.endswith('b')}")
        assert accepted, f"Valid zerosOnes input should be accepted"
        assert config.endswith('b'), f"Config should end with 'b', got: '{config}'"
        print("✓ PASSED\n")

def test_palindrome():
    """Test palindrome machine"""
    print("=" * 60)
    print("Testing Palindrome")
    print("=" * 60)
    
    # Test valid palindrome
    delta, A, w = turingMachineTests.palindrome(5)
    w = '010'
    accepted, config = turingMachine.simulateTM(delta, A, w)
    print(f"Input: {w} (valid palindrome)")
    print(f"Accepted: {accepted}")
    print(f"Config: '{config}'")
    print(f"Ends with 'b': {config.endswith('b')}")
    assert config.endswith('b'), f"Config should end with 'b', got: '{config}'"
    print("✓ PASSED\n")
    
    # Test invalid palindrome
    w = '0110'
    accepted, config = turingMachine.simulateTM(delta, A, w)
    print(f"Input: {w} (invalid palindrome)")
    print(f"Accepted: {accepted}")
    print(f"Config: '{config}'")
    print(f"Ends with 'b': {config.endswith('b')}")
    assert config.endswith('b'), f"Config should end with 'b', got: '{config}'"
    print("✓ PASSED\n")

def test_addition():
    """Test addition machine"""
    print("=" * 60)
    print("Testing Addition")
    print("=" * 60)
    
    for _ in range(3):
        delta, A, w = turingMachineTests.addition()
        accepted, config = turingMachine.simulateTM(delta, A, w)
        print(f"Input: {w}")
        print(f"Accepted: {accepted}")
        print(f"Config: '{config}'")
        print(f"Ends with 'b': {config.endswith('b')}")
        assert accepted, f"Addition should be accepted"
        assert config.endswith('b'), f"Config should end with 'b', got: '{config}'"
        print("✓ PASSED\n")

def test_binToDec():
    """Test binary to decimal machine"""
    print("=" * 60)
    print("Testing Binary to Decimal")
    print("=" * 60)
    
    for _ in range(3):
        delta, A, w = turingMachineTests.binToDec()
        accepted, config = turingMachine.simulateTM(delta, A, w)
        print(f"Input: {w} (binary)")
        print(f"Accepted: {accepted}")
        print(f"Config: '{config}'")
        print(f"Ends with 'b': {config.endswith('b')}")
        assert accepted, f"Binary to decimal should be accepted"
        assert config.endswith('b'), f"Config should end with 'b', got: '{config}'"
        # Check format: should start with 'b' and have decimal digits
        assert config.startswith('b'), f"Config should start with 'b', got: '{config}'"
        print("✓ PASSED\n")

def test_revPolishBool():
    """Test reverse Polish boolean notation machine"""
    print("=" * 60)
    print("Testing Boolean Reverse Polish Notation")
    print("=" * 60)
    
    for _ in range(5):
        delta, A, w = turingMachineTests.revPolishBool()
        accepted, config = turingMachine.simulateTM(delta, A, w)
        print(f"Input: {w}")
        print(f"Accepted: {accepted}")
        print(f"Config: '{config}'")
        print(f"Ends with 'b': {config.endswith('b')}")
        assert accepted, f"Reverse Polish boolean should be accepted"
        assert config.endswith('b'), f"Config should end with 'b', got: '{config}'"
        print("✓ PASSED\n")

def test_edge_cases():
    """Test edge cases"""
    print("=" * 60)
    print("Testing Edge Cases")
    print("=" * 60)
    
    # Test empty string
    delta, A, w = turingMachineTests.zerosOnes(0)
    w = ''
    accepted, config = turingMachine.simulateTM(delta, A, w)
    print(f"Input: '' (empty)")
    print(f"Accepted: {accepted}")
    print(f"Config: '{config}'")
    assert config == 'b' or config.endswith('b'), f"Empty input should result in 'b' or end with 'b', got: '{config}'"
    print("✓ PASSED\n")
    
    # Test single character result
    delta, A, w = turingMachineTests.revPolishBool()
    # Force a simple expression that results in single char
    w = '0'
    accepted, config = turingMachine.simulateTM(delta, A, w)
    print(f"Input: '0' (single char)")
    print(f"Accepted: {accepted}")
    print(f"Config: '{config}'")
    assert config.endswith('b'), f"Config should end with 'b', got: '{config}'"
    print("✓ PASSED\n")

def run_all_tests():
    """Run all test cases"""
    print("\n" + "=" * 60)
    print("COMPREHENSIVE TURING MACHINE TEST SUITE")
    print("=" * 60 + "\n")
    
    try:
        test_zerosOnes()
        test_palindrome()
        test_addition()
        test_binToDec()
        test_revPolishBool()
        test_edge_cases()
        
        print("=" * 60)
        print("ALL TESTS PASSED! ✓")
        print("=" * 60)
        return True
    except AssertionError as e:
        print("=" * 60)
        print(f"TEST FAILED: {e}")
        print("=" * 60)
        return False
    except Exception as e:
        print("=" * 60)
        print(f"ERROR: {e}")
        import traceback
        traceback.print_exc()
        print("=" * 60)
        return False

if __name__ == '__main__':
    success = run_all_tests()
    exit(0 if success else 1)

