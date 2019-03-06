#include "Model.h"

void Model::LoadModel(const std::string & fileName, std::string subfolder)
{
	Assimp::Importer importer;
	// scene importer									// splitting triangles  
	const aiScene * scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
	_subfolder = "/" + subfolder + "/";
	if (!scene)
	{
		std::cerr << fileName << "couldn't load, error: " << importer.GetErrorString() << std::endl;
		return;
	}

	// getting main node that surround everything
	LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);
}

void Model::RenderModel()
{
	// TODO check if it works with _meshToTexture ( for loop)
	for (size_t i = 0; i < _meshes.size(); i++)
	{
		unsigned int materialIndex = _meshToTexure[i];
		// checking that material  exists inside material list
		if (materialIndex < _textures.size() && _textures[materialIndex] != nullptr)
		{
			_textures[materialIndex]->UseTexture();
		}

		_meshes[i]->RenderMesh();
	}
}

void Model::ClearModel()
{
	// deleting all meshes
	for (size_t i = 0; i < _meshes.size(); i++)
	{
		if (_meshes[i])
		{
			delete _meshes[i];
			_meshes[i] = nullptr;
		}
	}
	//deleting all textures
	for (size_t i = 0; i < _textures.size(); i++)
	{
		if (_textures[i])
		{
			delete _textures[i];
			_textures[i] = nullptr;
		}
	}
}

void Model::LoadNode(aiNode * node, const aiScene * scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		// TODO recheck
		// getting id of that mesh of that node (from node)
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene);
	}
}

void Model::LoadMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indicies;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		// adding vertices 
		vertices.insert(vertices.end(), { mesh->mVertices[i].x,  mesh->mVertices[i].y,  mesh->mVertices[i].z });
		// adding u and v if it exists
		if (mesh->mTextureCoords[0])
		{
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x,  mesh->mTextureCoords[0][i].y });
		}
		else
		{
			vertices.insert(vertices.end(), { 0.0f, 0.0f });
		}
		// adding normals, reverse because of shader 
		// TODO put positive and change normalize at diffuseFctor (normalize(directiona)) to negative, then reverse normals
		vertices.insert(vertices.end(), { -mesh->mNormals[i].x,  -mesh->mNormals[i].y ,  -mesh->mNormals[i].z });
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		// each face has 3 values (for indicies)
		aiFace face = mesh->mFaces[i];
		for (size_t currenIndicie = 0; currenIndicie < face.mNumIndices; currenIndicie++)
		{
			indicies.push_back(face.mIndices[currenIndicie]);
		}
	}

	Mesh * newMesh = new Mesh();
	newMesh->CreateMesh(&vertices[0], &indicies[0], vertices.size(), indicies.size());
	_meshes.push_back(newMesh);
	// to which texture is mesh pointing
	_meshToTexure.push_back(mesh->mMaterialIndex);
}

void Model::LoadMaterials(const aiScene * scene)
{
	_textures.resize(scene->mNumMaterials);


	// iterating through all materials/textures
	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial * material = scene->mMaterials[i];

		_textures[i] = nullptr;
		// looking for diffuse texture
		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString path;
			// getting first diffuse texture
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				// getting relative path to texture, removing possible full paths
				int index = std::string(path.data).rfind("\\");
				std::string fileName = std::string(path.data).substr(index + 1);
				std::string texturePath = std::string("Textures/") + _subfolder + fileName;
				_textures[i] = new Texture(texturePath.c_str());

				// if didn't load
				// TODO test  alpha load
				if (!_textures[i]->LoadTexturePlain())
				{
					std::cerr << "Failed to load texture at " << texturePath << std::endl;
					delete _textures[i];
					_textures[i] = nullptr;
				}
			}
		}
		// in case texture is missing, load default
		if (!_textures[i])
		{
			_textures[i] = new Texture("Textures/plain.png");
			_textures[i]->LoadTextureAlpha();
		}
	}
}
