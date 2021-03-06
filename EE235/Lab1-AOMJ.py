# import cell
%matplotlib notebook
import numpy as np
import simpleaudio as sa
from scipy.io import wavfile as wav
import matplotlib
import matplotlib.pyplot as plt
#Summary
#In this lab, we learned how to create and edit arrays in Python to simulate signal and time vectors. We then experimented with editing and operating on the arrays, and read, wrote, and eventually played the audio they represented. From there we learned how to graph functions and the audio files in python.
#Assignment 1 -- Creating and Manipulating Arrays

# Part A
y1 = np.array([4,6,2])

# Part B
ca = y1[1]
cb = np.array([y1[1],y1[2]])
d = len(y1)
print('ca =',ca)
print('cb =',cb)
print('d =',d)

# Part C
x1 = 2*np.ones([5])
x2 = np.arange(-2,3,1)
print('x1 =',x1)
print('x2 =',x2)

# Part D
arrp = x1 + x2
arrc = np.concatenate((x1,x2))
print('arrp =', arrp)
print('arrc =', arrc)
ca = 6
cb = [6 2]
d = 3
x1 = [2. 2. 2. 2. 2.]
x2 = [-2 -1  0  1  2]
arrp = [0. 1. 2. 3. 4.]
arrc = [ 2.  2.  2.  2.  2. -2. -1.  0.  1.  2.]

#Discussion
#Adding two vectors results in each of their components of the same index being added together, while concatenation simply apends one vector two the end of another, effectively increasing the length to the sum of their lengths.

#When adding two vectors, they must have the same length, and there is no limit for the concatenate function (as long as they're both vectors).

# Assignment 2 - Amplitude Operations on Signals

# Part A
fs = 2
t = np.arange(0,3 + (1/fs), 1/fs)
x = .5*t
y = t**2
print('x =',x)
print('y =',y)

# Part B
z = x - 2*y
print('z =',z)

# Part C
n0 = int(2*fs)
w1 = z[n0]
print('w1 =',w1)

# Part D
n1 = int(0*fs)
n2 = int(1.5*fs)+1
w2 = z[n1:n2]
print('w2 =',w2)
x = [0.   0.25 0.5  0.75 1.   1.25 1.5 ]
y = [0.   0.25 1.   2.25 4.   6.25 9.  ]
z = [  0.    -0.25  -1.5   -3.75  -7.   -11.25 -16.5 ]
w1 = -7.0
w2 = [ 0.   -0.25 -1.5  -3.75]
Discussion
If we reduced the sampling frequency from 2 to 1, we would have half as many values to work with, because the sampling period would double. However, parts C and D would still hold because we found the time by using the sampling frequency (although we couldn't find t = 1.5 anymore because t would only consist of integers).

Assignment 3 -- Working with Sound Files
# Assignment 3 - Working with Sound Files

# Part A
y1 = sa.WaveObject.from_wave_file('train32.wav')
fs1, data1 = wav.read('train32.wav')
y2 = sa.WaveObject.from_wave_file('tuba11.wav')
fs2, data2 = wav.read('tuba11.wav')
print('y1 has',y1.num_channels,'channel(s)')
print('y2 has',y2.num_channels,'channel(s)')

# Part B
play_y1 = y1.play()
play_y1.wait_done()
play_y2 = y2.play()
play_y2.wait_done()
play_y1 = sa.play_buffer(data1,y1.num_channels,2,fs2)
play_y1.wait_done()
play_y2 = sa.play_buffer(data2,y2.num_channels,2,fs1)
play_y2.wait_done()

# Part C
len1 = len(data1)
len2 = len(data2)
print("y1's length is",len1)
print("y2's length is",len2)
y3 = data2[0:len1,0]
y4 = (y3 + data1).astype("int16")
wav.write("y4.wav",fs1,y4.astype("int16"))
play_obj = sa.play_buffer(y4,1,2,fs1)
play_obj.wait_done()

# Part D
pause = np.zeros(int(4*fs1))
y5 = np.concatenate([data1,pause,data2[:,0]]).astype("int16")
wav.write("y5.wav",fs1,y5.astype("int16"))
play_obj = sa.play_buffer(y5,1,2,fs1)
play_obj.wait_done()
y1 has 1 channel(s)
y2 has 2 channel(s)
y1's length is 50313
y2's length is 109708
#Discussion
#When the incorrect sampling frequency is used, the audio changes pitch and speed. For example, when tuba11.wav is called with fs1, it plays faster than it usually does and in a higher pitch.

#Train32.wav only has one channel while Tuba11.wav has two, so we had to only use one channel for tuba.wav, which means we threw away some of the audio data to combine them.

# Assignment 4 - Plotting Comparisons

# Part A
fs = 5
t = np.arange(-2,4 + 1/fs,1/fs)
w = abs(t)
x = 2 - t
y = (t**2) / -2

# Part B
fig1 = plt.figure(1)
plt.plot(t,w, label='w(t)')
plt.plot(t,x, label='x(t)')
plt.plot(t,y, label='y(t)')
plt.xlabel('t (sec)')
plt.grid()
plt.suptitle("w(t), x(t), and y(t)")
plt.legend()
plt.show()

#Discussion
#In order to change the lines for a colorblind person to be able to distinguish them, we would write the code:

plt.plot(t,w, label='w(t)', linestyle=':')

plt.plot(t,x, label='x(t)', linestyle='-')

plt.plot(t,y, label='y(t)')

#With this code, w would be a dotted line, x would be a dashed line, and y would be solid.

# Assignment 5 -- Plotting Sound Files using Subplots

# Part A
fs1, y1 = wav.read('train32.wav')
fs2, y2 = wav.read('tuba11.wav')
t1 = np.arange(0,len(y1),1) / fs1 * 1000
t2 = np.arange(0,len(y2),1) / fs2 * 1000

# Part B
fig2=plt.figure(2)
fig2.subplots_adjust(hspace=0.5,wspace=0.5)

plt.subplot(1,2,1)
plt.plot(t1,data1)
plt.title('y1')
plt.ylabel('Amplitude')
plt.xlabel('Time (ms)')
plt.ylim(-35000,35000)

plt.subplot(1,2,2)
plt.plot(t2,data2)
plt.title('y2')
plt.ylabel('Amplitude')
plt.xlabel('Time (ms)')
plt.xlim(0,10000)
plt.ylim(-35000,35000)

(-35000.0, 35000.0)
#Discussion
#The difference in sampling rates between the two graphs is completely indistinguishable here. This is because the sampling rate effectively deterimines how far apart each data point is, but both sampling rates are high enough that the distance between each point is too small to determine without looking at a much smaller time scale. As is, they look almost continuous because the samples are taken so close together for both plots.
