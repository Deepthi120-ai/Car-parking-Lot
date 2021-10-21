#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<wchar.h>
#include <time.h>
//Standard gui functions
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) ;
LRESULT CALLBACK dialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK depdialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void loadimages();
void registerarrival(HINSTANCE hInstance);
void displayarrivaldialog(HWND hwnd,HINSTANCE hInstance);
void registerdeparure(HINSTANCE hInstance);
void displaydepdialog(HWND hwnd);
void  check(WPARAM,HWND);
 
// Define used for handling buttons
#define a 1
#define de 2
#define ok 3
#define save 4
#define paid 5
#define c 6
#define check 7


//Gui variables
HWND vno,hadlg,lvl,hwndStatic,vno_d,hdlg, hlogo;
HWND hout,hrate;
HINSTANCE hInstance;

HBITMAP simage;

char sel[4];
 char str[50];
 wchar_t* slot[] = {L"P1", L"P2", L"P3",L"P4",L"P5",L"P6",L"P7",L"P8",L"P9",L"P10",L"P11",L"P12",L"P13",L"P14",L"P15",L"P16",L"P17",L"P18",L"P19",L"P20",L"P21",L"P22",L"P23",L"P24",L"P25"};
int vehiclevalid =0;	//Variable showing validity of vehicle number.To be handled by your program(Either 0 or 1, 1 being vehicle number valid)
int row,col;			// Variable to find the exact parking position in the array(0 to 4)
char vehicleno[30]={'\0'};		//Variable containing vehicle number. Should mandatorily have 10 characters.Vehicle number to be stored by you on arrival
char vehiclenod[30];	//Vehicle number provided by user during departure.Validation of the vehicle number to be handled by your program 
char camount[3];		//gui variables
float amount=0.0;		//amount to be calculated and updated in this variable by your program
int arr[3][5][5];		//3D array having levels,row and column
char lvl1[30];			//Level chosen by the user is in this array.To be stored in the file by your program
int L;
struct data
{
	char vehicleno[30];
	int hour;
	int min;
	int sec;
	int R,C,L;
};

struct data m[75];
int count=0;

