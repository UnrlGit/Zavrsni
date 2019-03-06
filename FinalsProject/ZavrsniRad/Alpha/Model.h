#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	Model() {}
	~Model() {}

	void LoadModel(const std::string& fileName, std::string subfolder);
	void RenderModel();
	void ClearModel();

private:
	void LoadNode(aiNode *node, const aiScene *scene);
	void LoadMesh(aiMesh *mesh, const aiScene *scene);
	void LoadMaterials(const aiScene * scene);

	std::vector<Mesh*> _meshes;
	std::vector<Texture*> _textures;
	std::vector<unsigned int> _meshToTexure;

	std::string _subfolder;
};
#endif // !MODEL_H