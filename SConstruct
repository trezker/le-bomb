import glob
import sys
import os


env = Environment(CPPPATH = ['include'])

debug = ARGUMENTS.get('debug', 0)
if int(debug):
	env.Append(CCFLAGS = '-g')
	env.Append(LIBS=['GL','GLU','glut','allegro-debug-4.9.16','a5_iio-debug-4.9.16','a5_font-debug-4.9.16','a5_ttf-debug-4.9.16','a5_primitives-debug-4.9.16','a5_dialog-debug-4.9.16','zoidcomd'])
else:
	env.Append(LIBS=['GL','GLU','glut','allegro-4.9.16','allegro_image-4.9.16','allegro_font-4.9.16','allegro_ttf-4.9.16','allegro_primitives-4.9.16','allegro_dialog-4.9.16','zoidcom'])

env.Append(CCFLAGS = '-Wall')


math_files = glob.glob('src/math/*.cpp')
math_files = [x.replace("src", "obj") for x in math_files]
math = env.StaticLibrary('lib/math', math_files)

#md5_files = glob.glob('src/md5/*.cpp')
#md5_files = [x.replace("src", "obj") for x in md5_files]
#md5 = env.StaticLibrary('lib/md5', md5_files)

particles_files = glob.glob('src/particles/*.cpp')
particles_files = [x.replace("src", "obj") for x in particles_files]
particles = env.StaticLibrary('lib/particles', particles_files)

scenegraph_files = glob.glob('src/scenegraph/*.cpp')
scenegraph_files = [x.replace("src", "obj") for x in scenegraph_files]
scenegraph = env.StaticLibrary('lib/scenegraph', scenegraph_files)

interface_files = glob.glob('src/interface/*.cpp')
interface_files = [x.replace("src", "obj") for x in interface_files]
interface = env.StaticLibrary('lib/interface', interface_files)

env.Append(LIBS = [scenegraph, particles, interface, math])
interface_test_files = glob.glob('src/interface/test/*.cpp')
interface_test_files = [x.replace("src", "obj") for x in interface_test_files]
env.Program('bin/interface_test', interface_test_files)

modelviewer_files = glob.glob('src/modelviewer/*.cpp')
modelviewer_files = [x.replace("src", "obj") for x in modelviewer_files]
env.Program('bin/modelviewer', modelviewer_files)

files = glob.glob('src/*.cpp')
files = [x.replace("src", "obj") for x in files]
env.BuildDir('obj','src', duplicate = 0)
env.Program('a53d',files)
