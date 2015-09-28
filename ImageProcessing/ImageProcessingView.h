
// ImageProcessingView.h : CImageProcessingView ��Ľӿ�
//

#pragma once


class CImageProcessingView : public CScrollView
{
protected: // �������л�����
	CImageProcessingView();
	DECLARE_DYNCREATE(CImageProcessingView)

// ����
public:
	CImageProcessingDoc* GetDocument() const;

private:
	CBitmap m_bitmapMemory;	 // �ڴ�λͼ
	CDC     m_dcMemory;	     // �ڴ�dc
	
	int m_iImgHeight;		// ͼƬ��
	int m_iImgWidth;		// ͼƬ��

// ����
public:
	void CreateMemoryDC();	   // ����λͼ���ڴ�dc
	void ReleaseMemoryDC();    // �ͷ�λͼ���ڴ�dc

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ImageProcessingView.cpp �еĵ��԰汾
inline CImageProcessingDoc* CImageProcessingView::GetDocument() const
   { return reinterpret_cast<CImageProcessingDoc*>(m_pDocument); }
#endif

