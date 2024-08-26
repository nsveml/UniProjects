import random
import sys
def randstr(max_length):
	length = random.randint(1, max_length)
	range_begin  = ord('a')
	range_end = ord('z')
	res = ""
	for i in range (0, length):
		res += chr(random.randint(range_begin, range_end))
	return res

max_length = 256
if(len(sys.argv)<3):
	print("Not enough arguments!\nUsage %s [outputfile] [test-count] " % sys.argv[0])
	sys.exit()
count = int(sys.argv[2])
add_samples = round(count*0.4)
find_sammples = round(count*0.2)
file=open(sys.argv[1], "w")
strings = []
for i in range (0,add_samples):
	add = random.randint(0, 1231243421)%2
	value = random.randint(0,18446744073709551615)
	curr_str = randstr(max_length)
	file.write("+ "  + curr_str +" " + str(value) + "\n")
	strings.append(curr_str)

for i in range (0, find_sammples):
	file.write(strings[i] + "\n")

for i in range (0, add_samples):
	file.write("- " + strings[i] + "\n")
file.close()

