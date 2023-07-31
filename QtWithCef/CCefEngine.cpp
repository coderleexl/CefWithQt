#include "CCefEngine.h"
#include "QResizeEvent"
#include "thread"
#include "qdebug.h"
#include "../include/cef_scheme.h"
#include "../include/cef_parser.h"
#include "QJsonObject"
#include "QJsonDocument"

class MyJSExtension :  public CefV8Handler {
public:
	// ʵ�� JavaScript ������ִ���߼�
	bool Execute(const CefString& name, CefRefPtr<CefV8Value> object,
		const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval,
		CefString& exception) override {
		if (name == "getData") {
			// �������ҳ��ȡ���ݵ��߼�
			// ...
            QJsonObject root;
            QJsonDocument doc(root);
            root.insert("name", "coerleex");
            root.insert("addr", "wuhan");
            retval = CefV8Value::CreateString(doc.toJson().data());

			return true;
		}
		else if (name == "sendData") {
			// �������ݷ��͵���ҳ���߼�
			// ...
			return true;
		}

		return false;
	}
    IMPLEMENT_REFCOUNTING(MyJSExtension);
};

CCefEngine* CCefEngine::GetInstance()
{
	static CCefEngine cefEngine;
	return &cefEngine;
}

bool CCefEngine::InitEngine()
{
    CefEnableHighDPISupport();
	bool ret = CefRegisterExtension("myExtension",
		"function getData() { native function getData(); return getData(); }"
		"function sendData(data) { native function sendData(); sendData(data); }",
		new MyJSExtension);
    
    HINSTANCE hInstance = GetModuleHandle(nullptr);
    CefMainArgs main_args(hInstance);
    int exit_code = CefExecuteProcess(main_args, nullptr, nullptr);
    if (exit_code >= 0) {
        return false;
    }
    CefSettings settings;
    settings.no_sandbox = true;
    // ������������CEF�ڵ������߳�������Browser�Ľ��棬�����������߳��ϡ�
    settings.multi_threaded_message_loop = true;
    //settings.log_severity = LOGSEVERITY_DISABLE; //��־

    // ���� SimpleApp ����
    CefRefPtr<SimpleApp> app = new SimpleApp;
    CefInitialize(main_args, settings, app, nullptr);
    connect(app.get(), &SimpleApp::cefOnctextInitialized, this, [this] {
        m_bIsInitFinished = true;
        m_pSimpleHandler = new SimpleHandler(false);
        Q_EMIT InitFinished();
        
        while (!m_CreateWindowQueue.empty())
        {
            auto p = m_CreateWindowQueue.front();
            m_CreateWindowQueue.pop_front();
            CreateBrowseWindow(p);
        }

        });
   
    return ret;
}

bool CCefEngine::IsInitFinished()
{
    return m_bIsInitFinished;
}

CCefEngine::CCefEngine(QObject *parent)
	: QObject(parent)
{}

void CCefEngine::CreateBrowseWindow(CCefWebView* parent)
{
    if (m_bIsInitFinished) {
        // ��������ã�
        CefBrowserSettings browser_settings;
        // Ҫ�򿪵���ַ
        std::string url = "https://www.google.com";
        // �����������Ϣ
        CefWindowInfo window_info;

        //window_info.SetAsPopup(NULL, "cefsimple");
        // ��ȡǶ�봰��ľ��
        CefWindowInfo cefWndInfo;
        CefRect winRect;
        QRect qtRect = parent->rect();
        winRect.Set(qtRect.left(), qtRect.top(), qtRect.width(), qtRect.height());

        window_info.SetAsChild((HWND)parent->winId(), winRect);
        // Create the first browser window.
        bool ret = CefBrowserHost::CreateBrowser(window_info, m_pSimpleHandler, url, browser_settings,
            nullptr, nullptr);
        Q_UNUSED(ret)
    }
    else
    {
        m_CreateWindowQueue.push_back(parent);
    }
}

CCefEngine::~CCefEngine()
{
    CefShutdown();
}

CCefWebView::CCefWebView(QWidget* parent) :QWidget(parent) 
{
    LONG_PTR style = GetWindowLongPtr(HWND(winId()), GWL_STYLE);
    style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

    // ���ø��º�Ĵ�����ʽ
    SetWindowLongPtr(HWND(winId()), GWL_STYLE, style);
}

void CCefWebView::SetUrl(const QString& url)
{

    if (m_sUrl.isEmpty())
    {
        CCefEngine::GetInstance()->CreateBrowseWindow(this);
    }
    else
    {
        auto browse = CCefEngine::GetInstance()->m_pSimpleHandler->GetBrowserByParent((HWND)winId());
        if (browse)
        {
            browse->GetMainFrame()->LoadURL(url.toStdString());
        }
    }
    m_sUrl = url;
}

void CCefWebView::resizeEvent(QResizeEvent* e)
{
    if (!CCefEngine::GetInstance()->IsInitFinished()) return;    
    auto browse = CCefEngine::GetInstance()->m_pSimpleHandler->GetBrowserByParent((HWND)winId());
    if (browse)
    {
        auto p = rect().topLeft();
        int w_ = e->size().width();
        int h_ = e->size().height();
        RECT winRect;
        GetWindowRect((HWND)winId(), &winRect);
        //SetWindowPos(browse->GetHost()->GetWindowHandle(), nullptr, x_, y_, w_, h_, 0);
        ::MoveWindow(browse->GetHost()->GetWindowHandle(),p.x(), p.y(), w_, h_, false);
        qInfo() << mapToGlobal(p) << w_ << h_ << " rect: " << rect() <<objectName();

		CefString code = "var data = myExtension.getData(); myExtension.sendData(data); ');";
        browse->GetMainFrame()->ExecuteJavaScript(code, browse->GetMainFrame()->GetURL(), 0);

        /*RECT winRect;
        GetWindowRect(browse->GetHost()->GetWindowHandle(), &winRect);
        qInfo() <<  mapToGlobal(p) << w_ << h_ << " rect: " << rect()<< winRect.bottom - winRect.top << winRect.top;
        InvalidateRect(browse->GetHost()->GetWindowHandle(), &winRect, true);
        */
    }
}
