#include "MeshLoader.h"

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

namespace MeshLoader
{
	void LoadObjFiles(ifstream& inFile, Mesh& mesh);

	void LoadObjFiles(ifstream& inFile, Mesh& mesh)
	{
		std::vector <unsigned int> vertexIndices, uIndices, normalIndices;
		std::vector<Vertex> temp_vertices;
		std::vector<TexCoord> temp_uvs;
		std::vector<Normal> temp_normals;


		string test;
		while (!inFile.eof())
		{
			inFile >> test;


			if (test == "v")
			{
				Vertex vertex;
				inFile >> vertex.x;
				inFile >> vertex.y;
				inFile >> vertex.z;
				temp_vertices.push_back(vertex);
			}
			else if (test == "vt")
			{
				TexCoord texcoord;
				inFile >> texcoord.u;
				inFile >> texcoord.v;
				temp_uvs.push_back(texcoord);
			}
			else if (test == "vn")
			{
				Normal normals;
				inFile >> normals.x;
				inFile >> normals.y;
				inFile >> normals.z;
				temp_normals.push_back(normals);
			}
			else if (test == "f")
			{
				for (int i = 0; i < 3; i++)
				{
					inFile >> test;


					std::replace(test.begin(), test.end(), '/', ' ');

					stringstream ss(test);
					GLushort temp;

					ss >> temp;
					vertexIndices.push_back(temp-1);
					ss >> temp;
					uIndices.push_back(temp-1);
					ss >> temp;
					normalIndices.push_back(temp-1);
				}
			}
		}
		mesh.IndexCount = vertexIndices.size();
		


		Normal* Normals = new Normal[mesh.IndexCount];
		for (int i = 0; i < mesh.IndexCount; i++)
		{
			Normals[i] = temp_normals[normalIndices[i]];
		}

		TexCoord* TexCoords = new TexCoord[mesh.IndexCount];
		for (int i = 0; i < mesh.IndexCount; i++)
		{
			TexCoords[i] = temp_uvs[uIndices[i]];
		}

		Vertex* Vertices = new Vertex[mesh.IndexCount];
		for (int i = 0; i < mesh.IndexCount; i++)
		{
			Vertices[i] = temp_vertices[vertexIndices[i]];
		}

		for (int i = 0; i < mesh.IndexCount; i++)
		{
			InterlacedVertex buffer;
			buffer.Vertices = temp_vertices[vertexIndices[i]];
			buffer.Normals = temp_normals[normalIndices[i]];
			buffer.TexCoords = temp_uvs[uIndices[i]];
			mesh.InterVertex.push_back(buffer);
		}
	}

	Mesh* MeshLoader::LoadObj(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadObjFiles(inFile, *mesh);

		return mesh;
	}
}