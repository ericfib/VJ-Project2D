#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include <string>
#include <glm/glm.hpp>
#include "TexturedQuad.h"
#include "ShaderProgram.h"



class Menu
{
public:
	Menu();
	~Menu();

	void initTitle(ShaderProgram& shaderProgram);
	void initInstructions(ShaderProgram& shaderProgram);
	void initCredits(ShaderProgram& shaderProgram);
	void updateCredits(int deltatime);
	void updatebg(int deltatime, float cam);
	void updatePositions(int deltatime, float cam);
	void renderTitle();
	void renderInstructions(int valor_cam);
	void renderCredits();
	void renderGameOver();
	void render_bg(int valor_cam);
	void render_water();
	void render_lives(int numLives);
	void render_numlevel(int currentLevel);

	void setPositions(float pos);

private:
	TexturedQuad *tex_quad_title[9], *tex_quad_instr[8], *tex_quad_cred[5];
	Texture tex_bg[18], tex_instr[8], tex_cred[8];
	ShaderProgram tx_prog;
	glm::mat4 projection;
	int currentTime;
	float const_cam, pos_bg, pos_cred, pos_lives, pos_levelnum;

};


#endif // _MENU_INCLUDE

