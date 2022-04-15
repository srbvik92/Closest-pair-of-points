# Closest-pair-of-points

This program calculates closest pair of points from given set of 2d points, and generates a simple ppm image highlighting the pair of points.

The big thing is that the program runs with O(n log(n)) time complexity. It uses merge sort to sort the points in x and y coordinates, and then breaks it into subarray, which takes O(n) time. So total running time is O(n log(n)) time.
![hide](https://user-images.githubusercontent.com/49802041/163526895-f1391b11-ec82-4380-9df2-80fc7c3297ae.png)
