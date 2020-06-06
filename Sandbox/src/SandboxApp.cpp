#include<Twig.h>

class ExampleLayer : public Twig::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		TWIG_INFO("ExampleLayer::Update");
	}

	void OnEvent(Twig::Event& event) override
	{
		TWIG_TRACE("{0}", event);
	}
};

class Sandbox : public Twig::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Twig::ImGuiLayer());
	}
	~Sandbox(){}	
};

Twig::Application* Twig::CreateApplication()
{
	return new Sandbox();
}