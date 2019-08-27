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

#ifndef CHECKHEADER_SLIB_UI_REFRESH_VIEW
#define CHECKHEADER_SLIB_UI_REFRESH_VIEW

#include "definition.h"

#include "view.h"

namespace slib
{

	class SLIB_EXPORT RefreshView : public ViewGroup
	{
		SLIB_DECLARE_OBJECT
		
	public:
		RefreshView();
		
		~RefreshView();

	public:
		sl_bool isRefreshing();
		
		void setRefreshing(sl_bool flag);
		
	public:
		SLIB_DECLARE_EVENT_HANDLER(RefreshView, Refresh)
		
	protected:
		Ref<ViewInstance> createNativeWidget(ViewInstance* parent) override;
		
	protected:
		void onAttachChild(View* child) override;
		
	protected:
		void _setRefreshing_NW(sl_bool flag);
		
		void _onRefresh_NW();
		
	protected:
		sl_bool m_flagRefreshing;
		
		Ref<Referable> m_platformContainer;
		
	};

}

#endif
