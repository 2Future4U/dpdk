/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2001-2018
 */

#ifndef _ICE_FLOW_H_
#define _ICE_FLOW_H_

#include "ice_flex_type.h"
#define ICE_IPV4_MAKE_PREFIX_MASK(prefix) ((u32)(~0) << (32 - (prefix)))
#define ICE_FLOW_PROF_ID_INVAL		0xfffffffffffffffful
#define ICE_FLOW_PROF_ID_BYPASS		0
#define ICE_FLOW_PROF_ID_DEFAULT	1
#define ICE_FLOW_ENTRY_HANDLE_INVAL	0
#define ICE_FLOW_VSI_INVAL		0xffff
#define ICE_FLOW_FLD_OFF_INVAL		0xffff

/* Use any of the type from flow field to generate a equivalent hash field */
#define ICE_FLOW_HASH_FLD(t)	(1ULL << (t))

#define ICE_FLOW_HASH_IPV4	\
	(ICE_FLOW_HASH_FLD(ICE_FLOW_FIELD_IDX_IPV4_SA) | \
	 ICE_FLOW_HASH_FLD(ICE_FLOW_FIELD_IDX_IPV4_DA))
#define ICE_FLOW_HASH_IPV6	\
	(ICE_FLOW_HASH_FLD(ICE_FLOW_FIELD_IDX_IPV6_SA) | \
	 ICE_FLOW_HASH_FLD(ICE_FLOW_FIELD_IDX_IPV6_DA))
#define ICE_FLOW_HASH_TCP_PORT	\
	(ICE_FLOW_HASH_FLD(ICE_FLOW_FIELD_IDX_TCP_SRC_PORT) | \
	 ICE_FLOW_HASH_FLD(ICE_FLOW_FIELD_IDX_TCP_DST_PORT))
#define ICE_FLOW_HASH_UDP_PORT	\
	(ICE_FLOW_HASH_FLD(ICE_FLOW_FIELD_IDX_UDP_SRC_PORT) | \
	 ICE_FLOW_HASH_FLD(ICE_FLOW_FIELD_IDX_UDP_DST_PORT))
#define ICE_FLOW_HASH_SCTP_PORT	\
	(ICE_FLOW_HASH_FLD(ICE_FLOW_FIELD_IDX_SCTP_SRC_PORT) | \
	 ICE_FLOW_HASH_FLD(ICE_FLOW_FIELD_IDX_SCTP_DST_PORT))

#define ICE_HASH_INVALID	0
#define ICE_HASH_TCP_IPV4	(ICE_FLOW_HASH_IPV4 | ICE_FLOW_HASH_TCP_PORT)
#define ICE_HASH_TCP_IPV6	(ICE_FLOW_HASH_IPV6 | ICE_FLOW_HASH_TCP_PORT)
#define ICE_HASH_UDP_IPV4	(ICE_FLOW_HASH_IPV4 | ICE_FLOW_HASH_UDP_PORT)
#define ICE_HASH_UDP_IPV6	(ICE_FLOW_HASH_IPV6 | ICE_FLOW_HASH_UDP_PORT)
#define ICE_HASH_SCTP_IPV4	(ICE_FLOW_HASH_IPV4 | ICE_FLOW_HASH_SCTP_PORT)
#define ICE_HASH_SCTP_IPV6	(ICE_FLOW_HASH_IPV6 | ICE_FLOW_HASH_SCTP_PORT)

/* Protocol header fields within a packet segment. A segment consists of one or
 * more protocol headers that make up a logical group of protocol headers. Each
 * logical group of protocol headers encapsulates or is encapsulated using/by
 * tunneling or encapsulation protocols for network virtualization such as GRE,
 * VxLAN, etc.
 */
enum ice_flow_seg_hdr {
	ICE_FLOW_SEG_HDR_NONE	= 0x00000000,
	ICE_FLOW_SEG_HDR_ETH	= 0x00000001,
	ICE_FLOW_SEG_HDR_VLAN	= 0x00000002,
	ICE_FLOW_SEG_HDR_IPV4	= 0x00000004,
	ICE_FLOW_SEG_HDR_IPV6	= 0x00000008,
	ICE_FLOW_SEG_HDR_ARP	= 0x00000010,
	ICE_FLOW_SEG_HDR_ICMP	= 0x00000020,
	ICE_FLOW_SEG_HDR_TCP	= 0x00000040,
	ICE_FLOW_SEG_HDR_UDP	= 0x00000080,
	ICE_FLOW_SEG_HDR_SCTP	= 0x00000100,
	ICE_FLOW_SEG_HDR_GRE	= 0x00000200,
};

