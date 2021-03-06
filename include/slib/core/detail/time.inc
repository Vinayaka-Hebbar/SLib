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

namespace slib
{

	SLIB_INLINE Time& Time::setZero() noexcept
	{
		m_time = 0;
		return *this;
	}
	
	SLIB_INLINE sl_int64 Time::toInt() const noexcept
	{
		return m_time;
	}

	SLIB_INLINE sl_int64 Time::toUnixTime() const noexcept
	{
		sl_int64 n = m_time / 1000000;
		if ((m_time % 1000000) < 0) {
			n += 1;
		}
		return n;
	}

	SLIB_INLINE double Time::toUnixTimef() const noexcept
	{
		return (double)(m_time / 1000000);
	}

	SLIB_INLINE Time& Time::operator=(const Time& other) noexcept
	{
		m_time = other.m_time;
		return *this;
	}
	
	SLIB_INLINE Time& Time::operator=(sl_int32 time) noexcept
	{
		m_time = time;
		return *this;
	}
	
	SLIB_INLINE Time& Time::operator=(sl_uint32 time) noexcept
	{
		m_time = time;
		return *this;
	}
	
	SLIB_INLINE Time& Time::operator=(sl_int64 time) noexcept
	{
		m_time = time;
		return *this;
	}
	
	SLIB_INLINE Time& Time::operator=(sl_uint64 time) noexcept
	{
		m_time = time;
		return *this;
	}
	
	SLIB_INLINE sl_bool Time::operator==(const Time& other) const noexcept
	{
		return m_time == other.m_time;
	}
	
	SLIB_INLINE sl_bool Time::operator<=(const Time& other) const noexcept
	{
		return m_time <= other.m_time;
	}
	
	SLIB_INLINE sl_bool Time::operator>=(const Time& other) const noexcept
	{
		return m_time >= other.m_time;
	}
	
	SLIB_INLINE sl_bool Time::operator!=(const Time& other) const noexcept
	{
		return m_time != other.m_time;
	}
	
	SLIB_INLINE sl_bool Time::operator<(const Time& other) const noexcept
	{
		return m_time < other.m_time;
	}
	
	SLIB_INLINE sl_bool Time::operator>(const Time& other) const noexcept
	{
		return m_time > other.m_time;
	}
	
	SLIB_INLINE Time Time::operator+(sl_int64 time) const noexcept
	{
		return m_time + time;
	}
	
	SLIB_INLINE Time Time::operator+(const Time& time) const noexcept
	{
		return m_time + time.m_time;
	}
	
	SLIB_INLINE Time& Time::operator+=(sl_int64 time) noexcept
	{
		m_time += time;
		return *this;
	}
	
	SLIB_INLINE Time& Time::operator+=(const Time& time) noexcept
	{
		m_time += time.m_time;
		return *this;
	}
	
	SLIB_INLINE Time Time::operator-(sl_int64 time) const noexcept
	{
		return m_time - time;
	}
	
	SLIB_INLINE Time Time::operator-(const Time& time) const noexcept
	{
		return m_time - time.m_time;
	}
	
	SLIB_INLINE Time& Time::operator-=(sl_int64 time) noexcept
	{
		m_time -= time;
		return *this;
	}
	
	SLIB_INLINE Time& Time::operator-=(const Time& time) noexcept
	{
		m_time -= time.m_time;
		return *this;
	}

}
