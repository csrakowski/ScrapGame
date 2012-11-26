#ifndef CHRIS_VECTOR_H
#define CHRIS_VECTOR_H

/*
	Christiaan Rakowski
	Two different 2 dimensional vector classes
	One Polar and one Cartesian
*/

#include "math.h"

// PI value taken from the Windows Calculator, Vista Edition
#ifndef PI
#define PI 3.1415926535897932384626433832795f
#endif

#ifndef RAD
#define RAD ( PI / 180 )
#endif

namespace Chris
{

class Vector
{
public:
	// Constructors
	Vector(): m_Angle( 90.0f ), m_Speed( 1.0f ) {};
	Vector( float a_Angle, float a_Speed ): m_Angle( a_Angle ), m_Speed( a_Speed ) {};
	~Vector() {};

	// Methods
	inline float UpdateX() { return ( sinf( m_Angle*RAD ) * m_Speed ); }
	inline float UpdateY() { return ( cosf( m_Angle*RAD ) * m_Speed ); }	

	// Member Data
	float m_Angle;
	float m_Speed;

}; // Vector Class


class Vector2D
{
public:
	// Constructors
	Vector2D(): X( 0.0f ), 	Y( 0.0f ) {};
	Vector2D( float a_X, float a_Y ): X( a_X ), Y( a_Y ) {};
	Vector2D( float a_Scalar ):	X( a_Scalar ), Y( a_Scalar ) {};
	Vector2D( Vector2D*	a_Vec ):	X( a_Vec->X ), Y( a_Vec->Y )  {};
	Vector2D( Vector2D&	a_Vec ):	X( a_Vec.X ), Y( a_Vec.Y )  {};
	~Vector2D() {};

	// Set Methods
	inline void Set( float a_X, float a_Y) { X = a_X;				Y = a_Y;			}
	inline void Set( float a_Scalar )		{ X = a_Scalar;		Y = a_Scalar;		}
	inline void Set( Vector2D*	a_Vec )	{ X = a_Vec->X;	Y = a_Vec->Y;	}
	inline void Set( Vector2D		a_Vec )	{ X = a_Vec.X;		Y = a_Vec.Y;		}

	//  Get Methods
	inline Vector2D Get() { return Vector2D( X, Y ); }
	//inline Vector2D* Get() { return this; }

	// Calculation Methods
	inline bool Equals(Vector2D* a_Vec)	{ return ( ( X == a_Vec->X )	&& ( Y == a_Vec->Y ) )	? true : false; }
	inline bool Equals(Vector2D a_Vec)		{ return ( ( X == a_Vec.X )		&& ( Y == a_Vec.Y ) )	? true : false; }
	inline bool Equals(float a_Scalar)			{ return ( ( X == a_Scalar )	&& ( Y == a_Scalar )	)	? true : false; }

	inline float Length()			{ return ( sqrtf(		(X*X) + (Y*Y) ) );	}
	inline float SqrLength()	{ return (				(X*X) +	 (Y*Y) );	}

	inline float Dot( Vector2D* a_Vec )	{ return ( ( X*a_Vec->X ) + ( Y*a_Vec->Y ) ); }
	inline float Dot( Vector2D		a_Vec )	{ return ( ( X*a_Vec.X ) +	 ( Y*a_Vec.Y ) );	}

	// Will look at this later
	//inline Vector3D Cross( Vector3D* a_Vec )		{ return ( Vector3D( ( Y*a_Vec->Z -Z*a_Vec->Y ),	( Z*a_Vec->X -	X*a_Vec->Z ),	( X*a_Vec->Y -	Y*a_Vec->X	) ) ); }
	//inline Vector3D Cross( Vector3D a_Vec )		{ return ( Vector3D( ( Y*a_Vec.Z -	Z*a_Vec.Y ),		( Z*a_Vec.X -	X*a_Vec.Z ),		( X*a_Vec.Y -	Y*a_Vec.X		) ) ); }

