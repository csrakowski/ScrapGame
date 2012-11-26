#ifndef	CHRIS_VECTOR3D_H
#define	CHRIS_VECTOR3D_H

/*
	A 3D Vector class, MA2 Week 3
	By Christiaan Rakowski,
	080327 - 1GA-2A
*/
#ifndef _INC_MATH
#include <math.h>
#endif

namespace Chris 
{

class Vector3D
{
public:
	// Constructors
	Vector3D(): X( 0.0f ), 	Y( 0.0f ), Z( 0.0f ) {};
	Vector3D( float a_X, float a_Y, float a_Z ): X( a_X ), Y( a_Y ), Z( a_Z ) {};
	Vector3D( float a_Scalar ):	X( a_Scalar ), Y( a_Scalar ), Z( a_Scalar )  {};
	Vector3D( Vector3D* a_Vec ):	X( a_Vec->X ), Y( a_Vec->Y ), Z( a_Vec->Z )  {};
	Vector3D( Vector3D& a_Vec ):	X( a_Vec.X ), Y( a_Vec.Y ), Z( a_Vec.Z )  {};
	~Vector3D() {};

	// Set Methods
	inline void Set( float a_X, float a_Y, float a_Z ) { X = a_X; Y = a_Y;	Z = a_Z;			}
	inline void Set( float a_Scalar )		{ X = a_Scalar;	Y = a_Scalar;		Z = a_Scalar;		}
	inline void Set( Vector3D* a_Vec )	{ X = a_Vec->X; Y = a_Vec->Y;	Z = a_Vec->Z;	}
	inline void Set( Vector3D& a_Vec )	{ X = a_Vec.X;	Y = a_Vec.Y;		Z = a_Vec.Z;		}

	//  Get Method
	inline Vector3D Get() { return Vector3D( X, Y, Z ); }
	//inline Vector3D* Get() { return this; }

	// Calculation Methods
	bool Equals(Vector3D* a_Vec)		{ return ( ( X == a_Vec->X )	&& ( Y == a_Vec->Y )&& ( Z == a_Vec->Z ) )	? true : false; }
	bool Equals(Vector3D a_Vec)		{ return ( ( X == a_Vec.X )		&& ( Y == a_Vec.Y )	&& ( Z == a_Vec.Z ) )	? true : false; }
	bool Equals(float a_Scalar)			{ return ( ( X == a_Scalar )	&& ( Y == a_Scalar )	&& ( Z == a_Scalar ) )	? true : false; }

	inline float Length()			{ };//return ( sqrtf(		(X*X) + (Y*Y) + (Z*Z) ) ); }
	inline float SqrLength()	{ return (				(X*X) +	 (Y*Y) + (Z*Z) ); }

	inline float Dot( Vector3D* a_Vec )	{ return ( X*a_Vec->X ) + ( Y*a_Vec->Y ) + ( Z*a_Vec->Z ); }
	inline float Dot( Vector3D& a_Vec )	{ return ( X*a_Vec.X ) +	   ( Y*a_Vec.Y ) +	  ( Z*a_Vec.Z );  }

	inline Vector3D Cross( Vector3D* a_Vec )		{ return ( Vector3D( ( Y*a_Vec->Z -Z*a_Vec->Y ),	( Z*a_Vec->X -	X*a_Vec->Z ),	( X*a_Vec->Y -	Y*a_Vec->X	) ) ); }
	inline Vector3D Cross( Vector3D a_Vec )		{ return ( Vector3D( ( Y*a_Vec.Z -	Z*a_Vec.Y ),		( Z*a_Vec.X -	X*a_Vec.Z ),		( X*a_Vec.Y -	Y*a_Vec.X		) ) ); }

	inline void Scale( int a_Scalar )	{	X*=( a_Scalar ); Y*=( a_Scalar ); Z*=( a_Scalar ); }
	inline void ScaleX( int a_Scalar )	{	X*=( a_Scalar ); }
	inline void ScaleY( int a_Scalar )	{	Y*=( a_Scalar ); }
	inline void ScaleZ( int a_Scalar )	{	Z*=( a_Scalar ); }

	inline void Invert() { X*=(-1); Y*=(-1); Z*=(-1); }
	inline void InvertX(){ X*=(-1); }
	inline void InvertY(){ Y*=(-1); }
	inline void InvertZ(){ Z*=(-1); }

