import os, time

input = "test/open_{}.txt"
check_output = "test/open_{}.output.txt"
output = "output.txt"


command = "./main < " + input + " > " + output
diff = "diff " + check_output + " " + output
for i in range(1,112):
    os.system(command.format(i,i))
    os.system(diff.format(i))
    print(i)