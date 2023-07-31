#pragma once

#include <qapplication.h>
#include <QObject>
#include <qwidget.h>
#include <QQueue>
#include "../cef_binary/tests/cefsimple/simple_handler.h"
#include "../cef_binary/tests/cefsimple/simple_app.h"

class CCefWebView :public QWidget {
	Q_OBJECT

public:
	CCefWebView(QWidget* parent);
	void SetUrl(const QString& url);
	void resizeEvent(QResizeEvent* e) override;
private:
	QString m_sUrl;
};

class CCefEngine  : public QObject
{
	Q_OBJECT
	friend class CCefWebView;
public:
		~CCefEngine();
		static CCefEngine* GetInstance();
		bool InitEngine();
		bool IsInitFinished();
Q_SIGNALS:
	void InitFinished();
private:
	QQueue <CCefWebView*> m_CreateWindowQueue;
	CCefEngine(QObject *parent = nullptr);
	void CreateBrowseWindow(CCefWebView* parent);

	CefRefPtr<SimpleApp> m_pSimpleApp;
	CefRefPtr<SimpleHandler> m_pSimpleHandler;
	bool m_bIsInitFinished{ false };
};
