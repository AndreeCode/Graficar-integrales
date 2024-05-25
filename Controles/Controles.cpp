#include "Controles.h"

#include <cmath>


double Pos_X=0,Pos_Y=0;
double Escl_X=50,Escl_Y=50;

double Inicio_Integral=-1;
double Final_Integral=1;


int tiempo=0;
int opcion =5;

void Pocicion_Recta(double x,double y);
void Escala_Recta(double x,double y);

void Reiniciar_tiempo(){
 	tiempo=0;
}


double funcion(double x){
	if(opcion ==0){
		return x;
	}else if(opcion==1){
		return 1/x;
	}
	else if(opcion==2){
		return 1/pow(x,2);
	}else if(opcion==3){
		return fabs(x);
	}
	else if(opcion==4){
		if (x >= 0) {
	        return static_cast<int>(x);
	    } else {
	        return static_cast<int>(x-1);
	    }
	}else{
		return 1/(pow(x,2)-1);
	}
	
}




void Registrar_GDI_Control(HINSTANCE,HWND);

void RegistrarControles(HINSTANCE hInstance,HWND hwnd){
	Registrar_GDI_Control(hInstance,hwnd);
}
void RegisterClassError(WNDCLASS wc){
	if(!RegisterClass(&wc)){ 
		MessageBox(NULL,"Error al crear la clase","Error",MB_ICONERROR);
	}
	
}
void Registrar_GDI_Control(HINSTANCE hInstance,HWND hwnd){
	
	
	WNDCLASS wc={0};
	wc.style=CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc=Control_GDI;
	wc.hInstance=hInstance;
	//wc.hCursor=LoadCursor(NULL,IDC_HAND);
	wc.hbrBackground=(HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName="GDI_CONTROL";
	RegisterClassError(wc);
}

void EliminarControl(HWND hwnd, HINSTANCE hInstance,LPCSTR classname) {
    if (!UnregisterClass(classname, hInstance)) {
        MessageBox(NULL, "Error al eliminar la clase", "Error", MB_ICONERROR);
    }
}


int w=0,h=0;

LRESULT CALLBACK Control_GDI(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam){

	switch(msg){
		case WM_CREATE:{
			SetTimer(hwnd,1,40,NULL);
			break;
		}
		case WM_TIMER:{
			switch(wParam){
				case 1:{
					if(tiempo<w){
						tiempo=tiempo+5;
						InvalidateRect(hwnd,NULL,TRUE);
					}
					break;
				}
				
			}
		}
		
		case WM_PAINT:{
			PAINTSTRUCT ps;
			HDC hDC=BeginPaint(hwnd,&ps);
			
			RECT rc;
			GetWindowRect(hwnd,&rc);
			
			HPEN red=CreatePen(PS_SOLID,1,RGB(255,0,0));
			HPEN blue=CreatePen(PS_SOLID,1,RGB(0,0,255));
			HPEN green=CreatePen(PS_SOLID,1,RGB(0,255,0));
			
			w=rc.right-rc.left;
			h=rc.bottom-rc.top;
			
			SelectObject(hDC,red);
			MoveToEx(hDC,Pos_X*Escl_X+w/2,0,NULL);
			LineTo(hDC,Pos_X*Escl_X+w/2,h);
			
			SelectObject(hDC,blue);
			MoveToEx(hDC,0,Pos_Y*Escl_Y+h/2,NULL);
			LineTo(hDC,w,Pos_Y*Escl_Y+h/2);
			
			SelectObject(hDC,green);
			if(tiempo<w){
				for (int x =0; x <tiempo; x++) {
		            double xValue =(double(x -w / 2) / Escl_X);
		            double yValue =funcion(xValue-Pos_X);
		            if(!std::isinf(yValue)){
		            	
		            	int y = h / 2 - float(yValue * Escl_Y);
		            	SetPixel(hDC,x,Pos_Y*Escl_Y+y,RGB(0,0,0));
	                	if(!((w/2+(Inicio_Integral+Pos_X)*Escl_X)>x) and !(x>(w/2+(Pos_X+Final_Integral)*Escl_X))){
	                		MoveToEx(hDC,x,Pos_Y*Escl_Y+h/2,NULL);
							LineTo(hDC,x,y+Pos_Y*Escl_Y);
					
						}
					}            
		        }
			}else{
				for (int x =0; x < w; x++) {
		            double xValue =(double(x -(w / 2)) / Escl_X);
		            double yValue =funcion(xValue-Pos_X);
		            if(!std::isinf(yValue)){
		            	
		            	int y = h / 2 - float(yValue * Escl_Y);
		            	SetPixel(hDC,x,Pos_Y*Escl_Y+y,RGB(0,0,0));
	                	if(!((w/2+(Inicio_Integral+Pos_X)*Escl_X)>x) and !(x>(w/2+(Pos_X+Final_Integral)*Escl_X))){
	                		MoveToEx(hDC,x,Pos_Y*Escl_Y+h/2,NULL);
							LineTo(hDC,x,y+Pos_Y*Escl_Y);
					
						}
					}        
		        }
			}
			
			
			DeleteObject(red);
			DeleteObject(blue);
			DeleteObject(green);
			EndPaint(hwnd,&ps);
			break;
		}
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

void Pocicion_Recta(double x,double y){
	Pos_X=x;
	Pos_Y=-y;
}
void Escala_Recta(double x,double y){
	if(x>0 && y>0){
		Escl_X=x;
		Escl_Y=y;
	}else{
		MessageBox(NULL, "por favor, digite numeros mayores a 0","Error!",MB_ICONEXCLAMATION|MB_OK);
	}
	
}
void Pociciones(float a,float b){
	Inicio_Integral=a;
	Final_Integral=b;
}

void camb(int cam){
	opcion=cam;
}