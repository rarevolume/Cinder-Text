#pragma once

#include <unordered_map>

#include "cinder/gl/Texture.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/Fbo.h"

#include "cinder/text/TextLayout.h"
#include "cinder/text/TextRenderer.h"

namespace cinder { namespace text { namespace gl {

class TextureRenderer : public cinder::text::Renderer {
  public:
	TextureRenderer();

	//void draw( const std::string& text, const ci::vec2& size = ci::vec2( 0 ) ) override;
	//void draw( const std::string& text, const Font& font, const ci::vec2 size = ci::vec2( 0 ) ) override;
	void draw() override;
	void setLayout( const cinder::text::Layout& layout ) override;
	void setOffset( ci::vec2 offset ) { mOffset = offset; }

	static void loadFont( const Font& font );
	static void unloadFont( const Font& font );

	ci::gl::TextureRef getTexture();

  protected:
	// Font + Glyph Caching (shared between all instances)
	typedef struct {
		ci::gl::Texture3dRef texArray;
		unsigned int layer;
		ci::vec2 subTexSize;
		ci::vec2 subTexOffset;
	} GlyphCache;

	typedef struct {
		std::map<uint32_t, GlyphCache > glyphs;
	} FontCache;

  private:
	// Texture (FBO) caching
	ci::vec2 mOffset; // amount to offset texture in FBO
	void renderToFbo();
	void allocateFbo( int size );
	ci::gl::FboRef mFbo;

	ci::gl::BatchRef mBatch;

	FontCache& getCacheForFont( const Font& font );
	static void cacheFont( const Font& font );
	static void uncacheFont( const Font& font );

	static std::unordered_map<Font, FontCache> fontCache;
};

} } } // namespace cinder::text::gl
