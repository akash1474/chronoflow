#include "GLFW/glfw3.h"
#include <future>
#include "imgui.h"


class Application
{
private:
	GLFWwindow* mWindow{0};
	int width;
	int height;


public:
	Application(const Application&) = delete;
	~Application() {}

	static Application& Get()
	{
		static Application instance;
		return instance;
	}

	static void Draw();
	static bool Init(std::string appName,int width,int height);
	static bool InitImGui();
	static void InitFonts();
	static void SetApplicationIcon(unsigned char* img, int length);
	static void CenterWindow();
	void BackupDataBeforeCrash(); // Unimplemented still working but making a commit
	ImVec2 GetSize(){return ImVec2{(float)Get().width,(float)Get().height};}
	void SetSize(int width,int height){Get().width=width;Get().height=height;}

	static void HandleCrash(int signal);
	static void SetupSystemSignalHandling();

	// Update TitleBar Color based on the width and current UserInterface/Page
	static void UpdateTitleBarColor();

	static void Destroy();
	static void HandleArguments(std::wstring args);
	static GLFWwindow* GetGLFWwindow() { return Get().mWindow; }


private:
	Application() {};
};