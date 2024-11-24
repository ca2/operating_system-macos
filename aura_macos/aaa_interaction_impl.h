#pragma once


#include "aura/user/user/interaction.h"
#include "aura/user/user/interaction_impl.h"


namespace aura_macos
{


   class CLASS_DECL_AURA_MACOS interaction_impl :
      virtual public ::user::interaction_impl
//,
  //    virtual public ::aura_window
   {
   public:


      string                           m_strWindowText;
      //::user::primitive *              m_pbasewnd;
      bool                             m_bNeedsUpdate;
      huge_int_rectangle                    m_rectLastOsPlacement;
      bool                             m_bEnabled;


      interaction_impl();
      //interaction_impl(::object * pobject);
      ~interaction_impl() override;


      //virtual void construct(oswindow hwnd);

//
//      void assert_ok() const override;
//      void dump(dump_context & dumpcontext) const override;
      
      void on_destroy() override;

//      bool is_destroying() const { return //::aura_window::m_bDestroying ||
//         ::user::interaction_impl::m_bDestroying; }

      //void native_create_host() override;
      
      virtual void release_graphics_resources();
      
      void update_graphics_resources() override;


      //virtual bool create_message_queue(::user::interaction * pinteraction, const char * pszName) override;

      virtual void install_message_routing(::channel * pchannel) override;


//
//      virtual ::user::interaction *  SetOwner(::user::interaction *   pOwnerWnd) override;

//      virtual ::user::interaction * get_wnd() const override;

      virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;
//
//      virtual void on_control_event(::user::control_event * pevent) override;

      void _002OnDraw(::image::image * pimage);

//
//      virtual bool has_focus() override;
//      virtual bool is_active() override;

      //DECLARE_MESSAGE_HANDLER(_001OnEraseBkgnd);
      DECLARE_MESSAGE_HANDLER(_001OnMove);
      DECLARE_MESSAGE_HANDLER(_001OnSize);
      DECLARE_MESSAGE_HANDLER(_001OnProdevianSynch);

      //virtual ::user::interaction_impl * from_os_data(void * pdata) override;
      //virtual void * get_os_data() const override;

//
//      bool Attach(oswindow hWndNew);
//      oswindow Detach();


      virtual void on_show_window() override;
      virtual void on_reposition() override;
      virtual void on_zorder();
      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      // subclassing/unsubclassing functions
//      virtual void pre_subclass_window() override;
//      bool SubclassWindow(oswindow hWnd);
//      //bool SubclassDlgItem(unsigned int nID, ::interaction_impl * pParent);
//      oswindow UnsubclassWindow();

//      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
//      bool ExecuteDlgInit(const char * lpszResourceName) override;
//      bool ExecuteDlgInit(LPVOID lpResource) override;

//      virtual bool ShowWindow(int iShow) override;
      //// for child windows, views, panes etc
//
//      virtual bool create_window(::user::interaction * pinteraction, const char * lpszClassName, const char * lpszWindowName, unsigned int uStyle, const ::int_rectangle & prectangle, ::user::interaction * puiParent, id id, ::create * pcreate = nullptr) override;
//

      //virtual ::e_status native_create_host() override;
  
      void destroy_impl_only() override;
      void start_destroying_window() override;
  
      void destroy_window() override;
  
      // advanced creation (allows access to extended styles)
//      virtual bool create_window_ex(
//      ::user::interaction * pinteraction,
//      ::pointer < ::user::system > pusersystem,
//      ::user::interaction * puiParent,
//      id id) override;
//
//      virtual bool _native_create_window_ex(::pointer < ::user::system > pusersystem) override;
//
//      virtual bool DestroyWindow() override;

      // special pre-creation and ::interaction_impl int_rectangle adjustment hooks
//      virtual bool pre_create_window(::user::system * pusersystem) override;

//      // Advanced: virtual AdjustWindowRect
//      enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
//      virtual void CalcWindowRect(INT_RECTANGLE * lpClientRect, unsigned int nAdjustType = adjustBorder) override;
//


      bool _is_window() override;

//      lresult send_message(const ::id & id, wparam wParam = 0, lparam lParam = 0, const ::int_point & point = {}) override;
//      bool post_message(const ::id & id, wparam wParam = 0, lparam lParam = 0) override;

//      bool SendNotifyMessage(const ::id & id, WPARAM wParam, LPARAM lParam);
//      bool SendChildNotifyLastMsg(LRESULT* pResult = nullptr);
//
//      bool DragDetect(const ::int_point & point) const override;



      // oswindow Text Functions
//      void set_window_text(const ::string & lpszString) override;
//      //character_count GetWindowText(char * lpszStringBuf, character_count nMaxCount);
//      void get_window_text(string & str) override;
      //character_count GetWindowTextLength();
//      void SetFont(::write_text::font* pFont, bool bRedraw = true);
      //    ::write_text::font* GetFont();


      // oswindow int_size and position Functions
      virtual bool window_impl_is_iconic();
      //virtual bool window_impl_is_zoomed();
//      void MoveWindow(int x, int y, int nWidth, int nHeight,
//                      bool bRepaint = true);
//      void MoveWindow(const ::int_rectangle & rectangle, bool bRepaint = true);
      //int SetWindowRgn(HRGN hRgn, bool bRedraw);
      //int GetWindowRgn(HRGN hRgn);


      //virtual bool set_window_position(iptr z, int x, int y, int cx, int cy, unsigned int nFlags);
      //virtual unsigned int ArrangeIconicWindows() override;
      //virtual void BringToTop(::e_display edisplay) override;
      //virtual bool BringWindowToTop() override;
//      using ::user::interaction_impl::window_rectangle;
//      virtual bool window_rectangle(RECTANGLE_I64 * lpRect) override;
//      using ::user::interaction_impl::client_rectangle;
//      virtual bool client_rectangle(RECTANGLE_I64 * lpRect) override;

      //virtual double_point client_screen_top_left() override;
//        virtual bool _001ClientToScreen(INT_RECTANGLE * lprect) override;
//        virtual bool _001ClientToScreen(INT_POINT * lppoint) override;
//        virtual bool _001ClientToScreen(RECTANGLE_I64 * lprect) override;
//        virtual bool _001ClientToScreen(POINT_I64 * lppoint) override;
//        virtual bool _001ScreenToClient(INT_RECTANGLE * lprect) override;
//        virtual bool _001ScreenToClient(INT_POINT * lppoint) override;
//        virtual bool _001ScreenToClient(RECTANGLE_I64 * lprect) override;
//        virtual bool _001ScreenToClient(POINT_I64 * lppoint) override;

      //virtual bool GetWindowPlacement(WINDOWPLACEMENT* lpuserinteractionpl);
      //virtual bool SetWindowPlacement(const WINDOWPLACEMENT* lpuserinteractionpl);

      //virtual void MapWindowPoints(::user::interaction * puserinteractionTo, INT_POINT * lpPoint, unsigned int nCount);
      //virtual void MapWindowPoints(::user::interaction * puserinteractionTo, INT_RECTANGLE * lpRect);

      //virtual ::draw2d::graphics * GetDC();
      //virtual ::draw2d::graphics * GetWindowDC();
      //virtual bool ReleaseDC(::draw2d::graphics_pointer & pgraphics);
      //virtual void Print(::draw2d::graphics_pointer & pgraphics, unsigned int dwFlags) const override;
      //virtual void PrintClient(::draw2d::graphics_pointer & pgraphics, unsigned int dwFlags) const override;

//      virtual void UpdateWindow() override;
//      virtual void SetRedraw(bool bRedraw = true) override;
//      //virtual bool GetUpdateRect(INT_RECTANGLE * lpRect, bool bErase = false) override;
//      virtual int GetUpdateRgn(::draw2d::region* pRgn, bool bErase = false) override;
//      virtual void Invalidate(bool bErase = true) override;
//      virtual void InvalidateRect(const ::int_rectangle &rectangle, bool bErase = true) override;
//      virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = true) override;
//      virtual void ValidateRect(const ::int_rectangle & rectangle) override;
//      virtual void ValidateRgn(::draw2d::region* pRgn) override;
      //virtual bool display(::e_display edisplay) override;
//      virtual void window_impl_maximize();
//      virtual void window_impl_restore();
      //virtual bool window_impl_is_visible();
      //virtual void ShowOwnedPopups(bool bShow = true) override;




      void set_origin(::draw2d::graphics_pointer & pgraphics) override;
      void offset_viewport_org(INT_RECTANGLE * lprectScreen);


      //virtual ::draw2d::graphics * GetDCEx(::draw2d::region* prgnClip, unsigned int flags) override;
      virtual void LockWindowUpdate() override;
      virtual void UnlockWindowUpdate() override;
//        virtual bool RedrawWindow(const ::int_rectangle & rectUpdate = nullptr, ::draw2d::region* prgnUpdate = nullptr, unsigned int flags = RDW_INVALIDATE | RDW_ERASE);
//       void window_update_screen_buffer() override;
      //virtual votru8id _001UpdateWindow(bool bUpdateBuffer = false) override;
      // xxx      virtual bool EnableScrollBar(int nSBFlags, unsigned int nArrowFlags = ESB_ENABLE_BOTH);

      //virtual bool DrawAnimatedRects(int idAni, const INT_RECTANGLE *lprcFrom, const INT_RECTANGLE *lprcTo) override;
//      void DrawCaption(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, unsigned int uFlags) override;


      // Timer Functions
//      virtual bool SetTimer(uptr uEvent, unsigned int nElapse, PFN_TIMER pfnTimer) override;
//      virtual bool KillTimer(uptr uEvent) override;

      // oswindow State Functions
      virtual bool IsWindowEnabled();
      void enable_window(bool bEnable = true) override;

//      virtual ::user::interaction *  GetActiveWindow() override;
//      virtual ::user::interaction *  SetActiveWindow() override;
//
//      virtual bool SetForegroundWindow() override;
//
//      virtual id SetDlgCtrlId(id id) override;
//      virtual id GetDlgCtrlId();
//

//
//      virtual ::user::interaction *  GetFocus() override;
//      bool  SetFocus() override;
//
//      virtual ::user::interaction *  get_desktop_window();

//      virtual void CloseWindow() override;
//      virtual bool OpenIcon() override;
//
//      virtual void CheckDlgButton(int nIDButton, unsigned int nCheck) override;
//      virtual void CheckRadioButton(int nIDFirstButton, int nIDLastButton, int nIDCheckButton) override;
//      virtual int GetCheckedRadioButton(int nIDFirstButton, int nIDLastButton) override;
//      virtual int DlgDirList(char * lpPathSpec, int nIDListBox,
//                             int nIDStaticPath, unsigned int nFileType) override;
//      virtual int DlgDirListComboBox(char * lpPathSpec, int nIDComboBox,
//                                     int nIDStaticPath, unsigned int nFileType) override;
//      virtual bool DlgDirSelect(char * lpString, int nSize, int nIDListBox) override;
//      virtual bool DlgDirSelectComboBox(char * lpString, int nSize, int nIDComboBox) override;

      //virtual unsigned int GetChildByIdInt(int nID, bool * lpTrans = nullptr, bool bSigned = true) const;
      //virtual int GetChildByIdText(int nID, char * lpStr, int nMaxCount) const;
      //virtual int GetChildByIdText(int nID, string & rectString) const;
//      virtual ::user::interaction * GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious = false) const;
//      virtual ::user::interaction * GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious = false) const;
//      virtual unsigned int IsDlgButtonChecked(int nIDButton) const override;
//      virtual LRESUlresultLT SendDlgItemMessage(int nID, const ::id & id, WPARAM wParam = 0, LPARAM lParam = 0) override;
//      virtual void SetDlgItemInt(int nID, unsigned int nValue, bool bSigned = true) override;
//      virtual void SetDlgItemText(int nID, const char * lpszString) override;
//
//      // Scrolling Functions
//      virtual int GetScrollPos(int nBar) const override;
//      virtual void GetScrollRange(int nBar, LPINT lpMinPos, LPINT lpMaxPos) const override;
//      virtual void ScrollWindow(int xAmount, int yAmount,
//                                const INT_RECTANGLE * prectangle = nullptr,
//                                const INT_RECTANGLE * lpClipRect = nullptr) override;
//      virtual int SetScrollPos(int nBar, int nPos, bool bRedraw = true) override;
//      virtual void SetScrollRange(int nBar, int nMinPos, int nMaxPos,
//                                  bool bRedraw = true) override;
//      virtual void ShowScrollBar(unsigned int nBar, bool bShow = true) override;
//      virtual void EnableScrollBarCtrl(int nBar, bool bEnable = true) override;
////      virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
//      // return sibling scrollbar control (or nullptr if none)
//
//      virtual int ScrollWindowEx(int Δx, int Δy,
//                                 const INT_RECTANGLE * prectScroll, const INT_RECTANGLE * lprectClip,
//                                 ::draw2d::region* prgnUpdate, INT_RECTANGLE * lpRectUpdate, unsigned int flags) override;
//      //xxx      virtual bool SetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo,
//      //xxx         bool bRedraw = true);
//      //xxx      virtual bool GetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo, unsigned int nMask = SIF_ALL);
//      virtual int GetScrollLimit(int nBar) override;
//
//
      // oswindow Access Functions
//      virtual ::user::interaction *  ChildWindowFromPoint(const ::int_point & point) override;
//      virtual ::user::interaction *  ChildWindowFromPoint(const ::int_point & point, unsigned int nFlags) override;
//
//      virtual ::user::interaction *  GetNextWindow(unsigned int nFlag = GW_HWNDNEXT);
//      virtual ::user::interaction *  GetTopWindow() override;
//
//      virtual ::user::interaction *  GetWindow(unsigned int nCmd);
//      virtual ::user::interaction *  GetLastActivePopup() override;
//
//      virtual bool IsChild(::user::interaction *    pWnd);
//      virtual ::user::interaction * get_parent() const override;
//      using ::user::interaction_impl::SetParent;
//      ::user::interaction * SetParent(::user::interaction * pWndNewParent) override;
//
//      // Alert Functions
//
//      bool FlashWindow(bool bInvert);
//
      //virtual int message_box(const char * lpszText, const char * lpszCaption = nullptr, unsigned int nType = e_message_box_ok) override;


//c

//      // Caret Functions
//      virtual void HideCaret() override;
//      virtual void ShowCaret() override;
//
//      // Shell Interaction Functions
//      virtual void DragAcceptFiles(bool bAccept = true) override;

      // icon Functions
//      virtual HICON SetIcon(HICON hIcon, bool bBigIcon);
//      virtual HICON GetIcon(bool bBigIcon) const;
//
//      // Context Help Functions
//      virtual bool SetWindowContextHelpId(unsigned int dwContextHelpId) override;
//      virtual unsigned int GetWindowContextHelpId() const override;

      // Dialog Data support
      //virtual bool update_data(bool bSaveAndValidate = true);
      // data wnd must be same type as this

//      // Help Command Handlers
//      void OnHelp();          // F1 (uses current action_context)
//      void OnHelpIndex();     // ID_HELP_INDEX
//      void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
//      void OnHelpUsing();     // ID_HELP_USING
//
//      void UpdateDialogControls(channel * pTarget, bool bDisableIfNoHndler) override;
//      void CenterWindow(::user::interaction * pAlternateOwner = nullptr) override;
//
//      void OnActivate(unsigned int nState, ::user::interaction * pWndOther, bool bMinimized);
//      void OnActivateApp(bool bActive, unsigned int dwThreadID);
//      LRESULT OnActivateTopLevel(WPARAM, LPARAM);
//      void OnCancelMode();
//      void OnChildActivate();
//      void OnClose();
//      void OnContextMenu(::user::interaction * pWnd, int_point pos);
//      bool OnCopyData(::user::interaction * pWnd, COPYDATASTRUCT* pCopyDataStruct);


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnShowWindow);


//      HBRUSH OnCtlColor(::draw2d::graphics_pointer & pgraphics, ::user::interaction * pWnd, unsigned int nCtlColor);

