#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Menu.h"
#include "Game.h"


Menu::Menu() {

	for (int i = 0; i < 2; i++) {
		tex_quad_title[i] = nullptr;
		tex_quad_cred[i] = nullptr;
		tex_quad_instr[i] = nullptr;
	}
}

Menu::~Menu() {
	for (int i = 0; i < 2; i++) {
		if (tex_quad_title[i]) delete tex_quad_title[i];
		if (tex_quad_cred[i]) delete tex_quad_cred[i];
		if (tex_quad_instr[i]) delete tex_quad_instr[i];
	}
}

void Menu::initTitle(ShaderProgram& texProgram) {
	tx_prog = texProgram;
	pos_bg = 0.f;
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(640.f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	tex_quad_title[0] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(256.f, 116.f);
	texCoords[0] = glm::vec2(0.f,0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_title[1] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(256.f, 32.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_title[2] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(1920.f, 480.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(3.f, 1.f);
	tex_quad_title[3] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(640.f, 240.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_title[4] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	tex_bg[0].loadFromFile("images/menu/desert.png", TEXTURE_PIXEL_FORMAT_RGB);
	tex_bg[0].setMagFilter(GL_NEAREST);
	tex_bg[1].loadFromFile("images/menu/title.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[1].setMagFilter(GL_NEAREST);
	tex_bg[2].loadFromFile("images/menu/press_to_play.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[2].setMagFilter(GL_NEAREST);
	tex_bg[3].loadFromFile("images/menu/bg_31.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[3].setMagFilter(GL_NEAREST);
	tex_bg[4].loadFromFile("images/menu/water.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[4].setMagFilter(GL_NEAREST);
}

void Menu::initInstructions(ShaderProgram& texProgram) {

}

void Menu::initCredits(ShaderProgram& texProgram) {

}

void Menu::updateTitle(int deltatime) {
	if (Game::instance().getKey(32)) {
		Game::instance().changeScene(2);
	}
}

void Menu::updateInstructions(int deltatime) {
	currentTime = deltatime;
}

void Menu::updateCredits(int deltatime) {
	currentTime = deltatime;
}

void Menu::updatebg(int deltatime, float valor_cam) {
	currentTime += deltatime;
	pos_bg += valor_cam;
}

void Menu::renderTitle() {
	glm::mat4 modelview;

	modelview = glm::mat4(1.0f);
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tx_prog.setUniform2f("texCoordDispl", 0.f, 0.f);

	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_title[0]->render(tex_bg[0]);

	tx_prog.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(modelview, glm::vec3(192.f, 64.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_title[1]->render(tex_bg[1]);


	modelview = glm::translate(modelview, glm::vec3(192.f, 400.f, 0.f));
	//modelview = glm::scale(modelview, glm::vec3(sin((currentTime/500.f) / 2 * 0.75f) + 0.75f / 2 + 0.25f, sin((currentTime / 500.f) / 2 * 0.75f) + 0.75f / 2 + 0.25f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(-192.f, -64.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_title[2]->render(tex_bg[2]);
}

void Menu::renderInstructions() {

}

void Menu::renderCredits() {

}


void Menu::render_bg(int valor_cam) {
	glm::mat4 modelview;

	modelview = glm::mat4(1.0f);
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tx_prog.setUniform2f("texCoordDispl", 0.f, 0.f);

	
	modelview = glm::translate(modelview, glm::vec3((valor_cam, 0.f, 0.f)));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_title[3]->render(tex_bg[3]);

}