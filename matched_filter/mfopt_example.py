#!/usr/bin/env python
import sys, array, numpy, math, time, cmath

# Four constilations: 45,135,225,315
# Symbol representation: Q1=11, Q2=01, Q3=00, Q4=10
dtor=math.pi/180
Q1=complex(math.cos(45*dtor),math.sin(45*dtor))
Q2=complex(math.cos(135*dtor),math.sin(135*dtor))
Q3=complex(math.cos(225*dtor),math.sin(225*dtor))
Q4=complex(math.cos(315*dtor),math.sin(315*dtor))

# The optimization with a 45 degree rotation
Q1_opt=complex(0,1)
Q2_opt=complex(-1,0)
Q3_opt=complex(0,-1)
Q4_opt=complex(1,0)

# known signal = 11110010
known=[Q1,Q1,Q3,Q4]
known_opt=[Q1_opt,Q1_opt,Q3_opt,Q4_opt]

# unknown signal
unknown=[Q1,Q1,Q3,Q4]   # Perfect Match

# coefficients, reversed complex conjugate
coeffs=[known[3].conjugate(),known[2].conjugate(),known[1].conjugate(),known[0].conjugate()]
coeffs_opt=[known_opt[3].conjugate(),known_opt[2].conjugate(),known_opt[1].conjugate(),known_opt[0].conjugate()]

# Convolve unknown with known
out=0
out_opt=0
len=len(unknown)
for i in range(0,len):
  out+=unknown[len-1-i]*coeffs[i]
  out_opt+=unknown[len-1-i]*coeffs_opt[i]

deg_offset=math.atan(out.imag/out.real)*(180/math.pi)
deg_offset_opt=math.atan(out_opt.imag/out_opt.real)*(180/math.pi)

print "Normal Coefficients:"
print "    Raw: " + str(out)
print "    Magnitude: " + str(math.sqrt(out.real*out.real+out.imag*out.imag))
print "    Offset: " + str(deg_offset)
print ""
print "Optimized Coefficients:"
print "    Raw: " + str(out_opt)
print "    Magnitude: " + str(math.sqrt(out_opt.real*out_opt.real+out_opt.imag*out_opt.imag))
print "    Offset: " + str(deg_offset_opt)
