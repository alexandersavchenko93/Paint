// Options.cpp: файл реализации
//

#include "stdafx.h"
#include "MyPaint.h"
#include "Options.h"
#include "afxdialogex.h"


// Диалоговое окно COptions

IMPLEMENT_DYNAMIC(COptions, CDialogEx)

COptions::COptions(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_OPTIONS, pParent)
	, Width(1)
{

}

COptions::~COptions()
{
}

void COptions::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WIDTH, Width);
	DDV_MinMaxInt(pDX, Width, 1, 5);
}


BEGIN_MESSAGE_MAP(COptions, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений COptions
