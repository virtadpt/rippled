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

#ifndef RIPPLE_TRANSACTIONACQUIRE_H
#define RIPPLE_TRANSACTIONACQUIRE_H

// VFALCO TODO rename to PeerTxRequest
// A transaction set we are trying to acquire
class TransactionAcquire
    : public PeerSet
    , public boost::enable_shared_from_this <TransactionAcquire>
    , public CountedObject <TransactionAcquire>
{
public:
    static char const* getCountedObjectName () { return "TransactionAcquire"; }

    typedef boost::shared_ptr<TransactionAcquire> pointer;

public:
    explicit TransactionAcquire (uint256 const& hash);
    virtual ~TransactionAcquire ()
    {
        ;
    }

    SHAMap::ref getMap ()
    {
        return mMap;
    }

    SHAMapAddNode takeNodes (const std::list<SHAMapNode>& IDs,
                             const std::list< Blob >& data, Peer::ref);

private:
    SHAMap::pointer     mMap;
    bool                mHaveRoot;

    void onTimer (bool progress, ScopedLockType& peerSetLock);
    void newPeer (Peer::ref peer)
    {
        trigger (peer);
    }

    void done ();
    void trigger (Peer::ref);
    boost::weak_ptr<PeerSet> pmDowncast ();
};

#endif
