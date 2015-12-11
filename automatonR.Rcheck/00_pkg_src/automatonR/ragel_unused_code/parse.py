import ragel_parser
import os
import sys

#input = raw_input("Timed Regular Expression: ")
ragel_parser.write_to_file(sys.argv[1], sys.argv[2])
#os.system("ragel -G2 automaton.rl -o ../src/automaton.cpp")
os.system("ragel -G2 automaton.rl -o ../src/automaton.cpp")
