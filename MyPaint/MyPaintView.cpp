
// MyPaintView.cpp: реализация класса CMyPaintView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MyPaint.h"
#endif

#include "MyPaintDoc.h"
#include "MyPaintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyPaintView

IMPLEMENT_DYNCREATE(CMyPaintView, CView)

BEGIN_MESSAGE_MAP(CMyPaintView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
//	ON_WM_MBUTTONDOWN()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// Создание или уничтожение CMyPaintView

CMyPaintView::CMyPaintView() noexcept :m_FirstPoint(0,0), n_SecondPoint(0,0), m_pTempElement(NULL)
{
	// TODO: добавьте код создания

}

CMyPaintView::~CMyPaintView()
{
}

BOOL CMyPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CMyPaintView

CElement * CMyPaintView::CreateElement(void) const
{
	CMyPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); // Check pointer

	switch (pDoc->GetElementType())
	{
	case RECTANGLE:
		return new CRectangle(m_FirstPoint, n_SecondPoint, pDoc->GetElementColor(), pDoc->GetPenWidth());
	case CIRCLE:
		return new CCircle(m_FirstPoint, n_SecondPoint, pDoc->GetElementColor(), pDoc->GetPenWidth());
	case CURVE:
		return new CCurve(m_FirstPoint, n_SecondPoint, pDoc->GetElementColor(), pDoc->GetPenWidth());
	case LINE:
		return new CLine(m_FirstPoint, n_SecondPoint, pDoc->GetElementColor(), pDoc->GetPenWidth());

	default:
		//Something Wrong
		AfxMessageBox(_T("Неверный код елемента"), MB_OK);
		AfxAbort();
	}
	return nullptr;
}

void CMyPaintView::OnDraw(CDC* pDC)
{
	CMyPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}


// Печать CMyPaintView

BOOL CMyPaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CMyPaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CMyPaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CMyPaintView

#ifdef _DEBUG
void CMyPaintView::AssertValid() const
{
	CView::AssertValid();
}

void CMyPaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyPaintDoc* CMyPaintView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyPaintDoc)));
	return (CMyPaintDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CMyPaintView

// Mouse Input

//On Mouse Move
void CMyPaintView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC aDC(this);
	if (nFlags& MK_LBUTTON)
	{
		n_SecondPoint = point;
		if (m_pTempElement)
		{
			if (CURVE == GetDocument()->GetElementType())
			{
				static_cast<CCurve*>(m_pTempElement)->AddSegment(n_SecondPoint);
				m_pTempElement->Draw(&aDC);
				return;
			}

			aDC.SetROP2(R2_NOTXORPEN);
			m_pTempElement->Draw(&aDC);
			delete m_pTempElement;
			m_pTempElement = nullptr;
		}
		m_pTempElement = CreateElement();
		m_pTempElement->Draw(&aDC);
	}
}

// On Left Button Up
void CMyPaintView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_pTempElement)
	{
		delete m_pTempElement;
		m_pTempElement = nullptr;
	}
}

// On Left Button Down
void CMyPaintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_FirstPoint = point;
}
