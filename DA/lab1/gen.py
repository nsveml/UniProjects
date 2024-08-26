#!/usr/bin/python3
import sys
import random
import string

if (len(sys.argv) == 1):
    size = int(input())
else:
    size = int(sys.argv[1])

for i in range(size):
        letters = string.ascii_uppercase
        dig = string.digits
        a = random.choice(letters)
        b = ''.join(random.choice(dig) for i in range(3))
        c = random.choice(letters)
        d = random.choice(letters)
        e = ''.join(random.choice(letters) for i in range(64))
        print(a+' '+b+' '+c+d+'\n'+e)

print("\n")

