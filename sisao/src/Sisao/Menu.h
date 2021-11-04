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
	void updateTitle(int deltatime);
	void updateInstructions(int deltatime);
	void renderTitle();
	void renderInstructions();
	void render_bg();

private:
	TexturedQuad *tex_quad[5];
	Texture tex_bg[5];
	ShaderProgram tx_prog;
	glm::mat4 projection;
	int currentTime;

};


#endif // _MENU_INCLUDE

