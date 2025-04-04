# midas-arm

First clone and build moveit2: https://moveit.picknik.ai/main/doc/tutorials/getting_started/getting_started.html 

build Midas_robot_description

```colcon build --packages-select Midas_robot_description```

build moveit2_custom_paths

```colcon build --packages-select moveit2_custom_paths```

run Midas_robot_description demo (will take a moment for robot arm to appear)

```ros2 launch Midas_robot_description demo.launch.py```

run moveit2_custom_paths midas_controller

```ros2 launch moveit2_custom_paths midas_controller.launch.py```