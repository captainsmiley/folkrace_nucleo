/*
 * Parameters.h
 *
 *  Created on: 28 jan. 2017
 *      Author: tgtob
 */

#ifndef SRC_PARAMETERS_H_
#define SRC_PARAMETERS_H_

#include "mbed.h"

class Parameters {
public:
	Parameters();
	bool try_write(char*  key, char* value);
	bool try_write_gen_int(int index,int value);
	virtual ~Parameters();

	/* **********  read functions ******** */
	int getGenInt(int index);
	int getTurn() {int tmp;tmp = m_turn;return tmp;}
	int getSpeed() {int tmp;tmp = m_speed;return tmp;}
	bool getDrive() {bool tmp;tmp = m_drive;return tmp;}
	enum ClientMode {OFFLINE,TURN_AND_DRIVE,TURN,DRIVE};
	ClientMode getClientMode() {ClientMode tmp;tmp = static_cast<ClientMode>(m_speed);return tmp;}

	/* ********** write functions ********* */
	void setClientMode(ClientMode m ) {m_client_mode = m;}
	void setTurn(int t ) {m_turn = t;}
	void setSpeed(int s ) {m_speed = s;}

private:
	enum PARAMETER_INDEX {TURN_P,SPEED_P,DRIVE_P,CLIENT_MODE_P,N_P};
	PARAMETER_INDEX find_index(char * str);
	static const char* m_parameter_names[]; // = {"turn","speed","drive"} const;
	static int m_turn;
	static int m_speed;
	static bool m_drive;
	static int m_client_mode;
	static int m_genInt[];

};

extern Parameters pms;

#endif /* SRC_PARAMETERS_H_ */
