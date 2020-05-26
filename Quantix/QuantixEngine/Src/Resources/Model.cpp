#include "Resources/Model.h"

#include <glad/glad.h>
#include <unordered_map>
#include <cstdint>
#include <iostream>

#include "Core/Debugger/Logger.h"

RTTR_PLUGIN_REGISTRATION
{
	rttr::registration::class_<Quantix::Resources::Model>("Model")
	.constructor<>()
	.constructor<const std::vector<Quantix::Resources::Vertex>&, const std::vector<QXuint>&>()
	.method("GetPath", &Quantix::Resources::Model::GetPath);
}

namespace Quantix::Resources
{
#pragma region Constructors

	Model::Model(const std::vector<Vertex>& vertices, const std::vector<QXuint>& indices) :
		_vertices {vertices},
		_indices {indices}
	{}

#pragma endregion

#pragma region Functions

	void Model::Init()
	{
		QXuint VBO, EBO;
		glGenVertexArrays(1, &_VAO);
		glBindVertexArray(_VAO);
		glGenBuffers(1, &VBO);
		/* bind VBO */
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		/* send data */
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)
			* _vertices.size(), (QXfloat*)_vertices.data(), GL_STATIC_DRAW);

		/* set VBO properties */
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(QXfloat),
			(void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(QXfloat),
			(void*)(3 * sizeof(QXfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(QXfloat),
			(void*)(5 * sizeof(QXfloat)));
		glEnableVertexAttribArray(2);
		/* create EBO */
		glGenBuffers(1, &EBO);

		/* set EBO */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QXuint) * _indices.size(),
			_indices.data(), GL_STATIC_DRAW);

		glBindVertexArray(0);

		_status.store(EResourceStatus::READY);
	}

	void Model::Load(const QXstring& file)
	{
		_path = file;

		if (!LoadFromCache(file))
			LoadWithLib(file);
	}

	QXbool Model::LoadFromCache(const QXstring& filePath)
	{
		QXstring cache_file = filePath + ".quantix";
		FILE* file;

		fopen_s(&file, cache_file.c_str(), "rb");

		if (file == nullptr)
			return false;

		QXsizei vertex_count, index_count;

		fread(&vertex_count, sizeof(QXsizei), 1, file);
		_vertices.resize(vertex_count);
		fread(_vertices.data(), sizeof(Vertex), vertex_count, file);

		fread(&index_count, sizeof(QXsizei), 1, file);
		_indices.resize(index_count);
		fread(_indices.data(), sizeof(QXuint), index_count, file);

		fclose(file);

		_status.store(EResourceStatus::LOADED);

		return true;
	}

	void Model::LoadWithLib(const QXstring& file)
	{
		Assimp::Importer Importer;
		const aiScene* pScene = Importer.ReadFile(file.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

		const aiMesh* paiMesh = pScene->mMeshes[0];
		const aiAnimation* paiAnim = pScene->mAnimations[0];

		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

		for (unsigned int i = 0; i < paiMesh->mNumVertices; i++)
		{
			const aiVector3D* pPos = &(paiMesh->mVertices[i]);
			const aiVector3D* pNormal = paiMesh->HasNormals() ? &(paiMesh->mNormals[i]) : &Zero3D;
			const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

			Vertex vertex = { Math::QXvec3(pPos->x, pPos->y, pPos->z),
							Math::QXvec2(pTexCoord->x, pTexCoord->y),
							Math::QXvec3(pNormal->x, pNormal->y, pNormal->z) };

			_vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < paiMesh->mNumFaces; i++)
		{
			const aiFace& Face = paiMesh->mFaces[i];
			_indices.push_back(Face.mIndices[0]);
			_indices.push_back(Face.mIndices[1]);
			_indices.push_back(Face.mIndices[2]);
		}
		
		_status.store(EResourceStatus::LOADED);
	}

#pragma endregion
}