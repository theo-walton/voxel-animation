# VoxelEngine

Renders animated voxel objects from infomation in a file.

each voxel object is made of one or more voxel chunks, each with its own animation.

An animation is defined as a matrix (that is applied to the voxel object) and a time that this transformation should occur in each cycle. Each frame the animation matrices are linearly interpolated to make sure the transition is smooth.

see the main.cpp for the basic process of drawing a voxObject

![alt text](https://raw.githubusercontent.com/theo-walton/VoxelEngine/master/images/voxel_moving_6.gif)
