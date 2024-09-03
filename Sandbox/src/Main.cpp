#include <Borealis.hpp>
#include <Sandbox2D.hpp>
#include <Core/EntryPoint.hpp>

class Sandbox : public Borealis::ApplicationManager
{
public:
	Sandbox() : ApplicationManager("Sandbox App")
	{
#ifndef _DIST
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
		//PushLayer(new gameLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{


	}

};


Borealis::ApplicationManager* Borealis::CreateApplication()
{
	return new Sandbox();
}