      DECLARE_MESSAGE_HANDLER(_001OnDestroy);
//      void OnEnable(bool bEnable);
//      void OnEndSession(bool bEnding);
//      void OnEnterIdle(unsigned int nWhy, ::user::interaction * pWho);
//      bool OnEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
//      void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
//      //xxx bool OnHelpInfo(HELPINFO* lpHelpInfo);
//      void OnIconEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
//      void OnKillFocus(::user::interaction * pNewWnd);
//      LRESULT OnMenuChar(unsigned int nChar, unsigned int nFlags, ::user::menu* pMenu);
//      void OnMenuSelect(unsigned int nItemID, unsigned int nFlags, HMENU hSysMenu);
//      void OnMove(int x, int y);
      DECLARE_MESSAGE_HANDLER(_001OnPaint);
      DECLARE_MESSAGE_HANDLER(_001OnPrint);
//      void OnParentNotify(const ::id & id, LPARAM lParam);
//      HCURSOR OnQueryDragIcon();
//      bool OnQueryEndSession();
//      bool OnQueryNewPalette();
//      bool OnQueryOpen();
//      void OnSetFocus(::user::interaction * pOldWnd);
//      void OnShowWindow(bool bShow, unsigned int nStatus);
//      void OnSize(unsigned int nType, int cx, int cy);
//      void OnTCard(unsigned int idAction, unsigned int dwActionData);
//      void OnWindowPosChanging(WINDOWPOS* lpuserinteractionpos);
//      void OnWindowPosChanged(WINDOWPOS* lpuserinteractionpos);
//
//      void OnChangeUIState(unsigned int nAction, unsigned int nUIElement);
//      void OnUpdateUIState(unsigned int nAction, unsigned int nUIElement);
//      unsigned int OnQueryUIState();

