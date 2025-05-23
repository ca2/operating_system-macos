#include "framework.h"


// interesting function
/*int_bool CLASS_DECL_lnx AfxCustomLogFont(unsigned int nIDS, LOGFONT* pLogFont)
 {
 ENSURE_ARG(pLogFont != nullptr);
 ASSERT(nIDS != 0);

 char szFontInfo[256];
 if (!AfxLoadString(nIDS, szFontInfo,_countof(szFontInfo)))
 return false;

 char * lpszSize = _tcschr(szFontInfo, '\n');
 if (lpszSize != nullptr)
 {
 // get int_point int_size and convert to pixels
 pLogFont->lfHeight = _ttoi(lpszSize+1);
 pLogFont->lfHeight =
 MulDiv(pLogFont->lfHeight, afxData.cyPixelsPerInch, 72);
 *lpszSize = '\0';
 }
 _template::checked::tcsncpy_s(pLogFont->lfFaceName, _countof(pLogFont->lfFaceName), szFontInfo, _TRUNCATE);
 return true;
 }*/

/*
 int_bool CLASS_DECL_lnx _AfxIsComboBoxControl(oswindow hWnd, unsigned int nStyle)
 {
 if (hWnd == nullptr)
 return false;
 // do cheap style compare first
 if ((unsigned int)(::GetWindowLong(hWnd, GWL_STYLE) & 0x0F) != nStyle)
 return false;

 // do expensive classname compare next
 char szCompare[_countof("combobox")+1];
 ::GetClassName(hWnd, szCompare, _countof(szCompare));
 return ::AfxInvariantStrICmp(szCompare, "combobox") == 0;
 }

 int_bool CLASS_DECL_lnx _AfxCompareClassName(oswindow hWnd, const char * lpszClassName)
 {
 ASSERT(::IsWindow(hWnd));
 char szTemp[32];
 ::GetClassName(hWnd, szTemp, _countof(szTemp));
 return ::AfxInvariantStrICmp(szTemp, lpszClassName) == 0;
 }

 oswindow CLASS_DECL_lnx _AfxChildWindowFromPoint(oswindow hWnd, INT_POINT int_point)
 {
 ASSERT(hWnd != nullptr);

 // check child windows
 ::_001ClientToScreen(hWnd, &point);
 oswindow hWndChild = ::GetWindow(hWnd, GW_CHILD);
 for (; hWndChild != nullptr; hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT))
 {
 if (_AfxGetDlgCtrlID(hWndChild) != (unsigned short)0 &&
 (::GetWindowLong(hWndChild, GWL_STYLE) & WS_VISIBLE))
 {
 // see if int_point hits the child ::window
 ::int_rectangle rectangle;
 ::window_rectangle(hWndChild, rectangle);
 if (rectangle.contains(point))
 return hWndChild;
 }
 }

 return nullptr;    // not found
 }

 void CLASS_DECL_lnx AfxSetWindowText(::user::interaction * hWndCtrl, const char * lpszNew)
 {
 hWndCtrl->set_window_text(lpszNew);
ENSURE(hWndCtrl);
 ENSURE(lpszNew);

 int nNewLen = lstrlen(lpszNew);
 char szOld[256]="";
 // fast check to see if text really changes (reduces flash in controls)
 if (nNewLen > _countof(szOld) ||
 ::GetWindowText(hWndCtrl, szOld, _countof(szOld)) != nNewLen ||
 lstrcmp(szOld, lpszNew) != 0)
 {
 // change it
 ::SetWindowText(hWndCtrl, lpszNew);
 }*/
//}

/*
 void CLASS_DECL_lnx AfxDeleteObject(HGDIOBJ* pObject)
 {
 ENSURE_ARG(pObject != nullptr);
 if (*pObject != nullptr)
 {
 ::DeleteObject(*pObject);
 *pObject = nullptr;
 }
 }*/

/*
 void CLASS_DECL_lnx AfxCancelModes(oswindow hWndRcvr)
 {
 // if we receive a message destined for a ::window, cancel any combobox
 //  popups that could be in toolbars or dialog bars
 oswindow hWndCancel = ::GetFocus();
 if (hWndCancel == nullptr)
 return;     // nothing to cancel

 if (hWndCancel == hWndRcvr)
 return;     // let input go to ::window with focus

 // focus is in part of a combo-box
 if (!_AfxIsComboBoxControl(hWndCancel, (unsigned int)CBS_DROPDOWNLIST))
 {
 // check as a dropdown
 hWndCancel = ::get_parent(hWndCancel);   // parent of edit is combo
 if (hWndCancel == hWndRcvr)
 return;     // let input go to part of combo

 if (!_AfxIsComboBoxControl(hWndCancel, (unsigned int)CBS_DROPDOWN))
 return;     // not a combo-box that is active
 }

 // combo-box is active, but if receiver is a popup, do nothing
 if (hWndRcvr != nullptr &&
 (::GetWindowLong(hWndRcvr, GWL_STYLE) & WS_CHILD) != 0 &&
 ::get_parent(hWndRcvr) == ::get_desktop_window())
 return;

 // finally, we should cancel the mode!
 ::SendMessage(hWndCancel, CB_SHOWDROPDOWN, false, 0L);
 }*/

/*
 void CLASS_DECL_lnx AfxGlobalFree(HGLOBAL hGlobal)
 {
 if (hGlobal == nullptr)
 return;

 // avoid bogus warning error messages from various debugging tools
 ASSERT(GlobalFlags(hGlobal) != GMEM_INVALID_HANDLE);
 unsigned int nCount = GlobalFlags(hGlobal) & GMEM_LOCKCOUNT;
 while (nCount--)
 GlobalUnlock(hGlobal);

 // finally, really free the handle
 GlobalFree(hGlobal);
 }
 */