	inline void Normalize() { float a_Length = 1/Length(); X *= a_Length; Y *= a_Length; Z *= a_Length; }

	// Operators
	void operator += ( const float a_Scalar )			{ X += a_Scalar;		Y += a_Scalar;		Z += a_Scalar;		}
	void operator += ( const Vector3D& a_Vector )	{ X += a_Vector.X;		Y += a_Vector.Y;	Z += a_Vector.Z;	}
	void operator += ( Vector3D* a_Vector )			{ X += a_Vector->X;	Y += a_Vector->Y;	Z += a_Vector->Z;	}

	void operator -= ( const float a_Scalar )			{ X -= a_Scalar;			Y -= a_Scalar;		Z -= a_Scalar;		}
	void operator -= ( const Vector3D& a_Vector )	{ X -= a_Vector.X;		Y -= a_Vector.Y;	Z -= a_Vector.Z;	}
	void operator -= ( Vector3D* a_Vector )			{ X -= a_Vector->X;	Y -= a_Vector->Y;	Z -= a_Vector->Z;	}

	void operator *= ( const float a_Scalar )			{ X *= a_Scalar;		Y *= a_Scalar;		Z *= a_Scalar;		}
	void operator *= ( const Vector3D& a_Vector )	{ X *= a_Vector.X;		Y *= a_Vector.Y;	Z *= a_Vector.Z;	}
	void operator *= ( Vector3D* a_Vector )			{ X *= a_Vector->X;	Y *= a_Vector->Y;	Z *= a_Vector->Z;	}

	void operator /= ( const float a_Scalar )			{ X /= a_Scalar;			Y /= a_Scalar;		Z /= a_Scalar;		}
	void operator /= ( const Vector3D& a_Vector )	{ X /= a_Vector.X;		Y /= a_Vector.Y;	Z /= a_Vector.Z;	}
	void operator /= ( Vector3D* a_Vector )			{ X /= a_Vector->X;	Y /= a_Vector->Y;	Z /= a_Vector->Z;	}

	void operator = ( const float a_Scalar )			{ X = a_Scalar;			Y = a_Scalar;			Z = a_Scalar;			}
	void operator = ( const Vector3D& a_Vector )	{ X = a_Vector.X;		Y = a_Vector.Y;		Z = a_Vector.Z;		}
	void operator = ( Vector3D* a_Vector )			{ X = a_Vector->X;	Y = a_Vector->Y;	Z = a_Vector->Z;	}

	friend Vector3D operator + ( const Vector3D& a_Vector,  const float a_Scalar )				{ return Vector3D( a_Vector.X		+ a_Scalar,		a_Vector.Y		+ a_Scalar,		a_Vector.Z		+ a_Scalar );			} 
	friend Vector3D operator + ( const Vector3D& a_Vector1, const Vector3D& a_Vector2 )	{ return Vector3D( a_Vector1.X	+ a_Vector2.X,	a_Vector1.Y	+ a_Vector2.Y,	a_Vector1.Z	+ a_Vector2.Z );		}
	friend Vector3D operator + ( const Vector3D& a_Vector1, const Vector3D* a_Vector2 )	{ return Vector3D( a_Vector1.X	+ a_Vector2->X,a_Vector1.Y	+ a_Vector2->Y,	a_Vector1.Z	+ a_Vector2->Z );	}
	friend Vector3D operator + ( const Vector3D* a_Vector1, const Vector3D& a_Vector2 )	{ return Vector3D( a_Vector1->X + a_Vector2.X,	a_Vector1->Y+ a_Vector2.Y,	a_Vector1->Z+ a_Vector2.Z );		}

	friend Vector3D operator - ( const Vector3D& a_Vector,  const float a_Scalar )				{ return Vector3D( a_Vector.X		- a_Scalar,			a_Vector.Y		- a_Scalar,			a_Vector.Z		- a_Scalar );			}
	friend Vector3D operator - ( const Vector3D& a_Vector1, const Vector3D& a_Vector2 )		{ return Vector3D( a_Vector1.X	- a_Vector2.X,	a_Vector1.Y	- a_Vector2.Y,	a_Vector1.Z	- a_Vector2.Z );		}
	friend Vector3D operator - ( const Vector3D& a_Vector1, const Vector3D* a_Vector2 )		{ return Vector3D( a_Vector1.X	- a_Vector2->X,	a_Vector1.Y	- a_Vector2->Y,	a_Vector1.Z	- a_Vector2->Z );	}
	friend Vector3D operator - ( const Vector3D* a_Vector1, const Vector3D& a_Vector2 )		{ return Vector3D( a_Vector1->X - a_Vector2.X,	a_Vector1->Y	- a_Vector2.Y,	a_Vector1->Z	- a_Vector2.Z );		}

