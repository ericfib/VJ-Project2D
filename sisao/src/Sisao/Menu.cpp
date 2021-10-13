#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Menu.h"
#include "Game.h"


Menu::Menu() {
	title = nullptr;
	instructions = nullptr;
	button = nullptr;
	background = nullptr;
}

Menu::~Menu() {
	if (title) delete title;
	if (instructions) delete instructions;
	if (button) delete button;
	if (background) delete background;
}

void Menu::initTitle(ShaderProgram& texProgram) {
	tx_prog = texProgram;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(128.f, 128.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(9.f, 9.f) };

	background = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);
	tex_bg.loadFromFile("images/rocks.jpg", TEXTURE_PIXEL_FORMAT_RGB);
	tex_bg.setMagFilter(GL_NEAREST);
	//title->init("fonts/ARCADECLASSIC.txt");
}

void Menu::updateTitle(int deltatime) {
	if (Game::instance().getSpecialKey(GLUT_KEY_F5)) {
		Game::instance().changeScene(2);
	}
}

void Menu::updateInstructions(int deltatime) {

}

void Menu::renderTitle() {
	glm::mat4 modelview;

	tx_prog.use();
	tx_prog.setUniformMatrix4f("projection", projection);
	tx_prog.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::mat4(1.0f);
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tx_prog.setUniform2f("texCoordDispl", 0.f, 0.f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(128.f, 304.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	background->render(tex_bg);
}

void Menu::renderInstructions() {

}


