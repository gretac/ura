from os import system

file_name = raw_input("File name (without .rl): ")
command1 = "ragel -G2 " + file_name + ".rl"
command2 = "g++ " + file_name + ".c" + " -o " + file_name
print command1
print command2

system(command1)
system(command2)
