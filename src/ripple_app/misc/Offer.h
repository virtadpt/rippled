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

#ifndef RIPPLE_OFFER_H
#define RIPPLE_OFFER_H

class Offer : public AccountItem
{
public:
    Offer () {}

    virtual ~Offer () {}

    AccountItem::pointer makeItem (const uint160&, SerializedLedgerEntry::ref ledgerEntry);

    LedgerEntryType getType ()
    {
        return (ltOFFER);
    }

    const STAmount& getTakerPays ()
    {
        return (mTakerPays);
    }
    const STAmount& getTakerGets ()
    {
        return (mTakerGets);
    }
    const RippleAddress& getAccount ()
    {
        return (mAccount);
    }
    int getSeq ()
    {
        return (mSeq);
    }
    Json::Value getJson (int);

private:
    // For accounts in a ledger
    explicit Offer (SerializedLedgerEntry::pointer ledgerEntry);

private:
    RippleAddress mAccount;
    STAmount mTakerGets;
    STAmount mTakerPays;
    int mSeq;
};

#endif

// vim:ts=4