enum ice_flow_field {
	/* L2 */
	ICE_FLOW_FIELD_IDX_ETH_DA,
	ICE_FLOW_FIELD_IDX_ETH_SA,
	ICE_FLOW_FIELD_IDX_S_VLAN,
	ICE_FLOW_FIELD_IDX_C_VLAN,
	ICE_FLOW_FIELD_IDX_ETH_TYPE,
	/* L3 */
	ICE_FLOW_FIELD_IDX_IP_DSCP,
	ICE_FLOW_FIELD_IDX_IP_TTL,
	ICE_FLOW_FIELD_IDX_IP_PROT,
	ICE_FLOW_FIELD_IDX_IPV4_SA,
	ICE_FLOW_FIELD_IDX_IPV4_DA,
	ICE_FLOW_FIELD_IDX_IPV6_SA,
	ICE_FLOW_FIELD_IDX_IPV6_DA,
	/* L4 */
	ICE_FLOW_FIELD_IDX_TCP_SRC_PORT,
	ICE_FLOW_FIELD_IDX_TCP_DST_PORT,
	ICE_FLOW_FIELD_IDX_UDP_SRC_PORT,
	ICE_FLOW_FIELD_IDX_UDP_DST_PORT,
	ICE_FLOW_FIELD_IDX_SCTP_SRC_PORT,
	ICE_FLOW_FIELD_IDX_SCTP_DST_PORT,
	ICE_FLOW_FIELD_IDX_TCP_FLAGS,
	/* ARP */
	ICE_FLOW_FIELD_IDX_ARP_SIP,
	ICE_FLOW_FIELD_IDX_ARP_DIP,
	ICE_FLOW_FIELD_IDX_ARP_SHA,
	ICE_FLOW_FIELD_IDX_ARP_DHA,
	ICE_FLOW_FIELD_IDX_ARP_OP,
	/* ICMP */
	ICE_FLOW_FIELD_IDX_ICMP_TYPE,
	ICE_FLOW_FIELD_IDX_ICMP_CODE,
	/* GRE */
	ICE_FLOW_FIELD_IDX_GRE_KEYID,
	 /* The total number of enums must not exceed 64 */
	ICE_FLOW_FIELD_IDX_MAX
};

/* Flow headers and fields for AVF support */
enum ice_flow_avf_hdr_field {
	/* Values 0 - 28 are reserved for future use */
	ICE_AVF_FLOW_FIELD_INVALID		= 0,
	ICE_AVF_FLOW_FIELD_UNICAST_IPV4_UDP	= 29,
	ICE_AVF_FLOW_FIELD_MULTICAST_IPV4_UDP,
	ICE_AVF_FLOW_FIELD_IPV4_UDP,
	ICE_AVF_FLOW_FIELD_IPV4_TCP_SYN_NO_ACK,
	ICE_AVF_FLOW_FIELD_IPV4_TCP,
	ICE_AVF_FLOW_FIELD_IPV4_SCTP,
	ICE_AVF_FLOW_FIELD_IPV4_OTHER,
	ICE_AVF_FLOW_FIELD_FRAG_IPV4,
	ICE_AVF_FLOW_FIELD_UNICAST_IPV6_UDP	= 39,
	ICE_AVF_FLOW_FIELD_MULTICAST_IPV6_UDP,
	ICE_AVF_FLOW_FIELD_IPV6_UDP,
	ICE_AVF_FLOW_FIELD_IPV6_TCP_SYN_NO_ACK,
	ICE_AVF_FLOW_FIELD_IPV6_TCP,
	ICE_AVF_FLOW_FIELD_IPV6_SCTP,
	ICE_AVF_FLOW_FIELD_IPV6_OTHER,
	ICE_AVF_FLOW_FIELD_FRAG_IPV6,
	ICE_AVF_FLOW_FIELD_RSVD47,
	ICE_AVF_FLOW_FIELD_FCOE_OX,
	ICE_AVF_FLOW_FIELD_FCOE_RX,
	ICE_AVF_FLOW_FIELD_FCOE_OTHER,
	/* Values 51-62 are reserved */
	ICE_AVF_FLOW_FIELD_L2_PAYLOAD		= 63,
	ICE_AVF_FLOW_FIELD_MAX
};

/* Supported RSS offloads  This macro is defined to support
 * VIRTCHNL_OP_GET_RSS_HENA_CAPS ops. PF driver sends the RSS hardware
 * capabilities to the caller of this ops.
 */
