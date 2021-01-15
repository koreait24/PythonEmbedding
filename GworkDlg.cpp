
// GworkDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Gwork.h"
#include "GworkDlg.h"
#include "afxdialogex.h"
#include <Python.h>

#define SCHEMA_MAX 100000
#define WORD_MAX 1000

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGworkDlg 대화 상자



CGworkDlg::CGworkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GWORK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_URL, eURL);
	DDX_Control(pDX, IDC_EDIT_KEY, eKEY);
	DDX_Control(pDX, IDC_STAT_LIST, lSTAT);
	DDX_Control(pDX, IDC_PRN_LIST, lPRN);
	DDX_Control(pDX, IDC_CLD_LIST, lCLD);
	DDX_Control(pDX, IDC_LEAF_LIST, lLEAF);
	DDX_Control(pDX, IDC_PRN_EDIT, ePRN);
	DDX_Control(pDX, IDC_CLD_EDIT, eCLD);
	DDX_Control(pDX, IDC_LEAF_EDIT, eLEAF);
	DDX_Control(pDX, IDC_LVALUE_EDIT, eLVALUE);
}

BEGIN_MESSAGE_MAP(CGworkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SCH, &CGworkDlg::OnBnClickedBtnSch)
	ON_BN_CLICKED(IDC_BTN_CNT, &CGworkDlg::OnBnClickedBtnCnt)
	ON_BN_CLICKED(IDC_BTN_ADD, &CGworkDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, &CGworkDlg::OnBnClickedBtnDel)
	ON_LBN_SELCHANGE(IDC_PRN_LIST, &CGworkDlg::OnLbnSelchangePrnlist)
	ON_LBN_SELCHANGE(IDC_CLD_LIST, &CGworkDlg::OnLbnSelchangeCldlist)
	ON_LBN_SELCHANGE(IDC_LEAF_LIST, &CGworkDlg::OnLbnSelchangeLeaflist)
	ON_BN_CLICKED(IDC_BTN_RESET, &CGworkDlg::OnBnClickedBtnReset)
END_MESSAGE_MAP()


// CGworkDlg 메시지 처리기

BOOL CGworkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	eURL.SetWindowText(_T("https://test-da005.firebaseio.com/"));

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGworkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGworkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGworkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGworkDlg::OnBnClickedBtnSch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("firebase key file(*.json)|*.json|"); // 모든 파일 표시
		// _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
	CFileDialog dlg(TRUE, _T("*.json"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		// 파일 경로를 가져와 사용할 경우, Edit Control에 값 저장
		eKEY.SetWindowText(strPathName);
	}
}


void CGworkDlg::InitDBTree(CString getStr)
{
	lPRN.ResetContent();
	lCLD.ResetContent();
	lLEAF.ResetContent();

	wchar_t *Token, *nextToken, *tempStr;
	wchar_t seps1[] = L",{}";
	wchar_t *list[WORD_MAX];
	wchar_t getStrW[SCHEMA_MAX];

	wcscpy_s(getStrW, SCHEMA_MAX, getStr);

	Token = wcstok_s(getStrW, seps1, &nextToken);
	if (Token != NULL)
	{
		lPRN.AddString(Token);
		lCLD.AddString(Token);
		lLEAF.AddString(Token);
	}
	tempStr = nextToken;

	for (int i = 1; Token != NULL; i++)
	{
		Token = wcstok_s(NULL, seps1, &nextToken);
		if (Token != NULL)
		{
			lPRN.AddString(Token);
			lCLD.AddString(Token);
			lLEAF.AddString(Token);
		}
	}

}

void CGworkDlg::OnBnClickedBtnCnt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString getKey;

	GetDlgItemTextW(IDC_EDIT_KEY, getKey);

	if (!getKey.Compare(L"\0"))
	{
		MessageBox(L"키 파일이 선택되지 않았습니다.");
	}
	else
	{
		lSTAT.AddString(_T("Python 인터프리터 초기화"));
		SelectPyCnt();
	}
}


void CGworkDlg::OnBnClickedBtnAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SelectPyPush();
}


void CGworkDlg::OnBnClickedBtnDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SelectPyDel();
}

void CGworkDlg::OnLbnSelchangePrnlist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString getDB, cStr, lStr;
	int index;
	index = lPRN.GetCurSel();
	lPRN.GetText(index, getDB);

	AfxExtractSubString(cStr, getDB, 0, ':');
	AfxExtractSubString(lStr, cStr, 1, '\'');
	ePRN.SetWindowText(lStr);
}


