#define STB_IMAGE_IMPLEMENTATION

#include <iomanip>

#include "camera.h"
#include "shader.h"
#include "window.h"

#include "objectList.h"
#include "sphereList.h"
#include "prismList.h"

int width = 1200;
int height = 800;

int main()
{
	//	Create window
	Window window(width, height);
	double time;

	std::vector<glm::vec3> positions = {
		glm::vec3(0.0f,  0.0f,  -5.0f),
		glm::vec3(0.0f,  0.0f, 0.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -6.3f),
		glm::vec3(5.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  -5.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(0.0f,  1.0f, -6.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-3.3f,  1.0f, -5.5f)
	};

	std::vector<glm::mat4> models;
	for (int i = 0; i < positions.size(); i++)
	{
		models.push_back(glm::translate(glm::mat4(1.0f), positions[i]));
		if (i >= positions.size() - 3)
		{
			models[i] = glm::scale(models[i], glm::vec3(0.2f));
		}
	}

	float vertices[] = {
		// Bottom face
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		// Front face
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		// Left face
		-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
		// Right face
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 // Bottom face          
		 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 // Top face
		 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	};


	//==================	LIGHT
	Shader lightCube("shaders/vertex.glsl", "shaders/fragmentLight.glsl");

	lightCube.addBufferObject(vertices, 36, 6);

	lightCube.addLayout(0, 3, 0);
	//==================

	std::vector<Light> lights;

	lights.push_back({
		glm::vec3(0.3f, 0.3f, 1.0f),
		positions[7],
		10.0f
		});

	lights.push_back({
		glm::vec3(1.0f, 0.3f, 0.3f),
		positions[8],
		10.0f
		});

	lights.push_back({
		glm::vec3(1.0f, 1.0f, 1.0f),
		positions[9],
		20.0f
		});

	//==================	COLOR CUBES

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	//	=== EVENT LOOP ===
	Camera camera(time, width, height, window.getInput(), 0.1);

	SphereList spheres = SphereList("shaders/vertex.glsl", "shaders/fragment.glsl", camera, lights);
	spheres.addSphere(glm::vec3(0, 0, -3), 1, glm::vec3(1));
	spheres[0].scale(glm::vec3(0.1));

	PrismList cubes = PrismList("shaders/vertex.glsl", "shaders/fragment.glsl", camera, lights);
	for (int i = 0; i < positions.size() - 3; i++)
	{
		cubes.addPrism(positions[i], glm::vec3(1), glm::vec3(0.4, 0.6, 0.4));
	}
	cubes[5].scale(glm::vec3(30, 0.1, 30));

	glfwSetTime(0);
	int k = 0;
	double fps = 0;
	while (!glfwWindowShouldClose(window.window_))
	{
		time = glfwGetTime();
		glfwSetTime(0);

		if (k == 500)
		{
			std::cout << fps/500 << " fps\n";
			fps = 0;
			k = 0;
		}
		fps += 1 / time;
		k++;


		camera.adjust(window.window_);

		window.input();
		window.mouseInput(camera);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.refresh();
	
		spheres.draw();

		cubes.draw();

		lightCube.use();
		for (int i = models.size() - 3; i < models.size(); i++)
		{
			//	- FRAGMENT -
			lightCube.uniformVec3("uColor", lights[i - 7].color);

			//	- VERTEX -
			lightCube.uniformMat4Ptr("uModel", glm::value_ptr(models[i]));
			lightCube.uniformMat4Ptr("uView", glm::value_ptr(camera.getView()));
			lightCube.uniformMat4Ptr("uProjection", camera.getProjection());

			lightCube.draw();
		}


		glfwSwapBuffers(window.window_);
		glfwPollEvents();
	}

	return 0;
}
