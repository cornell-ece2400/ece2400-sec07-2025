#=========================================================================
# selection-sort-int-ploy.py
#=========================================================================
# Simple python script for plotting measured execution time and doing a
# polynomial fit using matplotlib and numpy.
#
# Author : Christopher Batten
# Date   : October 14, 2021

# Set the backend to PDF to avoid using the GUI

import matplotlib
matplotlib.use('PDF')

# Import matplotlib for plotting and numpy for data analysis

import matplotlib.pyplot as plt
import numpy as np

# Arrays to store the size of the input array and corresponding measured
# execution time for each experiment

n = [  1000,  2000,  4000,  6000,  8000, 10000, 12000 ]
t = [     0,     0,     0,     0,     0,     0,     0 ]

# Use polyfit to find a best fit 0th, 1st, 2nd order polynomial equations

p0 = np.polyfit( n, t, 0 )
p1 = np.polyfit( n, t, 1 )
p2 = np.polyfit( n, t, 2 )

print "T(N) = {:.2e}".format( p0[0] )
print "T(N) = {:.2e}N + {:.2e}".format( p1[0], p1[1] )
print "T(N) = {:.2e}N^2 + {:.2e}N + {:.2e}".format( p2[0], p2[1], p2[2] )

# Create the figure and axis for our plot

fig, ax = plt.subplots()

# Use a scatter plot for the measured experimental results

ax.scatter( n, t )

# Plot the three best fit polynomial equations

trend0 = np.poly1d(p0)
ax.plot( n, trend0(n), '--' )

trend1 = np.poly1d(p1)
ax.plot( n, trend1(n), '--' )

trend2 = np.poly1d(p2)
ax.plot( n, trend2(n), '--' )

# Add some labels, grid, an save to a PDF

ax.set( xlabel="Input Array Size", ylabel="Measured Execution Time (s)" )
ax.grid()
fig.savefig( "selection-sort-int-plot.pdf", bbox_inches='tight' )

