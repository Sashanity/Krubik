#include "stdafx.h"
#include "BigCube.h"
#define M_PI 3.1415926

BigCube::BigCube(void)
	{
	ZeroMemory(&b,4);	
	ZeroMemory(R,9*4);
	ZeroMemory(Basis,9*4);
	R[0][0] = R[1][1] = R[2][2] = Basis[0][0] = Basis[1][1] = Basis[2][2] = 1;
	nSize = 0;
	numgr = -1;
	} 
BigCube::BigCube(float size)
	{
	nSize = (size > 0)? size : 0;
	ZeroMemory(&b,4);	
	ZeroMemory(R,9*4);
	ZeroMemory(Basis,9*4);
	numgr = -1;
	R[0][0] = R[1][1] = R[2][2] = Basis[0][0] = Basis[1][1] = Basis[2][2] = 1;
	} 
void BigCube:: InitCube(void)
	{
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			for(int k = 0; k < 3; k++)
				{
					kub[i][j][k].SetX(i); kub[i][j][k].SetY(j);	kub[i][j][k].SetZ(k);
					kub[i][j][k].SetSize (nSize);		
					kub[i][j][k].Refresh ();
				}
	numgr = -1;
	clear();
	}

void BigCube::clear()
	{
	int i, j, k;
	// верх
	for(i = 0; i < 3; i++)
		for(k = 0; k < 3; k++)
			for(j = 0; j < 3; j++)
				kub[i][j][k].SetColor(0, 0);
	//// низ
	for(i = 0; i < 3; i++)
		for(k = 0; k < 3; k++)
			for(j = 0; j < 3; j++)
				kub[i][j][k].SetColor(1, 1);
	// спереди
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			for(k = 0; k < 3; k++)
				kub[i][j][k].SetColor(2, 2);
	// сзади
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			for(k = 0; k < 3; k++)
				kub[i][j][k].SetColor(3, 3);
	// слева
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			for(k = 0; k < 3; k++)
				kub[i][j][k].SetColor(4, 4);
	// справа
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			for(k = 0; k < 3; k++)
				kub[i][j][k].SetColor(5, 5);
	}

void BigCube:: Draw(HDC hdc,HWND hwnd)
	{
	RECT rect;
	float tmp[3][3];
	GetClientRect (hwnd, &rect);
	PatBlt(hdc,0,0,rect.right,rect.bottom,WHITENESS);
	//повернули кубик целиком
	povorot(Basis,R);
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			for(int k = 0; k < 3; k++)
				kub[i][j][k].Recount(Basis);
	if(numgr != -1)
		{
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				tmp[i][j] = Basis[i][j];
		int i, j, k;
		// вокруг оси Z
		if (numgr == 0 || numgr == 1)
			{
				// numgr = 0 - нижняя часть
				// numgr = 1 - верхняя часть
				k = (numgr & 1) * 2;//как работает: пусть numgr == 1 -> 01b & 01b == 01b => 1 * 2 = 2, пусть numgr == 0 -> 00b & 01b == 00b => 0 * 2 = 0 (прикольная штука)
				// теперь нужно покрутить грань под номером current на угол povgr[numgr]
				// относительно центра этой грани
				Rot(3,(b*M_PI)/180);
				povorot(R,Basis);//крутим грань в локальных координатах
				for(i = 0; i < 3; i++)
					for(j = 0; j < 3; j++)
						kub[i][j][k].Recount(Basis);
			}
		//вокруг оси Y
		else if (numgr == 2 || numgr == 3)
			{
				j = (numgr & 1) * 2;
				Rot(2,(b*M_PI)/180);
				povorot(R,Basis);//крутим грань в локальных координатах
				for(i = 0; i < 3; i++)
					for(k = 0; k < 3; k++)
						kub[i][j][k].Recount(Basis);
			}
		//вокруг оси X
		else if (numgr == 4 || numgr == 5)
			{
				i = (numgr & 1) * 2;
				Rot(1,(b*M_PI)/180);
				povorot(R,Basis);//крутим грань в локальных координатах
				for(j = 0; j < 3; j++)
					for(k = 0; k < 3; k++)
						kub[i][j][k].Recount(Basis);
			}
		//возвращаем значение базиса назад
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				Basis[i][j] = tmp[i][j];
		}

	gran mas[6*27];
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			for(int k = 0; k < 3; k++)
				for(int g = 0; g < 6; g++)
					{
					mas[i*54+j*18+k*6+g] = kub[i][j][k].GetPlos()[g]; 
					}
	//сортируем полученный массив граней по глубине
	sort(mas,0,6*27-1);
	for(int i = 0; i < (6*27);i++)
		drawGran(hdc,rect,&mas[i]);
	tochka os[3] = {{200,0,0},{0,200,0},{0,0,200}};
	tochka osn[3];
	for(int i = 0; i < 3; i++)
		{
		osn[i].x = os[i].x * Basis[0][0] + os[i].y * Basis[1][0] + os[i].z * Basis[2][0];
		osn[i].y = os[i].x * Basis[0][1] + os[i].y * Basis[1][1] + os[i].z * Basis[2][1];
		osn[i].z = os[i].x * Basis[0][2] + os[i].y * Basis[1][2] + os[i].z * Basis[2][2];
		}
	HPEN hpen = CreatePen (PS_SOLID, 2, RGB (112, 128, 144));
	SelectBrush(hdc,hpen);
	MoveToEx(hdc,rect.right/2,rect.bottom/2,NULL);
	LineTo(hdc,osn[0].x + rect.right/2,-osn[0].y + rect.bottom/2);
	TextOut(hdc,osn[0].x + rect.right/2,-osn[0].y + rect.bottom/2,L"X",lstrlen(L"X"));
	MoveToEx(hdc,rect.right/2,rect.bottom/2,NULL);
	LineTo(hdc,osn[1].x + rect.right/2,-osn[1].y + rect.bottom/2);
	TextOut(hdc,osn[1].x + rect.right/2,-osn[1].y + rect.bottom/2,L"Y",lstrlen(L"Y"));
	MoveToEx(hdc,rect.right/2,rect.bottom/2,NULL);
	LineTo(hdc,osn[2].x + rect.right/2,-osn[2].y + rect.bottom/2);
	TextOut(hdc,osn[2].x + rect.right/2,-osn[2].y + rect.bottom/2,L"Z",lstrlen(L"Z"));    
	DeletePen(hpen);
	SelectPen (hdc, GetStockPen (BLACK_PEN));
	}
