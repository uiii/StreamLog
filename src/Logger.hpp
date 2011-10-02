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

#ifndef STREAMLOG_LOGGER_HPP
#define STREAMLOG_LOGGER_HPP

#include <map>
#include <list>
#include <memory>

#include "LogStream.hpp"

namespace StreamLog
{
    template <typename CategoryType>
    class Logger
    {
    public:
        Logger(std::list<CategoryType> categoryList);

        LogStream& operator[](CategoryType category);

    private:
        std::map<CategoryType, std::unique_ptr<LogStream>> logStreams_;
    };

    template<typename CategoryType>
    Logger<CategoryType>::Logger(std::list<CategoryType> categoryList)
    {
        for(CategoryType& category : categoryList)
        {
            logStreams_[category] = std::unique_ptr<LogStream>(new LogStream);
        }
    }

    template<typename CategoryType>
    LogStream& Logger<CategoryType>::operator[](CategoryType category)
    {
        return *logStreams_[category];
    }
}

#endif // STREAMLOG_LOGGER_HPP
