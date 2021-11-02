#!/usr/bin/env python
"""
Created on Fri Apr 23 17:04:58 2021
Plots the boundary layer at different locations

@author: ruloz
"""

description = """ Plot the boundary layer."""
import matplotlib.pyplot as plt
import numpy as np
import os


mainRoute = os.getcwd()+"/postProcessing/singleGraph/" # main route
time = os.listdir(mainRoute) # latestTime
files = os.listdir(mainRoute + str(max(time))) #get file name of latest time

y = []; Ux = []; Uy = []; Uz = []; U = []  #initialize arrays
def loadData():
	for i in files:
		sourceRoute = mainRoute + str(max(time)) +'/' + i #route for each file
		
		#laod data
		ydata, UxData, UyData, UzData = np.loadtxt(sourceRoute,unpack = True)
		
		#store data in arrays
		uData = np.sqrt(UxData**2 + UyData**2 + UzData **2)
		y.append(np.array(ydata))
		Ux.append(np.array(UxData))
		Uy.append(np.array(UyData))
		Uz.append(np.array(UzData))
		U.append(np.array(uData))
	
	return U, y
		
def plotBl():
	U, y = loadData()
	fig, ax = plt.subplots()
	labels = list(map(lambda sub:int(''.join(
		[ele for ele in sub if ele.isnumeric()])), files))
	for i in range(len(U)):
		ax.plot(U[i],y[i],label='x = %s mm' %labels[i])
	# plt.plot(U[0],y[0],label='x = 0 mm')
	# plt.plot(U[1],y[1],label='x = 3 mm')
	# plt.plot(U[2],y[2],label='x = 6 mm') 
	plt.xlabel('u [m/s]')
	plt.ylabel("y [m]")
	plt.legend()
	plt.savefig(str(time[0])+'.png', dpi=90)
	plt.show()
	
plotBl()	
