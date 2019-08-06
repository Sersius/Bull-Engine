#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "imGUI\imgui.h"
#include "imGUI\imgui_impl_sdl_gl3.h"
#include "Glew\include\glew.h"

#pragma comment( lib, "Glew/libx86/glew32.lib" )



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	glewInit();
	
	

	//GLfloat vertices[] =
	//{
	//	//FRONT
	//	1.0f,1.0f,0.0f,
	//	0.0f,1.0f,0.0f,
	//	0.0f,0.0f,0.0f,
	//	//FRONT 
	//	0.0f,0.0f,0.0f,
	//	1.0f,0.0f,0.0f,
	//	1.0f,1.0f,0.0f,
	//	//TOP
	//	0.0f,1.0f,0.0f,
	//	1.0f,1.0f,0.0f,
	//	0.0f,1.0f,-1.0f,
	//	//TOP
	//	0.0f,1.0f,-1.0f,
	//	1.0f,1.0f, 0.0f,
	//	1.0f,1.0f,-1.0f,
	//	//BOT
	//	0.0f,0.0f,0.0f,
	//	0.0f,0.0f,-1.0f,
	//	1.0f,0.0f,0.0f,
	//	//BOT
	//	0.0f,0.0f,-1.0f,
	//	1.0f,0.0f, -1.0f,
	//	1.0f,0.0f,0.0f,
	//	//LEFT
	//	0.0f,0.0f,0.0f,
	//	0.0f,1.0f,0.0f,
	//	0.0f,1.0f,-1.0f,
	//	//LEFT
	//	0.0f,1.0f,-1.0f,
	//	0.0f,0.0f,-1.0f,
	//	0.0f,0.0f,0.0f,
	//	//RIGHT
	//	1.0f,0.0f,0.0f,
	//	1.0f,1.0f,-1.0f,
	//	1.0f,1.0f,0.0f,
	//	//RIGHT
	//	1.0f,0.0f,0.0f,
	//	1.0f,0.0f,-1.0f,
	//	1.0f,1.0f,-1.0f,
	//	//BACK
	//	1.0f,0.0f,-1.0f,
	//	0.0f,1.0f,-1.0f,
	//	1.0f,1.0f,-1.0f,
	//	//BACK
	//	1.0f,0.0f,-1.0f,
	//	0.0f,0.0f,-1.0f,
	//	0.0f,1.0f,-1.0f,

	//};
	
	
	//glGenBuffers(1, (GLuint*) &(my_id));
	//glBindBuffer(GL_ARRAY_BUFFER, my_id);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 3, vertices, GL_STATIC_DRAW);

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}
update_status ModuleSceneIntro::PreUpdate(float dt)
{
	return(UPDATE_CONTINUE);
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	vertex = new float[72]{ 1.0f,1.0f,0.0f,  0.0f,1.0f,0.0f,   0.0f,0.0f,0.0f,   1.0f,0.0f,0.0f, //FRONT
							1.0f,1.0f,0.0f,  1.0f,1.0f,-1.0f,  0.0f,1.0f,-1.0f,  0.0f,1.0f,0.0f,  //TOP
							1.0f,1.0f,0.0f,  1.0f,0.0f,0.0f,   1.0f,0.0f,-1.0f,  1.0f,1.0f,-1.0f, //RIGHT
							0.0f,1.0f,0.0f,  0.0f,1.0f,-1.0f,   0.0f,0.0f,-1.0f,  0.0f,0.0f,0.0f,  //LEFT
							0.0f,0.0f,-1.0f, 1.0f,0.0f,-1.0f,   1.0f,0.0f,0.0f,   0.0f,0.0f,0.0f,  //BOTTOM
							1.0f,0.0f,-1.0f, 0.0f,0.0f,-1.0f,  0.0f,1.0f,-1.0f,  1.0f,1.0f,-1.0f  //BACK   
							
	}; 
	glGenBuffers(1, (GLuint*) &(my_id));
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 72, vertex, GL_STATIC_DRAW);

	indices = new uint[36]{ 0, 1, 2,   2, 3, 0,  // FRONT
							4, 5, 6,   6, 7, 4,	 // TOP
							8, 9, 10,  10,11,8,  // RIGHT
						    12,13,14,  14,15,12, // LEFT
							16,17,18,  18,19,16, // BOTTOM
							20,21,22,  22,23,20  // BACK
	};

	
	glGenBuffers(1, (GLuint*) &(my_indices));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 36, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_VERTEX_ARRAY);
	/*glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableClientState(GL_VERTEX_ARRAY);*/

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
}

