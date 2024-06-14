/**********Includes**********/
#include "esp_log.h"

#include "ble_pult_task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*BLE*/

#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "host/ble_hs.h"
#include "host/util/util.h"
#include "console/console.h"
#include "services/gap/ble_svc_gap.h"
#include "blecent.h"

#include "settings.h"

/**********Extern**********/
//extern QueueHandle_t tx_task_queue;
/**********LOG**********/

static const char* tag = "BLE_PULT_TASK";

/**********Functions declaration**********/
static void ble_pult_task(void* arg);

void ble_store_config_init(void);
static int blecent_gap_event(struct ble_gap_event* event, void* arg);

/**********Task**********/

/**********Settings**********/

/*** The UUID of the service containing the subscribable characterstic ***/
static const ble_uuid_t* remote_svc_uuid = BLE_UUID16_DECLARE(0x180d);

/*** The UUID of the subscribable chatacteristic ***/
static const ble_uuid_t* remote_chr_uuid = BLE_UUID16_DECLARE(0x2a37);

/**********Functions definition**********/

/**
 * Application Callback. Called when the custom subscribable chatacteristic
 * in the remote GATT server is read.
 * Expect to get the recently written data.
 **/
static int blecent_on_custom_read(
    uint16_t conn_handle,
    const struct ble_gatt_error* error,
    struct ble_gatt_attr* attr,
    void* arg) {
    MODLOG_DFLT(
        INFO,
        "Read complete for the subscribable characteristic; "
        "status=%d conn_handle=%d",
        error->status,
        conn_handle);
    if(error->status == 0) {
        MODLOG_DFLT(INFO, " attr_handle=%d value=", attr->handle);
        print_mbuf(attr->om);
    }
    MODLOG_DFLT(INFO, "\n");

    return 0;
}

/**
 * Application Callback. Called when the custom subscribable characteristic
 * in the remote GATT server is written to.
 * Client has previously subscribed to this characeteristic,
 * so expect a notification from the server.
 **/
static int blecent_on_custom_write(
    uint16_t conn_handle,
    const struct ble_gatt_error* error,
    struct ble_gatt_attr* attr,
    void* arg) {
    const struct peer_chr* chr;
    const struct peer* peer;
    int rc;

    MODLOG_DFLT(
        INFO,
        "Write to the custom subscribable characteristic complete; "
        "status=%d conn_handle=%d attr_handle=%d\n",
        error->status,
        conn_handle,
        attr->handle);

    peer = peer_find(conn_handle);
    chr = peer_chr_find_uuid(peer, remote_svc_uuid, remote_chr_uuid);
    if(chr == NULL) {
        MODLOG_DFLT(
            ERROR,
            "Error: Peer doesn't have the custom subscribable characteristic\n");
        goto err;
    }

    /*** Performs a read on the characteristic, the result is handled in blecent_on_new_read callback ***/
    rc = ble_gattc_read(
        conn_handle, chr->chr.val_handle, blecent_on_custom_read, NULL);
    if(rc != 0) {
        MODLOG_DFLT(
            ERROR,
            "Error: Failed to read the custom subscribable characteristic; "
            "rc=%d\n",
            rc);
        goto err;
    }

    return 0;
err:
    /* Terminate the connection */
    return ble_gap_terminate(peer->conn_handle, BLE_ERR_REM_USER_CONN_TERM);
}

/**
 * Application Callback. Called when the custom subscribable characteristic
 * is subscribed to.
 **/
static int blecent_on_custom_subscribe(
    uint16_t conn_handle,
    const struct ble_gatt_error* error,
    struct ble_gatt_attr* attr,
    void* arg) {
    const struct peer_chr* chr;
    uint8_t value;
    int rc;
    const struct peer* peer;

    MODLOG_DFLT(
        INFO,
        "Subscribe to the custom subscribable characteristic complete; "
        "status=%d conn_handle=%d",
        error->status,
        conn_handle);

    if(error->status == 0) {
        MODLOG_DFLT(INFO, " attr_handle=%d value=", attr->handle);
        print_mbuf(attr->om);
    }
    MODLOG_DFLT(INFO, "\n");

    peer = peer_find(conn_handle);
    chr = peer_chr_find_uuid(peer, remote_svc_uuid, remote_chr_uuid);
    if(chr == NULL) {
        MODLOG_DFLT(
            ERROR,
            "Error: Peer doesn't have the subscribable characteristic\n");
        goto err;
    }

    /* Write 1 byte to the new characteristic to test if it notifies after subscribing */
    value = 0x19;
    rc = ble_gattc_write_flat(
        conn_handle,
        chr->chr.val_handle,
        &value,
        sizeof(value),
        blecent_on_custom_write,
        NULL);
    if(rc != 0) {
        MODLOG_DFLT(
            ERROR,
            "Error: Failed to write to the subscribable characteristic; "
            "rc=%d\n",
            rc);
        goto err;
    }

    return 0;
err:
    /* Terminate the connection */
    return ble_gap_terminate(peer->conn_handle, BLE_ERR_REM_USER_CONN_TERM);
}

