/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details:
 *
 * Copyright (C) 2011-2012 Google, Inc.
 */

#ifndef MM_IFACE_MODEM_3GPP_H
#define MM_IFACE_MODEM_3GPP_H

#include <glib-object.h>
#include <gio/gio.h>
#define _LIBMM_INSIDE_MM
#include <libmm-glib.h>

#include "mm-port-serial-at.h"

#define MM_TYPE_IFACE_MODEM_3GPP               (mm_iface_modem_3gpp_get_type ())
#define MM_IFACE_MODEM_3GPP(obj)               (G_TYPE_CHECK_INSTANCE_CAST ((obj), MM_TYPE_IFACE_MODEM_3GPP, MMIfaceModem3gpp))
#define MM_IS_IFACE_MODEM_3GPP(obj)            (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MM_TYPE_IFACE_MODEM_3GPP))
#define MM_IFACE_MODEM_3GPP_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), MM_TYPE_IFACE_MODEM_3GPP, MMIfaceModem3gpp))

#define MM_IFACE_MODEM_3GPP_DBUS_SKELETON           "iface-modem-3gpp-dbus-skeleton"
#define MM_IFACE_MODEM_3GPP_REGISTRATION_STATE      "iface-modem-3gpp-registration-state"
#define MM_IFACE_MODEM_3GPP_CS_NETWORK_SUPPORTED    "iface-modem-3gpp-cs-network-supported"
#define MM_IFACE_MODEM_3GPP_PS_NETWORK_SUPPORTED    "iface-modem-3gpp-ps-network-supported"
#define MM_IFACE_MODEM_3GPP_EPS_NETWORK_SUPPORTED   "iface-modem-3gpp-eps-network-supported"
#define MM_IFACE_MODEM_3GPP_IGNORED_FACILITY_LOCKS  "iface-modem-3gpp-ignored-facility-locks"

#define MM_IFACE_MODEM_3GPP_ALL_ACCESS_TECHNOLOGIES_MASK    \
    (MM_MODEM_ACCESS_TECHNOLOGY_GSM |                       \
     MM_MODEM_ACCESS_TECHNOLOGY_GSM_COMPACT |               \
     MM_MODEM_ACCESS_TECHNOLOGY_GPRS |                      \
     MM_MODEM_ACCESS_TECHNOLOGY_EDGE |                      \
     MM_MODEM_ACCESS_TECHNOLOGY_UMTS |                      \
     MM_MODEM_ACCESS_TECHNOLOGY_HSDPA |                     \
     MM_MODEM_ACCESS_TECHNOLOGY_HSUPA |                     \
     MM_MODEM_ACCESS_TECHNOLOGY_HSPA |                      \
     MM_MODEM_ACCESS_TECHNOLOGY_HSPA_PLUS |                 \
     MM_MODEM_ACCESS_TECHNOLOGY_LTE)

typedef struct _MMIfaceModem3gpp MMIfaceModem3gpp;

struct _MMIfaceModem3gpp {
    GTypeInterface g_iface;

    /* Loading of the IMEI property */
    void (*load_imei) (MMIfaceModem3gpp *self,
                       GAsyncReadyCallback callback,
                       gpointer user_data);
    gchar * (*load_imei_finish) (MMIfaceModem3gpp *self,
                                 GAsyncResult *res,
                                 GError **error);

    /* Loading of the facility locks property */
    void (*load_enabled_facility_locks) (MMIfaceModem3gpp *self,
                                         GAsyncReadyCallback callback,
                                         gpointer user_data);
    MMModem3gppFacility (*load_enabled_facility_locks_finish) (MMIfaceModem3gpp *self,
                                                               GAsyncResult *res,
                                                               GError **error);

    /* Loading of the UE mode of operation for EPS property */
    void                          (* load_eps_ue_mode_operation)        (MMIfaceModem3gpp     *self,
                                                                         GAsyncReadyCallback   callback,
                                                                         gpointer              user_data);
    MMModem3gppEpsUeModeOperation (* load_eps_ue_mode_operation_finish) (MMIfaceModem3gpp     *self,
                                                                         GAsyncResult         *res,
                                                                         GError              **error);

    /* Asynchronous setting up unsolicited events */
    void (*setup_unsolicited_events) (MMIfaceModem3gpp *self,
                                      GAsyncReadyCallback callback,
                                      gpointer user_data);
    gboolean (*setup_unsolicited_events_finish) (MMIfaceModem3gpp *self,
                                                 GAsyncResult *res,
                                                 GError **error);

    /* Asynchronous enabling of unsolicited events */
    void (*enable_unsolicited_events) (MMIfaceModem3gpp *self,
                                       GAsyncReadyCallback callback,
                                       gpointer user_data);
    gboolean (*enable_unsolicited_events_finish) (MMIfaceModem3gpp *self,
                                                  GAsyncResult *res,
                                                  GError **error);