      // Nonclient-Area message handler member functions
//      bool OnNcActivate(bool bActive);
//      void OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
//      bool OnNcCreate(::user::system * lpCreateStruct);

//      LRESULT OnNcHitTest(::int_point point);
//      void OnNcLButtonDblClk(unsigned int nHitTest, const ::int_point & point);
//      void OnNcLButtonDown(unsigned int nHitTest, const ::int_point & point);
//      void OnNcLButtonUp(unsigned int nHitTest, const ::int_point & point);
//      void OnNcMButtonDblClk(unsigned int nHitTest, const ::int_point & point);
//      void OnNcMButtonDown(unsigned int nHitTest, const ::int_point & point);
//      void OnNcMButtonUp(unsigned int nHitTest, const ::int_point & point);
//      void OnNcMouseMove(unsigned int nHitTest, const ::int_point & point);
//      void OnNcPaint();
//      void OnNcRButtonDblClk(unsigned int nHitTest, const ::int_point & point);
//      void OnNcRButtonDown(unsigned int nHitTest, const ::int_point & point);
//      void OnNcRButtonUp(unsigned int nHitTest, const ::int_point & point);

      // ::aura::get_system() message handler member functions
//      void OnDropFiles(HDROP hDropInfo);
//      void OnPaletteIsChanging(::user::interaction * pRealizeWnd);
//      void OnSysChar(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
//      void OnSysCommand(unsigned int nID, LPARAM lParam);
//      void OnSysDeadChar(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
//      void OnSysKeyDown(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
//      void OnSysKeyUp(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
//      void OnCompacting(unsigned int nCpuTime);
//      void OnDevModeChange(char * lpDeviceName);
//      void OnFontChange();
//      void OnPaletteChanged(::user::interaction * pFocusWnd);
//      void OnSpoolerStatus(unsigned int nStatus, unsigned int nJobs);
//      void OnSysColorChange();
//      void OnTimeChange();
//      void OnSettingChange(unsigned int uFlags, const char * lpszSection);
//      void OnWinIniChange(const char * lpszSection);

//      // Input message handler member functions
//      void OnChar(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
//      void OnDeadChar(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
////      void OnHScroll(unsigned int nSBCode, unsigned int nPos, CScrollBar* pScrollBar);
//      //    void OnVScroll(unsigned int nSBCode, unsigned int nPos, CScrollBar* pScrollBar);
//      void OnKeyDown(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
//      void OnKeyUp(unsigned int nChar, unsigned int nRepCnt, unsigned int nFlags);
//      void OnLButtonDblClk(unsigned int nFlags, const ::int_point & point);
//      void OnLButtonDown(unsigned int nFlags, const ::int_point & point);
//      void OnLButtonUp(unsigned int nFlags, const ::int_point & point);
//      void OnMButtonDblClk(unsigned int nFlags, const ::int_point & point);
//      void OnMButtonDown(unsigned int nFlags, const ::int_point & point);
//      void OnMButtonUp(unsigned int nFlags, const ::int_point & point);
//      int OnMouseActivate(::user::interaction * pDesktopWnd, unsigned int nHitTest, const ::id & id);
//      void OnMouseMove(unsigned int nFlags, const ::int_point & point);
//      bool OnMouseWheel(unsigned int nFlags, short zDelta, const ::int_point & point);
//      LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);
//      void OnRButtonDblClk(unsigned int nFlags, const ::int_point & point);
//      void OnRButtonDown(unsigned int nFlags, const ::int_point & point);
//      void OnRButtonUp(unsigned int nFlags, const ::int_point & point);
//      DECLARE_MESSAGE_HANDLER(_001OnSetCursor);
//      void OnTimer(uptr uEvent);

