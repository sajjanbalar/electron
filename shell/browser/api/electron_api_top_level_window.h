// Copyright (c) 2018 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef SHELL_BROWSER_API_ELECTRON_API_TOP_LEVEL_WINDOW_H_
#define SHELL_BROWSER_API_ELECTRON_API_TOP_LEVEL_WINDOW_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "base/task/post_task.h"
#include "content/public/browser/browser_task_traits.h"
#include "content/public/browser/browser_thread.h"
#include "gin/handle.h"
#include "shell/browser/native_window.h"
#include "shell/browser/native_window_observer.h"
#include "shell/common/api/electron_api_native_image.h"
#include "shell/common/gin_helper/trackable_object.h"

namespace electron {

namespace api {

class View;

class TopLevelWindow : public gin_helper::TrackableObject<TopLevelWindow>,
                       public NativeWindowObserver {
 public:
  static gin_helper::WrappableBase* New(gin_helper::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  base::WeakPtr<TopLevelWindow> GetWeakPtr() {
    return weak_factory_.GetWeakPtr();
  }

  NativeWindow* window() const { return window_.get(); }

 protected:
  // Common constructor.
  TopLevelWindow(v8::Isolate* isolate, const gin_helper::Dictionary& options);
  // Creating independent TopLevelWindow instance.
  TopLevelWindow(gin_helper::Arguments* args,
                 const gin_helper::Dictionary& options);
  ~TopLevelWindow() override;

  // TrackableObject:
  void InitWith(v8::Isolate* isolate, v8::Local<v8::Object> wrapper) override;

  // NativeWindowObserver:
  void WillCloseWindow(bool* prevent_default) override;
  void OnWindowClosed() override;
  void OnWindowEndSession() override;
  void OnWindowBlur() override;
  void OnWindowFocus() override;
  void OnWindowShow() override;
  void OnWindowHide() override;
  void OnWindowMaximize() override;
  void OnWindowUnmaximize() override;
  void OnWindowMinimize() override;
  void OnWindowRestore() override;
  void OnWindowWillResize(const gfx::Rect& new_bounds,
                          bool* prevent_default) override;
  void OnWindowResize() override;
  void OnWindowWillMove(const gfx::Rect& new_bounds,
                        bool* prevent_default) override;
  void OnWindowMove() override;
  void OnWindowMoved() override;
  void OnWindowScrollTouchBegin() override;
  void OnWindowScrollTouchEnd() override;
  void OnWindowSwipe(const std::string& direction) override;
  void OnWindowRotateGesture(float rotation) override;
  void OnWindowSheetBegin() override;
  void OnWindowSheetEnd() override;
  void OnWindowEnterFullScreen() override;
  void OnWindowLeaveFullScreen() override;
  void OnWindowEnterHtmlFullScreen() override;
  void OnWindowLeaveHtmlFullScreen() override;
  void OnWindowAlwaysOnTopChanged() override;
  void OnExecuteAppCommand(const std::string& command_name) override;
  void OnTouchBarItemResult(const std::string& item_id,
                            const base::DictionaryValue& details) override;
  void OnNewWindowForTab() override;
#if defined(OS_WIN)
  void OnWindowMessage(UINT message, WPARAM w_param, LPARAM l_param) override;
#endif

  // Public APIs of NativeWindow.
  void SetContentView(gin::Handle<View> view);
  void Close();
  virtual void Focus();
  virtual void Blur();
  bool IsFocused();
  void Show();
  void ShowInactive();
  void Hide();
  bool IsVisible();
  bool IsEnabled();
  void SetEnabled(bool enable);
  void Maximize();
  void Unmaximize();
  bool IsMaximized();
  void Minimize();
  void Restore();
  bool IsMinimized();
  void SetFullScreen(bool fullscreen);
  bool IsFullscreen();
  void SetBounds(const gfx::Rect& bounds, gin_helper::Arguments* args);
  gfx::Rect GetBounds();
  void SetSize(int width, int height, gin_helper::Arguments* args);
  std::vector<int> GetSize();
  void SetContentSize(int width, int height, gin_helper::Arguments* args);
  std::vector<int> GetContentSize();
  void SetContentBounds(const gfx::Rect& bounds, gin_helper::Arguments* args);
  gfx::Rect GetContentBounds();
  bool IsNormal();
  gfx::Rect GetNormalBounds();
  void SetMinimumSize(int width, int height);
  std::vector<int> GetMinimumSize();
  void SetMaximumSize(int width, int height);
  std::vector<int> GetMaximumSize();
  void SetSheetOffset(double offsetY, gin_helper::Arguments* args);
  void SetResizable(bool resizable);
  bool IsResizable();
  void SetMovable(bool movable);
  void MoveAbove(const std::string& sourceId, gin_helper::Arguments* args);
  void MoveTop();
  bool IsMovable();
  void SetMinimizable(bool minimizable);
  bool IsMinimizable();
  void SetMaximizable(bool maximizable);
  bool IsMaximizable();
  void SetFullScreenable(bool fullscreenable);
  bool IsFullScreenable();
  void SetClosable(bool closable);
  bool IsClosable();
  void SetAlwaysOnTop(bool top, gin_helper::Arguments* args);
  bool IsAlwaysOnTop();
  void Center();
  void SetPosition(int x, int y, gin_helper::Arguments* args);
  std::vector<int> GetPosition();
  void SetTitle(const std::string& title);
  std::string GetTitle();
  void SetAccessibleTitle(const std::string& title);
  std::string GetAccessibleTitle();
  void FlashFrame(bool flash);
  void SetSkipTaskbar(bool skip);
  void SetExcludedFromShownWindowsMenu(bool excluded);
  bool IsExcludedFromShownWindowsMenu();
  void SetSimpleFullScreen(bool simple_fullscreen);
  bool IsSimpleFullScreen();
  void SetKiosk(bool kiosk);
  bool IsKiosk();
  virtual void SetBackgroundColor(const std::string& color_name);
  std::string GetBackgroundColor();
  void SetHasShadow(bool has_shadow);
  bool HasShadow();
  void SetOpacity(const double opacity);
  double GetOpacity();
  void SetShape(const std::vector<gfx::Rect>& rects);
  void SetRepresentedFilename(const std::string& filename);
  std::string GetRepresentedFilename();
  void SetDocumentEdited(bool edited);
  bool IsDocumentEdited();
  void SetIgnoreMouseEvents(bool ignore, gin_helper::Arguments* args);
  void SetContentProtection(bool enable, const std::string& sourceId);
  void SetFocusable(bool focusable);
  void SetMenu(v8::Isolate* isolate, v8::Local<v8::Value> menu);
  void RemoveMenu();
  void SetParentWindow(v8::Local<v8::Value> value, gin_helper::Arguments* args);
  virtual void SetBrowserView(v8::Local<v8::Value> value);
  virtual void AddBrowserView(v8::Local<v8::Value> value);
  virtual void RemoveBrowserView(v8::Local<v8::Value> value);
  virtual std::vector<v8::Local<v8::Value>> GetBrowserViews() const;
  virtual void ResetBrowserViews();
  std::string GetMediaSourceId() const;
  v8::Local<v8::Value> GetNativeWindowHandle();
  void SetProgressBar(double progress, gin_helper::Arguments* args);
  void SetOverlayIcon(const gfx::Image& overlay,
                      const std::string& description);
  void SetVisibleOnAllWorkspaces(bool visible);
  bool IsVisibleOnAllWorkspaces();
  void SetAutoHideCursor(bool auto_hide);
  virtual void SetVibrancy(v8::Isolate* isolate, v8::Local<v8::Value> value);

#if defined(OS_MACOSX)
  void SetTrafficLightPosition(const gfx::Point& position);
  gfx::Point GetTrafficLightPosition() const;
#endif

  void SetTouchBar(std::vector<gin_helper::PersistentDictionary> items);
  void RefreshTouchBarItem(const std::string& item_id);
  void SetEscapeTouchBarItem(gin_helper::PersistentDictionary item);
  void SelectPreviousTab();
  void SelectNextTab();
  void MergeAllWindows();
  void MoveTabToNewWindow();
  void ToggleTabBar();
  void AddTabbedWindow(NativeWindow* window, gin_helper::Arguments* args);
  void SetWindowButtonVisibility(bool visible, gin_helper::Arguments* args);
  void SetAutoHideMenuBar(bool auto_hide);
  bool IsMenuBarAutoHide();
  void SetMenuBarVisibility(bool visible);
  bool IsMenuBarVisible();
  void SetAspectRatio(double aspect_ratio, gin_helper::Arguments* args);
  void PreviewFile(const std::string& path, gin_helper::Arguments* args);
  void CloseFilePreview();

  // Public getters of NativeWindow.
  v8::Local<v8::Value> GetContentView() const;
  v8::Local<v8::Value> GetParentWindow() const;
  std::vector<v8::Local<v8::Object>> GetChildWindows() const;
  v8::Local<v8::Value> GetBrowserView(gin_helper::Arguments* args) const;
  bool IsModal() const;

  // Extra APIs added in JS.
  bool SetThumbarButtons(gin_helper::Arguments* args);
#if defined(TOOLKIT_VIEWS)
  void SetIcon(gin::Handle<NativeImage> icon);
#endif
#if defined(OS_WIN)
  typedef base::RepeatingCallback<void(v8::Local<v8::Value>,
                                       v8::Local<v8::Value>)>
      MessageCallback;
  bool HookWindowMessage(UINT message, const MessageCallback& callback);
  bool IsWindowMessageHooked(UINT message);
  void UnhookWindowMessage(UINT message);
  void UnhookAllWindowMessages();
  bool SetThumbnailClip(const gfx::Rect& region);
  bool SetThumbnailToolTip(const std::string& tooltip);
  void SetAppDetails(const gin_helper::Dictionary& options);
#endif
  int32_t GetID() const;

  // Helpers.

  // Remove BrowserView.
  void ResetBrowserView();

  // Remove this window from parent window's |child_windows_|.
  void RemoveFromParentChildWindows();

  template <typename... Args>
  void EmitEventSoon(base::StringPiece eventName) {
    base::PostTask(
        FROM_HERE, {content::BrowserThread::UI},
        base::BindOnce(base::IgnoreResult(&TopLevelWindow::Emit<Args...>),
                       weak_factory_.GetWeakPtr(), eventName));
  }

#if defined(OS_WIN)
  typedef std::map<UINT, MessageCallback> MessageCallbackMap;
  MessageCallbackMap messages_callback_map_;
#endif

  v8::Global<v8::Value> content_view_;
  std::map<int32_t, v8::Global<v8::Value>> browser_views_;
  v8::Global<v8::Value> menu_;
  v8::Global<v8::Value> parent_window_;
  KeyWeakMap<int> child_windows_;

  std::unique_ptr<NativeWindow> window_;

  // Reference to JS wrapper to prevent garbage collection.
  v8::Global<v8::Value> self_ref_;

  base::WeakPtrFactory<TopLevelWindow> weak_factory_;
};

}  // namespace api

}  // namespace electron

#endif  // SHELL_BROWSER_API_ELECTRON_API_TOP_LEVEL_WINDOW_H_