void BigCube::drawGran(HDC hdc,RECT rect,gran* gr)
	{
	POINT pol[4];
	SelectBrush (hdc, *(gr->brush));//выбор цвета грани
		pol[0].x = gr->v1->x + rect.right / 2; pol[0].y = -gr->v1->y + rect.bottom / 2;
		pol[1].x = gr->v2->x + rect.right / 2; pol[1].y = -gr->v2->y + rect.bottom / 2;
		pol[2].x = gr->v3->x + rect.right / 2; pol[2].y = -gr->v3->y + rect.bottom / 2;
		pol[3].x = gr->v4->x + rect.right / 2; pol[3].y = -gr->v4->y + rect.bottom / 2;
		Polygon (hdc, pol, 4);
	}
void sort(gran * mas,int left,int right)
	{
	int i = left,j = right;
	gran temp;
	float iz;
	float jz;
	float vspz = (mas[(i+j)/2].v1->z+mas[(i+j)/2].v2->z+mas[(i+j)/2].v3->z+mas[(i+j)/2].v4->z)/4;//значение коорд z барьера
	do
		{
		iz = (mas[i].v1->z+mas[i].v2->z+mas[i].v3->z+mas[i].v4->z)/4;
		jz = (mas[j].v1->z+mas[j].v2->z+mas[j].v3->z+mas[j].v4->z)/4;
		while(iz < vspz)
			{
			i++;
			iz = (mas[i].v1->z+mas[i].v2->z+mas[i].v3->z+mas[i].v4->z)/4;
			}
		while(vspz < jz)
			{
			j--;
			jz = (mas[j].v1->z+mas[j].v2->z+mas[j].v3->z+mas[j].v4->z)/4;
			}
		if(i <= j)
			{
			temp = mas[i]; mas[i] = mas[j]; mas[j] = temp; i++; j--;
			}
		}while(i < j);
		if(i < right) sort(mas,i,right);
		if(left < j)  sort(mas,left,j);
	}


void BigCube:: Rot(int number, float a)
	{
		 switch (number)
		{
			case 1: //x
				R[0][0] = 1; R[0][1] = 0; R[0][2] = 0;
				R[1][0] = 0; R[1][1] = cos (a); R[1][2] = sin (a);
				R[2][0] = 0; R[2][1] = -sin (a); R[2][2] = cos (a);
				break;
			case 2: //y
				R[0][0] = cos (a); R[0][1] = 0; R[0][2] = -sin (a);
				R[1][0] = 0; R[1][1] = 1; R[1][2] = 0;
				R[2][0] = sin (a); R[2][1] = 0; R[2][2] = cos (a);
				break;
			case 3://z
				R[0][0] = cos (a); R[0][1] = sin (a); R[0][2] = 0;
				R[1][0] = -sin (a); R[1][1] = cos (a); R[1][2] = 0;
				R[2][0] = 0; R[2][1] = 0; R[2][2] = 1;
				break;
			case 0:
				R[0][0] = 1; R[0][1] = 0; R[0][2] = 0;
				R[1][0] = 0; R[1][1] = 1; R[1][2] = 0;
				R[2][0] = 0; R[2][1] = 0; R[2][2] = 1;
			default: 
				return;
		}
	}
