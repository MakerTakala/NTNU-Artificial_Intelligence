import sys, random, os, glob
from optparse import OptionParser
 
filelist1 = glob.glob(os.path.join("./data/in", "*"))
for f in filelist1:
    os.remove(f)
filelist2 = glob.glob(os.path.join("./data/out", "*"))
for f in filelist2:
    os.remove(f)



parser = OptionParser()

parser.add_option('-t', '--testcase', action='store', dest='testcase', type='int', default=10, help='the number of testcase')
parser.add_option('-s', '--space', action='store', dest='space', type='int', default=0, help='the board size')
parser.add_option('-c', '--cells', action='store', dest='cells', type='int', default=0, help='the number of cells')

(options, args) = parser.parse_args(sys.argv)

if options.space == 0:
    options.space = random.randint(3, 60)
if options.cells == 0:
    options.cells = random.randint(3, options.space)


for i in range(options.testcase):
    in_file = open("./data/in/" + str(i + 1) + ".in", mode="w")

    cells = random.sample([x for x in range(0, options.space, 1)], options.cells)
    data = [0 for x in range(options.space)]
    for j in cells:
        data[j] = 1
    for x in data:
        in_file.write(str(x) + " ")




