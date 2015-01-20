/*
 Copyright (c) 2010, The Barbarian Group
 All rights reserved.

 Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and
    the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
    the following disclaimer in the documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include "MuGlobals.h"
#include "MuStream.h"
#include "MuException.h"

#include <iostream>

namespace mural {

    /**
     * The Url class is not completed and should NOT be used anywhere!
     */
    class Url : public MuObject {
        public:
            Url() {}
            //! Constructs a URL from a string. If \a isEscaped is false, automatically calls Url::encode(). Assumes UTF-8 input.
            explicit Url(const std::string &urlString, bool isEscaped = false);

            //! Returns the string representation of the URL as std::string. Encoded as UTF-8.
            std::string str() const { return mStr; }
            //! Returns the string representation of the URL as char*. Encoded as UTF-8.
            const char* c_str() const { return mStr.c_str(); }

            //! Replaces illegal URL characters as defined by RFC 2396 with their escaped equivalents and returns a copy of \a unescaped. Assumes UTF-8 input.
            static std::string encode(const std::string &unescaped);

        private:
            std::string mStr;
    };

    inline std::ostream& operator<<(std::ostream &out, const Url &url) {
        out << url.str();
        return out;
    }

    inline std::istream& operator>>(std::istream &is, Url &url) {
        std::string temp;
        is >> temp;
        url = Url(temp);
        return is;
    }

    //! Options for loadUrl() to dictate caching and timeout behavior
    class UrlOptions : public MuObject {
        public:
            UrlOptions(bool ignoreCache = false, float timeoutSeconds = 30.0f):
                mIgnoreCache(ignoreCache),
                mTimeout(timeoutSeconds)
            {}

            UrlOptions& ignoreCache(bool ignore = true) { mIgnoreCache = ignore; return *this; }
            bool getIgnoreCache() const { return mIgnoreCache; }
            void setIgnoreCache(bool ignore = true) { mIgnoreCache = ignore; }

            UrlOptions& timeout(float seconds) { mTimeout = seconds; return *this; }
            float getTimeout() const { return mTimeout; }
            void setTimeout(float seconds) { mTimeout = seconds; }

        private:
            bool mIgnoreCache;
            float mTimeout;
    };

}