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

#include "ThreadSpecificLogStream.hpp"

#include "StreamBinder.hpp"

StreamLog::ThreadSpecificLogStream::ThreadSpecificLogStream(StreamLog::LogStream& parent):
    parent_(parent)
{
}

StreamLog::ThreadSpecificLogStream&
    StreamLog::ThreadSpecificLogStream::operator<<(std::ostream& (*modifier)(std::ostream&))
{
    stream_buffer_ << modifier;

    if(modifier == (StreamLog::ostream_modifier)std::flush
        || modifier == (StreamLog::ostream_modifier)std::endl)
    {
        flush();
    }

    if(unitBuf_)
    {
        flush();
    }

    return *this;
}

StreamLog::ThreadSpecificLogStream&
    StreamLog::ThreadSpecificLogStream::operator<<(std::ios_base& (*modifier)(std::ios_base&))
{
    stream_buffer_ << modifier;

    if(modifier == std::unitbuf)
    {
        setUnitBuf(true);
    }
    else if(modifier == std::nounitbuf)
    {
        setUnitBuf(false);
    }

    if(unitBuf_)
    {
        flush();
    }

    return *this;
}

StreamLog::ThreadSpecificLogStream & StreamLog::ThreadSpecificLogStream::flush()
{
    StreamLog::StreamSet streams = StreamLog::StreamBinder::instance().getOutputStreams(parent_);

    for(std::ostream* stream : streams)
    {
        (*stream) << stream_buffer_.str();
    }

    return *this;
}

StreamLog::ThreadSpecificLogStream & StreamLog::ThreadSpecificLogStream::setUnitBuf(bool flag)
{
    unitBuf_ = flag;

    return *this;
}
