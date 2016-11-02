#include "unican.h"
#include "state_machine.h"
#include "telemetry.h"
#include "obc_setup.h"

//TODO:Check all this terrible english comments

/*
This event occures when valid unican message received
it's calls from within can_receive_message () so if
can_receive_message () called in interrupt handler
you will not want to do a lot of work here
*/
void unican_RX_event (uint16 msg_id, uint16 length)
{
  /* User code */
	unican_take_message();
	//diag_printf("Received unican message Id = %d; Length = %d\n",msg_id,length);
  /*end of user code*/
}

/*
This function should perform required software
reaction to unican message received from another
device.
*/
void unican_RX_message (unican_message* msg)
{
  /* User code */

	switch (msg->unican_msg_id)
	{
		case UNICAN_RATESENSOR_TELEMETRY_X:
		{
			//diag_printf("UNICAN_RATESENSOR_TELEMETRY_X\n");
			ratesensor_data data;
			data.temp = msg->data[5];
			data.val = *((float*)(&(msg->data[0])))+ratesensor_get_offset(0);
			add_ratesensor_data (&data, 0);
		} break;
		case UNICAN_RATESENSOR_TELEMETRY_Y:
		{
			//diag_printf("UNICAN_RATESENSOR_TELEMETRY_Y\n");
			ratesensor_data data;
			data.temp = msg->data[5];
			data.val = *((float*)(&(msg->data[0])))+ratesensor_get_offset(1);
			add_ratesensor_data (&data, 1);
		} break;
		case UNICAN_RATESENSOR_TELEMETRY_Z:
		{
			//diag_printf("UNICAN_RATESENSOR_TELEMETRY_Z\n");
			ratesensor_data data;
			data.temp = msg->data[5];
			data.val = *((float*)(&(msg->data[0])))+ratesensor_get_offset(2);
			add_ratesensor_data (&data, 2);
		} break;


		case UNICAN_MAGSENSOR_TELEMETRY_X:
		{
			//diag_printf("UNICAN_MAGSENSOR_TELEMETRY_X\n");
			magsensor_data data;
			data.temp = msg->data[5];
			data.val = *((float*)(&(msg->data[0])))+magsensor_get_offset(0);
			add_magsensor_data (&data, 0);
		} break;
		case UNICAN_MAGSENSOR_TELEMETRY_Y:
		{
			//diag_printf("UNICAN_MAGSENSOR_TELEMETRY_Y\n");
			magsensor_data data;
			data.temp = msg->data[5];
			data.val = *((float*)(&(msg->data[0])))+magsensor_get_offset(1);
			add_magsensor_data (&data, 1);
		} break;
		case UNICAN_MAGSENSOR_TELEMETRY_Z:
		{
			//diag_printf("UNICAN_MAGSENSOR_TELEMETRY_Z\n");
			magsensor_data data;
			data.temp = msg->data[5];
			data.val = *((float*)(&(msg->data[0])))+magsensor_get_offset(2);
			add_magsensor_data (&data, 2);
		} break;


		case UNICAN_MACHINE_SWITCH_TO_STATE_IDLE:
		{
			//diag_printf("Switch to state IDLE\n");
			SM_machine_request_state(SM_STATE_IDLE);
		} break;
		case UNICAN_MACHINE_SWITCH_TO_STATE_1:
		{
			//diag_printf("Switch to state 1\n");
			SM_machine_request_state(SM_STATE_BDot);
		} break;
		case UNICAN_MACHINE_SWITCH_TO_STATE_2:
		{
			//diag_printf("Switch to state 2\n");
			SM_machine_request_state(SM_STATE_Triad);
		} break;

		case UNICAN_CONFIG_SET_RATES_OFFSET_X:
		{
			ratesensor_set_offset (0,*(float*)(&(msg->data[0])) );
		} break;
		case UNICAN_CONFIG_SET_RATES_OFFSET_Y:
		{
			ratesensor_set_offset (1,*(float*)(&(msg->data[0])) );
		} break;
		case UNICAN_CONFIG_SET_RATES_OFFSET_Z:
		{
			ratesensor_set_offset (2,*(float*)(&(msg->data[0])) );
		} break;

		case UNICAN_CONFIG_SET_MAG_OFFSET_X:
		{
			magsensor_set_offset (0,*(float*)(&(msg->data[0])) );
		} break;
		case UNICAN_CONFIG_SET_MAG_OFFSET_Y:
		{
			magsensor_set_offset (1,*(float*)(&(msg->data[0])) );
		} break;
		case UNICAN_CONFIG_SET_MAG_OFFSET_Z:
		{
			magsensor_set_offset (2,*(float*)(&(msg->data[0])) );
		} break;


		case UNICAN_WHEEL_SPEED:
		{
			//diag_printf("UNICAN_WHEEL_SPEED\n");
			wheel_speed_data data;
			data.val = *((float*)(&(msg->data[0])));
			if (msg->unican_address_from == 0x0A)
				add_wheel_speed_data (&data, 0);
			if (msg->unican_address_from == 0x0B)
				add_wheel_speed_data (&data, 1);
			if (msg->unican_address_from == 0x0C)
				add_wheel_speed_data (&data, 2);
		} break;

		case UNICAN_WHEEL_TORQUE:
		{

		} break;


		default:
		{

		} break;
	}

  /*end of user code*/
}

/*
This function should perform required software
reaction to errors in unican
*/
void unican_error (uint16 errcode)
{
  
  /* User code */

  /*end of user code*/
}

