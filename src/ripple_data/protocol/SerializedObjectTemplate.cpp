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

SOTemplate::SOTemplate ()
{
}

void SOTemplate::push_back (SOElement const& r)
{
    // Ensure there is the enough space in the index mapping
    // table for all possible fields.
    //
    if (mIndex.empty ())
    {
        // Unmapped indices will be set to -1
        //
        mIndex.resize (SField::getNumFields () + 1, -1);
    }

    // Make sure the field's index is in range
    //
    assert (r.e_field.getNum () < mIndex.size ());

    // Make sure that this field hasn't already been assigned
    //
    assert (getIndex (r.e_field) == -1);

    // Add the field to the index mapping table
    //
    mIndex [r.e_field.getNum ()] = mTypes.size ();

    // Append the new element.
    //
    mTypes.push_back (new SOElement (r));
}

int SOTemplate::getIndex (SField::ref f) const
{
    // The mapping table should be large enough for any possible field
    //
    assert (f.getNum () < mIndex.size ());

    return mIndex[f.getNum ()];
}