#define ICE_DEFAULT_RSS_HENA ( \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_UDP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_SCTP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_TCP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_OTHER) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_FRAG_IPV4) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_UDP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_TCP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_SCTP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_OTHER) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_FRAG_IPV6) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_TCP_SYN_NO_ACK) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_UNICAST_IPV4_UDP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_MULTICAST_IPV4_UDP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_TCP_SYN_NO_ACK) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_UNICAST_IPV6_UDP) | \
	BIT_ULL(ICE_AVF_FLOW_FIELD_MULTICAST_IPV6_UDP))

enum ice_flow_dir {
	ICE_FLOW_DIR_UNDEFINED	= 0,
	ICE_FLOW_TX		= 0x01,
	ICE_FLOW_RX		= 0x02,
	ICE_FLOW_TX_RX		= ICE_FLOW_RX | ICE_FLOW_TX
};

enum ice_flow_priority {
	ICE_FLOW_PRIO_LOW,
	ICE_FLOW_PRIO_NORMAL,
	ICE_FLOW_PRIO_HIGH
};

#define ICE_FLOW_SEG_MAX		2
#define ICE_FLOW_SEG_RAW_FLD_MAX	2
#define ICE_FLOW_PROFILE_MAX		1024
#define ICE_FLOW_SW_FIELD_VECTOR_MAX	48
#define ICE_FLOW_ACL_FIELD_VECTOR_MAX	32
#define ICE_FLOW_FV_EXTRACT_SZ		2

#define ICE_FLOW_SET_HDRS(seg, val)	((seg)->hdrs |= (u32)(val))

struct ice_flow_seg_xtrct {
	u8 prot_id;	/* Protocol ID of extracted header field */
	u8 off;		/* Starting offset of the field in header in bytes */
	u8 idx;		/* Index of FV entry used */
	u8 disp;	/* Displacement of field in bits fr. FV entry's start */
};

enum ice_flow_fld_match_type {
	ICE_FLOW_FLD_TYPE_REG,		/* Value, mask */
	ICE_FLOW_FLD_TYPE_RANGE,	/* Value, mask, last (upper bound) */
	ICE_FLOW_FLD_TYPE_PREFIX,	/* IP address, prefix, size of prefix */
	ICE_FLOW_FLD_TYPE_SIZE,		/* Value, mask, size of match */
};

struct ice_flow_fld_loc {
	/* Describe offsets of field information relative to the beginning of
	 * input buffer provided when adding flow entries.
	 */
	u16 val;	/* Offset where the value is located */
	u16 mask;	/* Offset where the mask/prefix value is located */
	u16 last;	/* Length or offset where the upper value is located */
};

struct ice_flow_fld_info {
	enum ice_flow_fld_match_type type;
	/* Location where to retrieve data from an input buffer */
	struct ice_flow_fld_loc src;
	/* Location where to put the data into the final entry buffer */
	struct ice_flow_fld_loc entry;
	struct ice_flow_seg_xtrct xtrct;
};

struct ice_flow_seg_fld_raw {
	int off;	/* Offset from the start of the segment */
	struct ice_flow_fld_info info;
};

struct ice_flow_seg_info {
	u32 hdrs;	/* Bitmask indicating protocol headers present */
	u64 match;	/* Bitmask indicating header fields to be matched */
	u64 range;	/* Bitmask indicating header fields matched as ranges */

	struct ice_flow_fld_info fields[ICE_FLOW_FIELD_IDX_MAX];

	u8 raws_cnt;	/* Number of raw fields to be matched */
	struct ice_flow_seg_fld_raw raws[ICE_FLOW_SEG_RAW_FLD_MAX];
};

/* This structure describes a flow entry, and is tracked only in this file */
struct ice_flow_entry {
	struct LIST_ENTRY_TYPE l_entry;

	u64 id;
	u16 vsi_handle;
	enum ice_flow_priority priority;

	struct ice_flow_prof *prof;

	/* Flow entry's content */
	u16 entry_sz;
	void *entry;

	/* Action list */
	u8 acts_cnt;
	struct ice_flow_action *acts;
};

#define ICE_FLOW_ENTRY_HNDL(e)	((unsigned long)e)
#define ICE_FLOW_ENTRY_PTR(h)	((struct ice_flow_entry *)(h))

struct ice_flow_prof {
	struct LIST_ENTRY_TYPE l_entry;

	u64 id;
	enum ice_flow_dir dir;

