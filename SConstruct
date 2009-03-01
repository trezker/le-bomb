import glob
import sys
import os

files = glob.glob('src/*.cpp')
files = [x.replace("src", "obj") for x in files]

env = Environment(CPPPATH = ['include'])

debug = ARGUMENTS.get('debug', 0)
if int(debug):
	env.Append(CCFLAGS = '-g')
env.Append(CCFLAGS = '-Wall')

env.BuildDir('obj','src', duplicate = 0)
env.Append(LIBS=['allegro-4.9.9','a5_iio-4.9.9','a5_font-4.9.9','a5_ttf-4.9.9'])
env.Program('a53d',files)
