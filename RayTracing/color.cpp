//Anthony Tyrrell
//Oregon State University CS 551 
//Final Project -> RayTrace engine
//5/21/2016
#include "color.h"

using namespace COLOR;

namespace COLOR {

	Color::Color() {
		this->r = 0.0f;
		this->g = 0.0f;
		this->b = 0.0f;
		this->a = 0.0f;
	}

	Color::Color(float r, float g, float b, float a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	
	Color::Color(int r, int g, int b, int a) {
		this->r = ClampZeroOne( r / 255.0f);
		this->g = ClampZeroOne( g / 255.0f);
		this->b = ClampZeroOne( b / 255.0f);
		this->a = ClampZeroOne( a / 255.0f);
	}

	Color::Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
		this->r = ClampZeroOne( r / 255.0f);
		this->g = ClampZeroOne( g / 255.0f);
		this->b = ClampZeroOne( b / 255.0f);
		this->a = ClampZeroOne( a / 255.0f);
	}
		
	void Color::Clamp() {
		::Clamp(this->r);
		::Clamp(this->g);
		::Clamp(this->b);
		::Clamp(this->a);
	}

	void Clamp(float& v) {
		if(v > 1.0) v = 1.0;
		if(v < 0.0) v = 0.0;
	}	

	float ClampZeroOne(float n) {
		if (n < 0.0) return 0.0f;
		if (n > 1.0) return 1.0f;
		return n;
	}

	int ClampTwoFiveFive(int n) {
		if (n < 0) return 0;
		if (n > 255) return 255;
		return n;
	}

	unsigned int ConvertColor (Color color) {
		return CreateColor((int) (ClampZeroOne(color.r) * 255.0),
						   (int) (ClampZeroOne(color.g) * 255.0),
						   (int) (ClampZeroOne(color.b) * 255.0),
						   (int) (ClampZeroOne(color.a) * 255.0));
	}

	Color ConvertColor(unsigned int pixel) {
		unsigned int r, g, b, a;
		ExtractColor(pixel, r, g, b, a);
		Color result;
		result.r = ClampTwoFiveFive(r) / 255.0f;
		result.g = ClampTwoFiveFive(g) / 255.0f;
		result.b = ClampTwoFiveFive(b) / 255.0f;
		result.a = ClampTwoFiveFive(a) / 255.0f;
		return result;
	}

	Color ConvertColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
			Color result;
			result.r = ClampZeroOne(ClampTwoFiveFive(r) / 255.0f);
			result.g = ClampZeroOne(ClampTwoFiveFive(g) / 255.0f);
			result.b = ClampZeroOne(ClampTwoFiveFive(b) / 255.0f);
			result.a = ClampZeroOne(ClampTwoFiveFive(a) / 255.0f);

			return result;
	}

	void ConvertColor(Color color, unsigned int& r, unsigned int& g, unsigned int& b, unsigned int& a) {
		r = (unsigned int)(ClampTwoFiveFive(color.r) * 255.0f);
		g = (unsigned int)(ClampTwoFiveFive(color.g) * 255.0f);
		b = (unsigned int)(ClampTwoFiveFive(color.b) * 255.0f);
		a = (unsigned int)(ClampTwoFiveFive(color.a) * 255.0f);
	}

	void ExtractColor(unsigned int pixel, unsigned int& r, unsigned int& g, unsigned int& b, unsigned int& a){
		a = (pixel & 0xFF000000) >> 24;
		b = (pixel & 0x00FF0000) >> 16;
		g = (pixel & 0x0000FF00) >> 8;
		r = (pixel & 0x000000FF);
	}

	unsigned int CreateColor(int r, int g, int b, int a){
		return (a << 24) | (b << 16) | (g << 8) | r;
	}

	unsigned int GetPixel (int* video, int x, int y, int w, int h){
		if(x < 0 || x >= w) return 0;
		if(y < 0 || y >= h) return 0;
		return video[y * w + x];
	}

	Color operator*(float f, const Color &c) {
		Color result;
		
		result.r = f * c.r;
		result.g = f * c.g;
		result.b = f * c.b;
		result.a = f * c.a;

		result.r = result.r;
		result.g = result.g;
		result.b = result.b;
		result.a = result.a;
		
		return result;
	}

	Color Color::operator*(const Color &c) const {
		Color result = *this;
		
		result.r *= c.r;
		result.g *= c.g;
		result.b *= c.b;
		result.a *= c.a;
		
		result.r = result.r;
		result.g = result.g;
		result.b = result.b;
		result.a = result.a;
		
		return result;
	}

	Color Color::operator*(float f) const {
		Color result = *this;
		
		result.r *= f;
		result.g *= f;
		result.b *= f;
		result.a *= f;

		result.r = result.r;
		result.g = result.g;
		result.b = result.b;
		result.a = result.a;
		
		return result;
	}

	Color Color::operator+(const Color &c) const {
		Color result = *this;
		
		result.r += c.r;
		result.g += c.g;
		result.b += c.b;
		result.a += c.a;

		result.r = result.r;
		result.g = result.g;
		result.b = result.b;
		result.a = result.a;
		
		return result;
	}

	void Color::operator+=(const Color &c) {
		this->r = c.r;
		this->g = c.g;
		this->b = c.b;
		this->a = c.a;

		this->r	= this->r;
		this->g	= this->g;
		this->b	= this->b;
		this->a	= this->a;
	}

	Color Color::operator/(float f) const {
		Color result = *this;
		
		result.r /= f;
		result.g /= f;
		result.b /= f;
		result.a /= f;

		result.r = result.r;
		result.g = result.g;
		result.b = result.b;
		result.a = result.a;

		return result;
	}

	Color FromIntARGB(int pixel) {
		Color result;
		result.a = (((unsigned int) pixel) >> 24) / 255.0f;
		result.r = ((((unsigned int) pixel) << 8) >> 24)/ 255.0f;
		result.g = ((((unsigned int) pixel) << 16) >> 24) / 255.0f;
		result.b = ((((unsigned int) pixel) << 24) >> 24) / 255.0f;
		return result;
	}

	void ToonRamp(float &z) {
		if(z > 0.75f) z = 1.0f;
		else if (z > 0.4f) z = 0.65f;
		else if (z > 0.1f) z = 0.2f;
		else z = 0.0f;
	}
}