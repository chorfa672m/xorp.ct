// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001,2002 International Computer Science Institute
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software")
// to deal in the Software without restriction, subject to the conditions
// listed in the XORP LICENSE file. These conditions include: you must
// preserve this copyright notice, and you cannot mention the copyright
// holders in advertising related to the Software without their permission.
// The Software is provided WITHOUT ANY WARRANTY, EXPRESS OR IMPLIED. This
// notice is a summary of the XORP LICENSE file; the license in that file is
// legally binding.

// $XORP: xorp/libxipc/finder_messenger.hh,v 1.1 2003/01/21 18:51:36 hodson Exp $

#ifndef __LIBXIPC_FINDER_MESSENGER__
#define __LIBXIPC_FINDER_MESSENGER__

#include <map>

#include "libxorp/eventloop.hh"
#include "xrl_cmd_map.hh"
#include "xrl_sender.hh"

/**
 * @short Base class for FinderMessenger classes.
 *
 * FinderMessenger classes are expected to handle the transport and
 * dispatch of Xrl's and their responses.  This base class provides a
 * common code for actually doing the Xrl dispatch and handling the
 * state associated with their responses.
 */
class FinderMessengerBase : public XrlSender
{
public:
    FinderMessengerBase(EventLoop& e,
			XrlCmdMap& cmds)
	: _event_loop(e), _cmds(cmds)
    {}
    
    virtual ~FinderMessengerBase();
    
    typedef XrlSender::Callback SendCallback;

    virtual bool send(const Xrl& xrl, const SendCallback& scb) = 0;

    virtual bool pending() const = 0;

    inline XrlCmdMap& command_map();

    inline EventLoop& event_loop();
    
protected:
    /**
     * A method derived classes can implement to perform an action, eg
     * set context, immediately before the an Xrl is dispatched.
     *
     * By default a no-op.
     */
    virtual void pre_dispatch_xrl();

    /**
     * Find command associated with Xrl and dispatch it.  pre_dispatch_xrl()
     * and post_dispatch_xrl() are called either side of Xrl.  
     *
     * @param seqno sequence number to be passed to reply.
     */
    void dispatch_xrl(uint32_t seqno, const Xrl& x);

    /**
     * A method derived classes can implement to perform an action, eg
     * clear context, immediately after an Xrl is dispatched.  Response is
     * propagated by calling reply().
     *
     * By default a no-op.
     */
    virtual void post_dispatch_xrl();
    
    bool dispatch_xrl_response(uint32_t seqno,
			       const XrlError& e,
			       XrlArgs*);

    bool store_xrl_response(uint32_t seqno, const SendCallback& scb);
    
    virtual void reply(uint32_t seqno,
		       const XrlError& e,
		       const XrlArgs* reply_args) = 0;

    void response_timeout(uint32_t seqno);

private:
    struct ResponseState {
	ResponseState(uint32_t		   seqno,
		      const SendCallback&  cb,
		      FinderMessengerBase* fmb)
	    : scb(cb)
	{
	    expiry = fmb->event_loop().new_oneoff_after_ms(response_timeout_ms,
			callback(fmb,  &FinderMessengerBase::response_timeout,
				 seqno));
	}

	SendCallback scb;
	XorpTimer    expiry;

	static const uint32_t response_timeout_ms = 2000;
    };
    typedef map<uint32_t, ResponseState> SeqNoResponseMap;

    friend class ResponseState;

private:
    EventLoop&			 _event_loop;
    SeqNoResponseMap		 _expected_responses;
    XrlCmdMap&			 _cmds;
};

///////////////////////////////////////////////////////////////////////////////
//
// Inline methods

inline XrlCmdMap&
FinderMessengerBase::command_map()
{
    return _cmds;
}

inline EventLoop&
FinderMessengerBase::event_loop()
{
    return _event_loop;
}

#endif // __LIBXIPC_FINDER_MESSENGER__
