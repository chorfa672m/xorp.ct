/*
 * Copyright (c) 2001-2003 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'tgt-gen'.
 *
 * $XORP: xorp/xrl/targets/rip4_base.hh,v 1.3 2003/11/18 01:47:42 hodson Exp $
 */


#ifndef __XRL_INTERFACES_RIP4_BASE_HH__
#define __XRL_INTERFACES_RIP4_BASE_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XrlRip4Target"

#include "libxorp/xlog.h"
#include "libxipc/xrl_cmd_map.hh"

class XrlRip4TargetBase {
protected:
    XrlCmdMap* _cmds;

public:
    /**
     * Constructor.
     *
     * @param cmds an XrlCmdMap that the commands associated with the target
     *		   should be added to.  This is typically the XrlRouter
     *		   associated with the target.
     */
    XrlRip4TargetBase(XrlCmdMap* cmds = 0);

    /**
     * Destructor.
     *
     * Dissociates instance commands from command map.
     */
    virtual ~XrlRip4TargetBase();

    /**
     * Set command map.
     *
     * @param cmds pointer to command map to associate commands with.  This
     * argument is typically a pointer to the XrlRouter associated with the
     * target.
     *
     * @return true on success, false if cmds is null or a command map has
     * already been supplied.
     */
    bool set_command_map(XrlCmdMap* cmds);

    /**
     * Get Xrl instance name associated with command map.
     */
    inline const string& name() const { return _cmds->name(); }

