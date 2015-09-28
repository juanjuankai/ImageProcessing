
// ImageProcessingView.cpp : CImageProcessingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CImageProcessingView 构造/析构

CImageProcessingView::CImageProcessingView():
m_iImgHeight(0),
m_iImgWidth(0)
{
	// TODO:  在此处添加构造代码
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
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CImageProcessingView 绘制
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

	// 绘图
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
	
	// 获取客户区大小
	CRect rect;
	GetClientRect(&rect);

	int nWidth = m_iImgWidth > rect.Width() ? m_iImgWidth : rect.Width();
	int nHeight = m_iImgHeight > rect.Height() ? m_iImgHeight : rect.Height();

	// 滚动窗口
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
	// TODO:  计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProcessingView 打印

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CImageProcessingView 诊断

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG

// CImageProcessingView 消息处理程序
