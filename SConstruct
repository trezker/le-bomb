import glob
import sys
import os


env = Environment(CPPPATH = ['include'])

debug = ARGUMENTS.get('debug', 0)
if int(debug):
	env.Append(CCFLAGS = '-g')
	env.Append(LIBS=['allegro-debug-4.9.9','a5_iio-debug-4.9.9','a5_font-debug-4.9.9','a5_ttf-debug-4.9.9','a5_primitives-debug-4.9.9','zoidcomd'])
else:
	env.Append(LIBS=['allegro-4.9.9','a5_iio-4.9.9','a5_font-4.9.9','a5_ttf-4.9.9','a5_primitives-4.9.9','zoidcom'])

scenegraph_files = glob.glob('src/scenegraph/*.cpp')
scenegraph_files = [x.replace("src", "obj") for x in scenegraph_files]

files = glob.glob('src/*.cpp')
files = [x.replace("src", "obj") for x in files]
	
env.Append(CCFLAGS = '-Wall')

env.BuildDir('obj/scenegraph','src/scenegraph', duplicate = 0)
scenegraph = env.StaticLibrary('lib/scenegraph', scenegraph_files)

env.Append(LIBS = [scenegraph])
env.BuildDir('obj','src', duplicate = 0)
env.Program('a53d',files)
