#include "mbed.h"
//#include "mbed_events.h"
#include "rtos.h"
#include "BufferedSerial.h"
#include "Parameters.h"


//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------

Serial pc(SERIAL_TX, SERIAL_RX);
BufferedSerial esp(D1,D0);

DigitalOut myled(LED1);
DigitalOut led2(LED2);

//PwmOut servoPwm(D9);

//EventQueue queue(3 * EVENTS_EVENT_SIZE);
Thread event_queue_thread;


Thread esp_read_thread;
void read_esp();
void check_serial1();

Thread control_and_actuate_thread;
void control_and_actuate();




int main()
{
    esp.baud(115200);
    wait(0.1);
    esp_read_thread.start(control_and_actuate);
    wait(0.1);
    control_and_actuate_thread.start(control_and_actuate);
    wait(0.1);
    wait(0.1);
    wait(1);

    int i = 1;
    while(1) {
        wait(1);
        char tmp = 't';
        pc.printf("Main loop, %d , %c \r\n", i++, tmp);
        esp.printf("test\n");
        myled = !myled;
    }
}

void control_and_actuate()
{
	//servoPwm.period(0.015f);
	//servoPwm.pulsewidth(0.0015f);

	while(1)
	{

	}
}

void read_esp()
{
    while(1)
    {
    	//check_serial1();
    }
}

void check_serial1()
{
	char c;
	static char param[20] = {""};
	static char value[10] = {""};
	static uint8_t value_index = 0;
	static uint8_t param_index = 0;
	static int count = 0;
	static enum State {READ_PARAM,READ_VALUE,SEARCH} state;
	while (esp.readable()) {
		// read the incoming byte:
		c = esp.getc();
		switch (state)
		{
		case READ_PARAM:
			//pc.printf("State read param");
			count++;
			if(c=='='){
				count = 0;
				value[0] = '\0';
				value_index = 0;
				state = READ_VALUE;
			}
			else if(c=='&') {count = 0;param[0] = '\0';}
			else
				{
				param[param_index] = c;
				param_index++;
				if (param_index >= 20)
				{
					error("Param buffer ovf");
					param_index = 0;
					state = SEARCH;
				}
				param[param_index] = '\0';
				}
			break;
		/* Reading value from serial *** */
		case READ_VALUE:
			if(c=='=') {
				value[0] = '\0';
			}
			else if(c=='&'){
				pc.printf("Found param value:");
				pc.printf(param);pc.printf(value);
				pms.try_write(param,value);
			}
			else
			{
				value[value_index++] = c;
				if (param_index >= 20)
				{
					error("Value buffer ovf");
					param_index = 0;
					state = SEARCH;
				}
			value[value_index] = '\0';
			}
			break;

		/*****              Searching for & *************/
		case SEARCH:
			if(c=='&'){
				param[0] = '\0';
				param_index = 0;
				value[0] = '\0';
				value_index = 0;
				state = READ_PARAM;
			}
			break;
		}
		pc.putc(c);
	}
}

