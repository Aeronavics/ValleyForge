/**
 * \file
 *
 * \brief Ethernet Management for AVR UC3.
 *
 * Copyright (C) 2011 Atmel Corporation. All rights reserved.
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 * Atmel AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */


#include <string.h>

#include "gpio.h"
#include "flashc.h"

// Scheduler include files
#include "FreeRTOS.h"
#include "task.h"

// Demo program include files.
#include "conf_lwip_threads.h"

// ethernet includes
#include "ethernet.h"
#include "conf_eth.h"
#include "macb.h"

#include "displayTask.h"

#if (HTTP_USED == 1)
  #include "BasicWEB.h"
#endif

#if (TFTP_USED == 1)
  #include "BasicTFTP.h"
#endif

#if (SMTP_USED == 1)
  #include "BasicSMTP.h"
#endif

// lwIP includes/
#include "lwip/sys.h"
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/memp.h"
#include <lwip/dhcp.h>
#include <lwip/dns.h>
#include <lwip/netif.h>
#include "lwip/stats.h"
#include "netif/loopif.h"


//_____ M A C R O S ________________________________________________________

//The MAC address in user page
#define MAC_ADDR_OFFSET     0x000001F0
#define MAC_ADDR_ADDRESS    (AVR32_FLASHC_USER_PAGE_ADDRESS + MAC_ADDR_OFFSET)
#define MIN_COMP_MAC_ADDR   ((ETHERNET_CONF_ETHADDR4<<8)|ETHERNET_CONF_ETHADDR5)

//_____ D E F I N I T I O N S ______________________________________________

// global variable containing MAC Config (hw addr, IP, GW, ...)
struct netif MACB_if;

//_____ D E C L A R A T I O N S ____________________________________________

// Initialisation required by lwIP
static void prvlwIPInit( void );

// Initialisation of ethernet interfaces by reading config file
static void prvEthernetConfigureInterface(void * param);


void vStartEthernetTaskLauncher( unsigned portBASE_TYPE uxPriority )
{
	// Spawn the Sentinel task
	xTaskCreate( vStartEthernetTask, ( const signed portCHAR * )"ETHLAUNCH",
		configMINIMAL_STACK_SIZE, NULL, uxPriority, 
			( xTaskHandle * )NULL );
}

/*!
 * \brief create ethernet task, for ethernet management.
 *
 *  \param uxPriority   Input. priority for the task, it should be low
 * 
 */
portTASK_FUNCTION( vStartEthernetTask, pvParameters )
{
	static const gpio_map_t MACB_GPIO_MAP = {
		{EXTPHY_MACB_MDC_PIN,     EXTPHY_MACB_MDC_FUNCTION   },
		{EXTPHY_MACB_MDIO_PIN,    EXTPHY_MACB_MDIO_FUNCTION  },
		{EXTPHY_MACB_RXD_0_PIN,   EXTPHY_MACB_RXD_0_FUNCTION },
		{EXTPHY_MACB_TXD_0_PIN,   EXTPHY_MACB_TXD_0_FUNCTION },
		{EXTPHY_MACB_RXD_1_PIN,   EXTPHY_MACB_RXD_1_FUNCTION },
		{EXTPHY_MACB_TXD_1_PIN,   EXTPHY_MACB_TXD_1_FUNCTION },
		{EXTPHY_MACB_TX_EN_PIN,   EXTPHY_MACB_TX_EN_FUNCTION },
		{EXTPHY_MACB_RX_ER_PIN,   EXTPHY_MACB_RX_ER_FUNCTION },
		{EXTPHY_MACB_RX_DV_PIN,   EXTPHY_MACB_RX_DV_FUNCTION },
		{EXTPHY_MACB_TX_CLK_PIN,  EXTPHY_MACB_TX_CLK_FUNCTION}
	};

	// Assign GPIO to MACB
	gpio_enable_module(MACB_GPIO_MAP, 
		sizeof(MACB_GPIO_MAP) / sizeof(MACB_GPIO_MAP[0]));

	// Setup lwIP.
	prvlwIPInit();

#if (HTTP_USED == 1)
	/*
         * Create the WEB server task.  This uses the lwIP RTOS abstraction 
         * layer
         */
	sys_thread_new( "WEB", vBasicWEBServer, ( void * ) NULL, 
		lwipBASIC_WEB_SERVER_STACK_SIZE, 
                	lwipBASIC_WEB_SERVER_PRIORITY );
#endif

#if (TFTP_USED == 1)
	/*
	 * Create the TFTP server task.  This uses the lwIP RTOS abstraction 
	 * layer
	 */
	sys_thread_new( "TFTP", vBasicTFTPServer, ( void * ) NULL,
		lwipBASIC_TFTP_SERVER_STACK_SIZE, 
			lwipBASIC_TFTP_SERVER_PRIORITY );
#endif

#if (SMTP_USED == 1)
	/*
	 * Create the SMTP Client task.  This uses the lwIP RTOS abstraction 
	 * layer
	 */
	sys_thread_new( "SMTP", vBasicSMTPClient, ( void * ) NULL,
		lwipBASIC_SMTP_CLIENT_STACK_SIZE, 
			lwipBASIC_SMTP_CLIENT_PRIORITY );
#endif
	// Kill this task.
	vTaskDelete(NULL);
}


