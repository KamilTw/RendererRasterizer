#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Model.h"

class ObjectLoader
{
private:
	vector<float3> vertices;
	vector<float3> normals;
	vector<float> u;
	vector<float> v;
	vector<Material> materials;
public:
	Model loadObject(std::string objectFileName);
	void loadMaterial(string objectFileName, vector<Material>* materials);
};