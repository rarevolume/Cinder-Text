#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/FileWatcher.h"
#include "cinder/Utilities.h"
#include "cinder/Log.h"

#include "cinder/text/FontManager.h"
#include "cinder/text/TextLayout.h"
#include "cinder/text/gl/TextureRenderer.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class RichTextApp : public App
{
	public:
		void setup() override;
		void mouseDown( MouseEvent event ) override;
		void update() override;
		void draw() override;

		//void updateLayout();
		void textFileUpdated( const ci::WatchEvent& event );

		//std::string mAttrText = "<span font-family=\"HelveticaRounded LT Std Blk\" font-style=\"Black\">This is system \ntext</span><span font-family=\"Source Serif Pro\" font-style=\"Regular\" font-size=\"20\" color=\"#ff0000\"><span font-size=\"20\">Ligatures like \"fi tf\"</span> This is a test of mixing<br/>font attributes like <i>italics</i>, <span color=\"#0000FF\">color</span> and <b>Bold!</b> </span><span font-family=\"Source Serif Pro\"> Here is some white serif text at <span font-size=\"30\">different</span><span font-size=\"10\"> sizes</span></span>";

		cinder::text::Layout mLayout;
		cinder::text::gl::TextureRenderer mRenderer;

		ci::Rectf mTextBox;

		// Base font, need to remove this, shouldn't be required
		std::shared_ptr<cinder::text::Font> mBaseFont;

		std::string testTextFilename = "text/richText.txt";

	struct Glyph {
		ci::vec2 uv0;
		ci::vec2 uv1;
		ci::vec2 size;
		ci::vec2 offset;
		float textureId;
		float padding0, padding1, padding2;
	};

	std::map<uint32_t,int>	mGlyphMap;
	ci::gl::FboRef mFbo;
};

void RichTextApp::setup()
{
	setWindowSize( 1920.f, 1080.f );

	mTextBox = ci::Rectf( 50, 50, 1024.f, 1024.f );

	mBaseFont = std::make_shared<cinder::text::Font>( loadAsset( ( "fonts/SourceSansPro/SourceSansPro-Regular.otf" ) ), 12 );

	// Load font faces to use with rich text
	cinder::text::FontManager::get()->loadFace( getAssetPath( "fonts/SourceSansPro/SourceSansPro-Regular.otf" ) );
	cinder::text::FontManager::get()->loadFace( getAssetPath( "fonts/SourceSansPro/SourceSansPro-It.otf" ) );
	cinder::text::FontManager::get()->loadFace( getAssetPath( "fonts/SourceSansPro/SourceSansPro-Bold.otf" ) );
	
	ci::gl::Fbo::Format fboFormat;
	ci::gl::Texture::Format texFormat;
	texFormat.setMagFilter( GL_NEAREST );
	texFormat.setMinFilter( GL_LINEAR );
	texFormat.enableMipmapping( true );
	fboFormat.setSamples( 8 );
	fboFormat.setColorTextureFormat( texFormat );
 	mFbo = ci::gl::Fbo::create(  mTextBox.getWidth(), mTextBox.getHeight(), fboFormat );

	ci::FileWatcher::instance().watch( ci::app::getAssetPath( testTextFilename ), std::bind( &RichTextApp::textFileUpdated, this, std::placeholders::_1 ) );
}

void RichTextApp::mouseDown( MouseEvent event )
{
}

void RichTextApp::update()
{
}

void RichTextApp::textFileUpdated( const ci::WatchEvent& watchEvent )
{
	// Layout text
	cinder::text::RichText richText( ci::loadString( ci::loadFile( watchEvent.getFile() ) ) );
	cinder::text::AttributedString attr( richText );
	

	//attr << cinder::text::AttributeFontFamily( "test" )
	//     << cinder::text::AttributeFontStyle( "italic" )
	//     << cinder::text::AttributeFontSize( 28 )
	//     << cinder::text::RichText( "HELLO!" );

	mLayout.setSize( mTextBox.getSize() );
	mLayout.calculateLayout( attr );
	//mRenderer.setLayout( mLayout );
}

void RichTextApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
	ci::gl::enableAlphaBlending();
	ci::gl::ScopedMatrices matrices;
	ci::gl::translate( mTextBox.getUpperLeft() );

	ci::gl::color( 0.25, 0.25, 0.25 );
	ci::gl::drawStrokedRect( ci::Rectf( ci::vec2( 0.f ), mTextBox.getSize() ) );

	ci::gl::color( 1, 1, 1 );
	//mRenderer.draw();

	{
		ci::gl::ScopedViewport viewportScope( 0, 0, mFbo->getWidth(), mFbo->getHeight() );
		ci::gl::ScopedMatrices matricesScope;
		ci::gl::setMatricesWindow( mFbo->getSize(), true );
 		// Draw text into FBO
		ci::gl::ScopedFramebuffer fboScoped( mFbo );
		ci::gl::clear( ci::ColorA( 0.0, 0.0, 0.0, 0.0 ) );
		mRenderer.render( mLayout );
	}

	gl::draw( mFbo->getColorTexture() );
}

CINDER_APP( RichTextApp, RendererGl )