int validityA()
{
	int flag,i,j;
if(strlen(vehicleno)==10)
{
	for(i=0;i<2;i++)
	{	if('A'<=vehicleno[i] && vehicleno[i]<='Z')
			flag=0;
		else flag=1;
	}
	if(flag==0)
	{	
		for(i=2;i<4;i++)
		{
			if('0'<=vehicleno[i] && vehicleno[i]<='9')
				flag=0;
			else flag=1;
		}
		if(flag==0)
		{
			for(i=4;i<6;i++)
			{
				if('A'<=vehicleno[i] && vehicleno[i]<='Z')
					flag=0;
				else flag=1;
			}
			if(flag==0)
			{	
				for(i=6;i<10;i++)
				{
					if('0'<=vehicleno[i] && vehicleno[i]<='9')
						flag=0;
				}
				if(flag==0)
					for(j=0;j<75 && flag==0;j++)
					{
						if(strcmp(vehicleno,m[j].vehicleno)==0)
							flag=1;
						else 
							flag=0;
					}
					if(flag==0)
						return 1;
					else
						return 0;		
			}
			else
				 return 0;
		}
		else
			 return 0;
		
	}
	else
		 return 0;
	
		
}
else
	 return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)	
{

    MSG  msg;
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"Buttons";
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
	registerarrival(hInstance);
	registerdeparure(hInstance);
	
	
    CreateWindowW(wc.lpszClassName, L"Car Parking Solution",
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  150, 150, 400, 300, 0, 0, hInstance, 0);

    while (GetMessage(&msg, NULL, 0, 0)) 
	{
    
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
	{
    
    switch(msg) 
	{

        case WM_CREATE:
		CreateWindowW(L"Static", L"WELCOME TO PESU PARKING",WS_CHILD| WS_VISIBLE,100, 10, 300, 200, hwnd, 0, hInstance, 0);
		CreateWindowW(L"Static", L"Created by : Aishwarya, Akansha, Deepthi, Satwika", WS_CHILD| WS_VISIBLE,10, 40, 400, 200, hwnd, 0, hInstance, 0);
		CreateWindowW(L"Static", L"Plese a select an option", WS_CHILD| WS_VISIBLE,10, 80, 400, 200, hwnd, 0, hInstance, 0);
		CreateWindowW(L"Button", L"ENTRY",WS_VISIBLE | WS_CHILD ,10, 120, 80, 25, hwnd, (HMENU)a, NULL, NULL);
		CreateWindowW(L"Button", L"EXIT",WS_VISIBLE | WS_CHILD ,100, 120, 100, 25, hwnd, (HMENU)de, NULL, NULL);
		CreateWindowW(L"Button", L"CANCEL",WS_VISIBLE | WS_CHILD ,60, 200, 100, 25, hwnd, (HMENU)c, NULL, NULL);
		break;
		case WM_COMMAND:
		switch(wParam)
		{
			case 1:
			displayarrivaldialog(hwnd,hInstance);
			break;
			case 2:
			displaydepdialog(hwnd);
			break;
			case 6:
			PostQuitMessage(0);
			break;
		}
		break;
		case WM_DESTROY:
		PostQuitMessage(0);
		
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
	}
	
	LRESULT CALLBACK dialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		 switch(msg)
		 {
			 
			 case WM_CLOSE:
			 
			 DestroyWindow(hwnd);
			 break;
			 case WM_COMMAND:
			 
				if(LOWORD(wParam)==ok)
				{
					GetWindowText(vno,vehicleno,30);
					if( validityA()==0)
					{
					MessageBoxW(NULL, L"INVALID VEHICLE NUMBER", L"", MB_OK);
					}
					else
					{
						GetWindowText(lvl,lvl1,29);
						CreateWindowW(L"Static", L"Select slot",  WS_CHILD | WS_VISIBLE, 10, 150, 200, 50, hadlg, NULL, hInstance, NULL); 
						hout = CreateWindowW(L"Combobox", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,150, 150, 100, 600, hadlg, NULL, hInstance, NULL); 
						int g=0,x;
						for(int i=0;i<5;i++)
						{
							for(int j=0;j<5;j++)
							{
								if((strlen(lvl1)==1)&&(lvl1[0]=='1'))
								{
									if(*(*(*(arr+0)+i)+j)==0)
										
										SendMessageW(hout, CB_ADDSTRING, 0, (LPARAM) slot[g]); 
								}
								else if((strlen(lvl1)==1)&&(lvl1[0]=='2'))
								{
									if(*(*(*(arr+1)+i)+j)==0)
										SendMessageW(hout, CB_ADDSTRING, 0, (LPARAM) slot[g]); 
								}
								else if((strlen(lvl1)==1)&&(lvl1[0]=='3'))
								{	
									if(*(*(*(arr+2)+i)+j)==0)		
										SendMessageW(hout, CB_ADDSTRING, 0, (LPARAM) slot[g]); 
								}
								else
								{
									MessageBoxW(NULL, L"INVALID OPTION", L"", MB_OK);
									x=1;
									break;
								}
							g++;	
							}
							if(x==1)
								break;
				
						}
			
					CreateWindowW(L"Button", L"Save",WS_VISIBLE | WS_CHILD ,300,150, 80, 25, hadlg, (HMENU)save, NULL, NULL);
					break;
					}
				}
		
				if(HIWORD(wParam)==BN_CLICKED)	 
                  SendMessage(hout, CB_SHOWDROPDOWN, (WPARAM) TRUE, 0);
				if(HIWORD(wParam)==CBN_SELCHANGE)
				{
					int index  = SendMessage(hout, CB_GETCURSEL, 0, 0);
					 SendMessage(hout, (UINT)CB_GETLBTEXT  , (WPARAM)index, (LPARAM)sel);
					
					
					
				}		
				if(LOWORD(wParam)==save)
				{	
					
					DestroyWindow(hadlg);
					for(int i=0;i<25;i++) {
					
							wcstombs(str, slot[i], 49);
							if(strcmp(sel,str)==0)
							{ 	
						
							row=i/5;
							col=i%5;
							break;
						
					} }
						
					if(lvl1[0]=='1')
						*(*(*(arr+0)+row)+col)=1;
					else if(lvl1[0]=='2')
						*(*(*(arr+1)+row)+col)=1;	
					else if(lvl1[0]=='3')
						*(*(*(arr+2)+row)+col)=1;
					strcpy(m[count].vehicleno,vehicleno);
					time_t now;
					time(&now);
					struct tm *local = localtime(&now); 
					m[count].hour=local->tm_hour;
					m[count].min=local->tm_min;
					m[count].sec=local->tm_sec;
					m[count].R=row;
					m[count].C=col;
					L=((int)lvl1[0])-49;
					m[count].L=L;
					count++;//CALL YOUR ARRIVAL FUNCTION HERE
				}
             
		 }
			
			 return DefWindowProcW(hwnd, msg, wParam, lParam);
		 
	 }
	
void registerarrival(HINSTANCE hInstance)
{
	WNDCLASSW d = {0};
	d.lpszClassName = L"Mydialog";
	d.hInstance     = hInstance;
	d.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	d.lpfnWndProc   = dialogProc;
	d.hCursor       = LoadCursor(0, IDC_ARROW);
	RegisterClassW(&d);	
}
	
void displayarrivaldialog(HWND hwnd,HINSTANCE hInstance)
{
	hadlg = CreateWindowW(L"Mydialog",L"ENTRY",WS_VISIBLE|WS_OVERLAPPEDWINDOW,20,20,800,800,hwnd,NULL,NULL,NULL);
	CreateWindowW(L"Static", L"Vehicle number",WS_CHILD| WS_VISIBLE,10, 10, 300, 200, hadlg, 0, hInstance, 0);
	vno=CreateWindowW(L"Edit", L"",WS_CHILD| WS_VISIBLE,150, 10, 150, 20, hadlg, 0, hInstance, 0);
	CreateWindowW(L"Static", L"Level(1-3)",WS_CHILD| WS_VISIBLE,10, 50, 150, 50, hadlg, 0, hInstance, 0);
	lvl=CreateWindowW(L"Edit", L"",WS_CHILD| WS_VISIBLE,150, 50, 120, 20, hadlg, 0, hInstance, 0);
	CreateWindowW(L"Button", L"OK",WS_VISIBLE | WS_CHILD ,10,100, 80, 25, hadlg, (HMENU)ok, NULL, NULL);
	hlogo=CreateWindowW(L"Static", L"",WS_CHILD| WS_VISIBLE|SS_BITMAP,410, 100, 300, 200, hadlg, 0, hInstance, 0);
	loadimages();
	SendMessage(hlogo, STM_SETIMAGE,(WPARAM) IMAGE_BITMAP, (LPARAM) simage); 
}
	
LRESULT CALLBACK depdialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_COMMAND:
		if(LOWORD(wParam)==check)
			{
				GetWindowText(vno_d,vehiclenod,30);
				amount=0;
				vehiclevalid=0;
				int i=0,j=0,flag=0;
				for(i=0;i<75 && flag==0;i++)
				{
					if(strcmp(vehiclenod,m[i].vehicleno)==0)
					{
						time_t now;
						time(&now);						
						struct tm *local = localtime(&now);
						int timediff=((local->tm_min)*60+(local->tm_sec))-((m[i].min)*60+m[i].sec);
						if(0<=timediff && timediff<60)
							amount=20.0;
						else if(60<=timediff && timediff<120)
							amount=30.0;
						else if(120<=timediff && timediff<180)
							amount=40.0;
						else 
							amount=60.0;
						arr[m[i].L][m[i].R][m[i].C]=0;
						for(j=i;j<75;j++)
						{
							m[j]=m[j+1];
						}
						count--;
						flag=1;
						vehiclevalid=1;
					}
					
				}
				//CALL YOUR DEPARTURE FUNCTION HERE AND VALIDATE VEHICLE NUMBER WITH DATA IN FILE AND UPDATE THE VALUE OF vehiclevalid TO 0(INVLAID) OR 1(VALID)
				if(vehiclevalid)
				{
					CreateWindowW(L"Static", L"Amount to be paid : ",WS_CHILD| WS_VISIBLE,10, 100, 300, 200, hdlg, 0, hInstance, 0);
					sprintf(camount, "%0.2f", amount);
					hrate = CreateWindowW(L"Edit", L"",WS_CHILD| WS_VISIBLE,150, 100, 80, 25, hdlg, 0, hInstance, 0);
					SetWindowText(hrate,camount);
					CreateWindowW(L"Button", L"PAID",WS_VISIBLE | WS_CHILD ,100, 150, 80, 25, hdlg, (HMENU)paid, NULL, NULL);	
				}
				else
				{
					MessageBoxW(NULL, L"INVALID VEHICLE NUMBER!!", L"", MB_OK);
					break;
				}   
			}
			
		if(LOWORD(wParam)==paid)
		{ 
			MessageBoxW(NULL, L"THANK YOU!! VISIT AGAIN", L"", MB_OK);
			amount = 0;
		}
		break;
			
		default:
			return DefWindowProcW(hwnd, msg, wParam, lParam);
	}
		
}
	
