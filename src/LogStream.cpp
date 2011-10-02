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

#include "LogStream.hpp"

StreamLog::LogStream::LogStream()
{
}

StreamLog::ThreadSpecificLogStream& StreamLog::LogStream::getThreadSpecificLogStream_()
{
    if(! threadSpecificLogStream_.get())
    {
        threadSpecificLogStream_.reset(new StreamLog::ThreadSpecificLogStream(*this));
    }

    return *threadSpecificLogStream_.get();
}

StreamLog::ThreadSpecificLogStream& StreamLog::LogStream::operator<<(ostream_modifier modifier)
{
    ThreadSpecificLogStream& stream = getThreadSpecificLogStream_();

    stream << modifier;

    return stream;
}

StreamLog::ThreadSpecificLogStream& StreamLog::LogStream::operator<<(ios_base_modifier modifier)
{
    ThreadSpecificLogStream& stream = getThreadSpecificLogStream_();

    stream << modifier;

    return stream;
}

StreamLog::ThreadSpecificLogStream& StreamLog::LogStream::operator<<(ios_modifier modifier)
{
    ThreadSpecificLogStream& stream = getThreadSpecificLogStream_();

    stream << modifier;

    return stream;
}

void StreamLog::LogStream::bind(OutputStream& outputStream)
{
    boost::lock_guard<boost::mutex> lock(bindMutex_);

    // TODO polymorfismus
    outputStreams_.insert(outputStream);
}

void StreamLog::LogStream::unbind(OutputStream& outputStream)
{
    boost::lock_guard<boost::mutex> lock(bindMutex_);

    auto it = outputStreams_.find(outputStream);
    if(it != outputStreams_.end())
    {
        outputStreams_.erase(streamIt);
    }
}

StreamLog::OutputStreamSet StreamLog::LogStream::getOutputStreams()
{
    boost::lock_guard<boost::mutex> lock(bindMutex_);

    return outputStreams_;
}
