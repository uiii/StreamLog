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

#ifndef STREAMLOG_THREADSPECIFICLOGSTREAM_HPP
#define STREAMLOG_THREADSPECIFICLOGSTREAM_HPP

#include <ostream>
#include <sstream>

namespace StreamLog
{
    // forward declarations
    class LogStream;
}

namespace StreamLog
{
    typedef std::ostream& (*ostream_modifier)(std::ostream&);
    typedef std::ios_base& (*ios_base_modifier)(std::ios_base&);
    typedef std::ios& ( *ios_modifier )(std::ios&);


    class ThreadSpecificLogStream
    {
    public:
        ThreadSpecificLogStream(LogStream& parent);
        virtual ~ThreadSpecificLogStream();

        template< typename T >
        ThreadSpecificLogStream& operator<<(const T& input);

        ThreadSpecificLogStream& operator<<(ostream_modifier modifier);
        ThreadSpecificLogStream& operator<<(ios_base_modifier modifier);
        ThreadSpecificLogStream& operator<<(ios_modifier modifier);

        ThreadSpecificLogStream& flush();
        ThreadSpecificLogStream& setUnitBuf(bool flag);

    private:
        LogStream& parent_;

        std::stringstream stream_buffer_;
        bool unitBuf_;
    };

    template< typename T >
    ThreadSpecificLogStream& ThreadSpecificLogStream::operator<<(const T& input)
    {
        stream_buffer_ << input;

        if(unitBuf_)
        {
            flush();
        }

        return *this;
    }
}

#endif // STREAMLOG_THREADSPECIFICLOGSTREAM_HPP