void registerdeparure(HINSTANCE hInstance)
{
	WNDCLASSW dep = {0};
	dep.lpszClassName = L"Myddialog";
	dep.hInstance     = hInstance;
	dep.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	dep.lpfnWndProc   = depdialogProc;
	dep.hCursor       = LoadCursor(0, IDC_ARROW);
	RegisterClassW(&dep);	
}
	
void displaydepdialog(HWND hwnd)
{
	hdlg = CreateWindowW(L"Myddialog",L"EXIT",WS_VISIBLE|WS_OVERLAPPEDWINDOW,400,400,400,400,hwnd,NULL,NULL,NULL);
	CreateWindowW(L"Static", L"Vehicle number",WS_CHILD| WS_VISIBLE,10, 10, 300, 200, hdlg, 0, hInstance, 0);
	vno_d=CreateWindowW(L"Edit", L"",WS_CHILD| WS_VISIBLE,150, 10, 150, 20, hdlg, 0, hInstance, 0);
	GetWindowText(vno_d,vehiclenod,30);
	CreateWindowW(L"Button", L"CHECK",WS_VISIBLE | WS_CHILD ,100, 40, 80, 25, hdlg, (HMENU)check, NULL, NULL);	
}
	
void loadimages()	
{
	simage = (HBITMAP)LoadImageW(NULL,L"Parking.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);		//CHANGE THE PATH BASED ON WHERE U SAVE THE IMAGE
}