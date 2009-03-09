import Blender
import BPyMesh

def write(filename):
	start = Blender.sys.time()
	if not filename.lower().endswith('.tmf'):
		filename += '.tmf'
	
	scn= Blender.Scene.GetCurrent()
	ob= scn.objects.active
	if not ob:
		Blender.Draw.PupMenu('Error%t|Select 1 active object')
		return
	
	file = open(filename, 'wb')
	
	mesh = BPyMesh.getMeshFromObject(ob, None, True, False, scn)
	if not mesh:
		Blender.Draw.PupMenu('Error%t|Could not get mesh data from active object')
		return
	
	mesh.transform(ob.matrixWorld)
	
	
	file = open(filename, "wb")

	#Write vertex coords and normals
	for v in mesh.verts:
		file.write('C %.6f %.6f %.6f ' % tuple(v.co))
		file.write('N %.6f %.6f %.6f ' % tuple(v.no))
		file.write('\n')

	#Write faces		
	for f in mesh.faces:
		file.write('F ')
		for v in f:
			file.write('%i ' % v.index)
		file.write('\n')

	#Write texture coordinates
	for f in mesh.faces:
		for v in f.uv:
			file.write('T %.6f %.6f ' % tuple(v))
		file.write('\n')
		
	file.close()
	
	end = Blender.sys.time()
	message = 'Successfully exported "%s" in %.4f seconds' % ( Blender.sys.basename(filename), end-start)
	print message


Blender.Window.FileSelector(write, 'TMF Export', Blender.sys.makename(ext='.tmf'))
