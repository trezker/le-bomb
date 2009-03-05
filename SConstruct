import glob
import sys
import os

scenegraph_files = glob.glob('src/scenegraph/*.cpp')
scenegraph_files = [x.replace("src", "obj") for x in scenegraph_files]

files = glob.glob('src/*.cpp')
files = [x.replace("src", "obj") for x in files]

files += scenegraph_files

env = Environment(CPPPATH = ['include'])

debug = ARGUMENTS.get('debug', 0)
if int(debug):
	env.Append(CCFLAGS = '-g')
	env.Append(LIBS=['allegro-debug-4.9.9','a5_iio-debug-4.9.9','a5_font-debug-4.9.9','a5_ttf-debug-4.9.9','zoidcom'])
else:
	env.Append(LIBS=['allegro-4.9.9','a5_iio-4.9.9','a5_font-4.9.9','a5_ttf-4.9.9','zoidcom'])
	
env.Append(CCFLAGS = '-Wall')

#env.BuildDir('obj/scenegraph','src/scenegraph', duplicate = 0)
#env.StaticLibrary('lib/scenegraph', scenegraph_files)

#env.Append(LINKFLAGS = '-Llib')
#env.Append(LIBS = 'scenegraph')
env.BuildDir('obj','src', duplicate = 0)
env.Program('a53d',files)