	inline void Scale( int a_Scalar )	{	X*=( a_Scalar ); Y*=( a_Scalar ); }
	inline void ScaleX( int a_Scalar )	{	X*=( a_Scalar ); }
	inline void ScaleY( int a_Scalar )	{	Y*=( a_Scalar ); }

	inline void Invert()	{ X*=(-1); Y*=(-1); }
	inline void InvertX(){ X*=(-1); }
	inline void InvertY(){ Y*=(-1); }

	inline void Normalize() { float a_Length = Length(); X /= a_Length; Y /= a_Length; }

	// Operators
	void operator += ( const float a_Scalar )			{ X += a_Scalar;		Y += a_Scalar;		}
	void operator += ( const Vector2D a_Vector )	{ X += a_Vector.X;		Y += a_Vector.Y;	}
	void operator += ( Vector2D* a_Vector )			{ X += a_Vector->X;	Y += a_Vector->Y;	}

	void operator -= ( const float a_Scalar )			{ X -= a_Scalar;			Y -= a_Scalar;		}
	void operator -= ( const Vector2D a_Vector )	{ X -= a_Vector.X;		Y -= a_Vector.Y;	}
	void operator -= ( Vector2D* a_Vector )			{ X -= a_Vector->X;	Y -= a_Vector->Y;	}

	void operator *= ( const float a_Scalar )			{ X *= a_Scalar;		Y *= a_Scalar;		}
	void operator *= ( const Vector2D a_Vector )	{ X *= a_Vector.X;		Y *= a_Vector.Y;	}
	void operator *= ( Vector2D* a_Vector )			{ X *= a_Vector->X;	Y *= a_Vector->Y;	}

	void operator /= ( const float a_Scalar )			{ X /= a_Scalar;			Y /= a_Scalar;		}
	void operator /= ( const Vector2D a_Vector )	{ X /= a_Vector.X;		Y /= a_Vector.Y;	}
	void operator /= ( Vector2D* a_Vector )			{ X /= a_Vector->X;	Y /= a_Vector->Y;	}

	void operator = ( const float a_Scalar )			{ X = a_Scalar;			Y = a_Scalar;			}
	void operator = ( const Vector2D a_Vector )		{ X = a_Vector.X;		Y = a_Vector.Y;		}
	void operator = ( Vector2D* a_Vector )			{ X = a_Vector->X;	Y = a_Vector->Y;	}

	friend Vector2D operator + ( const Vector2D& a_Vector,  const float a_Scalar )				{ return Vector2D( a_Vector.X		+ a_Scalar,		a_Vector.Y		+ a_Scalar			);	} 
	friend Vector2D operator + ( const Vector2D& a_Vector1, const Vector2D& a_Vector2 )	{ return Vector2D( a_Vector1.X	+ a_Vector2.X,	a_Vector1.Y	+ a_Vector2.Y	);	}
	friend Vector2D operator + ( const Vector2D& a_Vector1, const Vector2D* a_Vector2 )	{ return Vector2D( a_Vector1.X	+ a_Vector2->X,a_Vector1.Y	+ a_Vector2->Y	);	}
	friend Vector2D operator + ( const Vector2D* a_Vector1, const Vector2D& a_Vector2 )	{ return Vector2D( a_Vector1->X + a_Vector2.X,	a_Vector1->Y+ a_Vector2.Y	);	}

	friend Vector2D operator - ( const Vector2D& a_Vector,  const float a_Scalar )				{ return Vector2D( a_Vector.X		- a_Scalar,			a_Vector.Y		- a_Scalar			);	}
	friend Vector2D operator - ( const Vector2D& a_Vector1, const Vector2D& a_Vector2 )		{ return Vector2D( a_Vector1.X	- a_Vector2.X,	a_Vector1.Y	- a_Vector2.Y		);	}
	friend Vector2D operator - ( const Vector2D& a_Vector1, const Vector2D* a_Vector2 )		{ return Vector2D( a_Vector1.X	- a_Vector2->X,	a_Vector1.Y	- a_Vector2->Y	);	}
	friend Vector2D operator - ( const Vector2D* a_Vector1, const Vector2D& a_Vector2 )		{ return Vector2D( a_Vector1->X - a_Vector2.X,	a_Vector1->Y	- a_Vector2.Y		);	}

