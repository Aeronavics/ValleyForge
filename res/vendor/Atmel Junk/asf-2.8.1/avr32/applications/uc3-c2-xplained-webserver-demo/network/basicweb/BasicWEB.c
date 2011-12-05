/**
 * \file
 *
 * \brief Basic Web Serveur for AVR UC3.
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

/*
 * Implements a simplistic WEB server.  Every time a connection is made and
 * data is received a dynamic page that shows the current FreeRTOS.org kernel
 * statistics is generated and returned.  The connection is then closed.
 *
 * This file was adapted from a FreeRTOS lwIP slip demo supplied by a third
 * party.
 */

#if (HTTP_USED == 1)

// Standard includes.
#include <stdio.h>
#include <string.h>
#include "gpio.h" 

#include "conf_eth.h"

// Scheduler includes
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

// Demo includes.
// Demo app includes.
#include "portmacro.h"

// lwIP includes.
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/memp.h"
#include "lwip/stats.h"
#include "netif/loopif.h"

// ethernet includes
#include "ethernet.h"
//! The size of the buffer in which the dynamic WEB page is created.
#define webMAX_PAGE_SIZE	512

//! Standard GET response.
#define webHTTP_OK	"HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n"

//! The port on which we listen.
#define webHTTP_PORT		( 80 )

//! Delay on close error.
#define webSHORT_DELAY		( 10 )

//! Format of the dynamic page that is returned on each connection.
#define webHTML_START \
"<html>\
<head>\
</head>\
<BODY onLoad=\"window.setTimeout(&quot;location.href='index.html'&quot;,1000)\
\" bgcolor=\"#FFFFFF\" text=\"#2477E6\"> \r\nWeb Server Demo"

#define webHTML_END \
"\r\n</pre>\
\r\n</font></BODY>\
</html>"

portCHAR cDynamicPage[ webMAX_PAGE_SIZE ];
portCHAR cPageHits[ 11 ];
portCHAR cPageCAN[ 15];

//! Function to process the current connection
static void prvweb_ParseHTMLRequest( struct netconn *pxNetCon );

#include "uc3c_gif.h"
/*
 *! \brief WEB server main task
 *         check for incoming connection and process it
 *
 *  \param pvParameters   Input. Not Used.
 *
 */
portTASK_FUNCTION( vBasicWEBServer, pvParameters );
portTASK_FUNCTION( vBasicWEBServer, pvParameters )
{
struct netconn *pxHTTPListener, *pxNewConnection;

	// Create a new tcp connection handle
	pxHTTPListener = netconn_new( NETCONN_TCP );
	netconn_bind(pxHTTPListener, NULL, webHTTP_PORT );
	netconn_listen( pxHTTPListener );

	// Loop forever
	for( ;; ){
		// Wait for a first connection.
		pxNewConnection = netconn_accept(pxHTTPListener);

		if(pxNewConnection != NULL)
		{
			prvweb_ParseHTMLRequest(pxNewConnection);
		}
	} 
}

static int html_add_button(char* buf, int len, char* id, char* value) 
{
	return snprintf(buf, len, "<input type=\"submit\" "
	"style=\"height: 50px\" "
	"name=\"%s\" "
	"value=\"%s\"/>&nbsp&nbsp",
	id, value);
}

