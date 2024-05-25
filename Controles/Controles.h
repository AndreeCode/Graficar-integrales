#include <windows.h>
#define WM_GET_V1 (WM_USER + 1)

void Pocicion_Recta(double,double);
void Pociciones(float,float);
void Escala_Recta(double,double);
void Reiniciar_tiempo();
void camb(int);

void EliminarControl(HWND , HINSTANCE ,LPCSTR);
void RegistrarControles(HINSTANCE,HWND);
LRESULT CALLBACK Control_GDI(HWND,UINT,WPARAM,LPARAM);
