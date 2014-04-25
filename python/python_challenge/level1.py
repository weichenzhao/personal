def convert(char):
    i = ord(char)
    if ( i > 96 and i < 121):
        return chr(i + 2)
    elif (i > 120 and i < 123):
        return chr(96 + (i + 2)%122)
    else:
        return char

if __name__ == '__main__':
    string = "map"
    original = "g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj."
    temp = map(convert, string)
    result = ''
    for char in temp:
        result += char
    print "http://www.pythonchallenge.com/pc/def/" + result + ".html"
