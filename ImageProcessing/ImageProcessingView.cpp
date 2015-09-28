
// ImageProcessingView.cpp : CImageProcessingView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

// CImageProcessingView

IMPLEMENT_DYNCREATE(CImageProcessingView, CScrollView)

BEGIN_MESSAGE_MAP(CImageProcessingView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CImageProcessingView ����/����

CImageProcessingView::CImageProcessingView():
m_iImgHeight(0),
m_iImgWidth(0)
{
	// TODO:  �ڴ˴���ӹ������
	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

CImageProcessingView::~CImageProcessingView()
{
}

BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CImageProcessingView ����
void CImageProcessingView::CreateMemoryDC()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	wchar_t strImg[1024];
	MultiByteToWideChar(CP_ACP, NULL, pDoc->GetImagePath().c_str(),\
		1024, strImg, 1024);
	Image img(strImg);
	m_iImgWidth = img.GetWidth();
	m_iImgHeight = img.GetHeight();

	CClientDC dc(this);
	m_dcMemory.CreateCompatibleDC(&dc);
	m_bitmapMemory.CreateCompatibleBitmap(&dc, m_iImgWidth, m_iImgHeight);
	SelectObject(m_dcMemory, m_bitmapMemory);

	// ��ͼ
	Graphics graphics(m_dcMemory);
	graphics.DrawImage(&img, 0, 0);
}

void CImageProcessingView::ReleaseMemoryDC()
{
	m_bitmapMemory.DeleteObject();
	m_dcMemory.DeleteDC();
}

void CImageProcessingView::OnDraw(CDC* pDC)
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->GetImagePath() == "")
		return;
	
	// ��ȡ�ͻ�����С
	CRect rect;
	GetClientRect(&rect);

	int nWidth = m_iImgWidth > rect.Width() ? m_iImgWidth : rect.Width();
	int nHeight = m_iImgHeight > rect.Height() ? m_iImgHeight : rect.Height();

	// ��������
	CSize sizeTotal;
	sizeTotal.cx = nWidth;
	sizeTotal.cy = nHeight;
	SetScrollSizes(MM_TEXT, sizeTotal);

	pDC->BitBlt(0, 0, nWidth, nHeight, &m_dcMemory, 0, 0, SRCCOPY);
}

void CImageProcessingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO:  �������ͼ�ĺϼƴ�С
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProcessingView ��ӡ

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CImageProcessingView ���

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG

// CImageProcessingView ��Ϣ�������
