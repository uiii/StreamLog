/**
* This file is part of the StreamLog project (https://github.com/uiii/StreamLog)
*
* Copyright (C) 2011 by Richard Jedlička <uiii.dev@gmail.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#ifndef STREAMLOG_LOGSTREAM_HPP
#define STREAMLOG_LOGSTREAM_HPP

#include <boost/thread.hpp>

#include "ThreadSpecificLogStream.hpp"

namespace StreamLog
{
    class LogStream
    {
    public:
        LogStream();

        LogStream(const LogStream&) = delete;
        LogStream& operator=(const LogStream&) = delete;

        template< typename T >
        ThreadSpecificLogStream& operator<<(const T& input);

    private:
        ThreadSpecificLogStream& getThreadSpecificLogStream_();

        boost::thread_specific_ptr<ThreadSpecificLogStream> threadSpecificLogStream_;
    };

    template< typename T >
    ThreadSpecificLogStream& LogStream::operator<<(const T& input)
    {
        ThreadSpecificLogStream& stream = getThreadSpecificLogStream_();

        stream << input;

        return stream;
    }
}

#endif // STREAMLOG_LOGSTREAM_HPP
