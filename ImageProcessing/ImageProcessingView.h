
// ImageProcessingView.h : CImageProcessingView 类的接口
//

#pragma once


class CImageProcessingView : public CScrollView
{
protected: // 仅从序列化创建
	CImageProcessingView();
	DECLARE_DYNCREATE(CImageProcessingView)

// 特性
public:
	CImageProcessingDoc* GetDocument() const;

private:
	CBitmap m_bitmapMemory;	 // 内存位图
	CDC     m_dcMemory;	     // 内存dc
	
	int m_iImgHeight;		// 图片高
	int m_iImgWidth;		// 图片宽

// 操作
public:
	void CreateMemoryDC();	   // 创建位图和内存dc
	void ReleaseMemoryDC();    // 释放位图和内存dc

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ImageProcessingView.cpp 中的调试版本
inline CImageProcessingDoc* CImageProcessingView::GetDocument() const
   { return reinterpret_cast<CImageProcessingDoc*>(m_pDocument); }
#endif

