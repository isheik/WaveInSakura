#pragma comment(lib, "Winmm.lib")
#include <windows.h>
#include "wav_media_player.h"

#include "resource2.h"
#define TITLE 	TEXT("Kitty on your lap")
#define SRATE 	11025

WNDCLASSEX Wcl;
const char Name[] = "Test app";
HWND hwnd;

	 WAVEFORMATEX wfe;
	 HWAVEOUT hWaveOut;
	 HWAVEIN hWaveIn;
	 //LPSTR bWave;
	 BYTE *bWave;
	 WAVEHDR whdr;

	MMRESULT rc;

// ### This callback does not work proparly cuz using WaveIn functions inside it, which is prohibited to cause deadlock
//VOID CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance,
//	DWORD dwParam1, DWORD dwParam2)
//{
//	switch (uMsg)
//	{
//	case WIM_OPEN:
//		OutputDebugStringA("open");
//		break;
//	case WIM_CLOSE:
//		waveInUnprepareHeader(hWaveIn, &whdr, sizeof(WAVEHDR));
		//break; // don't care
	//case WIM_DATA:
		// post message to process this input block received
		// NOTE: callback cannot call other waveform functions
		//....................................................

		//PostMessage((HWND)dwInstance, USR_INBLOCK, 0, dwParam1);
		//OutputDebugStringA("data");
		//rc = waveInStop(hWaveIn);
		//OutputDebugStringA("stop called");
		//if (rc == MMSYSERR_NOERROR)
		//{
		//	OutputDebugStringA("stop success");
		//}
		//else
		//{
		//	switch (rc)
		//	{
		//		case MMSYSERR_INVALHANDLE:
		//			OutputDebugStringA("stop invalid handle");
		//			break;
		//		case MMSYSERR_NODRIVER:
		//			OutputDebugStringA("stop no driver");
		//			break;
		//		case MMSYSERR_NOMEM:
		//			OutputDebugStringA("stop nomem");
		//			break;
		//		case WAVERR_UNPREPARED:
		//			OutputDebugStringA("stop UNPREPARED");
		//			break;
		//		default:
		//			OutputDebugStringA("stop default");
		//			break;
		//	}
		//}
		//rc = waveInClose(hWaveIn);
		//OutputDebugStringA("close called");
		//if (rc == MMSYSERR_NOERROR)
		//{
		//	OutputDebugStringA("close success");
		//}
		//else
		//{
		//	switch (rc)
		//	{
		//		case MMSYSERR_INVALHANDLE:
		//			OutputDebugStringA("close invalid handle");
		//			break;
		//		case MMSYSERR_NODRIVER:
		//			OutputDebugStringA("close no driver");
		//			break;
		//		case MMSYSERR_NOMEM:
		//			OutputDebugStringA("close nomem");
		//			break;
		//		case WAVERR_UNPREPARED:
		//			OutputDebugStringA("close UNPREPARED");
		//			break;
		//		default:
		//			OutputDebugStringA("close default");
		//			break;
		//	}
		//}
		//break;
	//case WOM_OPEN:
	//	OutputDebugStringA("wom open");
	//	break;
	//case WOM_DONE:
	//	waveOutClose(hWaveOut);
	//	break;
	//case WOM_CLOSE:
	//	waveOutUnprepareHeader(hWaveOut, &whdr, sizeof(WAVEHDR));
	//	break;
	//}
//}

VOID CALLBACK waveOutProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance,
	DWORD dwParam1, DWORD dwParam2)
{
	switch (uMsg)
	{
	case WOM_OPEN:
		OutputDebugStringA("wom open");
		break;
	case WOM_DONE:
		OutputDebugStringA("done");
		waveOutClose(hWaveOut);
		break;
	case WOM_CLOSE:
		waveOutUnprepareHeader(hWaveOut, &whdr, sizeof(WAVEHDR));
		break;
	}
}



