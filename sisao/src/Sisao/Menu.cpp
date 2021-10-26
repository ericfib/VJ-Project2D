#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Menu.h"
#include "Game.h"


Menu::Menu() {
	instructions = nullptr;
	button = nullptr;
	background = nullptr;
	new Text();
}

Menu::~Menu() {
	if (instructions) delete instructions;
	if (title) delete button;
	if (background) delete background;
}

void Menu::initTitle(ShaderProgram& texProgram) {
	tx_prog = texProgram;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(640.f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	background = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);
	tex_bg.loadFromFile("images/desert.png", TEXTURE_PIXEL_FORMAT_RGB);
	tex_bg.setMagFilter(GL_NEAREST);
	title.init("fonts/ARCADECLASSIC.ttf");
	
}

void Menu::initInstructions(ShaderProgram& texProgram) {

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
	
	modelview = glm::mat4(1.0f);
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tx_prog.setUniform2f("texCoordDispl", 0.f, 0.f);

	tx_prog.setUniformMatrix4f("modelview", modelview);
	background->render(tex_bg);
}

void Menu::renderInstructions() {

}


