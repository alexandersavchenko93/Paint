
// MyPaintView.h: интерфейс класса CMyPaintView
//

#pragma once
#include "Elements.h"


class CMyPaintView : public CView
{
protected: // создать только из сериализац
	CMyPaintView() noexcept;
	DECLARE_DYNCREATE(CMyPaintView)

// Атрибуты
public:
	CMyPaintDoc* GetDocument() const;

// Операции
public:

protected:
	CElement* CreateElement(void) const;  // Create Element
	
// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CMyPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
protected:
	CPoint m_FirstPoint;
	CPoint n_SecondPoint;
	CElement* m_pTempElement;
};

#ifndef _DEBUG  // версия отладки в MyPaintView.cpp
inline CMyPaintDoc* CMyPaintView::GetDocument() const
   { return reinterpret_cast<CMyPaintDoc*>(m_pDocument); }
#endif

