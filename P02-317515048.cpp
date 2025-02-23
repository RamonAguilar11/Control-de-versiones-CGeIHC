//Pr�ctica 2: �ndices, mesh, proyecciones, transformaciones geom�tricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al c�digo
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Variables externas -> Ejercicio, no reporte
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crear�an ac�
static const char* vShaderRojo = "shaders/shaderrojo.vert"; //Para el color rojo
static const char* fShaderRojo = "shaders/shaderrojo.frag";

static const char* vShaderAzul = "shaders/shaderazul.vert"; //Para el color azul
static const char* fShaderAzul = "shaders/shaderazul.frag";

static const char* vShaderVerde = "shaders/shaderverde.vert"; //Para el color verde
static const char* fShaderVerde = "shaders/shaderverde.frag";

static const char* vShaderArbol = "shaders/shaderarbol.vert"; //Para el color de los arbolitos
static const char* fShaderArbol = "shaders/shaderarbol.frag";

static const char* vShaderCafe = "shaders/shadercafe.vert"; //Para el color cafe
static const char* fShaderCafe = "shaders/shadercafe.frag";

float angulo = 0.0f;

//color caf� en RGB : 0.478, 0.255, 0.067

//Pir�mide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2, //cara frontal
		1,3,2, 
		3,0,2,
		1,0,3 //base
		
	};
	GLfloat vertices[] = {
		-1.0f, -1.0f,0.0f,	//0
		1.0f,-1.0f,0.0f,	//1
		0.0f,1.0f, -0.5f,	//2
		0.0f,-1.0f,-1.0f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//V�rtices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	//0
	GLfloat vertices_r[] = {
		//X		 Y		 Z				R		G		B
		-0.9f,	0.5f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.7f,	0.5f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.9f,	-0.5f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.9f,	-0.5f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.7f,	0.5f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.7f,	-0.5f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.7f,	0.5f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.7f,	0.3f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.7f,	0.3f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.4f,	0.3f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.6f,	0.3f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.4f,	0.1f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.4f,	0.3f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.6f,	0.1f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.4f,	0.1f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.6f,	0.3f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.7f,	0.1f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.4f,	0.1f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.1f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.7f,	0.1f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.7f,	-0.1f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.1f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.6f,	-0.5f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.7f,	-0.1f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.1f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.1f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.6f,	-0.5f,	0.0f,			1.0f,	0.0f,	0.0f,
		-0.4f,	-0.5f,	0.0f,			1.0f,	0.0f,	0.0f,
	
	};
	MeshColor *letra_r = new MeshColor();
	letra_r->CreateMeshColor(vertices_r, 180);
	meshColorList.push_back(letra_r);

	//1
	GLfloat vertices_a[] = {
		//X		 Y		 Z				R		G		B
		-0.4f,	-0.5f,	0.0f,			0.0f,	1.0f,	0.0f,
		-0.2f,	-0.5f,	0.0f,			0.0f,	1.0f,	0.0f,
		-0.2f,	0.3f,	0.0f,			0.0f,	1.0f,	0.0f,
		-0.2f,	0.3f,	0.0f,			0.0f,	1.0f,	0.0f,
		-0.2f,	-0.5f,	0.0f,			0.0f,	1.0f,	0.0f,
		0.0f,	0.3f,	0.0f,			0.0f,	1.0f,	0.0f,
		-0.2f,	0.3f,	0.0f,			0.0f,	1.0f,	0.0f,
		-0.15f,	0.5f,	0.0f,			0.0f,	1.0f,	0.0f,
		0.15f,	0.5f,	0.0f,			0.0f,	1.0f,	0.0f,
		-0.2f,	0.3f,	0.0f,			0.0f,	1.0f,	0.0f,
		0.2f,	0.3f,	0.0f,			0.0f,	1.0f,	0.0f,
		0.15f,	0.5f,	0.0f,			0.0f,	1.0f,	0.0f,
		0.0f,	0.3f,	0.0f,			0.0f,	1.0f,	0.0f,
		0.2f,	0.3f,	0.0f,			0.0f,	1.0f,	0.0f,
		0.2f,	-0.5f,	0.0f,			0.0f,	1.0f,	0.0f,
		0.4f,	-0.5f,	0.0f,			0.0f,	1.0f,	0.0f,
		0.2f,	0.3f,	0.0f,			0.0f,	1.0f,	0.0f,
		0.2f,	-0.5f,	0.0f,			0.0f,	1.0f,	0.0f,
		-0.1f,	0.0f,	0.0f,			0.0f,	1.0f,	0.0f,
		-0.2f,	-0.2f,	0.0f,			0.0f,	1.0f,	0.0f,
		0.1f,	0.0f,	0.0f,			0.0f,	1.0f,	0.0f,
		0.1f,	0.0f,	0.0f,			0.0f,	1.0f,	0.0f,
		-0.2f,	-0.2f,	0.0f,			0.0f,	1.0f,	0.0f,
		0.2f,	-0.2f,	0.0f,			0.0f,	1.0f,	0.0f,
		
	};

	MeshColor* letra_a = new MeshColor();
	letra_a->CreateMeshColor(vertices_a, 144); 
	meshColorList.push_back(letra_a); 

	//2
	GLfloat vertices_p[] = {
		//X		 Y		 Z				R		G		B
		0.4f,	-0.5f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.4f,	0.5f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.6f,	0.5f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.6f,	-0.5f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.4f,	-0.5f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.6f,	0.5f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.6f,	0.3f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.8f,	0.5f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.6f,	0.5f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.6f,	0.3f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.8f,	0.5f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.9f,	0.3f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.7f,	.3f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.7f,	0.1f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.9f,	0.3f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.9f,	0.1f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.7f,	0.1f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.9f,	0.3f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.6f,	0.1f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.8f,	-0.1f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.9f,	0.1f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.6f,	-0.1f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.8f,	-0.1f,	0.0f,			0.0f,	0.0f,	1.0f,
		0.6f,	0.1f,	0.0f,			0.0f,	0.0f,	1.0f,
					
	};

	MeshColor* letra_p = new MeshColor();
	letra_p->CreateMeshColor(vertices_p, 144); 
	meshColorList.push_back(letra_p); 
}


