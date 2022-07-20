#include "ultpch.h"
#include "Application.h"
#include "GLFW/glfw3.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Ultra {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	void Application::Run()
	{
		while (m_Running && m_Window->IsRunning()) {
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		ULT_CORE_TRACE("{0}", e.ToString());
	}

	Application::~Application()
	{
		
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		//m_Running = false;
		return true;
	}
}