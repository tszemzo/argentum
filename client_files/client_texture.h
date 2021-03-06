#ifndef _TEXTURE
#define _TEXTURE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

//Texture wrapper class
class LTexture {
	public:
		LTexture();

		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path, SDL_Renderer *gRenderer );

		bool loadFromRenderedText(SDL_Renderer *gRenderer, TTF_Font *gFont, std::string textureText, SDL_Color textColor);

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip=NULL, SDL_RendererFlip flip=SDL_FLIP_NONE);

		//Gets image dimensions
		int getWidth();
		int getHeight();

		LTexture(LTexture&& other);
        LTexture& operator=(LTexture&& other);

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};


#endif
