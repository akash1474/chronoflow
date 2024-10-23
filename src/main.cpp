#include "Application.h"
#include "pch.h"
#include "resources/AppIcon.embed"

int main(int argc, char* argv[])
{
	OpenGL::Timer timer;
	if (!Application::Init("ChronoFlow"))
		return -1;
	Application::SetupSystemSignalHandling();
	Application::SetApplicationIcon(AppIcon, IM_ARRAYSIZE(AppIcon));

	if (!Application::InitImGui())
		return -1;

	Application::InitFonts();

	if (argc > 1)
		Application::HandleArguments(GetCommandLineW());

	GL_WARN("BootUp Time: {}ms", timer.ElapsedMillis());
	while (!glfwWindowShouldClose(Application::GetGLFWwindow())) {
		Application::Draw();
	}

	Application::Destroy();
	return 0;
}

#ifdef _WIN32
	#ifdef GL_DIST
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	std::stringstream test(lpCmdLine);
	std::string segment;
	std::vector<std::string> seglist;

	while (std::getline(test, segment, ' ')) seglist.push_back(segment);

	return main((int)seglist.size(), &lpCmdLine);
}
	#endif
#endif
