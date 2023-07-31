// Copyright (c) 2023 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=1f351fed26d9a331d9924c893d8b3d52064a1ecf$
//

#include "libcef_dll/ctocpp/thread_ctocpp.h"
#include "libcef_dll/ctocpp/task_runner_ctocpp.h"
#include "libcef_dll/shutdown_checker.h"

// STATIC METHODS - Body may be edited by hand.

NO_SANITIZE("cfi-icall")
CefRefPtr<CefThread> CefThread::CreateThread(
    const CefString& display_name,
    cef_thread_priority_t priority,
    cef_message_loop_type_t message_loop_type,
    bool stoppable,
    cef_com_init_mode_t com_init_mode) {
  shutdown_checker::AssertNotShutdown();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: display_name

  // Execute
  cef_thread_t* _retval =
      cef_thread_create(display_name.GetStruct(), priority, message_loop_type,
                        stoppable, com_init_mode);

  // Return type: refptr_same
  return CefThreadCToCpp::Wrap(_retval);
}

// VIRTUAL METHODS - Body may be edited by hand.

NO_SANITIZE("cfi-icall")
CefRefPtr<CefTaskRunner> CefThreadCToCpp::GetTaskRunner() {
  shutdown_checker::AssertNotShutdown();

  cef_thread_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_task_runner)) {
    return nullptr;
  }

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_task_runner_t* _retval = _struct->get_task_runner(_struct);

  // Return type: refptr_same
  return CefTaskRunnerCToCpp::Wrap(_retval);
}

NO_SANITIZE("cfi-icall")
cef_platform_thread_id_t CefThreadCToCpp::GetPlatformThreadId() {
  shutdown_checker::AssertNotShutdown();

  cef_thread_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_platform_thread_id)) {
    return kInvalidPlatformThreadId;
  }

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_platform_thread_id_t _retval = _struct->get_platform_thread_id(_struct);

  // Return type: simple
  return _retval;
}

NO_SANITIZE("cfi-icall") void CefThreadCToCpp::Stop() {
  shutdown_checker::AssertNotShutdown();

  cef_thread_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, stop)) {
    return;
  }

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->stop(_struct);
}

NO_SANITIZE("cfi-icall") bool CefThreadCToCpp::IsRunning() {
  shutdown_checker::AssertNotShutdown();

  cef_thread_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, is_running)) {
    return false;
  }

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->is_running(_struct);

  // Return type: bool
  return _retval ? true : false;
}

// CONSTRUCTOR - Do not edit by hand.

CefThreadCToCpp::CefThreadCToCpp() {}

// DESTRUCTOR - Do not edit by hand.

CefThreadCToCpp::~CefThreadCToCpp() {
  shutdown_checker::AssertNotShutdown();
}

template <>
cef_thread_t*
CefCToCppRefCounted<CefThreadCToCpp, CefThread, cef_thread_t>::UnwrapDerived(
    CefWrapperType type,
    CefThread* c) {
  NOTREACHED() << "Unexpected class type: " << type;
  return nullptr;
}

template <>
CefWrapperType CefCToCppRefCounted<CefThreadCToCpp, CefThread, cef_thread_t>::
    kWrapperType = WT_THREAD;
