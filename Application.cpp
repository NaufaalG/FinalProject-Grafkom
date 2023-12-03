#include "Application.h"

Application::Application()
{

}

Application::~Application()
{
}

void Application::InitCamera()
{
	posCamX = 0.0f;
	posCamY = 1.0f;
	posCamZ = 8.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.001f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void Application::setupPerspective()
{
	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	shader->setMat4("projection", projection);
}

void Application::setupCamera()
{
	// LookAt camera (position, target/direction, up)
	viewPos = glm::vec3(2, 0, 4);
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ) , glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	shader->setMat4("view", view);
}

void Application::setupLighting()
{
	// set lighting attributes
	glm::vec3 lightPos = glm::vec3( 0, 1, 0);
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", viewPos);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	shader->setVec3("lightColor", lightColor);
}

void Application::Init()
{
	// Build a lighting map shader
	shader = new Shader("texturedCube.vert", "texturedCube.frag");
	shader->Init();
	// Create cube diffuse texture and specular texture

	// stand
	cubeDiffTex = new Texture("WoodFlooringAshSuperWhite001_COL_2K.jpg");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("WoodFlooringAshSuperWhite001_COL_2K.jpg");
	cubeSpecTex->Init();

	//meja dalem
	mejaDiffTex = new Texture("MetalGalvanizedSteelWorn001_COL_2K_METALNESS.jpg");
	mejaDiffTex->Init();
	mejaSpecTex = new Texture("MetalGalvanizedSteelWorn001_COL_2K_METALNESS.jpg");
	mejaSpecTex->Init();

	//tanah
	tanahDiffTex = new Texture("GroundGrassGreen002_COL_2K.jpg");
	tanahDiffTex->Init();
	tanahSpecTex = new Texture("GroundGrassGreen002_BUMP_2K.jpg");
	tanahSpecTex->Init();

	//meja2
	meja2DiffTex = new Texture("StoneBricksSplitface001_COL_2K.jpg");
	meja2DiffTex->Init();
	meja2SpecTex = new Texture("StoneBricksSplitface001_DISP_2K.jpg");
	meja2SpecTex->Init();

	//kursi
	kursiDiffTex = new Texture("WickerWeavesBrownRattan001_COL_VAR1_2K.jpg");
	kursiDiffTex->Init();
	kursiSpecTex = new Texture("WickerWeavesBrownRattan001_BUMP_2K.jpg");
	kursiSpecTex->Init();

	//atap
	atapDiffTex = new Texture("WoodFlooringAshSuperWhite001_COL_2K.jpg");
	atapDiffTex->Init();
	atapSpecTex = new Texture("WoodFlooringAshSuperWhite001_COL_2K.jpg");
	atapSpecTex->Init();

	//tiang
	tiangDiffTex = new Texture("WickerWeavesBrownRattan001_COL_VAR1_2K.jpg");
	tiangDiffTex->Init();
	tiangSpecTex = new Texture("WickerWeavesBrownRattan001_BUMP_2K.jpg");
	tiangSpecTex->Init();

	//busa
	busaDiffTex = new Texture("WickerWeavesBrownRattan001_COL_VAR1_2K.jpg");
	busaDiffTex->Init();
	busaSpecTex = new Texture("WickerWeavesBrownRattan001_BUMP_2K.jpg");
	busaSpecTex->Init();


	// Create instance of cube
	cube = new Cube(shader, cubeDiffTex, cubeSpecTex);
	cube->Init();
	cube->SetScale(0.5f, 0.5f, 0.5f);

	//bikin meja 
	meja = new Cube(shader, mejaDiffTex, mejaSpecTex);
	meja->Init();
	meja->SetScale(0.5f, 0.3f, 0.5f);

	//bikin tanah 
	tanah = new Cube(shader, tanahDiffTex, tanahSpecTex);
	tanah->Init();
	tanah->SetScale(5, 0.5f, 30);

	//bikin meja2
	meja2 = new Cube(shader, meja2DiffTex, meja2SpecTex);
	meja2->Init();
	meja2->SetScale(2.0f, 1.0f, 2.0f);

	//bikin kursi
	kursi = new Cube(shader, kursiDiffTex, kursiSpecTex);
	kursi->Init();
	kursi->SetScale(2.0f, 0.5f, 0.5f);

	//bikin atap 
	atap = new Cube(shader, atapDiffTex, atapSpecTex);
	atap->Init();
	atap->SetScale(2,0.3f,4);

	//bikin tiang
	tiang = new Cube(shader, tiangDiffTex, tiangSpecTex);
	tiang->Init();
	tiang->SetScale(0.12,0.9,0.12);

	//busa
	busa = new Cube(shader, tiangDiffTex, tiangSpecTex);
	busa->Init();
	busa->SetScale(0.5, 0.2, 0.5);
	InitCamera();
	


	setupLighting();
}