void CreateShaders()
{
	//0
	Shader* shader1 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
	//1
	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);
	//2
	Shader* shader3 = new Shader();  //shader para el color rojo
	shader3->CreateFromFiles(vShaderRojo, fShaderRojo);  
	shaderList.push_back(*shader3); 
	//3
	Shader* shader4 = new Shader();  //shader para el color azul
	shader4->CreateFromFiles(vShaderAzul, fShaderAzul); 
	shaderList.push_back(*shader4); 
	//4
	Shader* shader5 = new Shader();  //shader para el color verde
	shader5->CreateFromFiles(vShaderVerde, fShaderVerde);
	shaderList.push_back(*shader5);
	//5
	Shader* shader6 = new Shader();  //shader para el color de los arbolitos
	shader6->CreateFromFiles(vShaderArbol, fShaderArbol);
	shaderList.push_back(*shader6); 
	//6
	Shader* shader7 = new Shader();  //shader para el color cafe
	shader7->CreateFromFiles(vShaderCafe, fShaderCafe); 
	shaderList.push_back(*shader7); 
}


int main()
{
	mainWindow = Window(800, 800);
	mainWindow.Initialise();
	CreaPiramide(); //�ndice 0 en MeshList
	CrearCubo();//�ndice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, �ndices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;

	//Projection: Matriz de Dimensi�n 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f); //left right top bottom near far. No tiene perspectiva
	//glm::mat4 projection = glm::perspective(glm::radians(45.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f); //Rango de apertura de 60 rad (Angulo de vision del ojo)

	//Model: Matriz de Dimensi�n 4x4 en la cual se almacena la multiplicaci�n de las transformaciones geom�tricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

		/*
		//Para las letras hay que usar el segundo set de shaders con �ndice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas

		
		//Generando las letras de colores
		//Letra R
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f)); //Traslacion inicial para que se vean los v�rtices
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();

		//Letra A
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));  //Traslacion inicial para que se vean los v�rtices
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); //FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[1]->RenderMeshColor();

		//Letra P
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));  //Traslacion inicial para que se vean los v�rtices
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); //FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();
		*/

		//Generando la casita
		//Generando cubo rojo
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, -0.4f)); 
		model = glm::scale(model, glm::vec3(0.95f, 1.0f, 0.0f));
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //cubo 

		//Generando a la piramide azul del techo
		shaderList[3].useShader(); 
		uniformModel = shaderList[3].getModelLocation(); 
		uniformProjection = shaderList[3].getProjectLocation(); 

		model = glm::mat4(1.0);  
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -0.3f)); //Traslacion de posicionamiento  
		model = glm::scale(model, glm::vec3(0.60f, 0.25f, 0.0f)); //Escalamiento de la figura 
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA 
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)); 
		meshList[0]->RenderMesh(); //piramide
		
		//Generando ventanas y puerta
		shaderList[4].useShader(); 
		uniformModel = shaderList[4].getModelLocation(); 
		uniformProjection = shaderList[4].getProjectLocation(); 

		//Ventana izquierda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.2f, 0.0f, -0.2f));  //Traslacion de posicionamiento 
		model = glm::scale(model, glm::vec3(0.33f, 0.33f, 0.0f));  //Escalamiento de la figura
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); //FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)); 
		meshList[1]->RenderMesh(); 
		//Ventana derecha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.2f, 0.0f, -0.2f));  //Traslacion de posicionamiento 
		model = glm::scale(model, glm::vec3(0.33f, 0.33f, 0.0f));  //Escalamiento de la figura
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));  //FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)); 
		meshList[1]->RenderMesh(); 
		//Puerta
		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(0.0f, -0.535f, -0.2));  //Traslacion de posicionamiento 
		model = glm::scale(model, glm::vec3(0.33f, 0.33f, 0.0f));  //Escalamiento de la figura
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));  //FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Generando arbolitos
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();

		//Arbol izquierdo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.25f, -3.0f)); //Traslacion de posicionamiento 
		model = glm::scale(model, glm::vec3(0.2f, 0.25f, 0.0f)); //Escalamiento de la figura
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); //FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();
		//Arbol derecho
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.25f, -3.0f)); //Traslacion de posicionamiento 
		model = glm::scale(model, glm::vec3(0.2f, 0.25f, 0.0f)); //Escalamiento de la figura 
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); //FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Troncos
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();

		//Tronco izquierdo
		model = glm::mat4(1.0);  
		model = glm::translate(model, glm::vec3(-0.75f, -0.6f, -3.0f)); //Traslacion de posicionamiento   
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.0f)); //Escalamiento de la figura  
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));  //FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		//Tronco derecho
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.6f, -3.0f)); //Traslacion de posicionamiento  
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.0f)); //Escalamiento de la figura 
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); //FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();


		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslaci�n
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACI�N //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/