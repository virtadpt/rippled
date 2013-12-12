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

#ifndef RIPPLE_BASICS_LOGGEDTIMINGS_H_INCLUDED
#define RIPPLE_BASICS_LOGGEDTIMINGS_H_INCLUDED

namespace detail
{

/** Template class that performs destruction of an object.
    Default implementation simply calls delete
*/
template <typename Object>
struct Destroyer
{
    static void destroy (Object& object)
    {
        delete &object;
    }
};

/** Specialization for boost::shared_ptr.
*/
template <typename Object>
struct Destroyer <boost::shared_ptr <Object> >
{
    static void destroy (boost::shared_ptr <Object>& p)
    {
        p.reset ();
    }
};

/** Specialization for boost::unordered_map
*/
template <typename Key, typename Value>
struct Destroyer <boost::unordered_map <Key, Value> >
{
    static void destroy (boost::unordered_map <Key, Value>& v)
    {
        v.clear ();
    }
};

/** Cleans up an elaspsed time so it prints nicely */
inline double cleanElapsed (double seconds) noexcept
{
    if (seconds >= 10)
        return std::floor (seconds + 0.5);

    return static_cast <int> ((seconds * 10 + 0.5) / 10);
}

}

//------------------------------------------------------------------------------

/** Measure the time required to destroy an object.
*/

template <typename Object>
double timedDestroy (Object& object)
{
    int64 const startTime (Time::getHighResolutionTicks ());

    detail::Destroyer <Object>::destroy (object);

    return Time::highResolutionTicksToSeconds (
            Time::getHighResolutionTicks () - startTime);
}

/** Log the timed destruction of an object if the time exceeds a threshold.
*/
template <typename PartitionKey, typename Object>
void logTimedDestroy (
    Object& object, String objectDescription, double thresholdSeconds = 1)
{
    double const seconds = timedDestroy (object);

    if (seconds > thresholdSeconds)
    {
        LogSeverity const severity = lsWARNING;

        Log (severity, LogPartition::get <PartitionKey> ()) <<
            objectDescription << " took "<<
            String (detail::cleanElapsed (seconds)) <<
            " seconds to destroy";
    }
}

//------------------------------------------------------------------------------

/** Log a timed function call if the time exceeds a threshold. */
template <typename Function>
void logTimedCall (Journal::Stream stream,
                   String description,
                   char const* fileName,
                   int lineNumber,
    Function f, double thresholdSeconds = 1)
{
    double const seconds = measureFunctionCallTime (f);

    if (seconds > thresholdSeconds)
    {
        stream <<
            description << " took "<<
                String (detail::cleanElapsed (seconds)) <<
                " seconds to execute at " <<
                    Debug::getSourceLocation (fileName, lineNumber);
    }
}

#endif
