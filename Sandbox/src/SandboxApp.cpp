#include<Twig.h>

class Sandbox : public Twig::Application
{
public:
	Sandbox(){}
	~Sandbox(){}	

};

Twig::Application* Twig::CreateApplication()
{
	return new Sandbox();
}