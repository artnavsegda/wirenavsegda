#include <windows.h>
#include "settings.h"
#include "dialog.h"

struct eeprom e;

BOOL CALLBACK DialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hwndDlg, ID_DIALOG_TEXT, "Hello");
		for (int i = ID_DIALOG_COMBO_STARTLEVEL; i <= ID_DIALOG_COMBO_POSTCALIBRATIONDELAY; i++)
		{
			SendDlgItemMessage(hwndDlg, i, CB_ADDSTRING, 0, "Start level");
			SendDlgItemMessage(hwndDlg, i, CB_ADDSTRING, 0, "Cell delay");
			SendDlgItemMessage(hwndDlg, i, CB_ADDSTRING, 0, "Cell level");
			SendDlgItemMessage(hwndDlg, i, CB_ADDSTRING, 0, "Zero delay");
			SendDlgItemMessage(hwndDlg, i, CB_ADDSTRING, 0, "Zero test");
			SendDlgItemMessage(hwndDlg, i, CB_ADDSTRING, 0, "Purge");
			SendDlgItemMessage(hwndDlg, i, CB_ADDSTRING, 0, "Total mercury delay");
			SendDlgItemMessage(hwndDlg, i, CB_ADDSTRING, 0, "Total mercury");
			SendDlgItemMessage(hwndDlg, i, CB_ADDSTRING, 0, "Elemental mercury delay");
			SendDlgItemMessage(hwndDlg, i, CB_ADDSTRING, 0, "Elemental mercury");
			SendDlgItemMessage(hwndDlg, i, CB_ADDSTRING, 0, "Pre-calibration delay");
			SendDlgItemMessage(hwndDlg, i, CB_ADDSTRING, 0, "Calibration");
			SendDlgItemMessage(hwndDlg, i, CB_ADDSTRING, 0, "Post-calibration delay");
			SendDlgItemMessage(hwndDlg, i, CB_SETCURSEL, 0, ((char *)&e.jump_table)[i]);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_DIALOG_TEXT:
			break;
		case ID_DIALOG_EXIT:
			DestroyWindow(hwndDlg);
			return TRUE;
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwndDlg);
		return TRUE;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;
		break;
	}
	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	/*HANDLE eepromfile = CreateFile("eeprom.raw", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (eepromfile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "cannot open eeprom file", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	int numread;
	ReadFile(eepromfile, (void *)&e, sizeof(e), &numread, NULL);*/

	MSG Msg;
	HWND hwnd = CreateDialog(hInstance, "MainDialog", 0, DialogProc);
	ShowWindow(hwnd, nCmdShow);

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return 0;
}