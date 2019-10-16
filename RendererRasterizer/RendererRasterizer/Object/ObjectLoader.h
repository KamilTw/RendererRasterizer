#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Model.h"

class ObjectLoader
{
public:
	Model loadObject(std::string objectFileName);
	void loadMaterial(string objectFileName, Model* model);
};