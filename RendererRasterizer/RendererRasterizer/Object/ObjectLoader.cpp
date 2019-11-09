#include "ObjectLoader.h"

Model ObjectLoader::loadObject(std::string objectFileName)
{
	Model model = Model();
	vertices.clear();
	vIndexes.clear();

	materials.clear();
	mIndexes.clear();
	materialNames.clear();

	normals.clear();
	nIndexes.clear();

	u.clear();
	v.clear();

	loadMaterial(objectFileName);

	std::fstream file;
	file.open("Objects/" + objectFileName + ".obj");

	std::string line;
	int currentMaterialIndex = 0;

	if (!file.is_open())
	{
		std::cout << objectFileName << ".obj file not found" << std::endl << std::endl;
	}
	else
	{
		while (!file.eof())
		{
			getline(file, line);

			if (line[0] == 'v' && line[1] == ' ')				// vertices
			{
				float verticeX, verticeY, verticeZ;
				sscanf_s(line.c_str(), "v %f %f %f", &verticeX, &verticeY, &verticeZ);

				vertices.push_back(float3{ verticeX, verticeY, verticeZ });
			}
			else if (line[0] == 'v' && line[1] == 'n')			// normals
			{
				float normalX, normalY, normalZ;
				sscanf_s(line.c_str(), "vn %f %f %f", &normalX, &normalY, &normalZ);

				normals.push_back(float3{ normalX, normalY, normalZ });
			}
			else if (line[0] == 'v' && line[1] == 't')			// tex coords
			{
				float textureX, textureY, textureZ;
				sscanf_s(line.c_str(), "vt %f %f %f", &textureX, &textureY, &textureZ);

				u.push_back(textureX);
				v.push_back(textureY);
			}
			else if (line[0] == 'u' && line[1] == 's')			// current material
			{
				std::string materialName = line;
				materialName.erase(0, 7);
				for (int i = 0; i < materialNames.size(); i++)
				{
					if (materialNames[i] == materialName)
					{
						currentMaterialIndex = i;				// material index
					}
				}
			}
			else if (line[0] == 'f')							// faces
			{
				int vIndice1, vIndice2, vIndeice3;				// vertices indexes
				int vtIndice1, vtIndice2, vtIndice3;			// tex coords indexes
				int nIndice1, nIndice2, nIndice3;				// normal index
				sscanf_s(line.c_str(), "f %i/%i/%i %i/%i/%i %i/%i/%i", &vIndice1, &vtIndice1, &nIndice1, &vIndice2, &vtIndice2, &nIndice2, &vIndeice3, &vtIndice3, &nIndice3);

				// .obj file numerates from 1, not 0 (not materials)
				vIndexes.push_back(int3{ vIndice1 - 1, vIndice2 - 1, vIndeice3 - 1 });
				mIndexes.push_back(currentMaterialIndex);
				nIndexes.push_back(int3{ nIndice1 - 1, nIndice2 - 1, nIndice3 - 1 });
			}
		}
		model.vertices = vertices;
		model.vIndexes = vIndexes;

		model.materials = materials;
		model.mIndexes = mIndexes;

		model.normals = normals;
		model.nIndexes = nIndexes;

		file.close();
		std::cout << objectFileName << ".obj file loaded" << std::endl << std::endl;

		return model;
	}
}

void ObjectLoader::loadMaterial(string objectFileName)
{
	fstream file;
	string line;
	file.open("Objects/" + objectFileName + ".mtl");

	string materialName;
	float4 ka, kd, ks;

	if (!file.is_open())
	{
		cout << objectFileName << ".mtl file not found" << endl;
	}
	else
	{
		while (!file.eof())
		{
			getline(file, line);

			if (line[0] == 'n' && line[1] == 'e')								// material name
			{
				materialName = line;
				materialName.erase(0, 7);
			}
			else if (line[0] == '	' && line[1] == 'K' && line[2] == 'a')		// ambient color
			{
				float r, g, b;
				sscanf_s(line.c_str(), "	Ka %f %f %f", &r, &g, &b);

				ka = float4{ r, g, b, 1 };
			}
			else if (line[0] == '	' && line[1] == 'K' && line[2] == 'd')		// diffuse color
			{
				float r, g, b;
				sscanf_s(line.c_str(), "	Kd %f %f %f", &r, &g, &b);

				kd = float4{ r, g, b, 1 };
			}
			else if (line[0] == '	' && line[1] == 'K' && line[2] == 's')		// specular color
			{
				float r, g, b;
				sscanf_s(line.c_str(), "	Ks %f %f %f", &r, &g, &b);

				ks = float4{ r, g, b, 1 };

				materialNames.push_back(materialName);
				materials.push_back(Material{ka, kd, ks});
			}
		}

		file.close();
		cout << materialNames.size() << " materials loaded from " << objectFileName + ".mtl" << endl;
	}
}