    /**
     * Get version string of instance.
     */
    inline const char* version() const { return "rip4/0.0"; }

protected:

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get name of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_target_name(
	// Output values,
	string&	name) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get version string from Xrl Target
     */
    virtual XrlCmdError common_0_1_get_version(
	// Output values,
	string&	version) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get status of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_status(
	// Output values,
	uint32_t&	status,
	string&	reason) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Request clean shutdown of Xrl Target
     */
    virtual XrlCmdError common_0_1_shutdown() = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Announce target birth.
     */
    virtual XrlCmdError finder_event_observer_0_1_xrl_target_birth(
	// Input values,
	const string&	target_class,
	const string&	target_instance) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Announce target death.
     */
    virtual XrlCmdError finder_event_observer_0_1_xrl_target_death(
	// Input values,
	const string&	target_class,
	const string&	target_instance) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Add an address to run RIP process on. The addition of address is not
     *  instantaneous, RIP has to instantiate state in the FEA to send and
     *  receive packets. Once instantiated the address must be explicitly
     *  enabled with set_rip_address_enabled.
     *
     *  @param ifname the interface that owns vif that has address.
     *
     *  @param vifname virtual interface owning address.
     *
     *  @param addr the address to be added.
     */
    virtual XrlCmdError rip4_0_1_add_rip_address(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Remove an address RIP process is running on.
     *
     *  @param ifname the interface that owns vif that has address.
     *
     *  @param vifname virtual interface owning address.
     *
     *  @param addr the address to be removed.
     */
    virtual XrlCmdError rip4_0_1_remove_rip_address(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr) = 0;

    virtual XrlCmdError rip4_0_1_set_rip_address_enabled(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const bool&	enabled) = 0;

    virtual XrlCmdError rip4_0_1_get_rip_address_enabled(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	bool&	enabled) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get a textual description of the status of address RIP is running upon.
     *
     *  @param ifname the interface that owns vif that has the address.
     *
     *  @param vifname virtual interface owns the address.
     *
     *  @param addr the address to query.
     */
    virtual XrlCmdError rip4_0_1_get_rip_address_status(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	string&	status) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket4/0.1 when a packet arrives
     *  from an IPv4 source.
     *
     *  @param sockid the identifier associated with socket where error
     *  occurred.
     *
     *  @param src_host the originating host.
     *
     *  @param src_port the originating IP port.
     *
     *  @param data the data received.
     */
    virtual XrlCmdError socket4_user_0_1_recv_event(
	// Input values,
	const string&	sockid,
	const IPv4&	src_host,
	const uint32_t&	src_port,
	const vector<uint8_t>&	data) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket4/0.1 when a connection
     *  request is received from an IPv4 source.
     */
    virtual XrlCmdError socket4_user_0_1_connect_event(
	// Input values,
	const string&	sockid,
	const IPv4&	src_host,
	const uint32_t&	src_port,
	const string&	new_sockid,
	// Output values,
	bool&	accept) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket4/0.1 when an error occurs.
     *
     *  @param sockid the identifier associated with socket where error
     *  occurred.
     *
     *  @param error a textual description of the error.
     *
     *  @param fatal indication of whether socket is shutdown because of error.
     */
    virtual XrlCmdError socket4_user_0_1_error_event(
	// Input values,
	const string&	sockid,
	const string&	error,
	const bool&	fatal) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket4/0.1 when a socket is
     *  forcibly closed. This would typically happen when the address the
     *  socket is bound to is removed from an interface. This method is not
     *  called if the socket is closed through socket/0.1/close.
     */
    virtual XrlCmdError socket4_user_0_1_close_event(
	// Input values,
	const string&	sockid,
	const string&	reason) = 0;

private:
    const XrlCmdError handle_common_0_1_get_target_name(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_version(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_status(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_shutdown(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_event_observer_0_1_xrl_target_birth(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_event_observer_0_1_xrl_target_death(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip4_0_1_add_rip_address(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip4_0_1_remove_rip_address(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip4_0_1_set_rip_address_enabled(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip4_0_1_get_rip_address_enabled(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip4_0_1_get_rip_address_status(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_user_0_1_recv_event(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_user_0_1_connect_event(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_user_0_1_error_event(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_user_0_1_close_event(const XrlArgs& in, XrlArgs* out);

    void add_handlers()
    {
	if (_cmds->add_handler("common/0.1/get_target_name",
	    callback(this, &XrlRip4TargetBase::handle_common_0_1_get_target_name)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rip4/common/0.1/get_target_name");
	}
	if (_cmds->add_handler("common/0.1/get_version",
	    callback(this, &XrlRip4TargetBase::handle_common_0_1_get_version)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rip4/common/0.1/get_version");
	}
	if (_cmds->add_handler("common/0.1/get_status",
	    callback(this, &XrlRip4TargetBase::handle_common_0_1_get_status)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rip4/common/0.1/get_status");
	}
	if (_cmds->add_handler("common/0.1/shutdown",
	    callback(this, &XrlRip4TargetBase::handle_common_0_1_shutdown)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rip4/common/0.1/shutdown");
	}
	if (_cmds->add_handler("finder_event_observer/0.1/xrl_target_birth",
	    callback(this, &XrlRip4TargetBase::handle_finder_event_observer_0_1_xrl_target_birth)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rip4/finder_event_observer/0.1/xrl_target_birth");
	}
	if (_cmds->add_handler("finder_event_observer/0.1/xrl_target_death",
	    callback(this, &XrlRip4TargetBase::handle_finder_event_observer_0_1_xrl_target_death)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rip4/finder_event_observer/0.1/xrl_target_death");
	}
	if (_cmds->add_handler("rip4/0.1/add_rip_address",
	    callback(this, &XrlRip4TargetBase::handle_rip4_0_1_add_rip_address)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rip4/rip4/0.1/add_rip_address");
	}
	if (_cmds->add_handler("rip4/0.1/remove_rip_address",
	    callback(this, &XrlRip4TargetBase::handle_rip4_0_1_remove_rip_address)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rip4/rip4/0.1/remove_rip_address");
	}
	if (_cmds->add_handler("rip4/0.1/set_rip_address_enabled",
	    callback(this, &XrlRip4TargetBase::handle_rip4_0_1_set_rip_address_enabled)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rip4/rip4/0.1/set_rip_address_enabled");
	}
	if (_cmds->add_handler("rip4/0.1/get_rip_address_enabled",
	    callback(this, &XrlRip4TargetBase::handle_rip4_0_1_get_rip_address_enabled)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rip4/rip4/0.1/get_rip_address_enabled");
	}
	if (_cmds->add_handler("rip4/0.1/get_rip_address_status",
	    callback(this, &XrlRip4TargetBase::handle_rip4_0_1_get_rip_address_status)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rip4/rip4/0.1/get_rip_address_status");
	}
	if (_cmds->add_handler("socket4_user/0.1/recv_event",
	    callback(this, &XrlRip4TargetBase::handle_socket4_user_0_1_recv_event)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rip4/socket4_user/0.1/recv_event");
	}
	if (_cmds->add_handler("socket4_user/0.1/connect_event",
	    callback(this, &XrlRip4TargetBase::handle_socket4_user_0_1_connect_event)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rip4/socket4_user/0.1/connect_event");
	}
	if (_cmds->add_handler("socket4_user/0.1/error_event",
	    callback(this, &XrlRip4TargetBase::handle_socket4_user_0_1_error_event)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rip4/socket4_user/0.1/error_event");
	}
	if (_cmds->add_handler("socket4_user/0.1/close_event",
	    callback(this, &XrlRip4TargetBase::handle_socket4_user_0_1_close_event)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rip4/socket4_user/0.1/close_event");
	}
	_cmds->finalize();
    }

    void remove_handlers()
    {
	_cmds->remove_handler("common/0.1/get_target_name");
	_cmds->remove_handler("common/0.1/get_version");
	_cmds->remove_handler("common/0.1/get_status");
	_cmds->remove_handler("common/0.1/shutdown");
	_cmds->remove_handler("finder_event_observer/0.1/xrl_target_birth");
	_cmds->remove_handler("finder_event_observer/0.1/xrl_target_death");
	_cmds->remove_handler("rip4/0.1/add_rip_address");
	_cmds->remove_handler("rip4/0.1/remove_rip_address");
	_cmds->remove_handler("rip4/0.1/set_rip_address_enabled");
	_cmds->remove_handler("rip4/0.1/get_rip_address_enabled");
	_cmds->remove_handler("rip4/0.1/get_rip_address_status");
	_cmds->remove_handler("socket4_user/0.1/recv_event");
	_cmds->remove_handler("socket4_user/0.1/connect_event");
	_cmds->remove_handler("socket4_user/0.1/error_event");
	_cmds->remove_handler("socket4_user/0.1/close_event");
    }
};

#endif /* __XRL_INTERFACES_RIP4_BASE_HH__ */
