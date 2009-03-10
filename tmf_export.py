import Blender
import BPyMesh

def add_uvdata(uvdata, uv):
	return uvdata + '%.6f %.6f ' % tuple(uv)

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
	file.write("C " + `len(mesh.verts)` + "\n")
	for v in mesh.verts:
		file.write('%.6f %.6f %.6f ' % tuple(v.co))
		file.write('\n')

	file.write("N " + `len(mesh.verts)` + "\n")
	for v in mesh.verts:
		file.write('%.6f %.6f %.6f ' % tuple(v.no))
		file.write('\n')

	#Process faces
	faces = len(mesh.faces)
	data = ""
	uvdata = ""
	for face in mesh.faces:
		if face.v[2] < 0:
			# discard
			faces = faces - 1
		elif face.v[2] < 0:
			# Already a triangle, add it to the data, do not change the count
			data = data + `face.v[0].index` + " " + `face.v[1].index` + " " + `face.v[2].index` + "\n"
			for v in face.uv:
				add_uvdata(uvdata, v)
		else:
			# this one is a quad
			# Break it up into two triangles
			# Hence one additional face
			faces = faces + 1
			data = data + `face.v[0].index` + " " + `face.v[1].index` + " " + `face.v[3].index` + "\n"
			data = data + `face.v[1].index` + " " + `face.v[2].index` + " " + `face.v[3].index` + "\n"
			uvdata = add_uvdata(uvdata, face.uv[0])
			uvdata = add_uvdata(uvdata, face.uv[1])
			uvdata = add_uvdata(uvdata, face.uv[3])
			uvdata = uvdata + "\n"
			uvdata = add_uvdata(uvdata, face.uv[1])
			uvdata = add_uvdata(uvdata, face.uv[2])
			uvdata = add_uvdata(uvdata, face.uv[3])
			uvdata = uvdata + "\n"
	# Now I can write the header with the correct face count, and then the data
	file.write("F " + `faces` + "\n")
	file.write(data)
	uvs = faces*3
	file.write("T " + `uvs` + "\n")
	file.write(uvdata)

	file.close()
	
	end = Blender.sys.time()
	message = 'Successfully exported "%s" in %.4f seconds' % ( Blender.sys.basename(filename), end-start)
	print message


Blender.Window.FileSelector(write, 'TMF Export', Blender.sys.makename(ext='.tmf'))
