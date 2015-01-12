// A structure containing the register definitions for a single USART channel.
typedef struct
{
	volatile uint8_t* UDR;
	volatile uint8_t* UCSRA;
	volatile uint8_t* UCSRB;
	volatile uint8_t* UCSRC;
	volatile uint16_t* UBRR;
} Usart_registers;

 // A structure to contain the IO pin addresses representing the peripheral pins for a single USART channel.
typedef struct
{
	IO_pin_address tx_address;
	IO_pin_address rx_address;
	IO_pin_address xck_address;  // Optional, for peripherals that support synchronous USART
} Usart_pins;

// For internal use in the async comms stuff.
enum Usart_async_mode { ASYNC_BUFFER, ASYNC_STRING };

class Usartspi_imp; // Forward declaration


/**
 * Private, target specific implementation class for public Usart class.
 */
class Usart_imp
{
	friend class Usartspi_imp;

public:

	Usart_imp(Usart_channel channel, Usart_pins pins, Usart_registers registers);
	~Usart_imp(void);

	// Called whenever someone binds to this instance
	void bind(void);

	// Called whenever someone is finished with this instance
	void unbind(void);

	virtual void enable(void);

	virtual void disable(void);

	virtual void flush(void);

	virtual Usart_config_status configure(Usart_setup_mode mode, uint32_t baud_rate, uint8_t data_bits = 8, Usart_parity parity = USART_PARITY_NONE, uint8_t stop_bits = 1);

	virtual bool transmitter_ready(void);

	virtual bool receiver_has_data(void);

	virtual Usart_io_status transmit_byte(uint8_t data);

	virtual Usart_io_status transmit_byte_async(uint8_t data);

	virtual Usart_io_status transmit_buffer(uint8_t* data, size_t size);

	virtual Usart_io_status transmit_buffer_async(uint8_t* data, size_t size, Usart_Transmit_Callback cb_done, void *context);

	virtual Usart_io_status transmit_string(char *string, size_t max_len);

	virtual Usart_io_status transmit_string_async(char *string, size_t max_len, Usart_Transmit_Callback cb_done, void *context);


	virtual int16_t receive_byte(void);

	virtual int16_t receive_byte_async(void);


	virtual Usart_io_status receive_buffer(uint8_t *buffer, size_t size);

	virtual Usart_io_status receive_buffer_async(uint8_t *data, size_t size, Usart_Receive_Callback cb_done, void *context);


	virtual void enable_interrupts(void);

	virtual void disable_interrupts(void);

	virtual Usart_int_status attach_interrupt(Usart_interrupt_type type, Callback callback, void *context);

	virtual Usart_int_status detach_interrupt(Usart_interrupt_type type);

	virtual Usart_error_status get_errors(void);


protected: //// Utility Functions ////

	virtual Usart_config_status set_mode(Usart_setup_mode mode);

	virtual Usart_config_status set_framing(uint8_t data_bits, Usart_parity parity, uint8_t stop_bits);

	virtual Usart_config_status set_baud_rate(uint32_t baud_rate);


#ifdef USE_SPI_USART
	bool mspim_inuse(void);
#endif

public:  //// Asynchronous Interrupt Handling ////

	virtual void set_udrie(bool enabled);

	void isr_receive_byte(void);

	void isr_transmit_complete(void);

	void isr_transmit_ready(void);

	// The TX isr is called whenever the transmitter has finished transmitting,
	// and there is no more data to send.
	Callback tx_isr;
	void *tx_isr_p;
	bool tx_isr_enabled;

	// The RX isr is called whenever something has been received.
	// If an _async() call is active, this is called when it finishes.
	Callback rx_isr;
	void *rx_isr_p;
	bool rx_isr_enabled;

	// State machines used for asynchronous communications
	struct
	{
		bool active;

		uint8_t *buffer;
		size_t size;
		size_t index;

		Usart_async_mode mode;

		Usart_Transmit_Callback cb_done;
		void *cb_p;
	} async_tx;

	struct
	{
		bool active;

		uint8_t *buffer;
		size_t size;
		size_t index;

		Usart_Receive_Callback cb_done;
		void *cb_p;
	} async_rx;


protected:  //// Fields ////

	Usart_setup_mode mode;

	Usart_channel channel;

	Usart_pins pins;

	Usart_registers registers;

protected:

	// Methods

	Usart_imp(void);	// Poisoned.

	Usart_imp(Usart_imp*);	// Poisoned.

//friend class Lin_imp;
};




/**
 * The ATmega64M1/C1 chips can support basic UART through the LIN peripheral.
 * This class overrides the behaviour in Usart_imp to make the LIN
 * peripheral function as a UART.
 *
 * The LIN-UART has restricted functionality, and only supports
 * 8 data bits, odd/even/no parity, and 1 stop bit
 */
class Lin_imp : public Usart_imp
{
public:
	Lin_imp(Usart_channel channel, Usart_pins pins);
	~Lin_imp(void);

	void enable(void);

	void disable(void);

	void flush(void);

	Usart_config_status configure(Usart_setup_mode mode, uint32_t baud_rate, uint8_t data_bits = 8, Usart_parity parity = USART_PARITY_NONE, uint8_t stop_bits = 1);

	bool transmitter_ready(void);

	bool receiver_has_data(void);


	Usart_io_status transmit_byte(uint8_t data);

	Usart_io_status transmit_byte_async(uint8_t data);

	// NOTE: The following functions do not need to be overridden:
	// 	transmit_buffer()  transmit_buffer_async()
	// 	transmit_string()  transmit_string_async()

	int16_t receive_byte(void);

	int16_t receive_byte_async(void);

	// NOTE: The following functions do not need to be overridden:
	// 	receive_buffer()  receive_buffer_async()

	// NOTE: The following functions do not need to be overridden:
	// 	enable_interrupts()  disable_interrupts()
	//  attach_interrupt()  detach_interrupt()

	Usart_error_status get_errors(void);

	Usart_config_status set_mode(Usart_setup_mode mode);

	Usart_config_status set_framing(uint8_t data_bits, Usart_parity parity, uint8_t stop_bits);

	Usart_config_status set_baud_rate(uint32_t baud_rate);

	void set_udrie(bool enabled);

protected:
	Lin_imp(void);
	Lin_imp(Lin_imp*);
};


#ifdef USE_USART0
extern Usart_imp usart0_imp;
#endif

#ifdef USE_USART1
extern Usart_imp usart1_imp;
#endif

#ifdef USE_USART2
extern Usart_imp usart2_imp;
#endif

#ifdef USE_USART3
extern Usart_imp usart3_imp;
#endif