void CGworkDlg::OnLbnSelchangeCldlist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString getDB, cStr, lStr;
	int index;
	index = lCLD.GetCurSel();
	lCLD.GetText(index, getDB);

	AfxExtractSubString(cStr, getDB, 0, ':');
	AfxExtractSubString(lStr, cStr, 1, '\'');
	eCLD.SetWindowText(lStr);
}


void CGworkDlg::OnLbnSelchangeLeaflist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString getDB, cStr, lStr;
	int index;
	index = lLEAF.GetCurSel();
	lLEAF.GetText(index, getDB);

	AfxExtractSubString(cStr, getDB, 0, ':');
	AfxExtractSubString(lStr, cStr, 1, '\'');
	eLEAF.SetWindowText(lStr);
}



void CGworkDlg::OnBnClickedBtnReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ePRN.SetWindowTextW(L"");
	eCLD.SetWindowTextW(L"");
	eLEAF.SetWindowTextW(L"");
	eLVALUE.SetWindowTextW(L"");
}

void CGworkDlg::SelectPyCnt()
{
	Py_Initialize();

	PyObject *sysmodule = PyImport_ImportModule("sys");
	PyObject *syspath = PyObject_GetAttrString(sysmodule, "path");

	char Path[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, Path);

	PyList_Append(syspath, PyUnicode_FromString(Path));

	PyObject *pFunc, *pValue, *PyArgs;
	PyObject *pName = PyUnicode_FromString("ReadFB");
	PyObject *pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	CString urlStr, keyStr, statMsg;

	if (pModule != NULL)
	{
		PyArgs = PyTuple_New(2);
		GetDlgItemTextW(IDC_URL_EDIT, urlStr);
		PyTuple_SET_ITEM(PyArgs, 0, PyUnicode_FromUnicode(urlStr, urlStr.GetLength()));
		GetDlgItemTextW(IDC_KEY_EDIT, keyStr);
		PyTuple_SET_ITEM(PyArgs, 1, PyUnicode_FromUnicode(keyStr, keyStr.GetLength()));

		pFunc = PyObject_GetAttrString(pModule, "dbconnect");

		if (pFunc && PyCallable_Check(pFunc))
		{
			pValue = PyObject_CallObject(pFunc, PyArgs);
			if (pValue != NULL)
			{
				CString getStr;
				getStr = PyUnicode_AsUnicode(pValue);
				statMsg.Format(_T("(연결 성공) 실시간 데이터베이스 타겟 : (\"%s\")"),
					urlStr.GetBuffer());
				lSTAT.AddString(statMsg);
				statMsg.Format(_T("키 디렉터리 : (\"%s\"))"),
					keyStr.GetBuffer());
				lSTAT.AddString(statMsg);
				StatusConnect();
				InitDBTree(getStr);

				Py_DECREF(pModule);
				Py_XDECREF(PyArgs);
				Py_DECREF(pValue);
				Py_DECREF(pFunc);
			}
			else
			{
				lSTAT.AddString(L"연결실패.");
			}
		}
	}

	Py_Finalize();
}

void CGworkDlg::StatusConnect()
{
	GetDlgItem(IDC_URL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_RESET)->EnableWindow(TRUE);
}