	friend Vector2D operator * ( const Vector2D& a_Vector,  const float a_Scalar )				{ return Vector2D( a_Vector.X		* a_Scalar,		a_Vector.Y		* a_Scalar			);	}
	friend Vector2D operator * ( const Vector2D& a_Vector1, const Vector2D& a_Vector2 )	{ return Vector2D( a_Vector1.X	* a_Vector2.X,	a_Vector1.Y	* a_Vector2.Y	);	}
	friend Vector2D operator * ( const Vector2D& a_Vector1, const Vector2D* a_Vector2 )	{ return Vector2D( a_Vector1.X	* a_Vector2->X,a_Vector1.Y	* a_Vector2->Y );	}
	friend Vector2D operator * ( const Vector2D* a_Vector1, const Vector2D& a_Vector2 )	{ return Vector2D( a_Vector1->X * a_Vector2.X,	a_Vector1->Y* a_Vector2.Y	);	}

	friend Vector2D operator / ( const Vector2D& a_Vector,  const float a_Scalar )				{ return Vector2D( a_Vector.X		/ a_Scalar,			a_Vector.Y		/ a_Scalar			);	} 
	friend Vector2D operator / ( const Vector2D& a_Vector1, const Vector2D& a_Vector2 )		{ return Vector2D( a_Vector1.X	/ a_Vector2.X,	a_Vector1.Y	/ a_Vector2.Y		);	}
	friend Vector2D operator / ( const Vector2D& a_Vector1, const Vector2D* a_Vector2 )		{ return Vector2D( a_Vector1.X	/ a_Vector2->X,	a_Vector1.Y	/ a_Vector2->Y	);	}
	friend Vector2D operator / ( const Vector2D* a_Vector1, const Vector2D& a_Vector2 )		{ return Vector2D( a_Vector1->X / a_Vector2.X,	a_Vector1->Y/ a_Vector2.Y		);	}

	friend Vector2D operator == ( const Vector2D& a_Vector,	 const float a_Scalar )				{ return ( ( a_Vector.X == a_Scalar )			&& ( a_Vector.Y == a_Scalar ) )			? true : false; }
	friend Vector2D operator == ( const Vector2D& a_Vector1, const Vector2D& a_Vector2 )	{ return ( ( a_Vector1.X == a_Vector2.X )	&& ( a_Vector1.Y == a_Vector2.Y ) )	? true : false; }
	friend Vector2D operator == ( const Vector2D& a_Vector1, const Vector2D* a_Vector2 )	{ return ( ( a_Vector1.X == a_Vector2->X )	&& ( a_Vector1.Y == a_Vector2->Y ) )	? true : false; }
	friend Vector2D operator == ( const Vector2D* a_Vector1, const Vector2D& a_Vector2 )	{ return ( ( a_Vector1->X == a_Vector2.X )	&& ( a_Vector1->Y == a_Vector2.Y ) )	? true : false; }

	union
	{
		// float values for accurate calcualtions
		struct { float X, Y; };
		struct { float Abscissa, Ordinate; };	// Scientific Naming, added for completeness and those who like it
		struct { float U, V; };
		float Cell[2];

		// integer values for faster calculations and screen plotting when needed
		struct { int iX, iY; };
		struct { int iAbscissa, iOrdinate; };	
		struct { int iU, iV; };
		int iCell[2];
	};
}; // Vector2D Class
	
}; // Namespace Chris

#endif