    /* Asynchronous cleaning up of unsolicited events */
    void (*cleanup_unsolicited_events) (MMIfaceModem3gpp *self,
                                        GAsyncReadyCallback callback,
                                        gpointer user_data);
    gboolean (*cleanup_unsolicited_events_finish) (MMIfaceModem3gpp *self,
                                                   GAsyncResult *res,
                                                   GError **error);

    /* Asynchronous disabling of unsolicited events */
    void (*disable_unsolicited_events) (MMIfaceModem3gpp *self,
                                        GAsyncReadyCallback callback,
                                        gpointer user_data);
    gboolean (*disable_unsolicited_events_finish) (MMIfaceModem3gpp *self,
                                                   GAsyncResult *res,
                                                   GError **error);

    /* Setup unsolicited registration messages */
    void (* setup_unsolicited_registration_events) (MMIfaceModem3gpp *self,
                                                    GAsyncReadyCallback callback,
                                                    gpointer user_data);
    gboolean (*setup_unsolicited_registration_events_finish) (MMIfaceModem3gpp *self,
                                                              GAsyncResult *res,
                                                              GError **error);

    /* Asynchronous enabling of unsolicited registration events */
    void (*enable_unsolicited_registration_events) (MMIfaceModem3gpp *self,
                                                    gboolean cs_supported,
                                                    gboolean ps_supported,
                                                    gboolean eps_supported,
                                                    GAsyncReadyCallback callback,
                                                    gpointer user_data);
    gboolean (*enable_unsolicited_registration_events_finish) (MMIfaceModem3gpp *self,
                                                               GAsyncResult *res,
                                                               GError **error);

    /* Cleanup unsolicited registration messages */
    void (* cleanup_unsolicited_registration_events) (MMIfaceModem3gpp *self,
                                                      GAsyncReadyCallback callback,
                                                      gpointer user_data);
    gboolean (*cleanup_unsolicited_registration_events_finish) (MMIfaceModem3gpp *self,
                                                                GAsyncResult *res,
                                                                GError **error);
    /* Asynchronous disabling of unsolicited registration events */
    void (*disable_unsolicited_registration_events) (MMIfaceModem3gpp *self,
                                                     gboolean cs_supported,
                                                     gboolean ps_supported,
                                                     gboolean eps_supported,
                                                     GAsyncReadyCallback callback,
                                                     gpointer user_data);
    gboolean (*disable_unsolicited_registration_events_finish) (MMIfaceModem3gpp *self,
                                                                GAsyncResult *res,
                                                                GError **error);

    /* Run CS/PS/EPS registration state checks..
     * Note that no registration state is returned, implementations should call
     * mm_iface_modem_3gpp_update_registration_state(). */
    void (* run_registration_checks) (MMIfaceModem3gpp *self,
                                      gboolean cs_supported,
                                      gboolean ps_supported,
                                      gboolean eps_supported,
                                      GAsyncReadyCallback callback,
                                      gpointer user_data);
    gboolean (*run_registration_checks_finish) (MMIfaceModem3gpp *self,
                                                GAsyncResult *res,
                                                GError **error);

    /* Try to register in the network */
    void (* register_in_network) (MMIfaceModem3gpp *self,
                                  const gchar *operator_id,
                                  GCancellable *cancellable,
                                  GAsyncReadyCallback callback,
                                  gpointer user_data);
    gboolean (*register_in_network_finish) (MMIfaceModem3gpp *self,
                                            GAsyncResult *res,
                                            GError **error);

    /* Loading of the Operator Code property */
    void (*load_operator_code) (MMIfaceModem3gpp *self,
                                GAsyncReadyCallback callback,
                                gpointer user_data);
    gchar * (*load_operator_code_finish) (MMIfaceModem3gpp *self,
                                          GAsyncResult *res,
                                          GError **error);

    /* Loading of the Operator Name property */
    void (*load_operator_name) (MMIfaceModem3gpp *self,
                                GAsyncReadyCallback callback,
                                gpointer user_data);
    gchar * (*load_operator_name_finish) (MMIfaceModem3gpp *self,
                                          GAsyncResult *res,
                                          GError **error);

    /* Loading of the subscription state property */
    void (*load_subscription_state) (MMIfaceModem3gpp *self,
                                     GAsyncReadyCallback callback,
                                     gpointer user_data);
    MMModem3gppSubscriptionState (*load_subscription_state_finish) (MMIfaceModem3gpp *self,
                                                                    GAsyncResult *res,
                                                                    GError **error);

