// test1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "test1.h"
#include "wingdi.h"
#include "windowsx.h"
#include "winuser.h"
#include <string> // for string class
#include "commdlg.h"
#include <valarray>
#include <vector>

#define MAX_LOADSTRING 100

using namespace std;

class Hextile {

};

class Piece {

};

vector<Hextile> board;
vector<Piece>   pieces;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TEST1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEST1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

HFONT FAR PASCAL CreateTitleFont(void)
{
    CHOOSEFONT cf;
    LOGFONT lf;
    HFONT hfont;

    // Initialize members of the CHOOSEFONT structure.  

    cf.lStructSize = sizeof(CHOOSEFONT);
    cf.hwndOwner = (HWND)NULL;
    cf.hDC = (HDC)NULL;
    cf.lpLogFont = &lf;
    cf.iPointSize = 0;
    cf.Flags = CF_SCREENFONTS;
    cf.rgbColors = RGB(0, 0, 0);
    cf.lCustData = 0L;
    cf.lpfnHook = (LPCFHOOKPROC)NULL;
    cf.lpTemplateName = (LPCWSTR)NULL;
    cf.hInstance = (HINSTANCE)NULL;
    cf.lpszStyle = (LPWSTR)NULL;
    cf.nFontType = SCREEN_FONTTYPE;
    cf.nSizeMin = 15;
    cf.nSizeMax = 20;

    // Display the CHOOSEFONT common-dialog box.  

    ChooseFont(&cf);

    // Create a logical font based on the user's  
    // selection and return a handle identifying  
    // that font.  

    hfont = CreateFontIndirect(cf.lpLogFont);
    return (hfont);
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
    {
        POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
        if (DragDetect(hWnd, pt))
        {
            // Start dragging.
            char buff[200];
            snprintf(buff, sizeof(buff), "Dragging to (%d, %d)\n", pt.x, pt.y);
            std::string res_string = buff;

            OutputDebugStringA(buff);
        }
    }

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            TCHAR greeting[] = _T("Chinese Checkers");
            RECT* rect = new RECT{ 100L, 100L, 200L, 200L };
            HBRUSH hbr = CreateSolidBrush(RGB(0, 0, 0));

            RECT* r2 = new RECT{ 0L, 0L, 0L, 0L };
            LPRECT canvas_rect = LPRECT{r2};
            bool ret = GetClientRect(hWnd, canvas_rect);

            if (ret != true) {
                // Start dragging.
                char buff2[100];
                snprintf(buff2, sizeof(buff2), "GetClientRect(hWnd, buf_store) returned %d\n", ret);
                std::string res_string = buff2;
                OutputDebugStringA(buff2);

                PostMessage(hWnd, WM_CLOSE, 0, 0);
            }   
            
            //char buff[200];
            //snprintf(buff, sizeof(buff), "canvas_rect: top = %d, bottom = %d, left = %d, right = %d\n", canvas_rect->top, canvas_rect->bottom, canvas_rect->left, canvas_rect->right);
            //OutputDebugStringA(buff);
            RECT* middle = new RECT{};
            int s = 0;

            if (canvas_rect->right < canvas_rect->bottom) {
                middle->left = canvas_rect->right / 8;
                middle->right = 7 * canvas_rect->right / 8;
                s = middle->right - middle->left;
                middle->top = canvas_rect->bottom / 2 - s / 2;
                middle->bottom = middle->top + s;
            }
            else {
                middle->top = canvas_rect->bottom / 8;
                middle->bottom = 7 * canvas_rect->bottom / 8;
                s = middle->bottom - middle->top;
                middle->left = canvas_rect->right / 2 - s / 2;
                middle->right = middle->left + s;
            }

            Ellipse(hdc, middle->left, middle->top, middle->right, middle->bottom);

            UINT uAlignPrev = SetTextAlign(hdc, TA_CENTER);
//            MoveToEx(hdc, 10, 50, (LPPOINT)NULL);
//            SendMessage(hWnd,
//                WM_SETFONT,
//                (WPARAM) CreateTitleFont(),
//                (LPARAM) false
//            );
            TextOut(hdc,
                canvas_rect->right / 2, 5,
                greeting, _tcslen(greeting));
            SetTextAlign(hdc, uAlignPrev);

            // End application-specific layout section.
            EndPaint(hWnd, &ps);
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
float cartesian_x(float x_hex, float y_hex, float z_hex) {
    float x = x_hex;
    float y = y_hex;
    float z = z_hex;
    return x + z / 2.0;
    //return -y - z / 2.0;
}

float cartesian_y(float x_hex, float y_hex, float z_hex) {
    float x = x_hex;
    float y = y_hex;
    float z = z_hex;
    float inner = 3.0;
    //return -z * (inner).sqrt() / 0.6;
    return -z * std::sqrt(inner) / 2.0;
}

float cartesian_x_to_canvas_x(float x, float BOARD_WIDTH, float ABSTRACT_BOARD_WIDTH, float CANVAS_WIDTH) {
    return (BOARD_WIDTH / 2.0) + (x / (ABSTRACT_BOARD_WIDTH / 2.0)) * (BOARD_WIDTH / 2.0) + (CANVAS_WIDTH - BOARD_WIDTH) / 2.0;
}

float cartesian_y_to_canvas_y(float y, float BOARD_HEIGHT, float ABSTRACT_BOARD_HEIGHT, float CANVAS_HEIGHT, float BOARD_RECT_VERTICAL_OFFSET_IN_CANVAS) {
    return (BOARD_HEIGHT / 2.0) + (-(y / (ABSTRACT_BOARD_HEIGHT / 2.0))) * (BOARD_HEIGHT / 2.0) + BOARD_RECT_VERTICAL_OFFSET_IN_CANVAS;
}


//let yellow_color_array : Color = Color::rgba(0.902, 0.886, 0.110, 1.0);
//let red_color_array : Color = Color::rgba(0.902, 0.110, 0.110, 1.0);
//let blue_color_array : Color = Color::rgba(0.110, 0.110, 0.902, 1.0);
//let green_color_array : Color = Color::rgba(0.059, 0.600, 0.239, 1.0);
//let black_color_array : Color = Color::rgba(0.0, 0.0, 0.0, 1.0);
//let white_color_array : Color = Color::rgba(1.0, 1.0, 1.0, 1.0);
//let center_color_array : Color = Color::rgba(0.5, 0.5, 0.5, 1.0);

// yellow triangle: x in [-4, -1], y in [-4, -1], z in [5, 8]
//let x_min : i32 = -4;
//let x_max : i32 = -1;
//let y_min : i32 = -4;
//let y_max : i32 = -1;
//let z_min : i32 = 5;
//let z_max : i32 = 8;
//add_appropriate_hextiles_to_board(
//    &mut board,
//    x_min,
//    x_max,
//    y_min,
//    y_max,
//    z_min,
//    z_max,
//    );

// red triangle: x in [-8, -5], y in [1, 4], z in [1, 4]
//let x_min : i32 = -8;
//let x_max : i32 = -5;
//let y_min : i32 = 1;
//let y_max : i32 = 4;
//let z_min : i32 = 1;
//let z_max : i32 = 4;
//add_appropriate_hextiles_to_board(
//    &mut board,
//    x_min,
//    x_max,
//    y_min,
//    y_max,
//    z_min,
//    z_max,
//    );

// blue triangle: x in [1, 4], y in [-5, -8], z in [1, 4]
//let x_min : i32 = 1;
//let x_max : i32 = 4;
//let y_min : i32 = -8;
//let y_max : i32 = -5;
//let z_min : i32 = 1;
//let z_max : i32 = 4;
//add_appropriate_hextiles_to_board(
//    &mut board,
//    x_min,
//    x_max,
//    y_min,
//    y_max,
//    z_min,
//    z_max,
//    );

// black triangle:  x in [-8, -5], y in [5, 8], z in [-4 ,-1]
//let x_min : i32 = -4;
//let x_max : i32 = -1;
//let y_min : i32 = 5;
//let y_max : i32 = 8;
//let z_min : i32 = -4;
//let z_max : i32 = -1;
//add_appropriate_hextiles_to_board(
//    &mut board,
//    x_min,
//    x_max,
//    y_min,
//    y_max,
//    z_min,
//    z_max,
//    );

// green triangle: x in [5, 8], y in [-4, -1], z in [-4, -1]
//let x_min : i32 = 5;
//let x_max : i32 = 8;
//let y_min : i32 = -4;
//let y_max : i32 = -1;
//let z_min : i32 = -4;
//let z_max : i32 = -1;
//add_appropriate_hextiles_to_board(
//    &mut board,
//    x_min,
//    x_max,
//    y_min,
//    y_max,
//    z_min,
//    z_max,
//    );

//white triangle: x in [1, 4], y in [1, 4], z in [-5, -8]
//let x_min : i32 = 1;
//let x_max : i32 = 4;
//let y_min : i32 = 1;
//let y_max : i32 = 4;
//let z_min : i32 = -8;
//let z_max : i32 = -5;
//add_appropriate_hextiles_to_board(
//    &mut board,
//    x_min,
//    x_max,
//    y_min,
//    y_max,
//    z_min,
//    z_max,
//    );

// center squares
//let x_min : i32 = -4;
//let x_max : i32 = 4;
//let y_min : i32 = -4;
//let y_max : i32 = 4;
//let z_min : i32 = -4;
//let z_max : i32 = 4;
//add_appropriate_hextiles_to_board(
//    &mut board,
//    x_min,
//    x_max,
//    y_min,
//    y_max,
//    z_min,
//    z_max,
//    );
//println!("Being called from create_board, size of board Vec = {}", board.len());
//return board;
//}

// add the valid tiles in the given range to the board
//fn add_appropriate_hextiles_to_board(
//    board: &mut im::Vector<Hextile>,
//    x_min : i32,
//    x_max : i32,
//    y_min : i32,
//    y_max : i32,
//    z_min : i32,
 //   z_max : i32,
//    ) {
//    for x in x_min..(x_max + 1) {
//        for y in y_min..(y_max + 1) {
//            for z in z_min..(z_max + 1) {
//                if x + y + z == 0 {
//                    let tile : Hextile = Hextile{
//                        y_hex: y,
//                        x_hex : x,
///                        z_hex : z,
//                        piece_idx : None,
//                    };/
//                    board.push_back(tile);
///                }
//            }
//        }
//    }
//}

// Message handler for about box.
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
