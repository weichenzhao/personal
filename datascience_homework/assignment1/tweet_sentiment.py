import sys
import json
import re

def hw():
    print 'Hello, world!'

def lines(fp):
    print str(len(fp.readlines()))

def main():
    #sent_file = open(sys.argv[1])
    #tweet_file = open(sys.argv[2])
    #hw()
    #lines(sent_file)
    #lines(tweet_file)

    sent_file = open(sys.argv[1])
    tweet_file = open(sys.argv[2])

    scores = {}
    for line in sent_file:
        term, score  = line.split("\t")  # The file is tab-delimited. "\t" means "tab character"
        scores[term] = int(score)

    for line in tweet_file:
        newline = json.loads(line)
        #if(not ("lang" in newline and "text" in newline)): #print language
        #    print "lang/text not in this tweet"
        #    continue
        text = newline["text"]
        score = 0.0
        word_count = 0
        for word in re.split(r"\s|,|\.|\?", text):
            if (word == ''): 
                continue
            word_count += 1
            if(word in scores):
                score = score + scores[word]
        print score/word_count#, word_count

if __name__ == '__main__':
    main()
