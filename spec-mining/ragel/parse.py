import ragel_parser
import os

input = raw_input("Timed Regular Expression: ")
ragel_parser.write_to_file(input)
os.system("ragel -G2 automaton.rl -o ../src/automaton.cpp")
