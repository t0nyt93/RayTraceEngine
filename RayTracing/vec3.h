#include <stdio.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <cmath>

#ifndef VEC3_H
#define VEC3_H

class Vec3
{
    //protected:
    public:
        float x, y, z;

    public:
        Vec3( float=0, float=0, float=0 );
        Vec3&   operator=( const Vec3& );
        Vec3    operator+( const Vec3& );
        Vec3    operator-( const Vec3& );       // binary -
	   Vec3	 operator*( float );
        Vec3    operator-( );                   // unary -
        Vec3    Cross( Vec3& );
        float   Dot( Vec3& );
	void	Export( float [3] );
        float   Length( );
        void    Print( char * = "", FILE * = stderr );
        Vec3    Unit( );

	friend class Mat4;
};


void		WhoAmI( char *, char * );

inline float
SQR( float f )
{
	return f * f;
}

#endif
