#include "Mesh.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleLoadFBX.h"
#include "ModuleUI.h"
#include "InspectorWindow.h"
#include "Transform.h"
#include "Material.h"
#include "ModuleSceneIntro.h"

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

		}
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

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}
}