
#include "stdafx.h"
#include "Commdlg.h"
#include "Krubik.h"
#include "BigCube.h"
#include "Small.h"

using namespace std;
#define MAX_LOADSTRING 100
#define M_PI 3.1415926
int id;
int t,flag;
float a,turn;
vector<int>vect;
HWND hdlg;
BigCube kub(50);
CSmallBrick kub1;
HBRUSH CSmallBrick::mbrush[7];
void shake (BigCube &kub);

			
OPENFILENAME ofn;
WCHAR szFile[260];			
HANDLE hf;
TCHAR szFileName[MAX_LOADSTRING]; 
TCHAR szMsg[256];
const TCHAR filemsg1[] = L"История сохранена";
const TCHAR errormsg[] = L" Не выполнено ";
const TCHAR filemsg3[] = L"История загружена";
DWORD cbyte;

HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна


ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK	Hist (HWND, UINT, WPARAM, LPARAM);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
 	
	MSG msg;
	HACCEL hAccelTable;
	
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_KRUBIK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);


	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KRUBIK));

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KRUBIK));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_KRUBIK);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; 
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
HBITMAP hBitMap = NULL;
HDC hDcMem = NULL;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	
	RECT rect;
	switch (message)
	{
	case WM_CREATE:
		kub.InitCube();			
			CSmallBrick::mbrush[0] = CreateSolidBrush (RGB (210,180,140));
			CSmallBrick::mbrush[1] = CreateSolidBrush (RGB (255, 255, 0));
			CSmallBrick::mbrush[2] = CreateSolidBrush (RGB (255, 140, 0));
			CSmallBrick::mbrush[3] = CreateSolidBrush (RGB (60, 179, 113));
			CSmallBrick::mbrush[4] = CreateSolidBrush (RGB (70, 130, 180));
			CSmallBrick::mbrush[5] = CreateSolidBrush (RGB (255, 0, 0));
			CSmallBrick::mbrush[6] = GetStockBrush(NULL_BRUSH);
			shake (kub);
			GetClientRect (hWnd, &rect);
			hdc = GetDC (hWnd);
			hBitMap = CreateCompatibleBitmap (hdc, rect.right, rect.bottom);
			hDcMem = CreateCompatibleDC (hdc);
			SelectBitmap (hDcMem, hBitMap);
			PatBlt (hDcMem, 0, 0, rect.right, rect.bottom, WHITENESS);
			ReleaseDC (hWnd, hdc);
			
		break; 
			
	case WM_SIZE:
		DeleteDC (hDcMem);
		DeleteBitmap (hBitMap);
		GetClientRect (hWnd, &rect);
		hdc = GetDC (hWnd);
		hBitMap = CreateCompatibleBitmap (hdc, rect.right, rect.bottom);
		hDcMem = CreateCompatibleDC (hdc);
		SelectBitmap (hDcMem, hBitMap);
		PatBlt (hDcMem, 0, 0, rect.right, rect.bottom, BLACKNESS);
		InvalidateRect (hWnd, &rect, FALSE);

		break;

	case WM_KEYDOWN:			
		switch (wParam)
			{// поворот отдельной грани
				case 189:// -
					if (kub.numgr != -1)
						
						if ((flag=kub.AddPovgr (kub.numgr, -10)) >=0)
							{
							flag = flag +1;
							vect.push_back (-flag);
							GetClientRect (hdlg, &rect);
							InvalidateRect (hdlg, &rect, TRUE);
							}
						kub.Rot (0, 0);						
					
					break;
				case 187://+
					if (kub.numgr != -1)
						{
						if ((flag = kub.AddPovgr (kub.numgr, 10)) >= 0)
							{
							flag = flag + 1;
							vect.push_back (flag);
							GetClientRect (hdlg, &rect);
							InvalidateRect (hdlg, &rect, TRUE);
							}
						kub.Rot (0, 0);
						}
					break;
				case 49://0 низ
					
					if (kub.AddPovgr (0, 10) >=0)
						{
						vect.push_back (1);
						GetClientRect (hdlg, &rect);
						InvalidateRect (hdlg, &rect, TRUE);
						}
					kub.Rot (0, 0);
					break;

				case 50://1 верх
					
					if (kub.AddPovgr (1, 10)>=0)
						{
						vect.push_back (2);
						GetClientRect (hdlg, &rect);
						InvalidateRect (hdlg, &rect, TRUE);
						}
					kub.Rot (0, 0);
					break;
				case 51://2 перед
					
					if (kub.AddPovgr (2, 10)>=0)
						{
						vect.push_back (3);
						GetClientRect (hdlg, &rect);
						InvalidateRect (hdlg, &rect, TRUE);
						}
					kub.Rot (0, 0);
					break;
				case 52://3 зад
					
					if (kub.AddPovgr (3, 10) >=0)
						{
						vect.push_back (4);
						GetClientRect (hdlg, &rect);
						InvalidateRect (hdlg, &rect, TRUE);
						}
					kub.Rot (0, 0);
					break;
				case 53://4 левая
					
					if (kub.AddPovgr (4, 10) >=0)
						{
						vect.push_back (5);
						GetClientRect (hdlg, &rect);
						InvalidateRect (hdlg, &rect, TRUE);
						}
					kub.Rot (0, 0);
					break;
				case 54://5 правая
					
					if (kub.AddPovgr (5, 10) >=0)
						{
						vect.push_back (6);
						GetClientRect (hdlg, &rect);
						InvalidateRect (hdlg, &rect, TRUE);
						}
					kub.Rot (0, 0);
					break;

				//поворот куба
				case 37: // влево // ось Z
					a = LOWORD (lParam);
					a = (a*M_PI) / 180;					
					kub.Rot(3,a);
					kub.povorot (kub.Basis, kub.R);			
						
					break;
				case 39: // вправо // Ось Z
					a = -LOWORD (lParam);
					a = (a*M_PI) / 180;
					kub.Rot(3,a);
					kub.povorot (kub.Basis, kub.R);
					break;
				case 38: // вних // Ось X
					a = -LOWORD (lParam);
					a = (a*M_PI) / 180;
					kub.Rot(1,a);
					kub.povorot (kub.Basis, kub.R);
					break;
				case 40: // вверх // Ось X
					a = LOWORD (lParam);
					a = (a*M_PI) / 180;
					kub.Rot (1,a);
					kub.povorot (kub.Basis, kub.R);
					break;
				case 107: // + y
					a = LOWORD (lParam);
					a = (a*M_PI) / 180;
					kub.Rot (2,a);
					kub.povorot (kub.Basis, kub.R);
					break;
				case 109: // -y
					a = -LOWORD (lParam);
					a = (a*M_PI) / 180;
					kub.Rot(2,a);
					kub.povorot (kub.Basis, kub.R);
					break;
				default:
					return FALSE;
			}
		GetClientRect (hWnd, &rect);
		InvalidateRect (hWnd, &rect, FALSE);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		hdc = GetDC (hWnd);
		
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_SHAKE:
			shake (kub);
			kub.Draw (hdc, hWnd);
			vect.resize (0);
			InvalidateRect (hdlg, NULL, TRUE);
			UpdateWindow (hdlg);
			break;
		case ID_DONE:
			kub.InitCube ();
			kub.Draw (hdc, hWnd);
			break;
		case ID_SHOW:
			if (hdlg != NULL)
				{
				SetActiveWindow (hdlg);
				}
			else
				CreateDialog (hInst, MAKEINTRESOURCE (IDD_DIALOGHIST), hWnd, Hist);			
			break;
		case ID_SAVE:
			ZeroMemory (&ofn, sizeof (OPENFILENAME));
			ofn.lStructSize = sizeof (OPENFILENAME);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = sizeof (szFileName);
			ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			

			if (!GetSaveFileName (&ofn))
				{				
				for (int i = 0; i < sizeof (errormsg); i++)
					szMsg[i] = errormsg[i];
				MessageBox (0, szMsg, L"Сообщение", 0);
				return FALSE;  
				}
			hf = CreateFile (szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
			for (int i = 0; i < vect.size (); i++)
				{					
					WriteFile (hf, &vect[i], 4, &cbyte, NULL);
				}			
			CloseHandle (hf);
			for (int i = 0; i < sizeof (filemsg1); i++)
				szMsg[i] = filemsg1[i];
			MessageBox (0, szMsg, L"Сообщение", 0);
			break;

		case ID_OPEN:
			ZeroMemory (&ofn, sizeof (OPENFILENAME));
			ofn.lStructSize = sizeof (OPENFILENAME);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = sizeof (szFileName);
			ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;			

			if (!GetOpenFileName (&ofn))
				{
				for (int i = 0; i < sizeof (errormsg); i++)
					szMsg[i] = errormsg[i];
				MessageBox (0, szMsg, L"Сообщение", 0);
				return FALSE;
				}

			vect.resize (0);
			hf = CreateFile (szFileName, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, NULL);
			
			for (int i=0;;)
				{
				ReadFile (hf, &t, 4, &cbyte, NULL);
				if (cbyte == 4)
					{
					vect.push_back (t);
					}
				else
					break;
				}
			CloseHandle (hf);
			if (hdlg != NULL)
				{
				InvalidateRect (hdlg, NULL, TRUE);
				UpdateWindow (hdlg);
				}
			for (int i = 0; i < sizeof (filemsg3); i++)
				szMsg[i] = filemsg3[i];
			MessageBox (0, szMsg, L"Сообщение", 0);

			break;
		case ID_DOHIST:
			if (id != 0) 	break;
				
			if (vect.size () != 0)
				{
					id=SetTimer (hWnd, 1, 100, NULL);
					t = 0;
					turn = 0;
				}
			else
				{
				for (int i = 0; i < sizeof (filemsg3); i++)
					szMsg[i] = errormsg[i];
				MessageBox (0, szMsg, L"Сообщение", 0);
				}
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	
	
	case WM_PAINT:
		GetClientRect (hWnd, &rect);
		hdc = BeginPaint(hWnd, &ps);		
		kub.Draw (hDcMem, hWnd);	
		BitBlt (hdc, 0, 0, rect.right, rect.bottom, hDcMem, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;

	case WM_TIMER:
		if (t == vect.size ())
			{
			KillTimer (hWnd, 1);
			id = 0;
			}

		else
			if (turn == 90)
				{
				turn = 0;
				t++;
				}
			else
				{
				turn += 10;				
				kub.AddPovgr (abs(vect[t])-1,  (vect[t])>0?10:-10);
				kub.Rot (0, 0);				
				InvalidateRect (hWnd, NULL, FALSE);
				}


		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

//Обработичк для окна истории
BOOL CALLBACK Hist (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
	{
	PAINTSTRUCT ps;
	HDC hdc;
	WCHAR str[20];
	
	hdlg = hDlg;
	UNREFERENCED_PARAMETER (lParam);
	switch (message)
		{
			case WM_INITDIALOG:
				return (BOOL)TRUE;

			case WM_COMMAND:
				if (LOWORD (wParam) == IDOK || LOWORD (wParam) == IDCANCEL)
					{
					DestroyWindow (hDlg);
					hdlg = NULL;
					return (BOOL)TRUE;
					}
							
				break;
			case WM_PAINT:
				
				hdc = BeginPaint (hDlg, &ps);				
				int j=2,k;
				for (int i = 0, k = 0; k < 10, i < vect.size (); i++, k++)
					{					
					if (i % 10==0) { j = j + 20; k = 0; }	
					wsprintf (str, L"%d", vect[i]);
					TextOut (hdc, 10+k*20, j , str, lstrlen (str));	
					}	
								
				EndPaint (hDlg, &ps);
				break;
		}
	return (BOOL)FALSE;
	}


void shake (BigCube &kub)
	{
	int i,stime;
	long ltime;

	ltime = time (NULL);
	stime = (unsigned)ltime / 2;
	srand (stime);
	for (int j = 0; j < 20; j++)
		{	
	i = rand () % 6;
	kub.AddPovgr (i, 90);
		}
	}