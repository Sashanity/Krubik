#pragma once
#include <windows.h>
#include <windowsx.h>


struct tochka
	{
	float x, y, z;
	};
struct gran
	{
	tochka * v1, *v2, *v3, *v4;
	HBRUSH * brush;
	};
class CSmallBrick
	{
	
	public:
		CSmallBrick ();
		virtual ~CSmallBrick ();
		static HBRUSH mbrush[7];
		gran plos[6];
	private:
		
		float nSize;
		float nX; // x - координата
		float nY; // y - координата
		float nZ; // z - координата		
		int x;
		int y;
		int z;
		tochka mast[8], newmas[8];	
		
	public:		
				
		void SetX (int tx); 
		void SetY (int ty);
		void SetZ (int tz);
		void SetSize (float size); 		
		void SetColor (int side, int color);
		int GetX (); 
		int GetY ();
		int GetZ ();
		tochka GetCenter();
		float GetSize (); 	
		void Refresh (); // пересчиттывает координаты кубика
		void Recount (float basis[3][3]);
		gran * GetPlos (){ return plos; };
		CSmallBrick &  operator =(CSmallBrick &);
		void RotateNeg (int &t, int&r);
		void RotatePos (int &t, int&r);
		void RotateXNeg ();
		void RotateXPos ();
		void RotateYNeg ();
		void RotateYPos ();
		void RotateZNeg ();
		void RotateZPos ();
	};
