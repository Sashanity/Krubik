
#include "stdafx.h"
#include "Small.h"


float basis[3][3] =
	{ 1, 0, 0,
	0, 1, 0,
	0, 0, 1 };

RECT rect;
CSmallBrick::CSmallBrick ()
	{
	x = 0;
	y = 0;
	z = 0;
	nSize = 0;
	for (int i = 0; i < 8; i++)
		{
		mast[i].x = mast[i].y = mast[i].z = 0;
		newmas[i].x = newmas[i].y = newmas[i].z = 0;
		}
	
	plos[0].v1 = &newmas[0]; plos[0].v2 = &newmas[1]; plos[0].v3 = &newmas[2]; plos[0].v4 = &newmas[3];	
	plos[1].v1 = &newmas[4]; plos[1].v2 = &newmas[5]; plos[1].v3 = &newmas[6]; plos[1].v4 = &newmas[7];	
	plos[2].v1 = &newmas[0]; plos[2].v2 = &newmas[4]; plos[2].v3 = &newmas[5]; plos[2].v4 = &newmas[1];	
	plos[3].v1 = &newmas[2]; plos[3].v2 = &newmas[3]; plos[3].v3 = &newmas[7]; plos[3].v4 = &newmas[6];
	plos[4].v1 = &newmas[3]; plos[4].v2 = &newmas[7]; plos[4].v3 = &newmas[4]; plos[4].v4 = &newmas[0];	
	plos[5].v1 = &newmas[1]; plos[5].v2 = &newmas[2]; plos[5].v3 = &newmas[6]; plos[5].v4 = &newmas[5];
	for (int i = 0; i < 6; i++)
		plos[i].brush = &mbrush[6];
	}
CSmallBrick::~CSmallBrick ()
	{
	}
void CSmallBrick::SetX (int tx)
	{
	x = tx;
	}
void CSmallBrick::SetY (int ty)
	{
	y = ty;
	}
void CSmallBrick::SetZ (int tz)
	{
	z = tz;
	}
void CSmallBrick::SetSize (float size)
	{
	nSize = size;
	}

void CSmallBrick::SetColor (int side, int color)
	{
	plos[side].brush = &mbrush[color];
	}
int CSmallBrick::GetX ()
	{
	return x;
	}
int CSmallBrick::GetY ()
	{
	return y;
	}
int CSmallBrick::GetZ ()
	{
	return z;
	}
tochka CSmallBrick::GetCenter ()
	{
	tochka c = {nX,nY,nZ};
	return c;
	}
float CSmallBrick::GetSize ()
	{
	return nSize;
	}

void CSmallBrick::Refresh ()
	{
	nX = (x - 1.f) * nSize*1.1;
	nY = (y - 1.f) * nSize*1.1;
	nZ = (z - 1.f) * nSize*1.1;

	mast[0].x = nX - nSize / 2; mast[0].y = nY - nSize / 2; mast[0].z = nZ - nSize / 2;
	mast[1].x = nX + nSize / 2; mast[1].y = nY - nSize / 2, mast[1].z = nZ - nSize / 2;
	mast[2].x = nX + nSize / 2; mast[2].y = nY + nSize / 2, mast[2].z = nZ - nSize / 2;
	mast[3].x = nX - nSize / 2; mast[3].y = nY + nSize / 2, mast[3].z = nZ - nSize / 2;

	mast[4].x = nX - nSize / 2; mast[4].y = nY - nSize / 2, mast[4].z = nZ + nSize / 2;
	mast[5].x = nX + nSize / 2; mast[5].y = nY - nSize / 2, mast[5].z = nZ + nSize / 2;
	mast[6].x = nX + nSize / 2; mast[6].y = nY + nSize / 2, mast[6].z = nZ + nSize / 2;
	mast[7].x = nX - nSize / 2; mast[7].y = nY + nSize / 2, mast[7].z = nZ + nSize / 2;
	
	plos[0].v1 = &newmas[0]; plos[0].v2 = &newmas[1]; plos[0].v3 = &newmas[2]; plos[0].v4 = &newmas[3];	
	plos[1].v1 = &newmas[4]; plos[1].v2 = &newmas[5]; plos[1].v3 = &newmas[6]; plos[1].v4 = &newmas[7];	
	plos[2].v1 = &newmas[0]; plos[2].v2 = &newmas[4]; plos[2].v3 = &newmas[5]; plos[2].v4 = &newmas[1]; 	
	plos[3].v1 = &newmas[2]; plos[3].v2 = &newmas[3]; plos[3].v3 = &newmas[7]; plos[3].v4 = &newmas[6];
	plos[4].v1 = &newmas[3]; plos[4].v2 = &newmas[7]; plos[4].v3 = &newmas[4]; plos[4].v4 = &newmas[0];
	plos[5].v1 = &newmas[1]; plos[5].v2 = &newmas[2]; plos[5].v3 = &newmas[6]; plos[5].v4 = &newmas[5];  

	}
