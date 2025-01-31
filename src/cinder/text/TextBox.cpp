#include "cinder/text/TextBox.h"
#include "cinder/text/gl/TextureRenderer.h"

namespace cinder { namespace text {
/*
TextBox::TextBox()
	: TextBox( ci::vec2( cinder::text::GROW, cinder::text::GROW ) )
{}

TextBox::TextBox( ci::vec2 size, RendererRef renderer )
	: mFont( DefaultFont() )
	, mSize( size )
	, mColor( ci::Color::white() )
	, mRenderer( renderer )
	, mNeedsLayout( true )
	, mExternalAttributedString( false )
{
}

ci::ivec2 TextBox::getSize()
{
	layoutIfNeeded();
	ci::vec2 size = mLayout.measure();
	return ci::ivec2( ceil( size.x ), ceil( size.y ) );
}

TextBox& TextBox::setSize( ci::vec2 size )
{
	mSize = size;
	mNeedsLayout = true;
	return *this;
}

TextBox& TextBox::setFont( const Font& font )
{
	mFont = font;
	mNeedsLayout = true;
	return *this;
};

TextBox& TextBox::setText( std::string text )
{
	mText = text;
	mExternalAttributedString = false;
	mNeedsLayout = true;
	return *this;
}

TextBox& TextBox::setColor( ci::ColorA color )
{
	mColor = color;
	mNeedsLayout = true;
	return *this;
}

TextBox& TextBox::setAttrString( AttributedString attrString )
{
	mAttrString = attrString;
	mExternalAttributedString = true;
	mNeedsLayout = true;
	return *this;
}

TextBox& TextBox::setAlignment( Alignment alignment )
{
	mLayout.setAlignment( alignment );
	mNeedsLayout = true;
	return *this;
}

TextBox& TextBox::layoutIfNeeded()
{
	if( mNeedsLayout ) {
		doLayout();
	}

	return *this;
}

TextBox& TextBox::doLayout()
{
	if( !mExternalAttributedString ) {
		mAttrString = AttributedString( mText, mFont, mColor );
	}

	mLayout.setSize( mSize );
	mLayout.calculateLayout( mAttrString );
	mRenderer->setLayout( mLayout );
	mNeedsLayout = false;

	return *this;
}

void TextBox::draw()
{
	layoutIfNeeded();
	mRenderer->draw();
}
*/
} } // namespace cinder::text