void CGworkDlg::SelectPyPush()
{
	Py_Initialize();

	PyObject *sysmodule = PyImport_ImportModule("sys");
	PyObject *syspath = PyObject_GetAttrString(sysmodule, "path");

	char Path[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, Path);

	PyList_Append(syspath, PyUnicode_FromString(Path));

	PyObject *pFunc, *pValue, *PyArgs;
	PyObject *pName = PyUnicode_FromString("ReadFB");
	PyObject *pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	CString urlStr, keyStr, keyRef, keyChild, keyPush, keyValue, statMsg;
	const char getStr[WORD_MAX] = "\0";
	if (pModule != NULL)
	{
		PyArgs = PyTuple_New(6);

		GetDlgItemTextW(IDC_URL, urlStr);
		PyTuple_SET_ITEM(PyArgs, 0, PyUnicode_FromUnicode(urlStr, urlStr.GetLength()));
		GetDlgItemTextW(IDC_EDIT_KEY, keyStr);
		PyTuple_SET_ITEM(PyArgs, 1, PyUnicode_FromUnicode(keyStr, keyStr.GetLength()));
		GetDlgItemTextW(IDC_PRN_EDIT, keyRef);
		PyTuple_SET_ITEM(PyArgs, 2, PyUnicode_FromUnicode(keyRef, keyRef.GetLength()));
		GetDlgItemTextW(IDC_CLD_EDIT, keyChild);
		PyTuple_SET_ITEM(PyArgs, 3, PyUnicode_FromUnicode(keyChild, keyChild.GetLength()));
		GetDlgItemTextW(IDC_LEAF_EDIT, keyPush);
		PyTuple_SET_ITEM(PyArgs, 4, PyUnicode_FromUnicode(keyPush, keyPush.GetLength()));
		GetDlgItemTextW(IDC_LVALUE_EDIT, keyValue);
		PyTuple_SET_ITEM(PyArgs, 5, PyUnicode_FromUnicode(keyValue, keyValue.GetLength()));

		pFunc = PyObject_GetAttrString(pModule, "dbpush");

		if (pFunc && PyCallable_Check(pFunc))
		{
			pValue = PyObject_CallObject(pFunc, PyArgs);
			if (pValue != NULL)
			{
				CString getStr;
				getStr = PyUnicode_AsUnicode(pValue);

				statMsg.Format(_T("데이터 푸쉬 (\"%s\") 성공, 자식 노드 (\"%s\") 부모 노드 (\"%s\")"),
					keyPush.GetBuffer(), keyChild.GetBuffer(), keyRef.GetBuffer());
				lSTAT.AddString(statMsg);
				if (wcscmp(keyValue, L""))
				{
					statMsg.Format(_T("키 값 업데이트 : (\"%s\")"), keyValue.GetBuffer());
					lSTAT.AddString(statMsg);
				}

				InitDBTree(getStr);

				Py_DECREF(pModule);
				Py_XDECREF(PyArgs);
				Py_DECREF(pValue);
				Py_DECREF(pFunc);
			}

			else
			{
				lSTAT.AddString(L"데이터 푸쉬에 실패했습니다. 노드를 확인해주세요.");
			}
		}
	}
	else
	{
		MessageBox(L"Data Push Failed");
	}

	Py_Finalize();
}


void CGworkDlg::SelectPyDel()
{
	Py_Initialize();

	PyObject *sysmodule = PyImport_ImportModule("sys");
	PyObject *syspath = PyObject_GetAttrString(sysmodule, "path");

	char Path[_MAX_PATH];
	GetCurrentDirectoryA(_MAX_PATH, Path);

	PyList_Append(syspath, PyUnicode_FromString(Path));

	PyObject *pFunc, *pValue, *PyArgs;
	PyObject *pName = PyUnicode_FromString("ReadFB");
	PyObject *pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	CString urlStr, keyStr, keyRef, keyChild, keyDel, statMsg;
	const char getStr[WORD_MAX] = "\0";
	if (pModule != NULL)
	{
		PyArgs = PyTuple_New(5);

		GetDlgItemTextW(IDC_URL_EDIT, urlStr);
		PyTuple_SET_ITEM(PyArgs, 0, PyUnicode_FromUnicode(urlStr, urlStr.GetLength()));
		GetDlgItemTextW(IDC_KEY_EDIT, keyStr);
		PyTuple_SET_ITEM(PyArgs, 1, PyUnicode_FromUnicode(keyStr, keyStr.GetLength()));
		GetDlgItemTextW(IDC_PRN_EDIT, keyRef);
		PyTuple_SET_ITEM(PyArgs, 2, PyUnicode_FromUnicode(keyRef, keyRef.GetLength()));
		GetDlgItemTextW(IDC_CLD_EDIT, keyChild);
		PyTuple_SET_ITEM(PyArgs, 3, PyUnicode_FromUnicode(keyChild, keyChild.GetLength()));
		GetDlgItemTextW(IDC_LEAF_EDIT, keyDel);
		PyTuple_SET_ITEM(PyArgs, 4, PyUnicode_FromUnicode(keyDel, keyDel.GetLength()));

		pFunc = PyObject_GetAttrString(pModule, "dbdel");

		if (pFunc && PyCallable_Check(pFunc))
		{
			pValue = PyObject_CallObject(pFunc, PyArgs);
			if (pValue != NULL)
			{
				CString getStr;
				getStr = PyUnicode_AsUnicode(pValue);

				if (!getStr.Compare(L"\0")) 
				{
					lSTAT.AddString(L"데이터 삭제에 실패했습니다. 노드를 확인해주세요.");
				}
				else
				{
					statMsg.Format(_T("데이터 삭제 (\"%s\") 성공, 자식 노드 (\"%s\") 부모 노드 (\"%s\")"),
						keyDel.GetBuffer(), keyChild.GetBuffer(), keyRef.GetBuffer());
					lSTAT.AddString(statMsg);

					InitDBTree(getStr);
				}
				Py_DECREF(pModule);
				Py_XDECREF(PyArgs);
				Py_DECREF(pValue);
				Py_DECREF(pFunc);
			}
		}
	}
	Py_Finalize();
}