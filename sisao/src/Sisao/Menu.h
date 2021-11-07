#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include <string>
#include <glm/glm.hpp>
#include "Text.h"
#include "ShaderProgram.h"



class Menu
{
public:
	Menu();
	~Menu();

	void initTitle(ShaderProgram& shaderProgram);
	void initInstructions(ShaderProgram& shaderProgram);
	void initCredits(ShaderProgram& shaderProgram);
	void updateInstructions(int deltatime, int previousState);
	void updateCredits(int deltatime);
	void updatebg(int deltatime, float cam);
	void renderTitle();
	void renderInstructions(int valor_cam);
	void renderCredits();
	void render_bg(int valor_cam);
	void render_water();

private:
	TexturedQuad *tex_quad_title[5], *tex_quad_instr[8], *tex_quad_cred[5];
	Texture tex_bg[5], tex_instr[8], tex_cred[8];
	ShaderProgram tx_prog;
	glm::mat4 projection;
	int currentTime;
	float const_cam, pos_bg, pos_cred;

};


#endif // _MENU_INCLUDE