      // Initialization message handler member functions
//      void OnInitMenu(::user::menu* pMenu);
//      void OnInitMenuPopup(::user::menu* pPopupMenu, unsigned int nIndex, bool bSysMenu);

      // Clipboard message handler member functions
//      void OnAskCbFormatName(unsigned int nMaxCount, char * lpszString);
//      void OnChangeCbChain(oswindow hWndRemove, oswindow hWndAfter);
//      void OnDestroyClipboard();
//      void OnDrawClipboard();
//      void OnHScrollClipboard(::user::interaction * pClipAppWnd, unsigned int nSBCode, unsigned int nPos);
//      void OnPaintClipboard(::user::interaction * pClipAppWnd, HGLOBAL hPaintStruct);
//      void OnRenderAllFormats();
//      void OnRenderFormat(unsigned int nFormat);
//      void OnSizeClipboard(::user::interaction * pClipAppWnd, HGLOBAL hRect);
//      void OnVScrollClipboard(::user::interaction * pClipAppWnd, unsigned int nSBCode, unsigned int nPos);

      // control message handler member functions
      //xxx      int OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct);
      //xxx      void OnDeleteItem(int nIDCtl, LPDELETEITEMSTRUCT lpDeleteItemStruct);
      //xxx      void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
//      unsigned int OnGetDlgCode();
      //xxx      void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

