#! /usr/bin/python
from TOSSIM import *
import sys

t = Tossim([])
r = t.radio()
f = open("../topo.txt", "r")
f_aes = open("aes.txt", "w")
f_aes_enc = open("aes_enc.txt", "w")
f_aes_dec = open("aes_dec.txt", "w")

lines = f.readlines()
for line in lines:
  s = line.split()
  if (len(s) > 0):
    print " ", s[0], " ", s[1], " ", s[2];
    r.add(int(s[0]), int(s[1]), float(s[2]))

t.addChannel("aes", sys.stdout)
t.addChannel("f_aes_enc", f_aes_enc)
t.addChannel("f_aes_dec", f_aes_dec)
t.addChannel("com", sys.stdout)
t.addChannel("boot", sys.stdout)
t.addChannel("sys", sys.stdout)

noise = open("../meyer-heavy.txt", "r")
lines = noise.readlines()
for line in lines:
  str = line.strip()
  if (str != ""):
    val = int(str)
    for i in range(1, 4):
      t.getNode(i).addNoiseTraceReading(val)

for i in range(1, 4):
  print "Creating noise model for ",i;
  t.getNode(i).createNoiseModel()

t.getNode(1).bootAtTime(100001);
#t.getNode(2).bootAtTime(800008);
#t.getNode(3).bootAtTime(1800009);

for i in range(0, 300):
  t.runNextEvent()
