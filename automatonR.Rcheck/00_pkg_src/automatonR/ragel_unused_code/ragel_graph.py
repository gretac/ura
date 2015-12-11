from os import system

#file_name = raw_input("File name (without .rl): ")
file_name = "automaton"
command1 = "ragel -V " + file_name + ".rl -o " + file_name + ".dot"
command2 = "dot -Tpng " + file_name + ".dot -o " + file_name + ".png"
command3 = "open " + file_name + ".png"
print command1
print command2

system(command1)
system(command2)
system(command3)