/**
 * Performs 3 operations on the remote GATT server.
 * 1. Subscribes to a characteristic by writing 0x10 to it's CCCD.
 * 2. Writes to the characteristic and expect a notification from remote.
 * 3. Reads the characteristic and expect to get the recently written information.
 **/
static void blecent_custom_gatt_operations(const struct peer* peer) {
    const struct peer_dsc* dsc;
    int rc;
    uint8_t value[2];

    dsc = peer_dsc_find_uuid(
        peer,
        remote_svc_uuid,
        remote_chr_uuid,
        BLE_UUID16_DECLARE(BLE_GATT_DSC_CLT_CFG_UUID16));
    if(dsc == NULL) {
        MODLOG_DFLT(
            ERROR,
            "Error: Peer lacks a CCCD for the subscribable characterstic\n");
        goto err;
    }

    /*** Write 0x00 and 0x01 (The subscription code) to the CCCD ***/
    value[0] = 1;
    value[1] = 0;
    rc = ble_gattc_write_flat(
        peer->conn_handle,
        dsc->dsc.handle,
        value,
        sizeof(value),
        blecent_on_custom_subscribe,
        NULL);
    if(rc != 0) {
        MODLOG_DFLT(
            ERROR,
            "Error: Failed to subscribe to the subscribable characteristic; "
            "rc=%d\n",
            rc);
        goto err;
    }

    return;
err:
    /* Terminate the connection */
    ble_gap_terminate(peer->conn_handle, BLE_ERR_REM_USER_CONN_TERM);
}

/**
 * Application callback.  Called when the attempt to subscribe to notifications
 * for the ANS Unread Alert Status characteristic has completed.
 */
static int blecent_on_subscribe(
    uint16_t conn_handle,
    const struct ble_gatt_error* error,
    struct ble_gatt_attr* attr,
    void* arg) {
    struct peer* peer;

    MODLOG_DFLT(
        INFO,
        "Subscribe complete; status=%d conn_handle=%d "
        "attr_handle=%d\n",
        error->status,
        conn_handle,
        attr->handle);

    peer = peer_find(conn_handle);
    if(peer == NULL) {
        MODLOG_DFLT(ERROR, "Error in finding peer, aborting...");
        ble_gap_terminate(conn_handle, BLE_ERR_REM_USER_CONN_TERM);
    }
    /* Subscribe to, write to, and read the custom characteristic*/
    blecent_custom_gatt_operations(peer);

    return 0;
}

/**
 * Application callback.  Called when the read of the ANS Supported New Alert
 * Category characteristic has completed.
 */
static int blecent_on_read(
    uint16_t conn_handle,
    const struct ble_gatt_error* error,
    struct ble_gatt_attr* attr,
    void* arg) {
    MODLOG_DFLT(
        INFO,
        "Read complete; status=%d conn_handle=%d",
        error->status,
        conn_handle);
    if(error->status == 0) {
        MODLOG_DFLT(INFO, " attr_handle=%d value=", attr->handle);
        print_mbuf(attr->om);
    }
    MODLOG_DFLT(INFO, "\n");

    /* Write two bytes (99, 100) to the alert-notification-control-point
     * characteristic.
     */
    const struct peer_chr* chr;
    uint8_t value[2];
    int rc;
    const struct peer* peer = peer_find(conn_handle);
    const struct peer_dsc* dsc;
    dsc = peer_dsc_find_uuid(
        peer,
        BLE_UUID16_DECLARE(0x180d),
        BLE_UUID16_DECLARE(0x2a37),
        BLE_UUID16_DECLARE(BLE_GATT_DSC_CLT_CFG_UUID16));
    if(dsc == NULL) {
        MODLOG_DFLT(
            ERROR,
            "Error: Peer lacks a CCCD for the Unread Alert "
            "Status characteristic\n");
        goto err;
    }

    value[0] = 1;
    value[1] = 0;
    rc = ble_gattc_write_flat(
        conn_handle,
        dsc->dsc.handle,
        value,
        sizeof value,
        blecent_on_subscribe,
        NULL);
    if(rc != 0) {
        MODLOG_DFLT(
            ERROR,
            "Error: Failed to subscribe to characteristic; "
            "rc=%d\n",
            rc);
        goto err;
    }

    return 0;
err:
    /* Terminate the connection. */
    return ble_gap_terminate(peer->conn_handle, BLE_ERR_REM_USER_CONN_TERM);
}

