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

#ifndef RIPPLE_RIPPLESTATE_H
#define RIPPLE_RIPPLESTATE_H

//
// A ripple line's state.
// - Isolate ledger entry format.
//

class RippleState : public AccountItem
{
public:
    typedef boost::shared_ptr <RippleState> pointer;

public:
    RippleState () { }

    virtual ~RippleState () { }

    AccountItem::pointer makeItem (const uint160& accountID, SerializedLedgerEntry::ref ledgerEntry);

    LedgerEntryType getType ()
    {
        return ltRIPPLE_STATE;
    }

    void setViewAccount (const uint160& accountID);

    const uint160& getAccountID () const
    {
        return  mViewLowest ? mLowID : mHighID;
    }
    
    const uint160& getAccountIDPeer () const
    {
        return !mViewLowest ? mLowID : mHighID;
    }

    // True, Provided auth to peer.
    bool getAuth () const
    {
        return isSetBit (mFlags,  mViewLowest ? lsfLowAuth : lsfHighAuth);
    }

    bool getAuthPeer () const
    {
        return isSetBit (mFlags, !mViewLowest ? lsfLowAuth : lsfHighAuth);
    }

    bool getNoRipple () const
    {
        return isSetBit (mFlags, mViewLowest ? lsfLowNoRipple : lsfHighNoRipple);
    }

    bool getNoRipplePeer () const
    {
        return isSetBit (mFlags, !mViewLowest ? lsfLowNoRipple : lsfHighNoRipple);
    }

    const STAmount& getBalance () const
    {
        return mBalance;
    }

    const STAmount& getLimit () const
    {
        return  mViewLowest ? mLowLimit : mHighLimit;
    }

    const STAmount& getLimitPeer () const
    {
        return !mViewLowest ? mLowLimit : mHighLimit;
    }

    uint32 getQualityIn () const
    {
        return ((uint32) (mViewLowest ? mLowQualityIn : mHighQualityIn));
    }
    
    uint32 getQualityOut () const
    {
        return ((uint32) (mViewLowest ? mLowQualityOut : mHighQualityOut));
    }

    SerializedLedgerEntry::pointer getSLE ()
    {
        return mLedgerEntry;
    }
    
    const SerializedLedgerEntry& peekSLE () const
    {
        return *mLedgerEntry;
    }
    
    SerializedLedgerEntry& peekSLE ()
    {
        return *mLedgerEntry;
    }
    
    Json::Value getJson (int);

    Blob getRaw () const;

private:
    explicit RippleState (SerializedLedgerEntry::ref ledgerEntry);   // For accounts in a ledger

private:
    bool                            mValid;
    bool                            mViewLowest;

    uint32                          mFlags;

    STAmount                        mLowLimit;
    STAmount                        mHighLimit;

    uint160                         mLowID;
    uint160                         mHighID;

    uint64                          mLowQualityIn;
    uint64                          mLowQualityOut;
    uint64                          mHighQualityIn;
    uint64                          mHighQualityOut;

    STAmount                        mBalance;
};
#endif
// vim:ts=4
