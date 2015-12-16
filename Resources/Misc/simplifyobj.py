import sys

f = open(sys.argv[1])
lines = f.readlines()
newlines = []

for i, line in enumerate(lines):
    if line[0] == 'f' and line[1] == ' ':
        elems = line.split()[1:]
        vertices = [nums.split('/')[0] for nums in elems]
        newlines.append("f " + vertices[0] + " " + vertices[1] + " " + vertices[2] + '\n')
    elif line[0] == 'v' and line[1] == ' ':
        newlines.append(line)

print(''.join(newlines))
