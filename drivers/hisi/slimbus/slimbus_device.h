/*
 *	slimbus is a kernel driver which is used to manager SLIMbus devices
 *	Copyright (C) 2014	Hisilicon

 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.

 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __SLIMBUS_DEVICE_H__
#define __SLIMBUS_DEVICE_H__

#include "slimbus_types.h"
#include "slimbus.h"

/*
 * interface of slimbus client device
 */
typedef struct slimbus_device {

	/*
	 * initialize client device if needed
	 * @dev, pointer to slimbus device instance
	 *
	 * return 0 if read successful, otherwise, read failed
	 */
	int (*init)(struct slimbus_device *dev);

	/*
	 * set 8k/16k params for voice up/down
	 * @dev, pointer to slimbus device instance
	 * @track_type,  track type
	 * @params, pcm parameters
	 *
	 * return 0 if read successful, otherwise, read failed
	 */
	int (*param_set)(
				struct slimbus_device *dev,
				slimbus_track_type_t   track_type,
				slimbus_track_param_t *params);

	/*
	 * read element value via byte address (see specification for more details
	 * about difference between byte address and element address)
	 * @dev, pointer to slimbus device instance
	 * @byte_address, byte address of element
	 * @slice_size, see slimbus_slice_size_t
	 * @value, pre-allocated memory, contains read element value
	 *
	 * return 0 if read successful, otherwise, read failed
	 */
	int (*element_read)(
				struct slimbus_device  *dev,
				uint32_t				byte_address,
				slimbus_slice_size_t	slice_size,
				void				   *value);

	/*
	 * write element value via byte address (see specification for more details
	 * about difference between byte address and element address)
	 * @dev, pointer to slimbus device instance
	 * @byte_address, byte address of element
	 * @slice_size, see slimbus_slice_size_t
	 * @value, values to be writtern
	 *
	 * return 0 if write successful, otherwise, write failed
	 */
	int (*element_write)(
				struct slimbus_device  *dev,
				uint32_t				byte_address,
				slimbus_slice_size_t	slice_size,
				void				   *value);

	/*
	 * setup channel, this step should be done by sending CONNECT_SOURCE,
	 * CONNECT_SINK, NEXT_DEFINE_CHANNEL, NEXT_DEFINE_CONTENT messages
	 * @dev, pointer to slimbus device instance
	 * @track_type,  track type
	 * @params, pcm parameters
	 *
	 * return 0 if successful, otherwise, failed
	 */
	int (*track_configure)(
				struct slimbus_device	   *dev,
				slimbus_track_type_t	   track_type,
				slimbus_track_param_t	   *params);

	/*
	 * activate channel, this step should be done by sending
	 * NEXT_ACTIVATE_CHANNEL message
	 * @dev, pointer to slimbus device instance
	 * @track_type,  track type
	 *
	 * return 0 if successful, otherwise, failed
	 */
	int (*track_activate)(
				struct slimbus_device	   *dev,
				slimbus_track_type_t	   track_type);

	/*
	 * de-activate channel, this step should be done by sending
	 * NEXT_DEACTIVATE_CHANNEL message
	 * @dev, pointer to slimbus device instance
	 * @track_type,  track type
	 *
	 * return 0 if successful, otherwise, failed
	 */
	int (*track_deactivate)(
				struct slimbus_device	   *dev,
				slimbus_track_type_t	   track_type);


	/*
	 * remove channel, this step should be done by sending
	 * NEXT_REMOVE_CHANNEL message
	 * @dev, pointer to slimbus device instance
	 * @track_type,  track type
	 *
	 * return 0 if successful, otherwise, failed
	 */
	int (*track_remove)(
				struct slimbus_device	   *dev,
				slimbus_track_type_t	   track_type);
	/*
	 * switch framer, this step should be done by sending
	 * NEXT_ACTIVE_FRAMER message
	 * @dev_type, pointer to slimbus device
	 * @bus_config,  slimbus configuration param
	 *
	 * return 0 if successful, otherwise, failed
	 */
	int (*switch_framer)(
				slimbus_device_type_t	framer_type,
				slimbus_bus_config_t   *bus_config);

	/*
	 * pause clock, this step should be done by sending
	 * NEXT_PAUSE_CLOCK message
	 * @newrestarttime restart time control flag.
	 *
	 * return 0 if successful, otherwise, failed
	 */
	int (*pause_clock) (
				slimbus_restart_time_t newrestarttime);

	/* root frequency */
	slimbus_rf_type_t					rf;
	int 								slimbusclk_drv;
	int 								slimbusdata_drv;

}slimbus_device_t;


#endif /* __SLIMBUS_DEVICE_H__ */

