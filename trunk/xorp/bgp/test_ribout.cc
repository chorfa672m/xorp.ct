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

#ident "$XORP: xorp/bgp/test_ribout.cc,v 1.2 2002/12/14 23:15:32 mjh Exp $"

#include "bgp_module.h"
#include "config.h"
#include "libxorp/selector.hh"
#include "libxorp/xlog.h"
#include "libxorp/asnum.hh"

#include "main.hh"
#include "route_table_base.hh"
#include "route_table_ribout.hh"
#include "route_table_debug.hh"
#include "peer_handler_debug.hh"
#include "path_attribute_list.hh"
#include "local_data.hh"
#include "dump_iterators.hh"


int main(int, char** argv) {
    //stuff needed to create an eventloop
    xlog_init(argv[0], NULL);
    xlog_set_verbose(XLOG_VERBOSE_LOW);		// Least verbose messages
    xlog_add_default_output();
    xlog_start();
    BGPMain bgpmain;
    //    EventLoop* eventloop = bgpmain.get_eventloop();
    LocalData localdata;
    Iptuple iptuple;
    BGPPeerData *peer_data
	= new BGPPeerData(iptuple, AsNum((uint16_t)1), IPv4("2.0.0.1"), 30);
    peer_data->set_internal_peer(true);
    BGPPeer peer1(&localdata, peer_data, NULL, &bgpmain);
    DebugPeerHandler handler(&peer1);

    //trivial plumbing
    BGPDebugTable<IPv4>* debug_table
	 = new BGPDebugTable<IPv4>("D1", NULL);
    BGPRibOutTable<IPv4> *ribout_table
	= new BGPRibOutTable<IPv4>("RibOut", debug_table, &handler);

    debug_table->set_output_file("/tmp/test_ribout");
    debug_table->set_canned_response(ADD_USED);
    handler.set_output_file(debug_table->output_file());

    //create a load of attributes 
    IPNet<IPv4> net1("1.0.1.0/24");
    IPNet<IPv4> net2("1.0.2.0/24");
    IPNet<IPv4> net3("1.0.3.0/24");

    IPv4 nexthop1("2.0.0.1");
    NextHopAttribute<IPv4> nhatt1(nexthop1);

    IPv4 nexthop2("2.0.0.2");
    NextHopAttribute<IPv4> nhatt2(nexthop2);

    IPv4 nexthop3("2.0.0.3");
    NextHopAttribute<IPv4> nhatt3(nexthop3);

    OriginAttribute igp_origin_att(IGP);

    AsPath aspath1;
    aspath1.add_AS_in_sequence(AsNum((uint16_t)1));
    aspath1.add_AS_in_sequence(AsNum((uint16_t)2));
    aspath1.add_AS_in_sequence(AsNum((uint16_t)3));
    ASPathAttribute aspathatt1(aspath1);

    AsPath aspath2;
    aspath2.add_AS_in_sequence(AsNum((uint16_t)4));
    aspath2.add_AS_in_sequence(AsNum((uint16_t)5));
    aspath2.add_AS_in_sequence(AsNum((uint16_t)6));
    ASPathAttribute aspathatt2(aspath2);

    AsPath aspath3;
    aspath3.add_AS_in_sequence(AsNum((uint16_t)7));
    aspath3.add_AS_in_sequence(AsNum((uint16_t)8));
    aspath3.add_AS_in_sequence(AsNum((uint16_t)9));
    ASPathAttribute aspathatt3(aspath3);

    PathAttributeList<IPv4>* palist1 =
	new PathAttributeList<IPv4>(nhatt1, aspathatt1, igp_origin_att);

    PathAttributeList<IPv4>* palist2 =
	new PathAttributeList<IPv4>(nhatt2, aspathatt2, igp_origin_att);

    PathAttributeList<IPv4>* palist3 =
	new PathAttributeList<IPv4>(nhatt3, aspathatt3, igp_origin_att);

    //create a subnet route
    SubnetRoute<IPv4> *sr1, *sr2;

    InternalMessage<IPv4>* msg;

    UNUSED(sr2);
    UNUSED(palist2);
    UNUSED(palist3);
    //================================================================
    //Test1: trivial add and delete
    //================================================================
    //add a route
    debug_table->write_comment("TEST 1");
    debug_table->write_comment("ADD AND DELETE");
    sr1 = new SubnetRoute<IPv4>(net1, palist1);
    msg = new InternalMessage<IPv4>(sr1, &handler, 0);
    msg->set_push();
    ribout_table->add_route(*msg, debug_table);

    debug_table->write_separator();

    //delete the route
    ribout_table->delete_route(*msg, debug_table);
    msg->set_push();

    debug_table->write_separator();
    delete sr1;
    delete msg;

    //================================================================
    //Test2: three adds, two with the same PAlist.
    //================================================================
    //add a route
    debug_table->write_comment("TEST 2");
    debug_table->write_comment("THREE ADDS ON TWO PA_LISTS");
    sr1 = new SubnetRoute<IPv4>(net1, palist1);
    msg = new InternalMessage<IPv4>(sr1, &handler, 0);
    ribout_table->add_route(*msg, debug_table);
    delete sr1;
    delete msg;

    sr1 = new SubnetRoute<IPv4>(net2, palist2);
    msg = new InternalMessage<IPv4>(sr1, &handler, 0);
    ribout_table->add_route(*msg, debug_table);
    delete sr1;
    delete msg;

    sr1 = new SubnetRoute<IPv4>(net3, palist1);
    msg = new InternalMessage<IPv4>(sr1, &handler, 0);
    ribout_table->add_route(*msg, debug_table);
    delete sr1;
    delete msg;

    ribout_table->push(debug_table);

    debug_table->write_separator();

    //================================================================
    //Test3: delete then add
    //================================================================
    //add a route
    debug_table->write_comment("TEST 3");
    debug_table->write_comment("DELETE THEN ADD");
    sr1 = new SubnetRoute<IPv4>(net1, palist1);
    msg = new InternalMessage<IPv4>(sr1, &handler, 0);
    ribout_table->delete_route(*msg, debug_table);
    delete sr1;
    delete msg;

    sr1 = new SubnetRoute<IPv4>(net1, palist1);
    msg = new InternalMessage<IPv4>(sr1, &handler, 0);
    ribout_table->add_route(*msg, debug_table);
    delete sr1;
    delete msg;

    ribout_table->push(debug_table);

    debug_table->write_separator();

    //================================================================
    //Test4: add when peer is busy
    //================================================================
    //add a route
    debug_table->write_comment("TEST 4");
    debug_table->write_comment("ADD WHEN PEER BUSY");
    handler.set_canned_response(PEER_OUTPUT_BUSY);

    sr1 = new SubnetRoute<IPv4>(net1, palist1);
    msg = new InternalMessage<IPv4>(sr1, &handler, 0);
    ribout_table->add_route(*msg, debug_table);
    delete sr1;
    delete msg;

    ribout_table->push(debug_table);

    debug_table->write_separator();

    debug_table->write_comment("PEER_GOES IDLE");
    handler.set_canned_response(PEER_OUTPUT_OK);
    debug_table->set_next_messages(2);
    ribout_table->output_no_longer_busy();

    //================================================================
    //Check debug output against reference
    //================================================================

    debug_table->write_separator();
    debug_table->write_comment("SHUTDOWN AND CLEAN UP");

    delete ribout_table;
    delete debug_table;
    delete palist1;
    delete palist2;
    delete palist3;

    FILE *file = fopen("/tmp/test_ribout", "r");
    if (file == NULL) {
	fprintf(stderr, "Failed to read /tmp/test_ribout\n");
	fprintf(stderr, "TEST FAILED\n");
	exit(1);
    }
#define BUFSIZE 8192
    char testout[BUFSIZE];
    memset(testout, 0, BUFSIZE);
    int bytes1 = fread(testout, 1, BUFSIZE, file);
    if (bytes1 == BUFSIZE) {
	fprintf(stderr, "Output too long for buffer\n");
	fprintf(stderr, "TEST FAILED\n");
	exit(1);
    }
    fclose(file);
    
    file = fopen("test_ribout.reference", "r");
    if (file == NULL) {
	fprintf(stderr, "Failed to read test_ribout.reference\n");
	fprintf(stderr, "TEST FAILED\n");
	exit(1);
    }
    char refout[BUFSIZE];
    memset(refout, 0, BUFSIZE);
    int bytes2 = fread(refout, 1, BUFSIZE, file);
    if (bytes2 == BUFSIZE) {
	fprintf(stderr, "Output too long for buffer\n");
	fprintf(stderr, "TEST FAILED\n");
	exit(1);
    }
    fclose(file);
    
    if ((bytes1 != bytes2) || (memcmp(testout, refout, bytes1)!= 0)) {
	fprintf(stderr, "Output in /tmp/test_ribout doesn't match reference output\n");
	fprintf(stderr, "TEST FAILED\n");
	exit(1);
	
    }
    unlink("/tmp/test_ribout");
}


