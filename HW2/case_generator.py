import sys, random, os, glob
 
filelist = glob.glob(os.path.join("./in", "*"))
for f in filelist:
    os.remove(f)

for i in range(int(sys.argv[1])):
    in_file = open("./in/" + str(i + 1) + ".in", mode="w")

    for j in range(random.randint(3, 100)):
        d = random.randint(0, 1)
        in_file.write(str(d) + " ")






