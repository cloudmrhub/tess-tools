
with open('/data/PROJECTS/TESS/testdata/Told.dat', 'r') as f:
            lines = [line.rstrip('\n') for line in f]
            f.close()

print(lines)

for line in lines:
    coords, value = line.split("  ")
    x,y,z=coords.split(" ")
    print(x)



