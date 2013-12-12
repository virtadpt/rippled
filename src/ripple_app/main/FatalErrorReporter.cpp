//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2012, 2013 Ripple Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

FatalErrorReporter::FatalErrorReporter ()
{
    m_savedReporter = FatalError::setReporter (this);
}

FatalErrorReporter::~FatalErrorReporter ()
{
    FatalError::setReporter (m_savedReporter);
}

void FatalErrorReporter::reportMessage (String& formattedMessage)
{
    Log::out() << formattedMessage.toRawUTF8 ();
}

//------------------------------------------------------------------------------

class FatalErrorReporterTests : public UnitTest
{
public:
    FatalErrorReporterTests () : UnitTest ("FatalErrorReporter", "ripple", runManual)
    {
    }

    void runTest ()
    {
        beginTestCase ("report");

        FatalErrorReporter reporter;

        // We don't really expect the program to run after this
        // but the unit test is here so you can manually test it.

        FatalError ("The unit test intentionally failed", __FILE__, __LINE__);
    }
};

static FatalErrorReporterTests fatalErrorReporterTests;