	/* Keep track of flow entries associated with this flow profile */
	struct ice_lock entries_lock;
	struct LIST_HEAD_TYPE entries;

	u8 segs_cnt;
	struct ice_flow_seg_info segs[ICE_FLOW_SEG_MAX];

	/* software VSI handles referenced by this flow profile */
	ice_declare_bitmap(vsis, ICE_MAX_VSI);

	union {
		/* struct sw_recipe */
		/* struct fd */
		u32 data;
	} cfg;

	/* Default actions */
	u8 acts_cnt;
	struct ice_flow_action *acts;
};

struct ice_rss_cfg {
	struct LIST_ENTRY_TYPE l_entry;
	u64 hashed_flds;
	u32 packet_hdr;
};

enum ice_flow_action_type {
	ICE_FLOW_ACT_NOP,
	ICE_FLOW_ACT_ALLOW,
	ICE_FLOW_ACT_DROP,
	ICE_FLOW_ACT_COUNT,
	ICE_FLOW_ACT_FWD_VSI,
	ICE_FLOW_ACT_FWD_VSI_LIST,	/* Should be abstracted away */
	ICE_FLOW_ACT_FWD_QUEUE,		/* Can Queues be abstracted away? */
	ICE_FLOW_ACT_FWD_QUEUE_GROUP,	/* Can Queues be abstracted away? */
	ICE_FLOW_ACTION_PUSH,
	ICE_FLOW_ACTION_POP,
	ICE_FLOW_ACTION_MODIFY,
};

struct ice_flow_action {
	enum ice_flow_action_type type;
	union {
		u32 dummy;
	} data;
};

/* TDD esp in the linux code doesn't like prototypes, so
 * ifdef them all out, so they stop conflicting with our mocks
 */
u64
ice_flow_find_prof(struct ice_hw *hw, enum ice_block blk, enum ice_flow_dir dir,
		   struct ice_flow_seg_info *segs, u8 segs_cnt);
enum ice_status
ice_flow_add_prof(struct ice_hw *hw, enum ice_block blk, enum ice_flow_dir dir,
		  u64 prof_id, struct ice_flow_seg_info *segs, u8 segs_cnt,
		  struct ice_flow_action *acts, u8 acts_cnt,
		  struct ice_flow_prof **prof);
enum ice_status
ice_flow_rem_prof(struct ice_hw *hw, enum ice_block blk, u64 prof_id);

enum ice_status
ice_flow_get_hw_prof(struct ice_hw *hw, enum ice_block blk, u64 prof_id,
		     u8 *hw_prof);

u64 ice_flow_find_entry(struct ice_hw *hw, enum ice_block blk, u64 entry_id);
enum ice_status
ice_flow_add_entry(struct ice_hw *hw, enum ice_block blk, u64 prof_id,
		   u64 entry_id, u16 vsi, enum ice_flow_priority prio,
		   void *data, struct ice_flow_action *acts, u8 acts_cnt,
		   u64 *entry_h);
enum ice_status ice_flow_rem_entry(struct ice_hw *hw, u64 entry_h);
void
ice_flow_set_fld(struct ice_flow_seg_info *seg, enum ice_flow_field fld,
		 u16 val_loc, u16 mask_loc, u16 last_loc, bool range);
void
ice_flow_set_fld_prefix(struct ice_flow_seg_info *seg, enum ice_flow_field fld,
			u16 val_loc, u16 prefix_loc, u8 prefix_sz);
void
ice_flow_add_fld_raw(struct ice_flow_seg_info *seg, u16 off, u8 len,
		     u16 val_loc, u16 mask_loc);
void ice_rem_all_rss_vsi_ctx(struct ice_hw *hw, u16 vsi_handle);
enum ice_status ice_replay_rss_cfg(struct ice_hw *hw, u16 vsi_handle);
enum ice_status
ice_add_avf_rss_cfg(struct ice_hw *hw, u16 vsi_handle, u64 hashed_flds);
enum ice_status ice_rem_vsi_rss_cfg(struct ice_hw *hw, u16 vsi_handle);
enum ice_status
ice_add_rss_cfg(struct ice_hw *hw, u16 vsi_handle, u64 hashed_flds,
		u32 addl_hdrs);
enum ice_status
ice_rem_rss_cfg(struct ice_hw *hw, u16 vsi_handle, u64 hashed_flds,
		u32 addl_hdrs);
u64 ice_get_rss_cfg(struct ice_hw *hw, u16 vsi_handle, u32 hdrs);
#endif /* _ICE_FLOW_H_ */
