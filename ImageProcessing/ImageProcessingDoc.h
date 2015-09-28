
// ImageProcessingDoc.h : CImageProcessingDoc 类的接口
//

#include <string>
using std::string;
#pragma once


class CImageProcessingDoc : public CDocument
{
protected: // 仅从序列化创建
	CImageProcessingDoc();
	DECLARE_DYNCREATE(CImageProcessingDoc)

private:

	string m_strImagePath;		

// 特性
public:

// 操作
public:
	void Cstring2String(const CString str1, string &str2);

	string GetImagePath();

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileOpen();
};
