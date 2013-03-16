#include "ModelLoader.h"
ModelLoader::ModelLoader()
{
}

int ModelLoader::Load(char* path, bool texture) 
{
	int index = glGenLists(1);
	float x, y, z, nx, ny, nz, tu, tv;
	glNewList(index, GL_COMPILE);
		glBegin(GL_TRIANGLES);
			std::ifstream reader;
			char input;
			int i;
			int count;
			reader.open(path);
			if(reader.fail()) return -1;
			reader.get(input);
			while(input != ':')
			{
				reader.get(input);
			}
			reader >> count;
			reader.get(input);
			while(input != ':')
			{
				reader.get(input);
			}
			reader.get(input);
			reader.get(input);

			for(i = 0; i < count; i++) {
				reader >> x >> y >> z;
				reader >> tu >> tv;
				reader >> nx >> ny >> nz;
				if(texture) glTexCoord2f(tu, tv);
				glNormal3f(nx, ny, nz);
				glVertex3f(x, y, z);
			}
			reader.close();
		glEnd();
	glEndList();
	return index;
}