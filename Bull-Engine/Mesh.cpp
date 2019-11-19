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
Mesh::Mesh() : Component(parent, COMPONENT_TYPE::MESH), path(path)
{
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
	

	parent->BoundingBox();
	parent->DrawBoundingBox();
}

void Mesh::Draw()
{
	if (parent->mesh->active) {
		glPushMatrix();
		glMultMatrixf(parent->transform->GetGlobalMatrix().Transposed().ptr());
		if (parent->render_model) {
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			
			if (parent) {
				if (parent->material) {
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

			glPopMatrix();

		}
	}
}
void Mesh::DrawNormals()
{
	int size = 20;
	glColor3f(1.0f,1.0f,1.0f);
	
	for (uint i = 0; i < info_mesh.num_vertex * 3; i += 3)
	{
		glBegin(GL_LINES);
		glVertex3f(info_mesh.vertex[i], info_mesh.vertex[i + 1], info_mesh.vertex[i + 2]);
		glVertex3f(info_mesh.vertex[i] + info_mesh.normals[i] , info_mesh.vertex[i + 1] + info_mesh.normals[i + 1], info_mesh.vertex[i + 2] + info_mesh.normals[i + 2]);
		glEnd();
	}
	glColor3f(1.0f, 1.0f, 1.0f);
}
void Mesh::SaveMesh(JSON_Array* componentsObj)
{
	JSON_Value* component = json_value_init_object();
	JSON_Object* componentGO = json_value_get_object(component);

	json_object_set_number(componentGO, "Type:", this->type);
	json_object_set_number(componentGO, "id_index:", parent->mesh->info_mesh.id_index);
	json_object_set_number(componentGO, "id_vertex:", parent->mesh->info_mesh.id_vertex);
	json_object_set_number(componentGO, "id_normals:", parent->mesh->info_mesh.id_normals);
	json_object_set_number(componentGO, "id_uv:", parent->mesh->info_mesh.id_uvs);
	json_object_set_boolean(componentGO, "Active:", parent->mesh->active);
	json_object_set_string(componentGO, "path", path);
	json_object_set_string(componentGO, "path_file_format", final_path.c_str());

	json_array_append_value(componentsObj, component);
}

void Mesh::LoadMesh(JSON_Object* obj, GameObject* go)
{
	go->mesh->final_path = json_object_get_string(obj, "path_file_format");
	go->mesh->info_mesh.id_index = json_object_get_number(obj, "id_index:");
	go->mesh->info_mesh.id_vertex = json_object_get_number(obj, "id_vertex:");
	go->mesh->info_mesh.id_normals = json_object_get_number(obj, "id_normals:");
	go->mesh->info_mesh.id_uvs = json_object_get_number(obj, "id_uv:");
	go->active = json_object_get_boolean(obj, "Active:");

	if (final_path.compare("") == true) {
		App->loadFBX->ImportMesh(final_path.c_str(),go);
		App->renderer3D->meshes.push_back(go->mesh);
	}
}