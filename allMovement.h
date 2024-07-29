/*************************************************************************
 * AllMovements.hpp
 *
 **************************************************************************
 */


void reverse(int fd,int speed);
void forward(int fd,int speed);
void rightTurn(int fd,int left_speed,int right_speed);
void leftTurn(int fd,int left_speed,int right_speed);
void rotateClockwise(int fd,int speed);
void rotateCounterclockwise(int fd,int speed);
void stop(int fd);
