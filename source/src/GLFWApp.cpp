#include "../include/pch.h"

#include "../include/Resources/Application.h"
int main()
{
	Resources::Application app("openGl", 800, 600);
	app.Run();
	return 0;
}