/**
 * Performs three GATT operations against the specified peer:
 * 1. Reads the ANS Supported New Alert Category characteristic.
 * 2. After read is completed, writes the ANS Alert Notification Control Point characteristic.
 * 3. After write is completed, subscribes to notifications for the ANS Unread Alert Status
 *    characteristic.
 *
 * If the peer does not support a required service, characteristic, or
 * descriptor, then the peer lied when it claimed support for the alert
 * notification service!  When this happens, or if a GATT procedure fails,
 * this function immediately terminates the connection.
 */
static void blecent_read_write_subscribe(const struct peer* peer) {
    const struct peer_chr* chr;
    int rc;

    /* Read the supported-new-alert-category characteristic. */
    chr = peer_chr_find_uuid(
        peer, BLE_UUID16_DECLARE(0x180d), BLE_UUID16_DECLARE(0x2A37));
    if(chr == NULL) {
        MODLOG_DFLT(
            ERROR,
            "Error: Peer doesn't support the Supported New "
            "Alert Category characteristic\n");
        goto err;
    }

    rc = ble_gattc_read(
        peer->conn_handle, chr->chr.val_handle, blecent_on_read, NULL);
    if(rc != 0) {
        MODLOG_DFLT(ERROR, "Error: Failed to read characteristic; rc=%d\n", rc);
        goto err;
    }

    return;
err:
    /* Terminate the connection. */
    ble_gap_terminate(peer->conn_handle, BLE_ERR_REM_USER_CONN_TERM);
}

/**
 * Called when service discovery of the specified peer has completed.
 */
static void
    blecent_on_disc_complete(const struct peer* peer, int status, void* arg) {
    if(status != 0) {
        /* Service discovery failed.  Terminate the connection. */
        MODLOG_DFLT(
            ERROR,
            "Error: Service discovery failed; status=%d "
            "conn_handle=%d\n",
            status,
            peer->conn_handle);
        ble_gap_terminate(peer->conn_handle, BLE_ERR_REM_USER_CONN_TERM);
        return;
    }

    /* Service discovery has completed successfully.  Now we have a complete
     * list of services, characteristics, and descriptors that the peer
     * supports.
     */
    MODLOG_DFLT(
        INFO,
        "Service discovery complete; status=%d "
        "conn_handle=%d\n",
        status,
        peer->conn_handle);

    /* Now perform three GATT procedures against the peer: read,
     * write, and subscribe to notifications for the ANS service.
     */
    blecent_read_write_subscribe(peer);
}

/**
 * Initiates the GAP general discovery procedure.
 */
static void blecent_scan(void) {
    uint8_t own_addr_type;
    struct ble_gap_disc_params disc_params;
    int rc;

    /* Figure out address to use while advertising (no privacy for now) */
    rc = ble_hs_id_infer_auto(0, &own_addr_type);
    if(rc != 0) {
        MODLOG_DFLT(ERROR, "error determining address type; rc=%d\n", rc);
        return;
    }

    /* Tell the controller to filter duplicates; we don't want to process
     * repeated advertisements from the same device.
     */
    disc_params.filter_duplicates = 0;

    /**
     * Perform a passive scan.  I.e., don't send follow-up scan requests to
     * each advertiser.
     */
    disc_params.passive = 0;

    /* Use defaults for the rest of the parameters. */
    disc_params.itvl = 0;
    disc_params.window = 0;
    disc_params.filter_policy = 0;
    disc_params.limited = 0;

    rc = ble_gap_disc(
        own_addr_type, BLE_HS_FOREVER, &disc_params, blecent_gap_event, NULL);
    if(rc != 0) {
        MODLOG_DFLT(
            ERROR, "Error initiating GAP discovery procedure; rc=%d\n", rc);
    }
}

int32_t old_cnt = -1;

uint8_t to_bind = 0;

void ble_pult_bind(void) {
    to_bind = 1;
}

uint8_t is_mac_correct(const uint8_t* data) {
    if(memcmp(settings_get_btn_mac(), data, 6) == 0) {
        return 1;
    } else {
        return 0;
    }
}