//! Callback executed when the TCP/IP init is done.
static void tcpip_init_done(void *arg)
{
	sys_sem_t *sem;
	sem = (sys_sem_t *)arg;

	// Set hw and IP parameters, initialize MACB too
	prvEthernetConfigureInterface(NULL);

	// Signal the waiting thread that the TCP/IP init is done.
	sys_sem_signal(*sem);
}

/*!
 *  \brief status callback used to print address given by DHCP 
 */
void status_callback(struct netif *netif)
{ 
  char mess[20];  
  if (netif_is_up(netif)) {	
    strcpy(mess,"IP=");
    strcat(mess,inet_ntoa(*(struct in_addr*)&(netif->ip_addr)));
    sendMessage(mess);
  } else {
    sendMessage("status_callback==DOWN");
  }
}

/*!
 *  \brief start lwIP layer.
 */
static void prvlwIPInit( void )
{
	sys_sem_t sem;

	sem = sys_sem_new(0); // Create a new semaphore.
	tcpip_init(tcpip_init_done, &sem);
	sys_sem_wait(sem);    // Block until the lwIP stack is initialized.
	sys_sem_free(sem);    // Free the semaphore.
}

/*!
 *  \brief set ethernet config
 *  The MAC address should be pre-writen into user page 0x808001f0~0x808001f6;
 *  If the address was not written there, it will be written with the default 
 *  address.
 */
static void prvEthernetConfigureInterface(void * param)
{
	struct ip_addr    xIpAddr, xNetMask, xGateway;
	extern err_t      ethernetif_init( struct netif *netif );
	unsigned portCHAR MacAddress[6];
	
	bool MAC_compatible = true;
	U32 mac_address_temp0,mac_address_temp1;
	
	//get the MAC address from user page
	mac_address_temp0 =  *(U32*)(MAC_ADDR_ADDRESS); 
	mac_address_temp1 =  *(U32*)(MAC_ADDR_ADDRESS+4); 
	      
	//check if the first 4 bytes address are compatible with ATMEL range
	if((MSB0D(mac_address_temp0)!=ETHERNET_CONF_ETHADDR0)
		||(MSB1D(mac_address_temp0) != ETHERNET_CONF_ETHADDR1)
			||(MSB2D(mac_address_temp0) != ETHERNET_CONF_ETHADDR2)
			||(MSB3D(mac_address_temp0) != ETHERNET_CONF_ETHADDR3)){
		
		MAC_compatible = false;
	} else { //check the last 2 bytes address
		if (MSH(mac_address_temp1) < MIN_COMP_MAC_ADDR) {
			MAC_compatible = false;
		}
	}
	
	// use default MAC address if not compatible
	if (MAC_compatible == false) {		
		MacAddress[0] = ETHERNET_CONF_ETHADDR0;
		MacAddress[1] = ETHERNET_CONF_ETHADDR1;
		MacAddress[2] = ETHERNET_CONF_ETHADDR2;
		MacAddress[3] = ETHERNET_CONF_ETHADDR3;               
		MacAddress[4] = ETHERNET_CONF_ETHADDR4;
		MacAddress[5] = ETHERNET_CONF_ETHADDR5;
		//write into user page
		flashc_memcpy((void *)MAC_ADDR_ADDRESS, 
			&MacAddress[0], sizeof(MacAddress),   true);		
	} else {
		//use the address from user page
	        MacAddress[0] = MSB0D(mac_address_temp0);
	        MacAddress[1] = MSB1D(mac_address_temp0);
	        MacAddress[2] = MSB2D(mac_address_temp0);
	        MacAddress[3] = MSB3D(mac_address_temp0);
	        MacAddress[4] = MSB0D(mac_address_temp1);
	        MacAddress[5] = MSB1D(mac_address_temp1);  
        }

	// pass the MAC address to MACB module
	vMACBSetMACAddress( MacAddress );

  xIpAddr.addr  = 0;
  xNetMask.addr = 0;
  xNetMask.addr = 0;
  
  /* add data to netif */
  netif_add( &MACB_if, &xIpAddr, &xNetMask, &xGateway, NULL, ethernetif_init, tcpip_input );

	// make it the default interface
	netif_set_default( &MACB_if );

  /* Setup callback function for netif status change */
  netif_set_status_callback(&MACB_if, status_callback);

  /* bring it up */
  dhcp_start( &MACB_if );  
  sendMessage("LwIP: DHCP Started");

}
