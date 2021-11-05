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
	void updateTitle(int deltatime);
	void updateInstructions(int deltatime);
	void updateCredits(int deltatime);
	void updatebg(int deltatime, float cam);
	void renderTitle();
	void renderInstructions();
	void renderCredits();
	void render_bg(int valor_cam);

private:
	TexturedQuad *tex_quad_title[5], *tex_quad_instr[4], *tex_quad_cred[5];
	Texture tex_bg[5], tex_instr[5], tex_cred[5];
	ShaderProgram tx_prog;
	glm::mat4 projection;
	int currentTime;
	float const_cam, pos_bg;

};


#endif // _MENU_INCLUDE

