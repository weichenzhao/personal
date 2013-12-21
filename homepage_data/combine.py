import os
import glob
import pprint

#get folders to process
folders = []
id = []

for filename in glob.glob(r'./data/*ess]'):
    folders.append(filename)

pprint.PrettyPrinter(indent = 4).pprint(folders)

#create recving files
recv = []
for i in range(20):
    recv.append(open('./data/combined/' + str(i) + '.txt', 'w'))

#in each folder
for folder in folders:
    files = []
    for filename in os.listdir(folder):
        files.append(filename)

    file_handles = []
    for file in files:
        file_handles.append(open(folder + '/' + file, 'r'))
        #print folder + '/' + file

    #loop to combine
    for ids in file_handles[0]:
        if not ids in id:
            id.append(ids)
            recv[0].write(ids)
            for j in range(19)[1:]:
                recv[j].write(file_handles[j].readline())
        else:
            for j in range(19)[1:]:
                file_handles[j].readline()
           
#for handles in file_handles:
    #print "a line:"
    #print handles.readline() + handles.readline() + handles.readline()
    #pprint.PrettyPrinter(indent = 4).pprint(files)
