#pragma once


#include "ProgramRenderer.h"


class GameRenderer
{
public:
	GameRenderer(int windowW, int windowH);
	~GameRenderer();

	ProgramRenderer* addProgramRenderer(const char* pathVertex, const char* pathFragment);


	void render(glm::vec3& dirLight, glm::mat4& vp);

private:


	void createDepthMap();

	void createUniforms();



	void initRenderingDepth();

	void initRendering();






	int windowW;
	int windowH;



	std::vector<ProgramRenderer*> programRendererArray;

	Shader programDepth;

	GLuint depthFbo;
	GLuint depthMap;


	static int depthMapSize;


};

