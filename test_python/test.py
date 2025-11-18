#!/usr/bin/env python3
"""
Test Python file for 4coder
"""

def hello_world():
    """Print hello world"""
    print("Hello from 4coder!")
    
class TestClass:
    def __init__(self, name):
        self.name = name
    
    def greet(self):
        return f"Hello, {self.name}!"

if __name__ == "__main__":
    hello_world()
    test = TestClass("4coder")
    print(test.greet())
