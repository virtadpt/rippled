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

#ifndef RIPPLE_LEDGERCLEANER_H_INCLUDED
#define RIPPLE_LEDGERCLEANER_H_INCLUDED

/** Check the ledger/transaction databases to make sure they have continuity */
class LedgerCleaner
    : public Stoppable
    , public PropertyStream::Source
{
protected:
    explicit LedgerCleaner (Stoppable& parent);

public:
    /** Create a new object.
        The caller receives ownership and must delete the object when done.
    */
    static LedgerCleaner* New (
        Stoppable& parent,
        Journal journal);

    /** Destroy the object. */
    virtual ~LedgerCleaner () = 0;

    /** Start a long running task to clean the ledger.
        The ledger is cleaned asynchronously, on an implementation defined
        thread. This function call does not block. The long running task
        will be stopped if the Stoppable stops.

        Thread safety:
            Safe to call from any thread at any time.

        @param parameters A Json object with configurable parameters.
    */
    virtual void doClean (Json::Value const& parameters) = 0;
};

#endif
