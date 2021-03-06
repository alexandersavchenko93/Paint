
// MyPaintDoc.cpp: реализация класса CMyPaintDoc 
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MyPaint.h"
#endif

#include "MyPaintDoc.h"
#include "Options.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyPaintDoc

IMPLEMENT_DYNCREATE(CMyPaintDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyPaintDoc, CDocument)
	ON_COMMAND(ID_COLOR_BLACK, &CMyPaintDoc::OnColorBlack)
	ON_COMMAND(ID_COLOR_RED, &CMyPaintDoc::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CMyPaintDoc::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CMyPaintDoc::OnColorBlue)
	ON_COMMAND(ID_ELEMENT_LINE, &CMyPaintDoc::OnElementLine)
	ON_COMMAND(ID_ELEMENT_RECTANGLE, &CMyPaintDoc::OnElementRectangle)
	ON_COMMAND(ID_ELEMENT_CIRCLE, &CMyPaintDoc::OnElementCircle)
	ON_COMMAND(ID_ELEMENT_CURVE, &CMyPaintDoc::OnElementCurve)
	ON_COMMAND(ID_OPTIONS_WIDTH, &CMyPaintDoc::OnOptionsWidth)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CMyPaintDoc::OnUpdateColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CMyPaintDoc::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CMyPaintDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CMyPaintDoc::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_LINE, &CMyPaintDoc::OnUpdateElementLine)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_RECTANGLE, &CMyPaintDoc::OnUpdateElementRectangle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CIRCLE, &CMyPaintDoc::OnUpdateElementCircle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CURVE, &CMyPaintDoc::OnUpdateElementCurve)
END_MESSAGE_MAP()


// Создание или уничтожение CMyPaintDoc

CMyPaintDoc::CMyPaintDoc() noexcept :m_Color(BLACK), m_Element(LINE)
{
	// TODO: добавьте код для одноразового вызова конструктора
	//  wer = 0;
}

CMyPaintDoc::~CMyPaintDoc()
{
}

BOOL CMyPaintDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация CMyPaintDoc

void CMyPaintDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CMyPaintDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CMyPaintDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CMyPaintDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CMyPaintDoc

#ifdef _DEBUG
void CMyPaintDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyPaintDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CMyPaintDoc


void CMyPaintDoc::OnColorBlack()
{
	m_Color = BLACK;
}


void CMyPaintDoc::OnColorRed()
{
	m_Color = RED;
}


void CMyPaintDoc::OnColorGreen()
{
	m_Color = GREEN;
}


void CMyPaintDoc::OnColorBlue()
{
	m_Color = BLUE;
}


void CMyPaintDoc::OnElementLine()
{
	m_Element = LINE;
}


void CMyPaintDoc::OnElementRectangle()
{
	m_Element = RECTANGLE;
}


void CMyPaintDoc::OnElementCircle()
{
	m_Element = CIRCLE;
}


void CMyPaintDoc::OnElementCurve()
{
	m_Element = CURVE;
}

void CMyPaintDoc::OnOptionsWidth()
{
	COptions dlgOptions;
	dlgOptions.Width = m_Width;
	if (dlgOptions.DoModal() == IDOK) 
	{
		m_Width = dlgOptions.Width;
	}
}


void CMyPaintDoc::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Color == BLACK);
}


void CMyPaintDoc::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Color == RED);
}


void CMyPaintDoc::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Color == GREEN);
}


void CMyPaintDoc::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Color == BLUE);
}


void CMyPaintDoc::OnUpdateElementLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == LINE);
}


void CMyPaintDoc::OnUpdateElementRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == RECTANGLE);
}


void CMyPaintDoc::OnUpdateElementCircle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == CIRCLE);
}


void CMyPaintDoc::OnUpdateElementCurve(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Element == CURVE);
}

