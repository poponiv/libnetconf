/**
 * \file ssh.h
 * \author Radek Krejci <rkrejci@cesnet.cz>
 * \brief Functions to connect to NETCONF server via SSH2.
 *
 * Copyright (C) 2012 CESNET, z.s.p.o.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of the Company nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * ALTERNATIVELY, provided that this notice is retained in full, this
 * product may be distributed under the terms of the GNU General Public
 * License (GPL) version 2 or later, in which case the provisions
 * of the GPL apply INSTEAD OF those given above.
 *
 * This software is provided ``as is, and any express or implied
 * warranties, including, but not limited to, the implied warranties of
 * merchantability and fitness for a particular purpose are disclaimed.
 * In no event shall the company or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 *
 */

#ifndef SSH_H_
#define SSH_H_

#include "netconf.h"

/**
 * @brief Available SSH authentication mechanisms.
 * @ingroup session
 */
typedef enum
{
	NC_SSH_AUTH_PUBLIC_KEYS = 1, /**< SSH user authorization via publickeys */
	NC_SSH_AUTH_PASSWORD = 2,   /**< SSH user authorization via password */
	NC_SSH_AUTH_INTERACTIVE = 4 /**< interactive SSH user authorization */
} NC_SSH_AUTH_TYPE;

/**
 * @ingroup session
 * @brief Set preference of the SSH authentication methods.
 *
 * Allowed authentication types are defined as NC_SSH_AUTH_TYPE type.
 * Default preferences are:
 * 1. interactive (3)
 * 2. password (2)
 * 3. public keys (1)
 *
 * @param[in] type Setting preference for the given authentication type.
 * @param[in] preference Preference value. Higher value means higher preference.
 * Negative value disables the given authentication type. On equality of values,
 * the last set authentication type is preferred.
 */
void nc_ssh_pref(NC_SSH_AUTH_TYPE type, short int preference);

/**
 * @ingroup session
 * @brief Create NETCONF session to the specified server.
 *
 * This function internally can use various callbacks set by client to perform
 * SSH authentication. It selects authentication mechanism from the list
 * provided by the SSH server and according to preferences set by client via
 * nc_ssh_pref(). Then, appropriate callback function (set by
 * nc_callback_sshauth_password(), nc_callback_sshauth_passphrase(),
 * nc_set_publickey_path() or nc_set_privatekey_path()) is used to perform
 * authentication.
 *
 * @param[in] host Hostname or address (both Ipv4 and IPv6 are accepted). 'localhost'
 * is used by default if NULL is specified.
 * @param[in] port Port number of the server. Default value 830 is used if 0 is
 * specified.
 * @param[in] username Name of the user to login to the server. The user running the
 * application (detected from the effective UID) is used if NULL is specified.
 * @param[in] cpblts NETCONF capabilities structure with capabilities supported
 * by the client. Client can use nc_session_get_cpblts_default() to get the
 * structure with the list of all capabilities supported by libnetconf (this is
 * used in case of NULL parameter).
 * @return Structure describing the NETCONF session or NULL in case of error.
 */
struct nc_session *nc_session_connect(const char *host, unsigned short port, const char *username, struct nc_cpblts* cpblts);

#endif /* SSH_H_ */