float vrem[3][3];
void BigCube:: povorot (float m1[3][3], float m2[3][3])
	{
	vrem[0][0] = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0];
	vrem[0][1] = m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1];
	vrem[0][2] = m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2];

	vrem[1][0] = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0];
	vrem[1][1] = m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1];
	vrem[1][2] = m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2];

	vrem[2][0] = m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0];
	vrem[2][1] = m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1];
	vrem[2][2] = m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			Basis[i][j] = vrem[i][j];
	}


void BigCube::Refresh()
/*Перестоение массива bricks */
	{
	int x;
	int y;
	int z;
	CSmallBrick tempBr[3][3][3];
	for(int i = 0; i < 3; i++)
		{
		for(int j = 0; j < 3; j++)
			{
			for(int k = 0; k < 3; k++)
				{
				x = kub[i][j][k].GetX();
				y = kub[i][j][k].GetY();
				z = kub[i][j][k].GetZ();
				tempBr[x][y][z] = kub[i][j][k]; 
				}
			}
		}
	for(int i = 0; i < 3; i++)
		{
		for(int j = 0; j < 3; j++)
			{
			for(int k = 0; k < 3; k++)
				{
				kub[i][j][k] = tempBr[i][j][k]; 
				}
			}
		}
	}

void BigCube::RotateXNeg(int side)
/* Поворот кубика вокруг оси y в отрицательном направлении*/
	{
	for(int i = 0; i < 3; i++)
		{
		for(int j = 0; j < 3; j++)
			{
			kub[side][i][j].RotateXNeg();
			}
		}
	Refresh();
	} 
void BigCube::RotateXPos(int side)
/* Поворот кубика вокруг оси y в отрицательном направлении*/
	{
	for(int i = 0; i < 3; i++)
		{
		for(int j = 0; j < 3; j++)
			{
			kub[side][i][j].RotateXPos();
			}
		}
	Refresh();
	} 

void BigCube::RotateYNeg(int side)
/* Поворот кубика вокруг оси y в отрицательном направлении*/
	{
	for(int i = 0; i < 3; i++)
		{
		for(int k = 0; k < 3; k++)
			{
			kub[i][side][k].RotateYNeg();
			}
		}
	Refresh();
	} 
void BigCube::RotateYPos(int side)
/* Поворот кубика вокруг оси y в отрицательном направлении*/
	{
	for(int i = 0; i < 3; i++)
		{
		for(int k = 0; k < 3; k++)
			{
			kub[i][side][k].RotateYPos();
			}
		}
	Refresh();
	} 

void BigCube::RotateZNeg(int side)
/* Поворот кубика вокруг оси y в отрицательном направлении*/
	{
	for(int i = 0; i < 3; i++)
		{
		for(int j = 0; j < 3; j++)
			{
			kub[j][i][side].RotateZNeg();
			}
		}
	Refresh();
	} 
void BigCube::RotateZPos(int side)
/* Поворот кубика вокруг оси y в отрицательном направлении*/
	{
	for(int i = 0; i < 3; i++)
		{
		for(int j = 0; j < 3; j++)
			{
			kub[j][i][side].RotateZPos();
			}
		}
	Refresh();
	} 

void BigCube::Rotate(int side, bool dir)
	{
	switch(side)
	{
	case 0:
		{
		if (dir) RotateZPos(0);
		else RotateZNeg(0); 
		break;
		}
	case 1:
		{
		if (dir) RotateZPos(2);
		else RotateZNeg(2); 
		break;
		}
	case 2:
		{
		if (dir) RotateYPos(0);
		else RotateYNeg(0); 
		break;
		}
	case 3:
		{
		if (dir) RotateYPos(2);
		else RotateYNeg(2); 
		break;
		} 
	case 4:
		{
		if (dir) RotateXPos(0);
		else RotateXNeg(0); 
		break;
		}
	case 5:
		{
		if (dir) RotateXPos(2);
		else RotateXNeg(2); 
		break;
		}
	}
	} 