void Application::DeInit()
{
	delete cube;
}

void Application::Update(double deltaTime)
{
	angle += (float)((deltaTime * 1.5f) / 1000);
	cube->SetRotation(angle, 0, 1, 0);
}

void Application::Render()
{
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// setup perspective 
	setupPerspective();
	// setup camera
	setupCamera();

	//stand
	for (int i = 0; i < 8; i++) {
		cube->SetPosition(-6, i - 1, 0);
		cube->Draw();
	}

	for (int i = 0; i < 8; i++) {
		cube->SetPosition(-6, i - 1, 6);
		cube->Draw();
	}

	for (int i = 0; i < 8; i++) {
		cube->SetPosition(2, i - 1, 0);
		cube->Draw();
	}

	for (int i = 0; i < 8; i++) {
		cube->SetPosition(2, i - 1, 6);
		cube->Draw();
	}

	for (int i = 0; i < 0; i++) {
		cube->SetPosition(1, i - 1, 6);
		cube->Draw();
	}

	for (int i = 0; i < 0; i++) {
		cube->SetPosition(0, i - 1, 6);
		cube->Draw();
	}

	for (int i = 0; i < 3; i++) {
		cube->SetPosition(-1, i - 1, 6);
		cube->Draw();
	}


	for (int i = 0; i < 3; i++) {
		cube->SetPosition(-2, i - 1, 6);
		cube->Draw();
	}

	for (int i = 0; i < 3; i++) {
		cube->SetPosition(-3, i - 1, 6);
		cube->Draw();
	}

	for (int i = 0; i < 3; i++) {
		cube->SetPosition(-4, i - 1, 6);
		cube->Draw();
	}

	for (int i = 0; i < 3; i++) {
		cube->SetPosition(-5, i - 1, 6);
		cube->Draw();
	}

	for (int i = 0; i < 7; i++) {
		cube->SetPosition(-5 + i,6, 6);
		cube->Draw();
	}

	for (int i = 0; i < 7; i++) {
		cube->SetPosition(2, -1, 0 + i );
		cube->Draw();
	}

	for (int i = 0; i < 7; i++) {
		cube->SetPosition(-6, -1, 0 + i);
		cube->Draw();
	}

	for (int i = 0; i < 8; i++) {
		cube->SetPosition(-6 + i, 6, 0);
		cube->Draw();
	}

	for (int i = 0; i < 8; i++) {
		cube->SetPosition(-6 + i, -1, 0);
		cube->Draw();
	}

	for (int i = 0; i < 9; i++) {
		cube->SetPosition(-6 + i, 6, 1);
		cube->Draw();
	}

	for (int i = 0; i < 9; i++) {
		cube->SetPosition(-6 + i, 6, 2);
		cube->Draw();
	}
	
	for (int i = 0; i < 9; i++) {
		cube->SetPosition(-6 + i, 6, 3);
		cube->Draw();
	}

	for (int i = 0; i < 9; i++) {
		cube->SetPosition(-6 + i, 6, 4);
		cube->Draw();
	}

	for (int i = 0; i < 9; i++) {
		cube->SetPosition(-6 + i, 6, 5);
		cube->Draw();
	}

	for (int i = 0; i < 9; i++) {
		cube->SetPosition(-6 + i, 0, 0);
		cube->Draw();
	}

	for (int i = 0; i < 9; i++) {
		cube->SetPosition(-6 + i, 1, 0);
		cube->Draw();
	}

	for (int i = 0; i < 9; i++) {
		cube->SetPosition(-6 + i, 2, 0);
		cube->Draw();
	}

	for (int i = 0; i < 9; i++) {
		cube->SetPosition(-6 + i, 3, 0);
		cube->Draw();
	}

	for (int i = 0; i < 9; i++) {
		cube->SetPosition(-6 + i, 4, 0);
		cube->Draw();
	}

	for (int i = 0; i < 9; i++) {
		cube->SetPosition(-6 + i, 5, 0);
		cube->Draw();
	}

	for (int i = 0; i < 7; i++) {
		cube->SetPosition(-6, 0, 0 + i);
		cube->Draw();
	}

	for (int i = 0; i < 7; i++) {
		cube->SetPosition(-6, 1, 0 + i);
		cube->Draw();
	}

	for (int i = 0; i < 7; i++) {
		cube->SetPosition(2, 0, 0 + i);
		cube->Draw();
	}

	for (int i = 0; i < 7; i++) {
		cube->SetPosition(2, 1, 0 + i);
		cube->Draw();
	}

	//meja
	for (int i = 0; i < 5; i++) {
		meja->SetPosition(-5, 1, 1 + i);
		meja->Draw();
	}

	for (int i = 0; i < 5; i++) {
		meja->SetPosition(3, 1, 1 + i);
		meja->Draw();
	}

	//tanah 
	for (int i = 0; i < 5; i++) {
		tanah->SetPosition(1 - i, -2 , 0);
		tanah->Draw();
	}

	//meja depan
	for (int i = 0; i < 1; i++) {
		meja2->SetPosition(-1 + i, -0.5f, 3);
		meja2->Draw();
	}

	//kursi
	for (int i = 0; i < 1; i++) {
		kursi->SetPosition(-1 + i, -1, 8.9f);
		kursi->Draw();
	}

	for (int i = 0; i < 1; i++) {
		kursi->SetPosition(-1 + i, -1, 7.9f);
		kursi->Draw();
	}

	for (int i = 0; i < 1; i++) {
		kursi->SetPosition(-1 + i, 0, 7.9f);
		kursi->Draw();
	}


	for (int i = 0; i < 1; i++) {
		kursi->SetPosition(-1 + i, -1, 15.1f);
		kursi->Draw();
	}

	for (int i = 0; i < 1; i++) {
		kursi->SetPosition(-1 + i, -1, 16.1f);
		kursi->Draw();
	}

	for (int i = 0; i < 1; i++) {
		kursi->SetPosition(-1 + i, 0, 16.1f);
		kursi->Draw();
	}

	//kursi dalem tiang dan busa
	for (int i = 0; i < 1; i++) {
		tiang->SetPosition(-4, 0 + i, 8);
		tiang->Draw();
	}
	for (int i = 0; i < 1; i++) {
		busa->SetPosition(-1.03, -3 + i, 1.83);
		busa->Draw();
	}

	for (int i = 0; i < 1; i++) {
		busa->SetPosition(-1.03, 2.8 + i, 1.83);
		busa->Draw();
	}


	//atap depan
	for (int i = 0; i < 3; i++) {
		atap->SetPosition(-1.42 + i, 9, 0.5);
		atap->Draw();
	}



	glDisable(GL_DEPTH_TEST);

}

void Application::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);
}



void Application::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Application::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Application::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}



int main(int argc, char** argv) {
	Application app = Application();
	app.Start("Cube Example", 
		800, 600, 
		false, 
		false);
}