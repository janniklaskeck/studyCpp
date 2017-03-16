#include "Model.h"


Model::Model(const char* filename){
	char line[1024];
	
	FILE* file;
	fopen_s(&file, filename, "r");

	if (file == NULL) {
		fprintf(stderr, "Model %s nicht gefunden!\n", filename);
		return;
	}

	while( fgets(line, 1024, file) != NULL ){
		// Basic OBJ format (what kind of lines we have to expect):
		// http://en.wikipedia.org/wiki/Wavefront_.obj_file
		switch(line[0]){
			case 'v':  // vertex coordinates
				{
					Vector3D vertex;
					sscanf_s(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
					vertices.push_back(vertex);
				}
				break;
			case 'f':  // face
				{
					// TODO:
					// read facet list and store in variable "face"
					Face face;
					sscanf_s(line, "f %u %u %u",
						&face.vertex_indices[0],
						&face.vertex_indices[1],
						&face.vertex_indices[2]
					);

					// In Obj-Format the indices start with 1. In OpenGL they start with 0.
					// Convert the indices to OpenGL.
					face.vertex_indices[0]--;
					face.vertex_indices[1]--;
					face.vertex_indices[2]--;

					faces.push_back(face);
				}
				break;
		}
	}
	
	fclose(file);
}