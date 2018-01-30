/*******************************************************************
 *   _________     _____      _____    ____  _____    ___  ____    *
 *  |_   ___  |  |_   _|     |_   _|  |_   \|_   _|  |_  ||_  _|   *
 *    | |_  \_|    | |         | |      |   \ | |      | |_/ /     *
 *    |  _|        | |   _     | |      | |\ \| |      |  __'.     *
 *   _| |_        _| |__/ |   _| |_    _| |_\   |_    _| |  \ \_   *
 *  |_____|      |________|  |_____|  |_____|\____|  |____||____|  *
 *                                                                 *
 *******************************************************************
 *                                                                 *
 *  flink userspace library lite, subdevice function "watchdog"    *
 *                                                                 *
 *******************************************************************/
 
/** @file wd.c
 *  @brief flink userspace library, subdevice function "watchdog".
 *
 *  Contains the high-level functions for a flink subdevice
 *  which realizes the function "watchdog".
 *
 *  @author Martin Züger
 *  @author Raphael Lauber
 */

#include "flinklib.h"
#include "types.h"

/**
 * @brief Reads the base clock of a watchdog subdevice
 * @param subdev: Subdevice.
 * @param frequency: Contains the base clock in Hz.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_wd_get_baseclock(flink_subdev* subdev, uint32_t* base_clk) {
	
	uint32_t offset;
	
	offset = HEADER_SIZE + SUBHEADER_SIZE;
	
	if(flink_read(subdev, offset, REGISTER_WITH, base_clk) != REGISTER_WITH) {
		return EXIT_ERROR;
	}
	
	return EXIT_SUCCESS;
}

/**
 * @brief Reads the status word of a watchdog subdevice
 * @param subdev: Subdevice.
 * @param status: Contains the status word.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_wd_get_status(flink_subdev* subdev, uint8_t* status){
	
	uint32_t offset;
	
	offset = HEADER_SIZE + SUBHEADER_SIZE + REGISTER_WITH;
	
	if(flink_read_bit(subdev, offset, 0, status)) {
		return EXIT_ERROR;
	}
	
	return EXIT_SUCCESS;
}

/**
 * @brief Presets the watchdog counter
 * @param subdev: Subdevice.
 * @param counter: Desired counter value.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_wd_set_counter(flink_subdev* subdev, uint32_t counter){
	
	uint32_t offset;
	
	offset = HEADER_SIZE + SUBHEADER_SIZE + 2 * REGISTER_WITH;
	
	if(flink_write(subdev, offset, REGISTER_WITH, &counter) != REGISTER_WITH) {
		return EXIT_ERROR;
	}
	
	return EXIT_SUCCESS;
}

/**
 * @brief Starts the watchdog counter
 * @param subdev: Subdevice.
 * @return int: 0 on success, -1 in case of failure.
 */
int flink_wd_arm(flink_subdev* subdev){
	
	uint32_t offset;
	uint8_t arm = 1;

	offset = HEADER_SIZE + SUBHEADER_SIZE + REGISTER_WITH;
	
	if(flink_write_bit(subdev, offset, 1, &arm)) {
		return EXIT_ERROR;
	}
	
	return EXIT_SUCCESS;
}
