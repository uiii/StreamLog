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

#include "StreamBinder.hpp"

boost::mutex StreamLog::StreamBinder::static_mutex_;
StreamLog::StreamBinder* StreamLog::StreamBinder::instance_ = nullptr;

StreamLog::StreamBinder::StreamBinder()
{
}

void StreamLog::StreamBinder::bind(StreamLog::LogStream &logStream, std::ostream &outputStream)
{
    bindings_[&logStream].insert(&outputStream);
}

void StreamLog::StreamBinder::unbind(StreamLog::LogStream &logStream, std::ostream &outputStream)
{
    StreamSet& streams = bindings_[&logStream];

    auto streamIt = streams.find(&outputStream);
    if(streamIt != streams.end())
    {
        streams.erase(streamIt);
    }
}

const StreamLog::StreamSet & StreamLog::StreamBinder::getOutputStreams(StreamLog::LogStream &logStream)
{
    return bindings_[&logStream];
}

StreamLog::StreamBinder & StreamLog::StreamBinder::instance()
{
    if(! instance_)
    {
        boost::lock_guard<boost::mutex> lock(static_mutex_);
        if(! instance_)
        {
            instance_ = new StreamBinder;
        }
    }

    return *instance_;
}