INT_PTR CALLBACK handleClientDialog(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDB_REC:
			rc = waveInOpen(&hWaveIn, WAVE_MAPPER, &wfe,
				(DWORD)hwnd, 0, CALLBACK_WINDOW);
			//rc = waveInOpen(&hWaveIn, WAVE_MAPPER, &wfe,
				//(DWORD)(VOID*)waveInProc, (DWORD)hwnd, CALLBACK_FUNCTION);
			if (rc == MMSYSERR_NOERROR) {
				OutputDebugStringA("good");

				waveInPrepareHeader(hWaveIn, &whdr, sizeof(WAVEHDR));
				rc = waveInAddBuffer(hWaveIn, &whdr, sizeof(WAVEHDR));

				if (rc == MMSYSERR_NOERROR)
				{
					OutputDebugStringA("Added buffer probably");
				}
				else 
				{
					switch (rc)
					{
					case MMSYSERR_INVALHANDLE:
						OutputDebugStringA("invalid handle");
						break;
					case MMSYSERR_NODRIVER:
						OutputDebugStringA("no driver");
						break;
					case MMSYSERR_NOMEM:
						OutputDebugStringA("nomem");
						break;
					case WAVERR_UNPREPARED:
						OutputDebugStringA("UNPREPARED");
						break;
					}
				}

				rc = waveInStart(hWaveIn);
				if (rc == MMSYSERR_NOERROR)
				{
					OutputDebugStringA("Started");
				}
				else 
				{
					switch (rc)
					{
					case MMSYSERR_INVALHANDLE:
						OutputDebugStringA("start invalid handle");
						break;
					case MMSYSERR_NODRIVER:
						OutputDebugStringA("start no driver");
						break;
					case MMSYSERR_NOMEM:
						OutputDebugStringA("start nomem");
						break;
					case WAVERR_UNPREPARED:
						OutputDebugStringA("start UNPREPARED");
						break;
					}
				}
			}
			else {
				switch (rc) {
				case MMSYSERR_ALLOCATED:
					OutputDebugStringA("alloc");
					break;
				case MMSYSERR_BADDEVICEID:
					OutputDebugStringA("bad");
					break;
				case MMSYSERR_NODRIVER:
					OutputDebugStringA("NO DRIVER");
					break;
				case MMSYSERR_NOMEM:
					OutputDebugStringA("NO mem");
					break;
				case WAVERR_BADFORMAT:
					OutputDebugStringA("Bad form");
					break;
				case MMSYSERR_ERROR:
					OutputDebugStringA("Unknown");
					break;
				default:
					OutputDebugStringA("else");
					break;
				}
			}

			break;
		case IDB_PLAY:
			waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfe,
				(DWORD)hwnd, 0, CALLBACK_WINDOW);
			//rc = waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfe,
				//(DWORD)(VOID*)waveOutProc, (DWORD)hwnd, CALLBACK_FUNCTION);

			waveOutPrepareHeader(hWaveOut, &whdr, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &whdr, sizeof(WAVEHDR));
			break;
		default:
			break;
		}
	case IDCANCEL:
		EndDialog(hwndDlg, (INT_PTR)0);
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_DESTROY:
		free(bWave);
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		OutputDebugStringA("wm create");
		bWave = (BYTE*)malloc(SRATE * 5);
		//bWave = (LPSTR)malloc(SRATE * 3);

		wfe.wFormatTag = WAVE_FORMAT_PCM;
		wfe.nChannels = 1;
		wfe.nSamplesPerSec = SRATE;
		wfe.nAvgBytesPerSec = SRATE;
		wfe.wBitsPerSample = 8;
		wfe.nBlockAlign = wfe.nChannels * wfe.wBitsPerSample / 8;

		whdr.lpData = (LPSTR)bWave;
		whdr.dwBufferLength = SRATE * 5;
		whdr.dwLoops = 1;
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wp)) {
		case DE_CLIENT:
			DialogBox(Wcl.hInstance, MAKEINTRESOURCE(IDD_FORMVIEW), hwnd, handleClientDialog);
			return 0;
	}
	case WIM_OPEN:
		OutputDebugStringA("open");
		break;
	case WIM_CLOSE:
		waveInUnprepareHeader(hWaveIn, &whdr, sizeof(WAVEHDR));
		break; // don't care
	case WIM_DATA:
		// post message to process this input block received
		// NOTE: callback cannot call other waveform functions
		//....................................................

		//PostMessage((HWND)dwInstance, USR_INBLOCK, 0, dwParam1);
		OutputDebugStringA("data");
		rc = waveInStop(hWaveIn);
		OutputDebugStringA("stop called");
		if (rc == MMSYSERR_NOERROR)
		{
			OutputDebugStringA("stop success");
		}
		else
		{
			switch (rc)
			{
				case MMSYSERR_INVALHANDLE:
					OutputDebugStringA("stop invalid handle");
					break;
				case MMSYSERR_NODRIVER:
					OutputDebugStringA("stop no driver");
					break;
				case MMSYSERR_NOMEM:
					OutputDebugStringA("stop nomem");
					break;
				case WAVERR_UNPREPARED:
					OutputDebugStringA("stop UNPREPARED");
					break;
				default:
					OutputDebugStringA("stop default");
					break;
			}
		}
		rc = waveInClose(hWaveIn);
		OutputDebugStringA("close called");
		if (rc == MMSYSERR_NOERROR)
		{
			OutputDebugStringA("close success");
		}
		else
		{
			switch (rc)
			{
				case MMSYSERR_INVALHANDLE:
					OutputDebugStringA("close invalid handle");
					break;
				case MMSYSERR_NODRIVER:
					OutputDebugStringA("close no driver");
					break;
				case MMSYSERR_NOMEM:
					OutputDebugStringA("close nomem");
					break;
				case WAVERR_UNPREPARED:
					OutputDebugStringA("close UNPREPARED");
					break;
				default:
					OutputDebugStringA("close default");
					break;
			}
		}
		break;
	case WOM_OPEN:
		OutputDebugStringA("wom open");
		break;
	case WOM_DONE:
		OutputDebugStringA("done");
		waveOutClose(hWaveOut);
		break;
	case WOM_CLOSE:
		waveOutUnprepareHeader(hWaveOut, &whdr, sizeof(WAVEHDR));
		break;
	}

	return DefWindowProc(hWnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance, LPSTR lspszCmdParam, int nCmdShow)
{
	MSG Msg;

	Wcl.cbSize = sizeof(WNDCLASSEX);
	Wcl.style = CS_HREDRAW | CS_VREDRAW;
	Wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION); // large icon 
	Wcl.hIconSm = NULL; // use small version of large icon
	Wcl.hCursor = LoadCursor(NULL, IDC_ARROW);  // cursor style
	Wcl.lpfnWndProc = WndProc;
	Wcl.hInstance = hInst;
	Wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //white background
	Wcl.lpszClassName = Name;
	Wcl.lpszMenuName = "MYMENU"; // The menu Class
	Wcl.cbClsExtra = 0;      // no extra memory needed
	Wcl.cbWndExtra = 0;

	if (!RegisterClassEx(&Wcl))
		return 0;

	hwnd = CreateWindow(Name, Name, WS_OVERLAPPEDWINDOW, 10, 10,
		600, 400, NULL, NULL, hInst, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

