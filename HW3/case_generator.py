import sys, random, os, glob
from optparse import OptionParser


parser = OptionParser()

parser.add_option('-t', '--testcase', action='store', dest='testcase', type='int', default=10, help='the number of testcase')
parser.add_option('-n', '--space', action='store', dest='n', type='int', default=0, help='the number of row')
parser.add_option('-m', '--cells', action='store', dest='m', type='int', default=0, help='the number of column')

(options, args) = parser.parse_args(sys.argv)


for t in range(options.testcase):
    in_file = open("./input" + str(t + 1) + ".txt", mode="w")
    n = options.n
    m = options.m
    if n == 0:
       n  = random.randint(1, 8)
    if m == 0:
       m  = random.randint(1, 8)
    in_file.write(str(n) + " " + str(m) + "\n")
    for i in range(n):
        for j in range(m):
            in_file.write(str(random.randint(0, 1)) + " ")
        in_file.write("\n")




