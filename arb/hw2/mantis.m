mantis = Brick('ioType','instrbt','btDevice','EV3','btChannel',1);
left_motor = Device.MotorA;
right_motor = Device.MotorD;
sonic_motor = Device.MotorB;
sonic = Device.Port3;
gyro = Device.Port1;
touch = Device.Port4;

PAUSE_DURATION = 0.05;

while (mantis.inputReadSI(0, touch, Device.Pushed) ~= 1)
    go_straight(mantis, left_motor, right_motor, 300, -30, PAUSE_DURATION, touch);
end

mantis.outputStop(0, left_motor, Device.Brake);
mantis.outputStop(0, right_motor, Device.Brake);
