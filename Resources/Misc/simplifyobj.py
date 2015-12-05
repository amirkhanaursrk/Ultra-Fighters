import sys

f = open(sys.argv[1])
lines = f.readlines()

for i, line in enumerate(lines):
    if line[0] == 'f' and line[1] == ' ':
        elems = line.split()[1:]
        vertices = [nums.split('/')[0] for nums in elems]
        lines[i] = "f " + vertices[0] + " " + vertices[1] + " " + vertices[2] + '\n'

print(''.join(lines))
