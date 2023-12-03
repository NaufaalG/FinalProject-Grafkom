#pragma once

#include "RenderEngine.h"
#include "Cube.h"
#include "Shader.h"
#include "Texture.h"

class Application :
    public RenderEngine
{
public:
    Application();
    ~Application();
private:
	Shader *shader;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	Texture *cubeDiffTex, *cubeSpecTex, *mejaDiffTex, *mejaSpecTex, *tanahDiffTex, *tanahSpecTex, *meja2DiffTex, *meja2SpecTex, *kursiDiffTex, *kursiSpecTex, *atapDiffTex, *atapSpecTex, *tiangDiffTex, *tiangSpecTex, *busaDiffTex, *busaSpecTex;
	Cube *cube;
	Cube* meja;
	Cube* tanah;
	Cube* meja2;
	Cube* kursi;
	Cube* atap;
	Cube* tiang;
	Cube* busa;
	float angle = 0;
	glm::vec3 viewPos;
	void setupPerspective();
	void setupCamera();
	void setupLighting(); 
	virtual void Init();
	virtual void DeInit(); 
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow* window);
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();
};

