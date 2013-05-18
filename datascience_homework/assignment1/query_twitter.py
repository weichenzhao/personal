import urllib
import json

response = urllib.urlopen("http://search.twitter.com/search.json?q=microsoft")
result = json.load(response)
#print result.keys()
repet = len(result["results"])
for i in range(repet):
    print "the", i+1, "th result:", result["results"][i]["text"]
    print "\n"
