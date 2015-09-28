
// ImageProcessingDoc.h : CImageProcessingDoc ��Ľӿ�
//

#include <string>
using std::string;
#pragma once


class CImageProcessingDoc : public CDocument
{
protected: // �������л�����
	CImageProcessingDoc();
	DECLARE_DYNCREATE(CImageProcessingDoc)

private:

	string m_strImagePath;		

// ����
public:

// ����
public:
	void Cstring2String(const CString str1, string &str2);

	string GetImagePath();

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileOpen();
};
