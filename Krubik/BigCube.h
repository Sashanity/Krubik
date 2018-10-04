#pragma once
#include "Small.h"



class BigCube: public CSmallBrick
	{
	private:
		CSmallBrick kub[3][3][3];//массив маленьких кубиков
		float nSize;//длина ребра маленького кубика	
			
		int b;
	public:


		int numgr;// номер текущей грани
		float R[3][3];	  //матрица поворота
		float Basis[3][3]; //базис
		BigCube(void);
		BigCube(float size);
		virtual ~BigCube(void){};
		void InitCube(void);//инициализация куба
		void Rot(int number, float a);//функция поворота вокруг произвольной оси
		void povorot(float m1[3][3], float m2[3][3]);//произведение матриц поворота и базиса
		void Draw (HDC,HWND);//отрисовка куба;
		void clear();//задание исходных цветов граней кубика
		void drawGran(HDC,RECT,gran *);		
		void Refresh();
		void Rotate(int side, bool dir);
		void RotateXNeg(int side);
		void RotateXPos(int side);
		void RotateYNeg(int side);
		void RotateYPos(int side);
		void RotateZNeg(int side);
		void RotateZPos(int side); 
		friend void sort (gran *, int left, int right);//сортировка граней по глубине
		int AddPovgr(int gran,float ang)
			{
			if(numgr == -1 || numgr == gran)
				{
				int t;
				b += ang; 
				if (abs(b) < 90 )
			{
				numgr = gran;
				return -1;// если грань не на 90
			}
			else
				{
				
				// если угол стал кратным 90, то поварачиваем на массиве
			if ((b > 0))
				{
				Rotate (gran, true);
				}					
				else
					Rotate(gran,false);
				b = 0;
				t = numgr;
				numgr = -1;
				return t;//если на 90
			}
				}
			return -1;
			};
		
	};

