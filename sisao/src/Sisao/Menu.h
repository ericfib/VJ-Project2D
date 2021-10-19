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

private:
	Text title, title2, *instructions, *button;
	TexturedQuad *background;
	Texture tex_bg;
	ShaderProgram tx_prog;
	glm::mat4 projection;

};


#endif // _MENU_INCLUDE

