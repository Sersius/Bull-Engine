#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleLoadFBX.h"
#include "ModuleUI.h"
#include "InspectorWindow.h"
#include "ModuleSceneIntro.h"

#include "ModuleGameObject.h"
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"

#include "Glew/include/glew.h"


Mesh::Mesh(GameObject* parent,char* path) : Component(parent, COMPONENT_TYPE::MESH), path(path)
{
	GetMesh(path);
}

Mesh::~Mesh()
{

}

void Mesh::Update(float dt)
{

}

void Mesh::GetMesh(char* path)
{
	App->loadFBX->LoadFbx(path);
	this->path = path;
}

void Mesh::Draw()
{
	if (parent->render_model) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		if (parent) {
			if (parent->material->draw_texture == true) {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, parent->material->id);
			}
			if (parent->material->draw_checkers == true)
			{
				App->renderer3D->Checkers();
				glBindTexture(GL_TEXTURE_2D, App->renderer3D->ImageName);
			}
			if (parent->mesh->draw_normals)
			{
				DrawNormals();
			}

		}
		glBindBuffer(GL_NORMAL_ARRAY, info_mesh.id_normals);
		glNormalPointer(GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, info_mesh.id_vertex);
		glVertexPointer(3, GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, info_mesh.id_uvs);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info_mesh.id_index);
		if (App->renderer3D->wireframe == true) {
			glColor3d(1, 1., 0);
			glPolygonMode(GL_FRONT, GL_LINE);
		}
		glDrawElements(GL_TRIANGLES, info_mesh.num_index, GL_UNSIGNED_INT, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
		
	}
}
void Mesh::DrawNormals()
{
	int size = 2;
	glColor3f(1.0f,1.0f,1.0f);
	
	for (uint i = 0; i < info_mesh.num_vertex * 3; i += 3)
	{
		glBegin(GL_LINES);
		glVertex3f(info_mesh.vertex[i], info_mesh.vertex[i + 1], info_mesh.vertex[i + 2]);
		glVertex3f(info_mesh.vertex[i] + info_mesh.normals[i] * size, info_mesh.vertex[i + 1] + info_mesh.normals[i + 1]*size, info_mesh.vertex[i + 2] + info_mesh.normals[i + 2]*size);
		glEnd();
	}
	glColor3f(1.0f, 1.0f, 1.0f);
}