    /* Scan current networks, expect a GList of MMModem3gppNetworkInfo */
    void (* scan_networks) (MMIfaceModem3gpp *self,
                            GAsyncReadyCallback callback,
                            gpointer user_data);
    GList * (*scan_networks_finish) (MMIfaceModem3gpp *self,
                                     GAsyncResult *res,
                                     GError **error);

    /* Set UE mode of operation for EPS */
    void     (* set_eps_ue_mode_operation)        (MMIfaceModem3gpp               *self,
                                                   MMModem3gppEpsUeModeOperation   mode,
                                                   GAsyncReadyCallback             callback,
                                                   gpointer                        user_data);
    gboolean (* set_eps_ue_mode_operation_finish) (MMIfaceModem3gpp               *self,
                                                   GAsyncResult                   *res,
                                                   GError                        **error);
};

GType mm_iface_modem_3gpp_get_type (void);

/* Initialize Modem 3GPP interface (async) */
void     mm_iface_modem_3gpp_initialize        (MMIfaceModem3gpp *self,
                                                GCancellable *cancellable,
                                                GAsyncReadyCallback callback,
                                                gpointer user_data);
gboolean mm_iface_modem_3gpp_initialize_finish (MMIfaceModem3gpp *self,
                                                GAsyncResult *res,
                                                GError **error);

/* Enable Modem interface (async) */
void     mm_iface_modem_3gpp_enable        (MMIfaceModem3gpp *self,
                                            GCancellable *cancellable,
                                            GAsyncReadyCallback callback,
                                            gpointer user_data);
gboolean mm_iface_modem_3gpp_enable_finish (MMIfaceModem3gpp *self,
                                            GAsyncResult *res,
                                            GError **error);

/* Disable Modem interface (async) */
void     mm_iface_modem_3gpp_disable        (MMIfaceModem3gpp *self,
                                             GAsyncReadyCallback callback,
                                             gpointer user_data);
gboolean mm_iface_modem_3gpp_disable_finish (MMIfaceModem3gpp *self,
                                             GAsyncResult *res,
                                             GError **error);

/* Shutdown Modem 3GPP interface */
void mm_iface_modem_3gpp_shutdown (MMIfaceModem3gpp *self);

/* Objects implementing this interface can report new registration info,
 * access technologies and location.
 * This may happen when handling unsolicited registration messages, or when
 * the interface asks to run registration state checks. */
void mm_iface_modem_3gpp_update_cs_registration_state (MMIfaceModem3gpp *self,
                                                       MMModem3gppRegistrationState state);
void mm_iface_modem_3gpp_update_ps_registration_state (MMIfaceModem3gpp *self,
                                                       MMModem3gppRegistrationState state);
void mm_iface_modem_3gpp_update_eps_registration_state (MMIfaceModem3gpp *self,
                                                        MMModem3gppRegistrationState state);
void mm_iface_modem_3gpp_update_subscription_state (MMIfaceModem3gpp *self,
                                                    MMModem3gppSubscriptionState state);
void mm_iface_modem_3gpp_update_access_technologies (MMIfaceModem3gpp *self,
                                                     MMModemAccessTechnology access_tech);
void mm_iface_modem_3gpp_update_location            (MMIfaceModem3gpp *self,
                                                     gulong location_area_code,
                                                     gulong cell_id);

/* Run all registration checks */
void mm_iface_modem_3gpp_run_registration_checks (MMIfaceModem3gpp *self,
                                                  GAsyncReadyCallback callback,
                                                  gpointer user_data);
gboolean mm_iface_modem_3gpp_run_registration_checks_finish (MMIfaceModem3gpp *self,
                                                             GAsyncResult *res,
                                                             GError **error);

/* Request to reload current registration information */
void     mm_iface_modem_3gpp_reload_current_registration_info        (MMIfaceModem3gpp *self,
                                                                      GAsyncReadyCallback callback,
                                                                      gpointer user_data);
gboolean mm_iface_modem_3gpp_reload_current_registration_info_finish (MMIfaceModem3gpp *self,
                                                                      GAsyncResult *res,
                                                                      GError **error);
void     mm_iface_modem_3gpp_clear_current_operator                  (MMIfaceModem3gpp *self);

/* Allow registering in the network */
gboolean mm_iface_modem_3gpp_register_in_network_finish (MMIfaceModem3gpp *self,
                                                         GAsyncResult *res,
                                                         GError **error);
void     mm_iface_modem_3gpp_register_in_network        (MMIfaceModem3gpp *self,
                                                         const gchar *operator_id,
                                                         guint max_registration_time,
                                                         GAsyncReadyCallback callback,
                                                         gpointer user_data);

/* Bind properties for simple GetStatus() */
void mm_iface_modem_3gpp_bind_simple_status (MMIfaceModem3gpp *self,
                                             MMSimpleStatus *status);

#endif /* MM_IFACE_MODEM_3GPP_H */
