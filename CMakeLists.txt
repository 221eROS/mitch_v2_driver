cmake_minimum_required(VERSION 3.0.2)
project(mitch_v2_driver)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  roslib
  sensor_msgs
  std_msgs
  tf
  message_generation
)

#add_message_files(FILES
#		  CommandList.msg
#		  Transmission.msg
#		  RosLog.msg
#	         )

add_service_files(FILES
#		  RawDataStreaming.srv
		  Battery.srv
		  StopTransmission.srv
		  Shutdown.srv
		  Disconnect.srv
		  )

generate_messages(DEPENDENCIES
					std_msgs
#					geometry_msgs
                  )

find_package(lib221e CONFIG REQUIRED)
include_directories(${lib221e_INCLUDE_DIRS})
message(status ${lib221e_FOUND})
message(status ${lib221e_INCLUDE_DIRS})


find_library(MITCH_V2_LIB NAMES MitchV2 PATHS ${lib221e_INCLUDE_DIRS})
message(STATUS ${MITCH_V2_LIB})

find_library(SERIAL_LIB NAMES Connection PATHS ${lib221e_INCLUDE_DIRS})
message(STATUS ${SERIAL_LIB})

find_package(Boost REQUIRED COMPONENTS date_time)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

catkin_package(CATKIN_DEPENDS
              roscpp 
			  message_runtime
			  std_msgs
			  )

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${lib221e_INCLUDE_DIRS}
)

set(SOURCES src/internal/MitchV2_SerialConnection.cpp
	    src/internal/MitchV2_Request.cpp
    )

add_executable(mitch_v2_node "src/mitch_v2.cpp" ${SOURCES})
add_dependencies(mitch_v2_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(mitch_v2_node ${catkin_LIBRARIES} ${MITCH_V2_LIB} ${SERIAL_LIB} ${Boost_LIBRARIES}) 

add_executable(mitch_v2_stop_transmission "src/stop_transmission.cpp" ${SOURCES})
add_dependencies(mitch_v2_stop_transmission ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(mitch_v2_stop_transmission ${catkin_LIBRARIES} ${MITCH_V2_LIB} ${SERIAL_LIB} ${Boost_LIBRARIES}) 

add_executable(mitch_v2_shutdown "src/shutdown.cpp" ${SOURCES})
add_dependencies(mitch_v2_shutdown ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(mitch_v2_shutdown ${catkin_LIBRARIES} ${MITCH_V2_LIB} ${SERIAL_LIB} ${Boost_LIBRARIES}) 

add_executable(battery "src/battery.cpp" ${SOURCES})
add_dependencies(battery ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(battery ${catkin_LIBRARIES} ${MITCH_V2_LIB} ${SERIAL_LIB} ${Boost_LIBRARIES}) 

#add_executable(start_transmission "src/start_transmission.cpp" ${SOURCES})
#add_dependencies(start_transmission ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(start_transmission ${catkin_LIBRARIES} ${MUSE_LIB} ${SERIAL_LIB} ${Boost_LIBRARIES}) 

#add_executable(raw_data_subscriber "src/raw_data_subscriber.cpp" ${SOURCES})
#add_dependencies(raw_data_subscriber ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(raw_data_subscriber ${catkin_LIBRARIES} ${MUSE_LIB} ${SERIAL_LIB} ${Boost_LIBRARIES}) 