static void document_index_html(const char** buf, int* len)
{
	static char rsp[1620];
	int pos = 0;

	pos += snprintf(rsp + pos, sizeof(rsp) - pos,
	"HTTP/1.0 200 OK\n"
	"Server: lwIP\n"
	"Content-type: text/html\n\n"
	"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Frameset//EN\" \
         	\"http://www.w3.org/TR/html4/frameset.dtd\">"
	"<html>"
	"<head><title>Web Server Demo on Atmel AT32%s</title>"
	"</head>"
	"</html>"
	"<body bgcolor=\"white\" text=\"black\">"
	"<table width=\"100%%\">"
	"<tr valign=\"top\"><td width=\"80\">"
	"<a href=\"index.html\">"
	"<img src=\"image.gif\" border=\"0\" alt=\"logo\""
	"title=\"logo\"></a>" 
	"</td>"
	"<td width=\"500\">"
	"<h2>Web Server Demo on Atmel AT32%s</h2>"
	"<p>"

	"The web page is served by an Atmel AT32%s MCU. "
	"The LED can be controlled on this webpage. "
	"The web server is running on top of the lwIP TCP/IP stack. "

	"</p><hr><table>",
	"UC3C2512C", "UC3C2512C", "UC3C2512C");          

	pos += snprintf(rsp + pos, sizeof(rsp) - pos,
		"<tr><td><form method=\"get\">"
			"<input type=\"submit\" style=\"height: 50px\" \
				value=\"Refresh\"/>"
					"</form></td></tr>");

	pos += snprintf(rsp + pos, sizeof(rsp) - pos,
		"</table><br>");

	pos += snprintf(rsp + pos, sizeof(rsp) - pos, "<form id=\"form\""
		"name=\"form\" method=\"get\" action=\"index.html\">"
			"<fieldset style=\"width: 300;\">"
				"<legend>LED control</legend>");

	pos += html_add_button(rsp + pos, sizeof(rsp) - pos, "toggle", "ON");
	pos += html_add_button(rsp + pos, sizeof(rsp) - pos, "toggle", "OFF");
	pos += snprintf(rsp + pos, sizeof(rsp) - pos, "</fieldset></form>");

	pos += snprintf(rsp + pos, sizeof(rsp) - pos, "</td>"
		"<td>&nbsp;</td></tr></table></body></html>");

	if (pos >= sizeof rsp) {
			while(true);
	}

	buf[sizeof buf] = '\0';
	*buf = rsp;
	*len = pos;
}

static void query_led_on(const char** buf, int* len)
{
	document_index_html(buf, len);
	// Set Led
	gpio_clr_gpio_pin(LED0_GPIO);
}

static void query_led_off(const char** buf, int* len)
{
	document_index_html(buf, len);
	// Clear Led
	gpio_set_gpio_pin(LED0_GPIO);
}

void document_image_gif(const char** buf, int* len)
{
	*buf = uc3c_gif;
        *len = sizeof(uc3c_gif);
}

/*
 *! \brief parse the incoming request
 *         parse the HTML request and send file
 *
 *  \param pxNetCon   Input. The netconn to use to send and receive data.
 *
 */
char *data;
int len;
static void prvweb_ParseHTMLRequest( struct netconn *pxNetCon )
{
	struct netbuf      *pxRxBuffer;
	portCHAR           *pcRxString;
	unsigned portSHORT usLength;
	// We expect to immediately get data.
	pxRxBuffer = netconn_recv( pxNetCon );

	if( pxRxBuffer != NULL ){
		// Where is the data?
		netbuf_data( pxRxBuffer, ( void * ) &pcRxString, &usLength );
		// Is this a GET?  We don't handle anything else.

		if((NULL != pcRxString) && (!strncmp(pcRxString, "GET", 3))){
			if ((pcRxString[5]=='i')  && (pcRxString[6]=='m') 
				&& (pcRxString[7]=='a') && (pcRxString[8]=='g')
					&& (pcRxString[9]=='e')) {
				document_image_gif((const char**) &data, &len); 
			}
			else if ((pcRxString[23]=='O')&&(pcRxString[24]=='N')){
				query_led_on((const char**) &data,&len);
			}
			else if ((pcRxString[23]=='O') && (pcRxString[24]=='F')
					&& (pcRxString[25]=='F')) {
				query_led_off((const char**) &data,&len);
			}
			else {
				document_index_html((const char**) &data,&len);
			}
			netconn_write( pxNetCon, data, (u16_t) len, 
				NETCONN_COPY );
		}
		netbuf_delete( pxRxBuffer );
	}
	netconn_close( pxNetCon );
	netconn_delete( pxNetCon );
}

#endif

