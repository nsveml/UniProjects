import random
import sys
from typing import Pattern
def randpat(max_length):
	length = random.randint(1, max_length)
	range_begin  = 0
	range_end = 2**32 - 1
	res = ""
	for i in range (0, length):
		res += str(random.randint(range_begin, range_end)) + ' '
	return res

max_string_length = 1000
max_pattern_length = 100
strings_quantity = int(sys.argv[1])
patterns_quantity = int(sys.argv[2])
occurrence_rate = 0.03
patterns = []
for i in range (0, patterns_quantity):
	pat = randpat(max_pattern_length)
	print(pat)
	patterns.append(pat)
print('')
for i in range(0, strings_quantity):
	existing_pattern = random.randint(0, 100)
	if (existing_pattern < 100 * occurrence_rate):
		print(patterns[random.randint(0, len(patterns)- 1)])
	else:
		print(randpat(max_pattern_length))
