import matplotlib.pyplot as plt
import sys
import os
fig = plt.figure()

fp=open('Serial.txt','r')
data=fp.readlines()
x_ax=[]
y_ax=[]

for i in range(8,12):
	lines=data[(i-8)]
	x_ax.append(float(lines))
	y_ax.append(2**i)
plt.plot( y_ax, x_ax, label='Serial')

k = 1
while k < 17:
    if k == 3:
	k = k - 1
    if k == 10 or k == 14:
	k = k + 2
    st="Parallel_Naive_cores_"+str(k)+".txt"
    fp=open(st,'r')
    data=fp.readlines()
    x_axis=[]
    y_axis=[]
    for i in range(8,12):
	lines=data[(i-8)]
	x_axis.append(float(lines))
	y_axis.append(2**i)
    plt.plot(y_axis,x_axis,label='Core'+str(k))
    k = k + 2
plt.legend()
plt.grid()
plt.xlabel('Size')
plt.ylabel('Time')
plt.show()

fp=open('Serial.txt','r')
data=fp.readlines()
x_ax=[]
y_ax=[]

for i in range(8,12):
	lines=data[(i-8)]
	x_ax.append(float(lines))
	y_ax.append(2**i)

k = 1
while k < 17:
    if k == 3:
	k = k - 1
    if k == 10 or k == 14:
	k = k + 2
    st="Parallel_Naive_cores_"+str(k)+".txt"
    print (st)
    fp=open(st,'r')
    data=fp.readlines()
    x_axis=[]
    y_axis=[]
    for i in range(8,12):
	lines=data[(i-8)]
	speedup = (x_ax[(i-8)])/(float(lines))
	x_axis.append(speedup)
	y_axis.append(2**i)
    plt.plot(y_axis,x_axis,label='Core'+str(k))
    k = k + 2
plt.legend()
plt.grid()
plt.xlabel('Size')
plt.ylabel('Speedup')
plt.show()

fp=open('Serial.txt','r')
data=fp.readlines()
x_ax=[]
y_ax=[]

for i in range(8,12):
	lines=data[(i-8)]
	x_ax.append(float(lines))
	y_ax.append(2**i)

k = 1
while k < 17:
    if k == 1:
	k = k + 1
    if k == 10 or k == 14:
	k = k + 2
    st="Parallel_Naive_cores_"+str(k)+".txt"
    print (st)
    fp=open(st,'r')
    data=fp.readlines()
    x_axis=[]
    y_axis=[]
    for i in range(8,12):
	lines=data[(i-8)]
	speedup = (x_ax[(i-8)])/(float(lines))
	karp = (k - speedup)/(speedup * (k - 1))
	x_axis.append(karp)
	y_axis.append(2**i)
    plt.plot(y_axis,x_axis,label='Core'+str(k))
    k = k + 2
plt.legend()
plt.grid()
plt.xlabel('Size')
plt.ylabel('Karp-Flatt')
plt.show()

fp=open('Serial.txt','r')
data=fp.readlines()
x_ax=[]
y_ax=[]

for i in range(8,12):
	lines=data[(i-8)]
	x_ax.append(float(lines))
	y_ax.append(2**i)

k = 1
while k < 17:
    if k == 3:
	k = k - 1
    if k == 10 or k == 14:
	k = k + 2
    st="Parallel_Naive_cores_"+str(k)+".txt"
    print (st)
    fp=open(st,'r')
    data=fp.readlines()
    x_axis=[]
    y_axis=[]
    for i in range(8,12):
	lines=data[(i-8)]
	speedup = (x_ax[(i-8)])/(float(lines))
	x_axis.append((speedup/k))
	y_axis.append(2**i)
    plt.plot(y_axis,x_axis,label='Core'+str(k))
    k = k + 2
plt.legend()
plt.grid()
plt.xlabel('Size')
plt.ylabel('Efficiency')
plt.show()