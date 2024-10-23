#include "GLFW/glfw3.h"
#include <future>

class Application
{
private:
	GLFWwindow* mWindow{0};
	int width = 1100;
	int height = 650;

public:
	Application(const Application&) = delete;
	~Application() {}

	static Application& Get()
	{
		static Application instance;
		return instance;
	}

	static void Draw();
	static bool Init(std::string appName);
	static bool InitImGui();
	static void InitFonts();
	static void SetApplicationIcon(unsigned char* img, int length);
	void BackupDataBeforeCrash(); // Unimplemented still working but making a commit

	static void HandleCrash(int signal);
	static void SetupSystemSignalHandling();

	// Update TitleBar Color based on the width and current UserInterface/Page
	static void UpdateTitleBarColor();

	static void Destroy();
	static void HandleArguments(std::wstring args);
	static void CenterWindowOnScreen();
	static GLFWwindow* GetGLFWwindow() { return Get().mWindow; }


private:
	Application() {};
};