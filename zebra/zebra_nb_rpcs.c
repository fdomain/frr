/*
 * Copyright (C) 2020 Cumulus Networks, Inc.
 *                    Chirag Shah
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; see the file COPYING; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <zebra.h>
#include "northbound.h"
#include "libfrr.h"

#include "zebra/zebra_nb.h"
#include "zebra/zebra_router.h"
#include "zebra/zebra_vrf.h"
#include "zebra/zebra_vxlan.h"

/*
 * XPath: /frr-zebra:clear-evpn-dup-addr
 */
int clear_evpn_dup_addr_rpc(const char *xpath, const struct list *input,
			    struct list *output)
{
	struct zebra_vrf *zvrf;
	int ret = NB_OK;
	struct yang_data *yang_dup_choice = NULL, *yang_dup_vni = NULL,
			 *yang_dup_ip = NULL, *yang_dup_mac = NULL;

	yang_dup_choice = yang_data_list_find(input, "%s/%s", xpath,
					      "input/clear-dup-choice");

	zvrf = zebra_vrf_get_evpn();

	if (yang_dup_choice
	    && strcmp(yang_dup_choice->value, "all-case") == 0) {
		zebra_vxlan_clear_dup_detect_vni_all(NULL, zvrf);
	} else {
		vni_t vni;
		struct ipaddr host_ip = {.ipa_type = IPADDR_NONE};
		struct ethaddr mac;

		yang_dup_vni = yang_data_list_find(
			input, "%s/%s", xpath,
			"input/clear-dup-choice/single-case/vni-id");
		if (yang_dup_vni) {
			vni = yang_str2uint32(yang_dup_vni->value);

			yang_dup_mac = yang_data_list_find(
				input, "%s/%s", xpath,
				"input/clear-dup-choice/single-case/vni-id/mac-addr");
			yang_dup_ip = yang_data_list_find(
				input, "%s/%s", xpath,
				"input/clear-dup-choice/single-case/vni-id/vni-ipaddr");

			if (yang_dup_mac) {
				yang_str2mac(value, &mac);
				ret = zebra_vxlan_clear_dup_detect_vni_mac(
					zvrf, vni, &mac);
			} else if (yang_dup_ip) {
				yang_str2ip(yang_dup_ip->value, &host_ip);
				ret = zebra_vxlan_clear_dup_detect_vni_ip(
					zvrf, vni, &host_ip);
			} else
				ret = zebra_vxlan_clear_dup_detect_vni(zvrf,
								       vni);
		}
	}
	ret = (ret != CMD_SUCCESS) ? NB_ERR : NB_OK;

	return ret;
}

/*
 * XPath: /frr-zebra:get-route-information
 */
int get_route_information_rpc(const char *xpath, const struct list *input,
			      struct list *output)
{
	/* TODO: implement me. */
	return NB_ERR_NOT_FOUND;
}

/*
 * XPath: /frr-zebra:get-v6-mroute-info
 */
int get_v6_mroute_info_rpc(const char *xpath, const struct list *input,
			   struct list *output)
{
	/* TODO: implement me. */
	return NB_ERR_NOT_FOUND;
}

/*
 * XPath: /frr-zebra:get-vrf-info
 */
int get_vrf_info_rpc(const char *xpath, const struct list *input,
		     struct list *output)
{
	/* TODO: implement me. */
	return NB_ERR_NOT_FOUND;
}

/*
 * XPath: /frr-zebra:get-vrf-vni-info
 */
int get_vrf_vni_info_rpc(const char *xpath, const struct list *input,
			 struct list *output)
{
	/* TODO: implement me. */
	return NB_ERR_NOT_FOUND;
}

/*
 * XPath: /frr-zebra:get-evpn-info
 */
int get_evpn_info_rpc(const char *xpath, const struct list *input,
		      struct list *output)
{
	/* TODO: implement me. */
	return NB_ERR_NOT_FOUND;
}

/*
 * XPath: /frr-zebra:get-vni-info
 */
int get_vni_info_rpc(const char *xpath, const struct list *input,
		     struct list *output)
{
	/* TODO: implement me. */
	return NB_ERR_NOT_FOUND;
}

/*
 * XPath: /frr-zebra:get-evpn-vni-rmac
 */
int get_evpn_vni_rmac_rpc(const char *xpath, const struct list *input,
			  struct list *output)
{
	/* TODO: implement me. */
	return NB_ERR_NOT_FOUND;
}

/*
 * XPath: /frr-zebra:get-evpn-vni-nexthops
 */
int get_evpn_vni_nexthops_rpc(const char *xpath, const struct list *input,
			      struct list *output)
{
	/* TODO: implement me. */
	return NB_ERR_NOT_FOUND;
}

/*
 * XPath: /frr-zebra:get-evpn-macs
 */
int get_evpn_macs_rpc(const char *xpath, const struct list *input,
		      struct list *output)
{
	/* TODO: implement me. */
	return NB_ERR_NOT_FOUND;
}

/*
 * XPath: /frr-zebra:get-evpn-arp-cache
 */
int get_evpn_arp_cache_rpc(const char *xpath, const struct list *input,
			   struct list *output)
{
	/* TODO: implement me. */
	return NB_ERR_NOT_FOUND;
}

/*
 * XPath: /frr-zebra:get-pbr-ipset
 */
int get_pbr_ipset_rpc(const char *xpath, const struct list *input,
		      struct list *output)
{
	/* TODO: implement me. */
	return NB_ERR_NOT_FOUND;
}

/*
 * XPath: /frr-zebra:get-pbr-iptable
 */
int get_pbr_iptable_rpc(const char *xpath, const struct list *input,
			struct list *output)
{
	/* TODO: implement me. */
	return NB_ERR_NOT_FOUND;
}

/*
 * XPath: /frr-zebra:get-debugs
 */
int get_debugs_rpc(const char *xpath, const struct list *input,
		   struct list *output)
{
	/* TODO: implement me. */
	return NB_ERR_NOT_FOUND;
}
