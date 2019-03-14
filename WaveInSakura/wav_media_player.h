#define IDM_HELP		200
#define IDM_EXIT		201
#define HTOIP			202
#define IPTOH			203
#define SVTOP			204
#define PTOSV			205
#define DE_CLIENT		210
#define DE_SERVER		240

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance, LPSTR lspszCmdParam, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void window_printline(char* str, int str_size);
long delay(SYSTEMTIME t1, SYSTEMTIME t2);
char* replace_char(char* str, char find, char replace);
char* openSelectFileDialog();
BOOL CreateSocketInformation(SOCKET s);
void FreeSocketInformation(DWORD Event);
DWORD WINAPI runUDPServer(LPVOID tUdpParams);
DWORD WINAPI runTCPServer(LPVOID tTcpParams);
INT_PTR CALLBACK handleServerDialog(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK handleClientDialog(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);
