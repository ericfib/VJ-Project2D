#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Windows.h>
#include <MMSystem.h>
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

///////////////////// TITLE /////////////////////

void Menu::initTitle(ShaderProgram& texProgram) {
	tx_prog = texProgram;
	pos_bg = 0.f;
	pos_lives = 0.f;
	pos_levelnum = 0.f;
	currentTime = 0;
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

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(1920.f, 300.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(3.f, 1.f);
	tex_quad_title[4] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(150.f, 50.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_title[5] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(150.f, 52.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_title[6] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(200.f, 50.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_title[7] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(178.f, 40.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_title[8] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

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
	tex_bg[5].loadFromFile("images/menu/3lives.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[5].setMagFilter(GL_NEAREST);
	tex_bg[6].loadFromFile("images/menu/2lives.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[6].setMagFilter(GL_NEAREST);
	tex_bg[7].loadFromFile("images/menu/1lives.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[7].setMagFilter(GL_NEAREST);
	tex_bg[8].loadFromFile("images/menu/0lives.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[8].setMagFilter(GL_NEAREST);

	tex_bg[9].loadFromFile("images/menu/level1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[9].setMagFilter(GL_NEAREST);
	tex_bg[10].loadFromFile("images/menu/level2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[10].setMagFilter(GL_NEAREST);
	tex_bg[11].loadFromFile("images/menu/level3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[11].setMagFilter(GL_NEAREST);
	tex_bg[12].loadFromFile("images/menu/level4.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[12].setMagFilter(GL_NEAREST);
	tex_bg[13].loadFromFile("images/menu/level5.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[13].setMagFilter(GL_NEAREST);

	tex_bg[14].loadFromFile("images/menu/game_over.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[14].setMagFilter(GL_NEAREST);
	tex_bg[15].loadFromFile("images/menu/try_again.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[15].setMagFilter(GL_NEAREST);

	tex_bg[16].loadFromFile("images/menu/instr/bg_black.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[16].setMagFilter(GL_NEAREST);

	tex_bg[17].loadFromFile("images/menu/show_controls.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_bg[17].setMagFilter(GL_NEAREST);
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


	modelview = glm::translate(modelview, glm::vec3(192.f, 330.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(-192.f, -64.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_title[2]->render(tex_bg[2]);

	modelview = glm::translate(modelview, glm::vec3(225.f, 360.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(-192.f, -330.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_title[8]->render(tex_bg[17]);
}

///////////////////// INSTRUCTIONS /////////////////////

void Menu::initInstructions(ShaderProgram& texProgram) {
	tx_prog = texProgram;
	currentTime = 0;

	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(640.f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	tex_quad_instr[0] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);
	
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(250.f, 201.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_instr[1] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);
	
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(150.f, 40.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_instr[2] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(50.f, 50.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_instr[3] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);
	
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(150.f, 50.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_instr[4] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(50.f, 30.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_instr[5] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(180.f, 100.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_instr[6] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	tex_instr[0].loadFromFile("images/menu/instr/bg_black.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_instr[0].setMagFilter(GL_NEAREST);
	tex_instr[1].loadFromFile("images/menu/instr/keys_W1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_instr[1].setMagFilter(GL_NEAREST);
	tex_instr[2].loadFromFile("images/menu/instr/mov.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_instr[2].setMagFilter(GL_NEAREST);
	tex_instr[3].loadFromFile("images/menu/instr/GW.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_instr[3].setMagFilter(GL_NEAREST);
	tex_instr[4].loadFromFile("images/menu/instr/godmode.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_instr[4].setMagFilter(GL_NEAREST);
	tex_instr[5].loadFromFile("images/menu/instr/back.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_instr[5].setMagFilter(GL_NEAREST);
	tex_instr[6].loadFromFile("images/menu/instr/gdm_textos.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_instr[6].setMagFilter(GL_NEAREST);
}

void Menu::renderInstructions(int valor_cam) {
	glm::mat4 modelview;

	modelview = glm::mat4(1.0f);
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tx_prog.setUniform2f("texCoordDispl", 0.f, 0.f);

	modelview = glm::translate(modelview, glm::vec3(0.f, 0.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_instr[0]->render(tex_instr[0]);

	modelview = glm::translate(modelview, glm::vec3(85.f, 85.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_instr[1]->render(tex_instr[1]);

	modelview = glm::translate(modelview, glm::vec3(250.f, 80.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_instr[2]->render(tex_instr[2]);

	modelview = glm::translate(modelview, glm::vec3(-150.f, 120.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_instr[3]->render(tex_instr[3]);

	modelview = glm::translate(modelview, glm::vec3(150.f, 0.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_instr[4]->render(tex_instr[4]);

	modelview = glm::translate(modelview, glm::vec3(40.f, 40.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_instr[6]->render(tex_instr[6]);

	modelview = glm::translate(modelview, glm::vec3(-360.f, -310.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_instr[5]->render(tex_instr[5]);

}

///////////////////// CREDITS /////////////////////

void Menu::initCredits(ShaderProgram& texProgram) {
	tx_prog = texProgram;
	currentTime = 0;

	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(640.f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	tex_quad_cred[0] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(256.f, 116.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_cred[1] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(200.f, 100.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_cred[2] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(300.f, 60.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_cred[3] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(200.f, 50.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	tex_quad_cred[4] = TexturedQuad::createTexturedQuad(geom, texCoords, tx_prog);

	tex_cred[0].loadFromFile("images/menu/desert.png", TEXTURE_PIXEL_FORMAT_RGB);
	tex_cred[0].setMagFilter(GL_NEAREST);
	tex_cred[1].loadFromFile("images/menu/title.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_cred[1].setMagFilter(GL_NEAREST);
	tex_cred[2].loadFromFile("images/menu/cred/credits_devs.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_cred[2].setMagFilter(GL_NEAREST);
	tex_cred[3].loadFromFile("images/menu/cred/credits_ty.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_cred[3].setMagFilter(GL_NEAREST);
	tex_cred[4].loadFromFile("images/menu/cred/credits_playagain.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex_cred[4].setMagFilter(GL_NEAREST);

}


void Menu::updateCredits(int deltatime) {
	currentTime += deltatime;
}


void Menu::renderCredits() {
	glm::mat4 modelview;

	modelview = glm::mat4(1.0f);
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tx_prog.setUniform2f("texCoordDispl", 0.f, 0.f);

	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_cred[0]->render(tex_cred[0]);

	modelview = glm::translate(modelview, glm::vec3(192.f, 64.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(0.f, (sin(currentTime / 1000.f) * 50), 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_cred[1]->render(tex_cred[1]);

	modelview = glm::translate(modelview, glm::vec3(215.f, 200.f, 0.f));
	//modelview = glm::translate(modelview, glm::vec3(0.f, sin(currentTime / 400.f) * 5, 0.f));
	modelview = glm::translate(modelview, glm::vec3(-192.f, -64.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_cred[2]->render(tex_cred[2]);

	modelview = glm::translate(modelview, glm::vec3(170.f, 300.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(-215.f, -200.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_cred[3]->render(tex_cred[3]);

	modelview = glm::translate(modelview, glm::vec3(220.f, 370.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(-170.f, -300.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_cred[4]->render(tex_cred[4]);

}


///////////////////// GAME OVER /////////////////////

void Menu::renderGameOver()
{
	glm::mat4 modelview;

	modelview = glm::mat4(1.0f);
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tx_prog.setUniform2f("texCoordDispl", 0.f, 0.f);

	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_title[0]->render(tex_instr[16]);

	modelview = glm::translate(modelview, glm::vec3(190.f, 100.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_title[1]->render(tex_bg[14]);

	modelview = glm::translate(modelview, glm::vec3(215.f, 320.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(-190.f, -100.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_title[7]->render(tex_bg[15]);


}

///////////////////// GAME_BG /////////////////////


void Menu::render_bg(int valor_cam) {
	glm::mat4 modelview;

	modelview = glm::mat4(1.0f);
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tx_prog.setUniform2f("texCoordDispl", 0.f, 0.f);

	
	modelview = glm::translate(modelview, glm::vec3(valor_cam, 0.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_title[3]->render(tex_bg[3]);



}

void Menu::updatebg(int deltatime, float valor_cam) {
	currentTime += deltatime;
	pos_bg += valor_cam;
}

///////////////////// GAME_WATER /////////////////////

void Menu::render_water() {
	glm::mat4 modelview;

	modelview = glm::mat4(1.0f);
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tx_prog.setUniform2f("texCoordDispl", 0.f, 0.f);

	modelview = glm::translate(modelview, glm::vec3(0.f, 220.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tex_quad_title[4]->renderTransparent(tex_bg[4]);

}

///////////////////// HEALTH_BAR /////////////////////

void Menu::render_lives(int numLives) {
	glm::mat4 modelview;

	modelview = glm::mat4(1.0f);
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tx_prog.setUniform2f("texCoordDispl", 0.f, 0.f);

	modelview = glm::translate(modelview, glm::vec3(pos_lives, 0.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	if (numLives == 3) tex_quad_title[5]->render(tex_bg[5]);
	else if (numLives == 2) tex_quad_title[5]->render(tex_bg[6]);
	else if (numLives == 1) tex_quad_title[5]->render(tex_bg[7]);
	else if (numLives == 0) tex_quad_title[5]->render(tex_bg[8]);
}

void Menu::setPositions(float pos)
{
	pos_lives = pos;
	pos_levelnum = pos;
}


///////////////////// LEVEL NUMBER /////////////////////

void Menu::render_numlevel(int currentLevel)
{
	glm::mat4 modelview;

	modelview = glm::mat4(1.0f);
	tx_prog.setUniformMatrix4f("modelview", modelview);
	tx_prog.setUniform2f("texCoordDispl", 0.f, 0.f);

	modelview = glm::translate(modelview, glm::vec3(pos_levelnum, 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(500.f, 0.f, 0.f));
	tx_prog.setUniformMatrix4f("modelview", modelview);
	if (currentLevel == 1) tex_quad_title[6]->render(tex_bg[9]);
	else if (currentLevel == 2) tex_quad_title[6]->render(tex_bg[10]);
	else if (currentLevel == 3) tex_quad_title[6]->render(tex_bg[11]);
	else if (currentLevel == 4) tex_quad_title[6]->render(tex_bg[12]);
	else if (currentLevel == 5) tex_quad_title[6]->render(tex_bg[13]);
}

void Menu::updatePositions(int deltatime, float cam) {
	pos_lives += cam;
	pos_levelnum += cam;
}