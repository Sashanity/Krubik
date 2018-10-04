#pragma once
#include "Small.h"



class BigCube: public CSmallBrick
	{
	private:
		CSmallBrick kub[3][3][3];//������ ��������� �������
		float nSize;//����� ����� ���������� ������	
			
		int b;
	public:


		int numgr;// ����� ������� �����
		float R[3][3];	  //������� ��������
		float Basis[3][3]; //�����
		BigCube(void);
		BigCube(float size);
		virtual ~BigCube(void){};
		void InitCube(void);//������������� ����
		void Rot(int number, float a);//������� �������� ������ ������������ ���
		void povorot(float m1[3][3], float m2[3][3]);//������������ ������ �������� � ������
		void Draw (HDC,HWND);//��������� ����;
		void clear();//������� �������� ������ ������ ������
		void drawGran(HDC,RECT,gran *);		
		void Refresh();
		void Rotate(int side, bool dir);
		void RotateXNeg(int side);
		void RotateXPos(int side);
		void RotateYNeg(int side);
		void RotateYPos(int side);
		void RotateZNeg(int side);
		void RotateZPos(int side); 
		friend void sort (gran *, int left, int right);//���������� ������ �� �������
		int AddPovgr(int gran,float ang)
			{
			if(numgr == -1 || numgr == gran)
				{
				int t;
				b += ang; 
				if (abs(b) < 90 )
			{
				numgr = gran;
				return -1;// ���� ����� �� �� 90
			}
			else
				{
				
				// ���� ���� ���� ������� 90, �� ������������ �� �������
			if ((b > 0))
				{
				Rotate (gran, true);
				}					
				else
					Rotate(gran,false);
				b = 0;
				t = numgr;
				numgr = -1;
				return t;//���� �� 90
			}
				}
			return -1;
			};
		
	};