      // MDI message handler member functions
//      void OnMDIActivate(bool bActivate,
//                         ::user::interaction * pActivateWnd, ::user::interaction * pDeactivateWnd);

      // menu loop notification messages
//      void OnEnterMenuLoop(bool bIstrack_popup_menu);
//      void OnExitMenuLoop(bool bIstrack_popup_menu);

      // Win4 messages
      //xxx      void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
      //xxx      void OnStyleChanging(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
//      void OnSizing(unsigned int nSide, INT_RECTANGLE * lpRect);
//      void OnMoving(unsigned int nSide, INT_RECTANGLE * lpRect);
//      void OnCaptureChanged(::user::interaction * pWnd);
//      bool OnDeviceChange(unsigned int nEventType, uptr dwData);

      // Overridables and other helpers (for implementation of derived classes)
      // for deriving from a standard control
      // xxx      virtual WNDPROC* GetSuperWndProcAddr();

      // for dialog data exchange and validation
      //      virtual void do_data_exchange(CDataExchange* pDX);

      // for modality
//      virtual void BeginModalState() override;
//      virtual void EndModalState() override;

      // for translating oswindows messages in main message pump
      virtual void pre_translate_message(::message::message * pmessage) override;

      virtual void default_message_handler(::message::message * pmessage) override;

      // for processing oswindows messages
      virtual void message_handler(::message::message * pusermessage) override;
      //virtual bool OnWndMsg(const ::id & id, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

      // for handling default processing
//      LRESULT Default() override;
//      virtual LRESULT DefWindowProc(const ::id & id, WPARAM wParam, LPARAM lParam);

      void post_non_client_destroy() override;


      friend class frame_window;
//
//      virtual int GetWindowLong(int nIndex);
//      virtual int SetWindowLong(int nIndex, int lValue);


      void _001WindowMinimize();

      //void _001OnTriggerMouseInside() override;

      virtual void show_task(bool bShow) override;

      virtual void window_show_change_visibility();
      
      void show_software_keyboard(::user::element * pelement) override;

      void hide_software_keyboard(::user::element * pelement) override;

   };


} // namespace aura_macos