void CSmallBrick ::Recount (float basis[3][3])
{

for (int i = 0; i < 8; i++)
{
newmas[i].x = mast[i].x * basis[0][0] + mast[i].y * basis[1][0] + mast[i].z * basis[2][0];
newmas[i].y = mast[i].x * basis[0][1] + mast[i].y * basis[1][1] + mast[i].z * basis[2][1];
newmas[i].z = mast[i].x * basis[0][2] + mast[i].y * basis[1][2] + mast[i].z * basis[2][2];
}
}
CSmallBrick & CSmallBrick :: operator = (CSmallBrick & source)
	{
	nX = source.nX;
	nY = source.nY;
	nZ = source.nZ;
	nSize = source.nSize;
	x = source.x;
	y = source.y;
	z = source.z;
	for (int i = 0; i < 8; i++)
		mast[i] = source.mast[i];

	for (int i = 0; i < 6; i++)
		plos[i].brush = source.plos[i].brush;
	return *this;
	}

//ПОВОРОТЫ
void CSmallBrick::RotateNeg (int &t, int&r)
/*Изменение координат при повороте в отрицательном направлении */
	{
	if ((t == 0) && (r == 0)) { t = 2; return; }
	if ((t == 1) && (r == 0)) { t = 2; r = 1; return; }
	if ((t == 2) && (r == 0)) { r = 2; return; }
	if ((t == 2) && (r == 1)) { t = 1; r = 2; return; }
	if ((t == 2) && (r == 2)) { t = 0; return; }
	if ((t == 1) && (r == 2)) { t = 0; r = 1; return; }
	if ((t == 0) && (r == 2)) { t = 0; r = 0; return; }
	if ((t == 0) && (r == 1)) { t = 1; r = 0; return; }
	}
void CSmallBrick::RotatePos (int &t, int&r)
/*Изменение координат при повороте в положительном направлении*/
	{
	if ((t == 0) && (r == 0)) { r = 2; return; }
	if ((t == 1) && (r == 0)) { t = 0; r = 1; return; }
	if ((t == 2) && (r == 0)) { t = 0; return; }
	if ((t == 2) && (r == 1)) { t = 1; r = 0; return; }
	if ((t == 2) && (r == 2)) { r = 0; return; }
	if ((t == 1) && (r == 2)) { t = 2; r = 1; return; }
	if ((t == 0) && (r == 2)) { t = 2; return; }
	if ((t == 0) && (r == 1)) { t = 1; r = 2; return; }
	}

void CSmallBrick::RotateXNeg ()
//Поворот кубика по оси x в отрицательную сторону
	{
	HBRUSH * tmp = plos[0].brush;
	plos[0].brush = plos[3].brush;
	plos[3].brush = plos[1].brush;
	plos[1].brush = plos[2].brush;
	plos[2].brush = tmp;
	RotateNeg (z, y);
	Refresh ();
	}
void CSmallBrick::RotateXPos ()
/*Поворот кубика по оси x в положительную сторону*/
	{
	HBRUSH * tmp = plos[0].brush;
	plos[0].brush = plos[2].brush;
	plos[2].brush = plos[1].brush;
	plos[1].brush = plos[3].brush;
	plos[3].brush = tmp;
	RotatePos (z, y);
	Refresh ();
	}

void CSmallBrick::RotateYNeg ()
//Поворот кубика по оси y в отрицательную сторону
	{
	HBRUSH * tmp = plos[5].brush;
	plos[5].brush = plos[0].brush;
	plos[0].brush = plos[4].brush;
	plos[4].brush = plos[1].brush;
	plos[1].brush = tmp;
	RotateNeg (x, z);
	Refresh ();
	}
void CSmallBrick::RotateYPos ()
/*Поворот кубика по оси y в положительную сторону*/
	{
	HBRUSH * tmp = plos[5].brush;
	plos[5].brush = plos[1].brush;
	plos[1].brush = plos[4].brush;
	plos[4].brush = plos[0].brush;
	plos[0].brush = tmp;
	RotatePos (x, z);
	Refresh ();
	}

void CSmallBrick::RotateZNeg ()
//Поворот кубика по оси z в отрицательную сторону 
	{
	HBRUSH * tmp = plos[5].brush;
	plos[5].brush = plos[3].brush;
	plos[3].brush = plos[4].brush;
	plos[4].brush = plos[2].brush;
	plos[2].brush = tmp;
	RotateNeg (y, x);
	Refresh ();
	}
void CSmallBrick::RotateZPos ()
/* Поворот кубика по оси z в положительную сторону */
	{
	HBRUSH * tmp = plos[5].brush;
	plos[5].brush = plos[2].brush;
	plos[2].brush = plos[4].brush;
	plos[4].brush = plos[3].brush;
	plos[3].brush = tmp;
	RotatePos (y, x);
	Refresh ();
	}


	

