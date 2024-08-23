/*************************************************************************
 * AllMovements.hpp
 *
 **************************************************************************
 */


extern void reverse(int fd,int speed);
extern void forward(int fd,int speed);
extern void rightTurn(int fd,int left_speed,int right_speed);
extern void leftTurn(int fd,int left_speed,int right_speed);
extern void rotateClockwise(int fd,int speed);
extern void rotateCounterclockwise(int fd,int speed);
extern void stop(int fd);
