import random

def randpat(max_length):
	range_begin  = 0
	range_end = 2**32 - 1
	res = ""
	for i in range (0, max_length):
		res += str(random.randint(range_begin, range_end)) + ' '
	return res

max_string_length = 1000000
max_pattern_length = 1000
occurrence_rate = 0.1

pat = randpat(max_pattern_length)
print(pat)
print('')
while max_string_length > 0:
    existing_pattern = random.randint(0, 100);
    if (existing_pattern < 100 * occurrence_rate):
        print(pat + '')
    else:
        print(randpat(max_pattern_length) + ' ')
    max_string_length -= 1000;
