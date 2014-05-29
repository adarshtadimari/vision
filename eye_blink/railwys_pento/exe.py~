import os

folder = ('1','panto1')
command_file = open('picexe', 'w')
command_file.write("#!/bin/bash\n")
for name in folder:
    os.system("ls " + str(name) + " > " + str(name) +"files.txt")
    with open(str(name) + "files.txt", 'r') as a_file:
        for pic in a_file:
            print(pic) 
            command = "./a.out " + str(name) + "/" + str(pic)
            command_file.write(command)
            #os.system(command)

command_file.close()
