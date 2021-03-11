/* main.c - Application main entry point */

/*
 * Copyright (c) 2019 Aaron Tsui <aaron.tsui@outlook.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/printk.h>
#include <sys/byteorder.h>
#include <zephyr.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>

#include "Arduino.h"
#include "thermo.h"
#include "maxik.h"

#define LED_GREEN (6)
#define LED_RED (8)
#define LED_BLUE (12)

struct bt_conn *default_conn;

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL,
				  BT_UUID_16_ENCODE(BT_UUID_TEMPERATURE_VAL)),
};

static void connected(struct bt_conn *conn, uint8_t err)
{
	if (err)
	{
		printk("Connection failed (err 0x%02x)\n", err);
	}
	else
	{
		default_conn = bt_conn_ref(conn);
		printk("Connected\n");

		digitalWrite(LED_GREEN, HIGH);
	}
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("Disconnected (reason 0x%02x)\n", reason);

	if (default_conn)
	{
		bt_conn_unref(default_conn);
		default_conn = NULL;
	}

	digitalWrite(LED_GREEN, LOW);
}

static struct bt_conn_cb conn_callbacks = {
	.connected = connected,
	.disconnected = disconnected,
};

static void bt_ready(void)
{
	int err;

	printk("Bluetooth initialized\n");

	err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err)
	{
		printk("Advertising failed to start (err %d)\n", err);
		return;
	}

	printk("Advertising successfully started\n");
}

static void bt_init(void)
{

	int err;

	err = bt_enable(NULL);
	if (err)
	{
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	bt_ready();

	bt_conn_cb_register(&conn_callbacks);
}

void main(void)
{

	pinMode(LED_BLUE, OUTPUT);
	pinMode(LED_GREEN, OUTPUT);

	digitalWrite(LED_BLUE, HIGH);
	digitalWrite(LED_GREEN, LOW);

	maxik_init();
	bt_init();

	// while (1)
	// {
	// 	update_temperature();
	// }

	while (1)
	{

		if (default_conn)
		{
			if (!check_temperature())
			{
				k_sleep(K_SECONDS(1));
			}
		}
		else
		{

			k_sleep(K_SECONDS(1));
		}
	}
}