static int blecent_should_connect(const struct ble_gap_disc_desc* disc) {
    struct ble_hs_adv_fields fields;
    int rc;
    int i;

    rc = ble_hs_adv_parse_fields(&fields, disc->data, disc->length_data);
    if(rc != 0) {
        return 0;
    }

    char name[32] = {0};
    if(fields.name_len > 0 && fields.mfg_data_len > 0 &&
       strncmp((char*)fields.name, "test", 4) == 0) {
        memcpy(name, fields.name, fields.name_len);

        MODLOG_DFLT(
            INFO,
            "MAC %x %x %x %x %x %x %d",
            disc->addr.val[0],
            disc->addr.val[1],
            disc->addr.val[2],
            disc->addr.val[3],
            disc->addr.val[4],
            disc->addr.val[5],
            disc->rssi);
        uint8_t cnt = fields.mfg_data[2];
        int16_t val = (fields.mfg_data[3] << 8) | fields.mfg_data[4];
        uint16_t msg = 0;

        if(is_mac_correct(disc->addr.val)) {
            if(old_cnt != cnt || val == 0xFFFF) {
                MODLOG_DFLT(INFO, "val %d", val);
                old_cnt = cnt;
                if(val < 100) {
                    val = 100;
                }
                msg = val;
                //xQueueSend(tx_task_queue, &msg, portMAX_DELAY);
            } else {
                //MODLOG_DFLT(INFO, "cnt %d", cnt);
            }
            //}
        } else {
            MODLOG_DFLT(INFO, "wrong dev");
        }
        if(to_bind == 1 && val > 4000) {
            settings_save_ble_btn(disc->addr.val);
            to_bind = 0;
        }
    }
    return 0;
}

/**
 * Connects to the sender of the specified advertisement of it looks
 * interesting.  A device is "interesting" if it advertises connectability and
 * support for the Alert Notification service.
 */
static void blecent_connect_if_interesting(void* disc) {
    uint8_t own_addr_type;
    int rc;
    ble_addr_t* addr;

    if(!blecent_should_connect((struct ble_gap_disc_desc*)disc)) {
        return;
    }
}

/**
 * The nimble host executes this callback when a GAP event occurs.  The
 * application associates a GAP event callback with each connection that is
 * established.  blecent uses the same callback for all connections.
 *
 * @param event                 The event being signalled.
 * @param arg                   Application-specified argument; unused by
 *                                  blecent.
 *
 * @return                      0 if the application successfully handled the
 *                                  event; nonzero on failure.  The semantics
 *                                  of the return code is specific to the
 *                                  particular GAP event being signalled.
 */
