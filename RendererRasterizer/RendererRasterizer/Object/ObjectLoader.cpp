#include "ObjectLoader.h"

Model ObjectLoader::loadObject(std::string objectFileName)
{
	Model model = Model();
	vertices.clear();
	normals.clear();
	u.clear();
	v.clear();
	materials.clear();

	loadMaterial(objectFileName, &materials);

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
				for (int i = 0; i < materials.size(); i++)
				{
					if (materials[i].name == materialName)
					{
						currentMaterialIndex = i;				// material index
					}
				}
			}
			else if (line[0] == 'f')							// faces
			{
				int vIndice1, vIndice2, vIndeice3;				// vertices indexes
				int vtIndice1, vtIndice2, vtIndice3;			// tex coords indexes
				int normal;										// normal index
				sscanf_s(line.c_str(), "f %i/%i/%i %i/%i/%i %i/%i/%i", &vIndice1, &vtIndice1, &normal, &vIndice2, &vtIndice2, &normal, &vIndeice3, &vtIndice3, &normal);

				// .obj file numerates from 1, not 0 (not materials)
				model.addTriangle(&Triangle(vertices[vIndice1 - 1], vertices[vIndice2 - 1], vertices[vIndeice3 - 1],									// vertices
									materials[currentMaterialIndex].kd, materials[currentMaterialIndex].kd, materials[currentMaterialIndex].kd));		// colors
			}
		}

		file.close();
		std::cout << objectFileName << ".obj file loaded" << std::endl << std::endl;

		return model;
	}
}

void ObjectLoader::loadMaterial(string objectFileName, vector<Material> *materials)
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

				materials->push_back(Material{ ka, kd, ks, materialName });
			}
		}

		file.close();
		cout << materials->size() << " materials loaded from " << objectFileName + ".mtl" << endl;
	}
}