	friend Vector3D operator * ( const Vector3D& a_Vector,  const float a_Scalar )				{ return Vector3D( a_Vector.X		* a_Scalar,		a_Vector.Y		* a_Scalar,		a_Vector.Z		* a_Scalar );			}
	friend Vector3D operator * ( const Vector3D& a_Vector1, const Vector3D& a_Vector2 )	{ return Vector3D( a_Vector1.X	* a_Vector2.X,	a_Vector1.Y	* a_Vector2.Y,	a_Vector1.Z	* a_Vector2.Z );		}
	friend Vector3D operator * ( const Vector3D& a_Vector1, const Vector3D* a_Vector2 )	{ return Vector3D( a_Vector1.X	* a_Vector2->X,a_Vector1.Y	* a_Vector2->Y,	a_Vector1.Z	* a_Vector2->Z );	}
	friend Vector3D operator * ( const Vector3D* a_Vector1, const Vector3D& a_Vector2 )	{ return Vector3D( a_Vector1->X * a_Vector2.X,	a_Vector1->Y* a_Vector2.Y,	a_Vector1->Z* a_Vector2.Z );		}

	friend Vector3D operator / ( const Vector3D& a_Vector,  const float a_Scalar )				{ return Vector3D( a_Vector.X		/ a_Scalar,			a_Vector.Y		/ a_Scalar,			a_Vector.Z		/ a_Scalar );			} 
	friend Vector3D operator / ( const Vector3D& a_Vector1, const Vector3D& a_Vector2 )		{ return Vector3D( a_Vector1.X	/ a_Vector2.X,	a_Vector1.Y	/ a_Vector2.Y,	a_Vector1.Z	/ a_Vector2.Z );		}
	friend Vector3D operator / ( const Vector3D& a_Vector1, const Vector3D* a_Vector2 )		{ return Vector3D( a_Vector1.X	/ a_Vector2->X,	a_Vector1.Y	/ a_Vector2->Y,	a_Vector1.Z	/ a_Vector2->Z );	}
	friend Vector3D operator / ( const Vector3D* a_Vector1, const Vector3D& a_Vector2 )		{ return Vector3D( a_Vector1->X / a_Vector2.X,	a_Vector1->Y/ a_Vector2.Y,	a_Vector1->Z/ a_Vector2.Z );		}

	friend Vector3D operator == ( const Vector3D& a_Vector,  const float a_Scalar )				{ return ( ( a_Vector.X == a_Scalar )			&& ( a_Vector.Y == a_Scalar ) 			&& ( a_Vector.Z == a_Scalar ) )				? true : false; }
	friend Vector3D operator == ( const Vector3D& a_Vector1, const Vector3D& a_Vector2 )	{ return ( ( a_Vector1.X == a_Vector2.X )	&& ( a_Vector1.Y == a_Vector2.Y ) 	&& ( a_Vector1.Z == a_Vector2.Z ) )		? true : false; }
	friend Vector3D operator == ( const Vector3D& a_Vector1, const Vector3D* a_Vector2 )	{ return ( ( a_Vector1.X == a_Vector2->X )	&& ( a_Vector1.Y == a_Vector2->Y ) 	&& ( a_Vector1.Z == a_Vector2->Z ) )		? true : false; }
	friend Vector3D operator == ( const Vector3D* a_Vector1, const Vector3D& a_Vector2 )	{ return ( ( a_Vector1->X == a_Vector2.X )	&& ( a_Vector1->Y == a_Vector2.Y ) 	&& ( a_Vector1->Z == a_Vector2.Z ) )		? true : false; }

	// Member Data
	union
	{
		struct { float X, Y, Z; };
		struct { int iX, iY, iZ; };
		float	Cell[3];
		int		iCell[3];
	};

}; // Vector3D Class

}; // Namespace Chris

#endif
