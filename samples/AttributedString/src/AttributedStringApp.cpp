#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class AttributedStringApp : public App
{
	public:
		void setup() override;
		void mouseDown( MouseEvent event ) override;
		void update() override;
		void draw() override;
};

void AttributedStringApp::setup()
{

}

void AttributedStringApp::mouseDown( MouseEvent event )
{
}

void AttributedStringApp::update()
{
}

void AttributedStringApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
}

CINDER_APP( AttributedStringApp, RendererGl )
