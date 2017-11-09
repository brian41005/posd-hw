import re
s = '''
happy(yo3landa).
listens2Music(mia). 
   listens2Music(yolanda):-  happy(yolanda). 
   playsAirGuitar(mia):-  listens2Music(0.5). 
   playsAirGuitar(yolanda):-  listens2Music(1234).
   X =/= 1.2.
'''
pattern = re.compile(
    '([+-]?\d+(?:\.\d+)?|[a-zA-Z_][a-zA-Z_0-9]*|\(|\)|\.|\=\/=|\==|\:-|\=)')
for c in pattern.findall(s):
    print("%s" % (c), end=' ')
