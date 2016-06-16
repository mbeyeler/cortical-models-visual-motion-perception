import numpy as np
import matplotlib.pyplot as plt
from motionenergy import MotionEnergy

# grayscale stimulus showing sine grating and plaid
file_str = 'inp_grating_plaid_gray_32x32x2400.dat'
num_stims = 2  # number of stimuli (grating, plaid)
num_frames_per_trial = 50  # number of trials per stimulus

file_stream, dim = read_input_header(file_str)
width, height, length = dim

ME = MotionEnergy(width, height, 1)
speed = 1.5  # pixels per frame

for stim in xrange(num_stims):
	for trial in xrange(length/num_frames_per_trial/num_stims):
		for _ in xrange(num_frames_per_trial):
			# read new frame from file
			frame = read_input_frame(file_stream, dim)

			# calculate V1 complex cell responses
			out = ME.calcV1complex(frame, speed)
			out = out.astype(np.float32)

			# plot, ...

file_stream.close()