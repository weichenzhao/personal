import struct
import socket

#PART1: pre-processing
#load ip to location map into memory
lines = [line.replace('\"', '').replace('\r\n', '').split(',') for line in open('ip-to-country.csv')]

#convert string to int-form ip address
for elem in lines:
    elem[0] = int(elem[0])
    elem[1] = int(elem[1])
    elem.insert(2, 0)
length = len(lines) - 1

def ip2int(addr):
    return struct.unpack("!I", socket.inet_aton(addr))[0]

def bsearch(num):
    bound = [0, len(lines)-1]
    while(bound[1]-bound[0]>1):
        pos = (bound[0] + bound[1])>>1
        if num<lines[pos][0]: #left
            bound[1] = pos # upper bound
        elif num>lines[pos][1]: #right
            bound[0] = pos # lower bound
        else: # in pos
            lines[pos][2] += 1
            return pos
    if num>=lines[bound[0]][0] and num<=lines[bound[0]][1]:
        lines[bound[0]][2] += 1
        return bound[0]
    elif num>=lines[bound[1]][0] and num<=lines[bound[1]][1]:
        lines[bound[1]][2] += 1
        return bound[1]
    return None

#for i in range(100):
    #print lines[i][1]-lines[i][0], len(lines[i]), lines[i]

result = open('./data/combined/ip.txt', 'w')
overall = open('./data/combined/ip_country.txt', 'w')

file = open('./data/combined/3.txt', 'r')
file.readline()
for ips in file:
    if not '.' in ips: #possible: ipv6, unknown
        #print 'ipv6 address'
        continue
    #print ips, ip2int(ips)
    bsearch(ip2int(ips))

countries = {}
for elem in lines: 
    if elem[2] != 0:
        if elem[-1][0] == ' ':
            elem[-1] = elem[-1][1:]
        if elem[-1] in countries:
            countries[elem[-1]] += elem[2]
        else:
            countries[elem[-1]] = elem[2]
        result.write(str(elem[2:]) + '\n')

for country in countries.keys():
    overall.write(country + '		' + str(countries[country]) + '\n')
