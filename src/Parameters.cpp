/*
 * Parameters.cpp
 *
 *  Created on: 28 jan. 2017
 *      Author: tgtob
 */


#include <Parameters.h>

Parameters::Parameters() {
	// TODO Auto-generated constructor stub

}

Parameters pms;

int Parameters::m_turn = 0;
int Parameters::m_speed = 1000;
bool Parameters::m_drive = 0;
int Parameters::m_client_mode = 0;
#define GEN_INT_COUNT 5
int Parameters::m_genInt[GEN_INT_COUNT] = {};
const char* Parameters::m_parameter_names[N_P] {"turn","speed","drive","c_mode"};

bool Parameters::try_write(char* key, char* value)
{
	PARAMETER_INDEX i = find_index(key);
	switch (i)
	{
	case TURN_P:
		m_turn = atoi(value);
		return true;
	case SPEED_P:
		m_speed = atoi(value);
		break;
	case DRIVE_P:
		m_drive = (bool) atoi(value);
		break;
	case CLIENT_MODE_P:
				m_client_mode = atoi(value);
		break;

	case N_P:
		return false;
	default:
		return false;
	}

	return false;
}

bool Parameters::try_write_gen_int(int index,int value)
{
	if(index<GEN_INT_COUNT)
	{
		m_genInt[index] = value;
		return true;
	}
	return false;
}

int Parameters::getGenInt(int index)
{
	int tmp;
	if(index<GEN_INT_COUNT)
	{
		tmp = m_genInt[index];
	}
	else tmp  = -1;

	return tmp;
}

Parameters::PARAMETER_INDEX Parameters::find_index(char * str)
{
	for(int i=0 ; i<int(N_P) ; ++i)
	{
		if(strcmp(str,m_parameter_names[i]))
		{
			return static_cast<PARAMETER_INDEX>(i);
		}
	}
	return N_P;
}


Parameters::~Parameters() {
	// TODO Auto-generated destructor stub
}

