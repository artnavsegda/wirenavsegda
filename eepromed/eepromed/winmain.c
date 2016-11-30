#include <windows.h>
#include "settings.h"
#include "dialog.h"

struct eeprom e = {
	.jump_table = {
		.startlevel = CELLDELAY,
		.celldelay = CELLLEVEL,
		.celllevel = TOTALMERCURYDELAY,
		.zerodelay = ZEROTEST,
		.zerotest = TOTALMERCURYDELAY,
		.purge = TOTALMERCURYDELAY,
		.totalmercurydelay = TOTALMERCURY,
		.totalmercury = TOTALMERCURY,
		.elementalmercurydelay = ELEMENTALMERCURY,
		.elementalmercury = TOTALMERCURY,
		.precalibrationdelay = CALIBRATION,
		.calibration = POSTCALIBRATIONDELAY,
		.postcalibrationdelay = TOTALMERCURYDELAY
	}
};

int modecount(int mode)
{
	switch (mode)
	{
	case STARTLEVEL: return 0;
	case CELLDELAY: return 1;
	case CELLLEVEL: return 2;
	case ZERODELAY: return 3;
	case ZEROTEST: return 4;
	case PURGE: return 5;
	case TOTALMERCURYDELAY: return 6;
	case TOTALMERCURY: return 7;
	case ELEMENTALMERCURYDELAY: return 8;
	case ELEMENTALMERCURY: return 9;
	case PRECALIBRATIONDELAY: return 10;
	case CALIBRATION: return 11;
	case POSTCALIBRATIONDELAY: return 12;
	}
}

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
			SendDlgItemMessage(hwndDlg, i, CB_SETCURSEL, modecount(((int *)&e.jump_table)[i-ID_DIALOG_COMBO_STARTLEVEL]),0);
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