
#include "Application.h"
#include "ModuleLoadFBX.h"
#include "Glew/include/glew.h" 
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"


#pragma comment (lib, "Assimp/libx86/assimp.lib")

ModuleLoadFBX::ModuleLoadFBX(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleLoadFBX::~ModuleLoadFBX()
{}

// Load assets
bool ModuleLoadFBX::Start()
{
	bool ret = true;
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);


	return ret;
}
update_status ModuleLoadFBX::PreUpdate(float dt)
{

	return(UPDATE_CONTINUE);
}

// Load assets
bool ModuleLoadFBX::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();
	return true;
}

// Update
update_status ModuleLoadFBX::Update(float dt)
{
	return UPDATE_CONTINUE;
}
bool ModuleLoadFBX::LoadFbx(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes()) {
	
		aiNode* rootNode = scene->mRootNode;
		for (int i = 0; i < rootNode->mNumChildren; ++i)
		{
			LoadModelInfo(scene,rootNode->mChildren[i], path);
		}
		return true;
	}
	else
	{
		return false;
	}

}

void ModuleLoadFBX::LoadModelInfo(const aiScene* scene, aiNode* node,const char* path)
{
	
	if (scene != nullptr && scene->HasMeshes()) {   
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* new_mesh = scene->mMeshes[node->mMeshes[i]];
			mesh.num_vertex = new_mesh->mNumVertices;
			mesh.vertex = new uint[mesh.num_vertex * 3];
			memcpy(mesh.vertex, new_mesh->mVertices, sizeof(float)*mesh.num_vertex * 3);
			LOG("New mesh with %d vertices", mesh.num_vertex);

			if (new_mesh->HasFaces()) {
				mesh.num_index = new_mesh->mNumFaces * 3;
				mesh.index = new uint[mesh.num_index]; // assume each face is a triangle
				for (uint i = 0; i < new_mesh->mNumFaces; ++i)
				{
					if (new_mesh->mFaces[i].mNumIndices != 3) {
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else    
						memcpy(&mesh.index[i*3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
				} 
			}
			if (new_mesh->HasNormals()) {
				mesh.num_normals = new_mesh->mNumVertices;
				mesh.normals = new float[mesh.num_normals * 3]; // assume each face is a triangle
				memcpy(mesh.normals, new_mesh->mNormals, sizeof(float)*mesh.num_normals * 3);
			}
		}

		glGenBuffers(1, (GLuint*) &(mesh.id_vertex));
		glBindBuffer(GL_ARRAY_BUFFER, mesh.id_vertex);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh.num_vertex, mesh.vertex, GL_STATIC_DRAW);

		glGenBuffers(1, (GLuint*) &(mesh.id_index));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.id_index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * mesh.num_index, mesh.index, GL_STATIC_DRAW);

		glGenBuffers(1, (GLuint*)&(mesh.id_normals));
		glBindBuffer(GL_ARRAY_BUFFER, mesh.id_normals);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh.num_normals, mesh.normals, GL_STATIC_DRAW);

		App->renderer3D->meshes.push_back(mesh);
		
	}
	else {
		LOG("Error loading scene %s", path);
		
	}
	
}





