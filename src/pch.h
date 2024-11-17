#pragma once

#define GL_USE_OPENGL_LATEST


#include <algorithm>
#include <windows.h>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>
#include <map>
#include <mutex>
#include <random>
#include <sstream>
#include <stdexcept>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <string_view>
#include <codecvt>
#include <locale>
#include <cstdio>

// Extlib
#include "FontAwesome6.h"

#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <GL/gl.h>

#define TAGLIB_STATIC
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui.h"
#include "imgui_impl_glfw.h"
#ifdef GL_USE_OPENGL_LATEST 
	#include "imgui_impl_opengl3.h"
#else
	#include "imgui_impl_opengl2.h"
#endif

#include "imgui_internal.h"

#include "Log.h"
#include "Timer.h"

