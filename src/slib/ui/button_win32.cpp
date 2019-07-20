/*
 *   Copyright (c) 2008-2018 SLIBIO <https://github.com/SLIBIO>
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 */

#include "slib/core/definition.h"

#if defined(SLIB_UI_IS_WIN32)

#include "slib/ui/button.h"

#include "view_win32.h"

#include <commctrl.h>

namespace slib
{

	namespace priv
	{
		namespace button
		{
			class ButtonInstance : public Win32_ViewInstance
			{
			public:
				sl_bool processCommand(SHORT code, LRESULT& result) override
				{
					if (code == BN_CLICKED) {
						onClick();
						return sl_true;
					}
					return sl_false;
				}
			};
		}
	}

	using namespace priv::button;

	Ref<ViewInstance> Button::createNativeWidget(ViewInstance* parent)
	{
		Win32_UI_Shared* shared = Win32_UI_Shared::get();
		if (!shared) {
			return sl_null;
		}
		String16 text = m_text;
		DWORD style = WS_TABSTOP;
		if (m_flagDefaultButton) {
			style |= BS_DEFPUSHBUTTON;
		}
		Ref<ButtonInstance> ret = Win32_ViewInstance::create<ButtonInstance>(this, parent, L"BUTTON", (LPCWSTR)(text.getData()), style, 0);
		if (ret.isNotNull()) {
			HWND handle = ret->getHandle();
			Ref<Font> font = getFont();
			HFONT hFont = GraphicsPlatform::getGdiFont(font.get());
			if (hFont) {
				::SendMessageW(handle, WM_SETFONT, (WPARAM)hFont, TRUE);
			}
			{
				RECT rc;
				rc.left = (LONG)(getPaddingLeft());
				rc.top = (LONG)(getPaddingTop());
				rc.right = (LONG)(getPaddingRight());
				rc.bottom = (LONG)(getPaddingBottom());
				SendMessageW(handle, BCM_SETTEXTMARGIN, 0, (LPARAM)&rc);
			}
		}
		return ret;
	}

	void Button::_setText_NW(const String& text)
	{
		HWND handle = UIPlatform::getViewHandle(this);
		if (handle) {
			Windows::setWindowText(handle, text);
		}
	}

	void Button::_setDefaultButton_NW(sl_bool flag)
	{
		HWND handle = UIPlatform::getViewHandle(this);
		if (handle) {
			LONG old = ::GetWindowLongW(handle, GWL_STYLE);
			if (flag) {
				::SetWindowLongW(handle, GWL_STYLE, old | BS_DEFPUSHBUTTON);
			} else {
				::SetWindowLongW(handle, GWL_STYLE, old & (~(BS_DEFPUSHBUTTON)));
			}
			::SetWindowPos(handle, NULL, 0, 0, 0, 0
				, SWP_FRAMECHANGED | SWP_NOREPOSITION | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_ASYNCWINDOWPOS);
		}
	}

	sl_bool Button::_measureSize_NW(UISize& _out)
	{
		HWND handle = UIPlatform::getViewHandle(this);
		if (handle) {
			SIZE size = { 0, 0 };
			SendMessageW(handle, BCM_GETIDEALSIZE, 0, (LPARAM)&size);
			_out.x = (sl_ui_len)(size.cx);
			_out.y = (sl_ui_len)(size.cy);
			return sl_true;
		}
		return sl_false;
	}
	
	void Button::onChangePadding_NW()
	{
		HWND handle = UIPlatform::getViewHandle(this);
		if (handle) {
			RECT rc;
			rc.left = (LONG)(getPaddingLeft());
			rc.top = (LONG)(getPaddingTop());
			rc.right = (LONG)(getPaddingRight());
			rc.bottom = (LONG)(getPaddingBottom());
			SendMessageW(handle, BCM_SETTEXTMARGIN, 0, (LPARAM)&rc);
		}
	}

	void Button::_setFont_NW(const Ref<Font>& font)
	{
		HWND handle = UIPlatform::getViewHandle(this);
		if (handle) {
			HFONT hFont = GraphicsPlatform::getGdiFont(font.get());
			if (hFont) {
				::SendMessageW(handle, WM_SETFONT, (WPARAM)hFont, TRUE);
			}
		}
	}

}

#endif