static int blecent_gap_event(struct ble_gap_event* event, void* arg) {
    uint16_t val = 0;
    struct ble_gap_conn_desc desc;
    struct ble_hs_adv_fields fields;
    int rc;

    switch(event->type) {
    case BLE_GAP_EVENT_DISC:
        rc = ble_hs_adv_parse_fields(
            &fields, event->disc.data, event->disc.length_data);
        if(rc != 0) {
            return 0;
        }

        /* An advertisment report was received during GAP discovery. */
        print_adv_fields(&fields);

        /* Try to connect to the advertiser if it looks interesting. */
        blecent_connect_if_interesting(&event->disc);
        return 0;

    case BLE_GAP_EVENT_CONNECT:
        /* A new connection was established or a connection attempt failed. */
        if(event->connect.status == 0) {
            /* Connection successfully established. */
            MODLOG_DFLT(INFO, "Connection established ");

            rc = ble_gap_conn_find(event->connect.conn_handle, &desc);
            assert(rc == 0);
            print_conn_desc(&desc);

            /* Remember peer. */
            rc = peer_add(event->connect.conn_handle);
            if(rc != 0) {
                MODLOG_DFLT(ERROR, "Failed to add peer; rc=%d\n", rc);
                return 0;
            }

            /* Perform service discovery */
            rc = peer_disc_all(
                event->connect.conn_handle, blecent_on_disc_complete, NULL);
            if(rc != 0) {
                MODLOG_DFLT(ERROR, "Failed to discover services; rc=%d\n", rc);
                return 0;
            }
        } else {
            /* Connection attempt failed; resume scanning. */
            MODLOG_DFLT(
                ERROR,
                "Error: Connection failed; status=%d\n",
                event->connect.status);
            blecent_scan();
        }

        return 0;

    case BLE_GAP_EVENT_DISCONNECT:
        /* Connection terminated. */
        MODLOG_DFLT(INFO, "disconnect; reason=%d ", event->disconnect.reason);
        print_conn_desc(&event->disconnect.conn);
        MODLOG_DFLT(INFO, "\n");

        /* Forget about peer. */
        peer_delete(event->disconnect.conn.conn_handle);

        /* Resume scanning. */
        blecent_scan();
        return 0;

    case BLE_GAP_EVENT_DISC_COMPLETE:
        MODLOG_DFLT(
            INFO,
            "discovery complete; reason=%d\n",
            event->disc_complete.reason);
        return 0;

    case BLE_GAP_EVENT_ENC_CHANGE:
        /* Encryption has been enabled or disabled for this connection. */
        MODLOG_DFLT(
            INFO,
            "encryption change event; status=%d ",
            event->enc_change.status);
        rc = ble_gap_conn_find(event->enc_change.conn_handle, &desc);
        assert(rc == 0);
        print_conn_desc(&desc);
        return 0;

    case BLE_GAP_EVENT_NOTIFY_RX:
        /* Peer sent us a notification or indication. 
        MODLOG_DFLT(INFO, "received %s; conn_handle=%d attr_handle=%d "
                    "attr_len=%d\n",
                    event->notify_rx.indication ?
                    "indication" :
                    "notification",
                    event->notify_rx.conn_handle,
                    event->notify_rx.attr_handle,
                    OS_MBUF_PKTLEN(event->notify_rx.om));
                    */
        val = (event->notify_rx.om->om_data[0] << 8) |
              event->notify_rx.om->om_data[1];
        MODLOG_DFLT(INFO, "data %u\n", val);
        MODLOG_DFLT(INFO, "attr handle %u\n", event->notify_rx.attr_handle);

        /* Attribute data is contained in event->notify_rx.om. Use
         * `os_mbuf_copydata` to copy the data received in notification mbuf */
        return 0;

    case BLE_GAP_EVENT_MTU:
        MODLOG_DFLT(
            INFO,
            "mtu update event; conn_handle=%d cid=%d mtu=%d\n",
            event->mtu.conn_handle,
            event->mtu.channel_id,
            event->mtu.value);
        return 0;

    case BLE_GAP_EVENT_REPEAT_PAIRING:
        /* We already have a bond with the peer, but it is attempting to
         * establish a new secure link.  This app sacrifices security for
         * convenience: just throw away the old bond and accept the new link.
         */

        /* Delete the old bond. */
        rc = ble_gap_conn_find(event->repeat_pairing.conn_handle, &desc);
        assert(rc == 0);
        ble_store_util_delete_peer(&desc.peer_id_addr);

        /* Return BLE_GAP_REPEAT_PAIRING_RETRY to indicate that the host should
         * continue with the pairing operation.
         */
        return BLE_GAP_REPEAT_PAIRING_RETRY;

    default:
        return 0;
    }
}

static void blecent_on_reset(int reason) {
    MODLOG_DFLT(ERROR, "Resetting state; reason=%d\n", reason);
}

static void blecent_on_sync(void) {
    int rc;

    /* Make sure we have proper identity address set (public preferred) */
    rc = ble_hs_util_ensure_addr(0);
    assert(rc == 0);

#if !CONFIG_EXAMPLE_INIT_DEINIT_LOOP
    /* Begin scanning for a peripheral to connect to. */
    blecent_scan();
#endif
}

void blecent_host_task(void* param) {
    ESP_LOGI(tag, "BLE Host Task Started");
    /* This function will return only when nimble_port_stop() is executed */
    nimble_port_run();

    nimble_port_freertos_deinit();
}

void ble_pult_task_create(uint32_t stack_size, uint32_t prio) {
    //TODO do we need task handler
    ESP_LOGI(tag, "create task %lu | %lu", stack_size, prio);
    xTaskCreate(ble_pult_task, "BLE_Pult_Task", stack_size, NULL, prio, NULL);
}

static void ble_pult_task(void* arg) {
    int rc;
    esp_err_t ret;
    ret = nimble_port_init();
    if(ret != ESP_OK) {
        ESP_LOGE(tag, "Failed to init nimble %d ", ret);
        return;
    }

    /* Configure the host. */
    ble_hs_cfg.reset_cb = blecent_on_reset;
    ble_hs_cfg.sync_cb = blecent_on_sync;
    ble_hs_cfg.store_status_cb = ble_store_util_status_rr;

    /* Initialize data structures to track connected peers. */
    rc = peer_init(MYNEWT_VAL(BLE_MAX_CONNECTIONS), 64, 64, 64);
    assert(rc == 0);

    /* Set the default device name. */
    rc = ble_svc_gap_device_name_set("nimble-blecent");
    assert(rc == 0);

    /* XXX Need to have template for store */
    ble_store_config_init();

    nimble_port_freertos_init(blecent_host_task);
    while(1) {
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}