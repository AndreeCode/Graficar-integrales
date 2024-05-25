#include "Controles/Controles.h"
#include <windows.h>
#include <cmath>
#define ID_EDT_POS 10000
#define ID_EDT_ESCALA 10001
#define ID_EDT_TIME 10002
#define ID_EDT_A_B 10003
#define ID_EDT_CAMB 10004

HWND btn_editar_pos;
HWND edt_posX,edt_posY;

HWND btn_editar_escala;
HWND edt_escalX,edt_escalY;

HWND btn_a_b;
HWND edt_a;
HWND edt_b;


HWND btn_camb;
HWND edt_camb;

HWND btn_reiniciar_tmp;

HWND Graficar_Funciones;


/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE:{
			
			btn_editar_pos=CreateWindowEx(0,"BUTTON","Pos(x,y)",WS_VISIBLE|WS_CHILD,10,10,80,25,hwnd,(HMENU)ID_EDT_POS,0,0);
			edt_posX=CreateWindowEx(0,"EDIT","0.0",WS_VISIBLE|WS_CHILD|WS_BORDER,100,10,80,25,hwnd,0,0,0);
			edt_posY=CreateWindowEx(0,"EDIT","0.0",WS_VISIBLE|WS_CHILD|WS_BORDER,180,10,80,25,hwnd,0,0,0);
			
			btn_editar_escala=CreateWindowEx(0,"BUTTON","Escal(x,y)",WS_VISIBLE|WS_CHILD,10,45,80,25,hwnd,(HMENU)ID_EDT_ESCALA,0,0);
			edt_escalX=CreateWindowEx(0,"EDIT","50.0",WS_VISIBLE|WS_CHILD|WS_BORDER,100,45,80,25,hwnd,0,0,0);
			edt_escalY=CreateWindowEx(0,"EDIT","50.0",WS_VISIBLE|WS_CHILD|WS_BORDER,180,45,80,25,hwnd,0,0,0);
			btn_reiniciar_tmp=CreateWindowEx(0,"BUTTON","---",WS_CHILD|WS_VISIBLE,300,10,80,25,hwnd,(HMENU)ID_EDT_TIME,0,0);
			
			btn_a_b=CreateWindowEx(0,"BUTTON","A_B",WS_CHILD|WS_VISIBLE,300,200,80,25,hwnd,(HMENU)ID_EDT_A_B,0,0);
			edt_a=CreateWindowEx(0,"EDIT","-1.0",WS_VISIBLE|WS_CHILD|WS_BORDER,300,230,80,25,hwnd,0,0,0);
			edt_b=CreateWindowEx(0,"EDIT","1.0",WS_VISIBLE|WS_CHILD|WS_BORDER,300,260,80,25,hwnd,0,0,0);
			btn_camb=CreateWindowEx(0,"BUTTON","camb",WS_VISIBLE|WS_CHILD,300,100,80,25,hwnd,(HMENU)ID_EDT_CAMB,0,0);
			edt_camb=CreateWindowEx(0,"EDIT","5",WS_VISIBLE|WS_CHILD|WS_BORDER,300,130,80,25,hwnd,0,0,0);
			
			Graficar_Funciones=CreateWindowEx(0,"GDI_CONTROL",0,WS_VISIBLE|WS_CHILD|WS_BORDER,50,80,200,200,hwnd,0,0,0);
			
			break;
		}
		case WM_COMMAND:{
			if(LOWORD(wParam)==ID_EDT_POS){
				
				char texto1[6];
				GetWindowText(edt_posX,texto1,6);
				double Position_X=atof(texto1);
				
				GetWindowText(edt_posY,texto1,6);
				double Position_Y=atof(texto1);
				
				Pocicion_Recta(Position_X,Position_Y);
				
				
				InvalidateRect(Graficar_Funciones,NULL,TRUE);
			}
			if(LOWORD(wParam)==ID_EDT_ESCALA){
				
				char texto1[4];
				GetWindowText(edt_escalX,texto1,4);
				double Escale_X=atof(texto1);
				
				GetWindowText(edt_escalY,texto1,4);
				double Escale_Y=atof(texto1);
				
				Escala_Recta(Escale_X,Escale_Y);
				
				
				InvalidateRect(Graficar_Funciones,NULL,TRUE);
			}if(LOWORD(wParam)==ID_EDT_TIME){
				Reiniciar_tiempo();
			}if(LOWORD(wParam)==ID_EDT_A_B){
				char texto1[4];
				double a=-1;
				double b=1;

				GetWindowText(edt_a,texto1,4);
				
				if(strcmp(texto1, "inf")==0){
					a=-INFINITY;
				}else{
					a=atof(texto1);
				}
				
				GetWindowText(edt_b,texto1,4);
				if(strcmp(texto1, "inf")==0){
					b=INFINITY;
				}else{
					b=atof(texto1);
				}
				if(a<b){
					Pociciones(a,b);
					InvalidateRect(Graficar_Funciones,NULL,TRUE);
				}else{
					MessageBox(NULL, "'a' tiene que ser menos a 'b'","Error!",MB_ICONEXCLAMATION|MB_OK);
				}
				
				
			}if(LOWORD(wParam)==ID_EDT_CAMB){
				char texto1[4];
				GetWindowText(edt_camb,texto1,4);
				int cam=atoi(texto1);
				camb(cam);
				InvalidateRect(Graficar_Funciones,NULL,TRUE);
			}
			
			
			break;
		}
		
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	RegistrarControles(hInstance,hwnd);
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","GrafInt",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
	EliminarControl(hwnd,hInstance,"GDI_CONTROL");
}

