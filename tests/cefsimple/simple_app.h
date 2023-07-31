// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_

#include "include/cef_app.h"
#include "include/cef_render_process_handler.h"

#ifdef QT_PROJECT
#include <qobject.h>
#endif // QT_PROJECT

// Implement application-level callbacks for the browser process.
#ifdef QT_PROJECT
class SimpleApp :public QObject, public CefApp, public CefBrowserProcessHandler, public CefRenderProcessHandler {
    Q_OBJECT
#else
class SimpleApp : public CefApp, public CefBrowserProcessHandler, public CefRenderProcessHandler {
#endif // QT_PROJECT
 public:
  SimpleApp();

  // CefApp methods:
  CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override {
    return this;
  }

  // CefBrowserProcessHandler methods:
  void OnContextInitialized() override;
  void OnWebKitInitialized() override;
  CefRefPtr<CefClient> GetDefaultClient() override;

#ifdef QT_PROJECT
Q_SIGNALS:
    void cefOnctextInitialized();
    void cefOnWebKitInitialized();
#endif

 private:
  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(SimpleApp);
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
