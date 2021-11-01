#pragma once

#include "Structs.h"

namespace MeshLoader
{
	Mesh* Load(char* path);
	Mesh* LoadObj(char* path);
};

