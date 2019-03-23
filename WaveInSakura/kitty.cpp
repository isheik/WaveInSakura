#pragma comment(lib, "Winmm.lib")
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
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
BYTE *bWave1;
BYTE *bWave2;
BYTE *bSave;
BYTE *bTmp;
WAVEHDR whdr1;
WAVEHDR whdr2;
int dwLength = 0;
int dwCount;
BOOL blReset = FALSE;

MMRESULT rc;



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
			bWave1 = (BYTE*)malloc(SRATE);
			bWave2 = (BYTE*)malloc(SRATE);

			whdr1.lpData = (LPSTR)bWave1;
			whdr1.dwBufferLength = SRATE;
			whdr1.dwBytesRecorded = 0;
			whdr1.dwFlags = 0;
			whdr1.dwLoops = 1;
			whdr1.lpNext = NULL;
			whdr1.dwUser = 0;
			whdr1.reserved = 0;

			whdr2.lpData = (LPSTR)bWave2;
			whdr2.dwBufferLength = SRATE;
			whdr2.dwBytesRecorded = 0;
			whdr2.dwFlags = 0;
			whdr2.dwLoops = 1;
			whdr2.lpNext = NULL;
			whdr2.dwUser = 0;
			whdr2.reserved = 0;

			rc = waveInOpen(&hWaveIn, WAVE_MAPPER, &wfe,
				(DWORD)hwnd, 0, CALLBACK_WINDOW);
			//rc = waveInOpen(&hWaveIn, WAVE_MAPPER, &wfe,
				//(DWORD)(VOID*)waveInProc, (DWORD)hwnd, CALLBACK_FUNCTION);
			if (rc == MMSYSERR_NOERROR) {
				OutputDebugStringA("good");
				waveInPrepareHeader(hWaveIn, &whdr1, sizeof(WAVEHDR));
				waveInPrepareHeader(hWaveIn, &whdr2, sizeof(WAVEHDR));

			//	rc = waveInAddBuffer(hWaveIn, &whdr, sizeof(WAVEHDR));
			//	if (rc == MMSYSERR_NOERROR)
			//	{
			//		OutputDebugStringA("Added buffer probably");
			//	}
			//	else 
			//	{
			//		switch (rc)
			//		{
			//		case MMSYSERR_INVALHANDLE:
			//			OutputDebugStringA("invalid handle");
			//			break;
			//		case MMSYSERR_NODRIVER:
			//			OutputDebugStringA("no driver");
			//			break;
			//		case MMSYSERR_NOMEM:
			//			OutputDebugStringA("nomem");
			//			break;
			//		case WAVERR_UNPREPARED:
			//			OutputDebugStringA("UNPREPARED");
			//			break;
			//		}
			//	}

			//	rc = waveInStart(hWaveIn);
			//	if (rc == MMSYSERR_NOERROR)
			//	{
			//		OutputDebugStringA("Started");
			//	}
			//	else 
			//	{
			//		switch (rc)
			//		{
			//		case MMSYSERR_INVALHANDLE:
			//			OutputDebugStringA("start invalid handle");
			//			break;
			//		case MMSYSERR_NODRIVER:
			//			OutputDebugStringA("start no driver");
			//			break;
			//		case MMSYSERR_NOMEM:
			//			OutputDebugStringA("start nomem");
			//			break;
			//		case WAVERR_UNPREPARED:
			//			OutputDebugStringA("start UNPREPARED");
			//			break;
			//		}
			//	}
			//}
			//else {
			//	switch (rc) {
			//	case MMSYSERR_ALLOCATED:
			//		OutputDebugStringA("alloc");
			//		break;
			//	case MMSYSERR_BADDEVICEID:
			//		OutputDebugStringA("bad");
			//		break;
			//	case MMSYSERR_NODRIVER:
			//		OutputDebugStringA("NO DRIVER");
			//		break;
			//	case MMSYSERR_NOMEM:
			//		OutputDebugStringA("NO mem");
			//		break;
			//	case WAVERR_BADFORMAT:
			//		OutputDebugStringA("Bad form");
			//		break;
			//	case MMSYSERR_ERROR:
			//		OutputDebugStringA("Unknown");
			//		break;
			//	default:
			//		OutputDebugStringA("else");
			//		break;
			//	}
			}

			break;
		case IDB_PLAY:
			//waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfe,
			//	(DWORD)hwnd, 0, CALLBACK_WINDOW);

			//waveOutPrepareHeader(hWaveOut, &whdr, sizeof(WAVEHDR));
			//waveOutWrite(hWaveOut, &whdr, sizeof(WAVEHDR));
			whdr1.lpData = (LPSTR)bSave;
			whdr1.dwBufferLength = dwLength;
			whdr1.dwBytesRecorded = 0;
			whdr1.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
			whdr1.dwLoops = 1;
			whdr1.lpNext = NULL;
			whdr1.dwUser = 0;
			whdr1.reserved = 0;

			waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfe,
				(DWORD)hwnd, 0, CALLBACK_WINDOW);
			waveOutPrepareHeader(
				hWaveOut, &whdr1, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &whdr1, sizeof(WAVEHDR));
			break;
		case IDB_REC_END:
			blReset = TRUE;
			waveInReset(hWaveIn);
			break;
		case IDB_PLAY_END:
			waveOutReset(hWaveOut);
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
		//free(bWave);
		if (bSave)
		{
			free(bSave);
		}
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		OutputDebugStringA("wm create");
		//bWave = (LPSTR)malloc(SRATE * 3);

		wfe.wFormatTag = WAVE_FORMAT_PCM;
		wfe.nChannels = 1;
		wfe.nSamplesPerSec = SRATE;
		wfe.nAvgBytesPerSec = SRATE;
		wfe.wBitsPerSample = 8;
		//wfe.nBlockAlign = wfe.nChannels * wfe.wBitsPerSample / 8;
		wfe.nBlockAlign = 1;
		wfe.cbSize = 0;

		return 0;
	case WM_COMMAND:
		switch (LOWORD(wp)) {
		case DE_CLIENT:
			DialogBox(Wcl.hInstance, MAKEINTRESOURCE(IDD_FORMVIEW), hwnd, handleClientDialog);
			return 0;
		}
	case WIM_OPEN:
		OutputDebugStringA("open");
		dwLength = 0;
		bSave = (BYTE*)realloc(bSave, 1);
		waveInAddBuffer(hWaveIn, &whdr1, sizeof(WAVEHDR));
		waveInAddBuffer(hWaveIn, &whdr2, sizeof(WAVEHDR));
		waveInStart(hWaveIn);
		break;
	case WIM_DATA:
		// post message to process this input block received
		// NOTE: callback cannot call other waveform functions
		//....................................................

		//PostMessage((HWND)dwInstance, USR_INBLOCK, 0, dwParam1);
		OutputDebugStringA("data");
		bTmp = (BYTE*)realloc(bSave, dwLength + ((PWAVEHDR)lp)->dwBytesRecorded);
		char sbuf[512];
		sprintf_s(sbuf, "%d\n", ((PWAVEHDR)lp)->dwBytesRecorded);
		OutputDebugString(sbuf);

		if (blReset || !bTmp) {
			waveInClose(hWaveIn);
			blReset = FALSE;
			return 0;
		}

		bSave = bTmp;
		for (dwCount = 0; dwCount < ((PWAVEHDR)lp)->dwBytesRecorded; dwCount++)
			*(bSave + dwLength + dwCount) = *(((PWAVEHDR)lp)->lpData + dwCount);
		dwLength += ((PWAVEHDR)lp)->dwBytesRecorded;
		waveInAddBuffer(hWaveIn, (PWAVEHDR)lp, sizeof(WAVEHDR));

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
		break;
	case WIM_CLOSE:
		OutputDebugStringA("wim close");
		waveInUnprepareHeader(hWaveIn, &whdr1, sizeof(WAVEHDR));
		waveInUnprepareHeader(hWaveIn, &whdr2, sizeof(WAVEHDR));
		free(bWave1);
		free(bWave2);
		break; // don't care
	case WOM_OPEN:
		OutputDebugStringA("wom open");
		break;
	case WOM_DONE:
		OutputDebugStringA("done");
		waveOutClose(hWaveOut);
		break;
	case WOM_CLOSE:
		waveOutUnprepareHeader(hWaveOut, &whdr1, sizeof(WAVEHDR));
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

